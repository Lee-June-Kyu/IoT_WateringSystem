const Sequelize = require('sequelize');

class Humidity extends Sequelize.Model {
  static init(sequelize) {
    return super.init(
      {
        humidity_value: {
          type: Sequelize.STRING(50),
          allowNull: false,
        }
      },
      {
        sequelize,
        timestamps: true,
        underscored: false,
        modelName: 'Humidity',
        tableName: 'humidity',
        paranoid: false,
        charset: 'utf8',
        collate: 'utf8_general_ci'
      }
    );
  }
  
  static associate(db) {
    db.Humidity.belongsTo(db.Plant);
  }
}

module.exports = Humidity;