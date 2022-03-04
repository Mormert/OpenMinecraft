// Game server for running Open Minecraft

const port = process.env.PORT || 314;

const express = require('express');
const app = express();

const httpServer = require("http").createServer(app);

const io = require("socket.io")(httpServer, {
    cors: {
        origin: "http://localhost/", // Set to where the webpage build resides.
        methods: ["GET", "POST"],
        credentials:true
    }
});

app.get('/', function(req, res) {
    res.send("If you see this, the game server for Open MC is online.");
});

httpServer.listen(port);
console.log("Server started on port: " + port);

io.on('connection', client => {
    client.on('position', data => {

        console.log(data);

        // Sent to all players except sender
        client.broadcast.emit("position", data);
    });

    client.on('block_update', data => {
        // Sent to all players except sender
        client.broadcast.emit("block_update", data);
    });

    client.on('disconnect', () => {
        console.log("disconnected");
    });

});