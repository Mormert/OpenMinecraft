## Docs for running the server locally

Depends only on NodeJS, NPM

```shell
npm install
npm start
```

##Docs for deploying the NodeJS server to a Heroku App

Create a new app on the Heroku platform

### 1. Installing Heroku CLI, then login
```shell
heroku login
```

### 2. Installing Heroku Builds plugin
```shell
heroku plugins:install heroku-builds
```

### 3. Create & upload build from local dir
```shell
heroku builds:create -a MY_APP
```