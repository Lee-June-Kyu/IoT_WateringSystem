const Sequelize = require('sequelize');

class Plant extends Sequelize.Model {
  static init(sequelize) {
    return super.init(
      {
        plant_name: {
          type: Sequelize.STRING(50),
          allowNull: false,
        },
        plant_kind: {
          type: Sequelize.STRING(50),
          allowNull: false,
        },
        watering_date: {
          type: Sequelize.DATE,
          allowNull: false,
        },
        watering_cycle: {
          type: Sequelize.INTEGER,
          allowNull: false,
        },
        arduino_url: {
          type: Sequelize.STRING(50),
          allowNull: false,
        },
        starting_date: {
          type: Sequelize.DATE,
          allowNull: true,
        },
        motor_status: {
          type: Sequelize.BOOLEAN,
          defaultValue: false
        },
        watering_status: {
          type: Sequelize.BOOLEAN,
          defaultValue: false
        },
        etc: {
          type: Sequelize.STRING(200),
          allowNull: true,
        },
        
      },
      {
        sequelize,
        timestamps: true,
        underscored: false,
        modelName: 'Plant',
        tableName: 'plant',
        paranoid: false,
        charset: 'utf8',
        collate: 'utf8_general_ci'
      }
    );
  }
  
  static associate(db) {
    db.Plant.hasMany(db.Humidity);
  }
}

module.exports = Plant;