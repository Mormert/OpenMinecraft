// Game server for running Open Minecraft

const port = process.env.PORT || 314;

const express = require('express');
const app = express();

const httpServer = require("http").createServer(app);

const io = require("socket.io")(httpServer, {
    cors: {
        origin: "http://localhost/", // Set to where the webpage build resides.
        methods: ["GET", "POST"],
        credentials: true
    }
});

app.get('/', function (req, res) {
    res.send("If you see this, the game server for Open MC is online.");
});

httpServer.listen(port);
console.log("Server started on port: " + port);

// Store all placed blocks, sent to new players joining the server
const placed_blocks = new Map();

io.on('connection', client => {

    console.log(client.id + " connected.");

    client.on('position', data => {

        // Add the client ID as the first data parameter
        data = client.id + '\n' + data;

        // Sent to all players except sender
        client.broadcast.emit("position", data);
    });

    client.on('block_update', data => {

        splitData = data.split(/\r?\n/);
        posX = splitData[1];
        posY = splitData[2];
        posZ = splitData[3];

        // blockPos is used as a hash
        var blockPos = "" + posX + "," + posY + "," + posZ;

        placed_blocks.set(blockPos, data);

        // Sent to all players except sender
        client.broadcast.emit("block_update", data);
    });

    client.on('disconnect', () => {
        console.log(client.id + " disconnected.");

        // Sent to all players except sender
        client.broadcast.emit("player_disconnected", client.id);
    });

    // Send how the world looks like to new players
    // TODO: Send batched
    placed_blocks.forEach((value, key) => {
        console.log(value);
        client.emit('block_update', value);
    });

});