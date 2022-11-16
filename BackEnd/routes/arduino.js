const express = require("express");

const router = express.Router();

const { Humidity, Plant } = require("../models");

router.post("/humidity/:id", async (req, res) => {
  try {
    if (!!req.params.id) {
      let plant = await Plant.findOne({
        where: { id: req.params.id },
      });

      if (plant.watering_status == true) {
        let dataSet = req.rawHeaders[11];
        let jsonData = JSON.parse(dataSet);

        await Humidity.create({
          humidity_value: jsonData["humidity"],
          PlantId: req.params.id,
        });
        // plant.watering_status = true;
        try {
          return res.status(200).send("gg");
        } catch (error) {
          return res.sendStatus(400);
        }
      } else {
        return res.sendStatus(204);
      }
    } else {
      return res.status(204).send("No Content");
    }
  } catch {
    return res.sendStatus(404);
  }
});

router.get("/motor/:id", async (req, res, next) => {
  try {
    if (!!req.params.id) {
      let plant = await Plant.findOne({
        where: { id: req.params.id },
      });

      if (plant.motor_status == true) {
        await Plant.update(
          { motor_status: false },
          { where: { id: req.params.id } }
        );
        return res.status(200).send("active motor");
      } else {
        return res.sendStatus(204);
      }
    } else {
      return res.status(204).send("No Content");
    }
  } catch {
    return res.sendStatus(404);
  }
});

module.exports = router;
