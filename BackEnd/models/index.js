const Sequelize = require('sequelize');
const Humidity = require('./humidity');
const Plant = require('./plant');

const env = 'development';
const config = require('../config/config')[env];
const db = {};

const sequelize = new Sequelize(config.database, config.username, config.password, config);

db.sequelize = sequelize;
// db.Sequelize = Sequelize;

db.Humidity=Humidity;
db.Plant = Plant;

Humidity.init(sequelize);
Plant.init(sequelize);

Humidity.associate(db);
Plant.associate(db);

module.exports = db;
