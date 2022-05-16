// Game server & back-end for running Open Minecraft

const port = process.env.PORT || 314;

const express = require('express');
const session = require("express-session");

const bodyParser = require("body-parser");
const passport = require("passport");

const app = express();

const sessionMiddleware = session({secret: "super-duper-mega-secret", resave: false, saveUninitialized: false});
app.use(sessionMiddleware);
app.use(express.json());
app.use(bodyParser.urlencoded({extended: false}));
app.use(passport.initialize());
app.use(passport.session());
app.use(express.static(__dirname + '/public'));

const httpServer = require("http").createServer(app);

const io = require("socket.io")(httpServer, {
    cors: {origin: "http://localhost/", methods: ["GET", "POST"], credentials: true}
});

const gameLogic = require('./game-logic');
gameLogic.startGameLogic(io);

const apiEndpoints = require('./api-endpoints');
apiEndpoints.startApiEndpoints(io, app, passport, gameLogic);

httpServer.listen(port);
console.log("Server started on port: " + port);

