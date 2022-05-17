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

        function LoginReqGuard(req, res) {
            const isAuthenticated = !!req.user;
            if (!isAuthenticated) {
                console.log("Unknown user");
                res.render("login", {loginsuccess: "Please sign in"});
                return false;
            }
            return true;
        }

        function AdminReqGuard(req, res) {
            if (req.user.role !== "admin") {
                res.render("accessdenied");
                return false;
            }
            return true;
        }

        const BearerStrategy = require('passport-http-bearer').Strategy;
        const LocalStrategy = require('passport-local');

        const API_USER = {
            id: -1,
            username: "api-anonymous-user",
        };

        module.exports.startApiEndpoints = function (io, app, passport, gameLogic) {

            passport.use(new BearerStrategy(
                function (token, cb) {

                    var UserDataRepository = dbConnection.getRepository("UserData");

                    UserDataRepository.findOne({
                        where: {
                            apikey: token
                        }
                    }).then(function (user) {
                        if (!user) {
                            console.log("token failed!");
                            return cb(null, false);
                        } else {
                            console.log("token success!");
                            return cb(null, user);
                        }
                    });


                    /*if (token === "super-secret-token") {
                        return cb(null, API_USER);
                    } else {
                        return cb(null, false);
                    }*/


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
                console.log("serialize user " + user.id);
                done(null, user);
            });

            passport.deserializeUser(function (user, done) {
                console.log("deserialize user " + user.id);
                var UserDataRepository = dbConnection.getRepository("UserData");
                UserDataRepository.findOne({id: user.id}).then(function (user) {
                    done(null, user);
                });
            });

            app.get('/', function (req, res) {
                if (!LoginReqGuard(req, res)) {
                    return;
                }

                var UserDataRepository = dbConnection.getRepository("SensorData");
                UserDataRepository.find().then(function (sensordatapoints) {
                    res.render("dashboard", {
                        sensordatapoints: sensordatapoints,
                        currentplayercount: gameLogic.g_connected_players_counter
                    });
                });

            });

            app.get('/manageusers', function (req, res) {
                if (!LoginReqGuard(req, res)) {
                    return;
                }

                if (!AdminReqGuard(req, res)) {
                    return;
                }

                var UserDataRepository = dbConnection.getRepository("UserData");
                UserDataRepository.find().then(function (users) {
                    res.render("manageusers", {users: users});
                });
            });

            app.post('/manageusers/remove', function (req, res) {
                if (!LoginReqGuard(req, res)) {
                    return;
                }

                if (!AdminReqGuard(req, res)) {
                    return;
                }

                const userid = req.body.id;

                var UserDataRepository = dbConnection.getRepository("UserData");
                if (req.body.id !== "1") // can't delete super admin guard
                {
                    UserDataRepository.delete({id: req.body.id});
                }
                UserDataRepository.find().then(function (users) {
                    res.redirect("/manageusers")
                });

            });

            app.post('/manageusers/updateapikey', function (req, res) {
                if (!LoginReqGuard(req, res)) {
                    return;
                }

                if (!AdminReqGuard(req, res)) {
                    return;
                }

                var UserDataRepository = dbConnection.getRepository("UserData");
                UserDataRepository.findOne({id: req.body.id}).then(function (user) {
                    user.apikey = req.body.apikey;
                    UserDataRepository.save(user)
                        .then(function (savedPost) {
                            console.log("Post has been saved: ", savedPost);
                            res.redirect("/manageusers");
                        });
                });

            });

            app.get('/manageaccount', function (req, res) {
                if (!LoginReqGuard(req, res)) {
                    return;
                }

                res.render("manageaccount", {
                    accountname: req.user.username,
                    apikey: req.user.apikey,
                    role: req.user.role
                });
            });

            app.post('/manageaccount/updateapikey', function (req, res) {
                if (!LoginReqGuard(req, res)) {
                    return;
                }

                var UserDataRepository = dbConnection.getRepository("UserData");
                UserDataRepository.findOne({id: req.user.id}).then(function (user) {
                    user.apikey = req.body.apikey;
                    UserDataRepository.save(user)
                        .then(function (savedPost) {
                            console.log("Post has been saved: ", savedPost);
                            res.redirect("/manageaccount");
                        });
                });

            });

            app.post('/manageaccount/updatepassword', function (req, res) {
                if (!LoginReqGuard(req, res)) {
                    return;
                }

                var UserDataRepository = dbConnection.getRepository("UserData");
                UserDataRepository.findOne({id: req.user.id}).then(function (user) {
                    user.password = req.body.updatepassword;
                    UserDataRepository.save(user)
                        .then(function (savedPost) {
                            console.log("Post has been saved: ", savedPost);
                            res.redirect("/manageaccount");
                        });
                });

            });

            app.post("/addmoderator", (req, res) => {
                if (!LoginReqGuard(req, res)) {
                    return;
                }

                if (req.user.role !== "admin") {
                    res.render("accessdenied");
                    return;
                }

                const NewUserData = {
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
                res.render('login', {loginsuccess: "Login failed!"});
            });

            app.post("/logout", (req, res) => {
                console.log(`Logout ${req.session.id}`);
                req.logout();
                res.cookie("connect.sid", "", {expires: new Date()});
                res.render('login', {loginsuccess: "You logged out, sign in with another account?"})
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
                    SensorDataRepository.save(SensorData)
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