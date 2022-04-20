module.exports = {
    name: "SensorData",
    columns: {
        id: {
            primary: true,
            type: "int",
            generated: true
        },
        time: {
            type: "int"
        },
        humidity: {
            type: "real"
        },
        temperature: {
            type: "real"
        },
        brightness: {
            type: "real"
        }
    }
};