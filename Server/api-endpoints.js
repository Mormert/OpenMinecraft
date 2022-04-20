// Back-end API for Open MC

(function () {

    const typeorm = require("typeorm");
    const EntitySchema = typeorm.EntitySchema;

    let dbConnection = null;

    typeorm.createConnection({
        type: "sqlite",
        database: "db.sqlite",
        logging: true,
        synchronize: true,
        entities: [
            new EntitySchema(require("./DatabaseTables/SensorData"))
        ]
    }).then(function (connection) {
        dbConnection = connection;
        console.log("Connection to database established.");
    }).catch(function (error) {
        console.log("Error: ", error);
    });

    const BearerStrategy = require('passport-http-bearer').Strategy;

    const API_USER = {
        id: 1,
        username: "api-user",
    };

    module.exports.startApiEndpoints = function (io, app, passport, gameLogic) {

        passport.use(new BearerStrategy(
            function (token, cb) {
                if (token === "super-secret-token") {
                    return cb(null, API_USER);
                } else {
                    return cb(null, false);
                }
            }));

        app.get('/', function (req, res) {
            res.send("If you see this, the game server for Open MC is online.");
        });

        app.post('/env', passport.authenticate("bearer", {session: false}), function (req, res) {

            if (dbConnection !== null) {
                const SensorData = {
                    time: Math.floor(+new Date() / 1000),
                    humidity: req.body.humidity,
                    temperature: req.body.temperature,
                    brightness: req.body.brightness
                };

                var SensorDataRepository = dbConnection.getRepository("SensorData");
                SensorDataRepository.save(SensorData)
                    .then(function (savedPost) {
                        console.log("Post has been saved: ", savedPost);
                    });
            }

            res.send("SUCCESS");
            gameLogic.updateGameEnvironment(req.body, io);
        });

    }

}());