// Back-end API for Open MC

(function () {

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
            res.send("SUCCESS");
            gameLogic.updateGameEnvironment(req.body, io);
        });

    }

}());