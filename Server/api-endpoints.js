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
                new EntitySchema(require("./DatabaseTables/SensorData")),
                new EntitySchema(require("./DatabaseTables/UserData"))
            ]
        }).then(function (connection) {
            dbConnection = connection;
            console.log("Connection to database established.");

            var UserDataRepository = dbConnection.getRepository("UserData");

            UserDataRepository.findOne({
                where: {
                    role: "admin",
                }
            }).then(function (user) {
                if (!user) {
                    console.log("No admin account exists, adding one with default password: admin");

                    const UserData_Admin = {
                        username: "admin",
                        password: "admin",
                        apikey: "the-admin-super-secret-api-key",
                        role: "admin"
                    };

                    var UserDataRepository = dbConnection.getRepository("UserData");
                    UserDataRepository.save(UserData_Admin)
                        .then(function (savedPost) {
                            console.log("Post has been saved: ", savedPost);
                        });

                }
            });

        }).catch(function (error) {
            console.log("Error: ", error);
        });

        const BearerStrategy = require('passport-http-bearer').Strategy;
        const LocalStrategy = require('passport-local');

        const API_USER = {
            id: -1,
            username: "api-anonymous-user",
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

            passport.use(new LocalStrategy(function verify(username, password, cb) {

                var UserDataRepository = dbConnection.getRepository("UserData");

                // TODO : Use cryptography for passwords
                UserDataRepository.findOne({
                    where: {
                        username: username,
                        password: password
                    }
                }).then(function (user) {
                    if (!user) {
                        console.log("User login failed");
                        return cb(null, false, {message: 'Incorrect username or password.'});
                    } else {
                        console.log("User login successful");
                        return cb(null, user);
                    }
                });
            }));


            passport.serializeUser(function (user, done) {
                done(null, user);
            });

            passport.deserializeUser(function (user, done) {
                done(null, user);
            });

            /*app.get('/', function (req, res) {
                res.send("If you see this, the game server for Open MC is online.");
            });*/

            app.get('/', function (req, res) {
                const isAuthenticated = !!req.user;
                if (isAuthenticated) {
                    console.log(`User is authenticated, session is ${req.session.id}`);
                } else {
                    console.log("Unknown user");
                }
                res.sendFile(isAuthenticated ? "dashboard.html" : "login.html", {root: __dirname});
            });

            app.get('/manageusers', function (req, res) {
                const isAuthenticated = !!req.user;
                if(!isAuthenticated)
                {
                    console.log("Unknown user");
                    res.sendFile("login.html", {root: __dirname});
                    return;
                }

                if(req.user.role === "admin")
                {
                    res.sendFile("manageusers.html", {root: __dirname});
                    return;
                }

                res.sendFile("accessdenied.html", {root: __dirname});
            });

            app.get('/manageaccount', function (req, res) {
                const isAuthenticated = !!req.user;
                if(!isAuthenticated)
                {
                    console.log("Unknown user");
                    res.sendFile("login.html", {root: __dirname});
                    return;
                }

                res.sendFile("manageaccount.html", {root: __dirname});
            });

            app.post("/addmoderator", (req, res) => {
                const isAuthenticated = !!req.user;
                if(!isAuthenticated)
                {
                    console.log("Unknown user");
                    res.sendFile("login.html", {root: __dirname});
                    return;
                }

                if(req.user.role !== "admin")
                {
                    res.sendFile("accessdenied.html", {root: __dirname});
                    return;
                }

                const NewUserData= {
                    username: req.body.username,
                    password: req.body.password,
                    apikey: req.body.apikey,
                    role: req.body.role
                };

                var UserDataRepository = dbConnection.getRepository("UserData");
                UserDataRepository.save(NewUserData)
                    .then(function (savedPost) {
                        console.log("Post has been saved: ", savedPost);
                    });

                res.redirect("/manageusers");
            });

            app.get('/login', function (req, res) {
                res.sendFile(__dirname + '/login.html');
            });

            app.post("/logout", (req, res) => {
                console.log(`Logout ${req.session.id}`);
                req.logout();
                res.cookie("connect.sid", "", { expires: new Date() });
                res.redirect("/");
            });

            app.post('/login/password',
                passport.authenticate('local', {failureRedirect: '/login', failureMessage: true}),
                function (req, res) {
                    res.redirect('/');
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
                    SensorDataRepository.SensorDataRepository.save(SensorData)
                        .then(function (savedPost) {
                            console.log("Post has been saved: ", savedPost);
                        });
                }

                res.send("SUCCESS");
                gameLogic.updateGameEnvironment(req.body, io);
            });

        }

    }()
)
;