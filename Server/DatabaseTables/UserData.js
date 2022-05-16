module.exports = {
    name: "UserData",
    columns: {
        id: {
            primary: true,
            type: "int",
            generated: true
        },
        username: {
            type: "varchar"
        },
        password: {
            type: "varchar"
        },
        apikey: {
            type: "varchar"
        },
        role: {
            type: "varchar"
        },
    }
};