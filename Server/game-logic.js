// Real time multiplayer logic for Open MC

(function () {

    // Store all placed blocks, sent to new players joining the server
    const placed_blocks = new Map();

    module.exports.updateGameEnvironment = function (data, io) {
        const humidity = data.humidity;
        const brightness = data.brightness;

        data = humidity + '\n' + brightness;

        io.emit("environment_update", data)
    }

    module.exports.startGameLogic = function (io) {


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
    }

}());