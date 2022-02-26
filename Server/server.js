const io = require('socket.io')();

io.on('connection', client => {
    client.on('position', data => {

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

io.listen(314);

