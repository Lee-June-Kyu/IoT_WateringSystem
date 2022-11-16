const express = require("express");
const router = express.Router();
const { Humidity, Plant } = require("../models");

router.get("/plants", async (req, res, next) => {
  try {
    const plants = await Plant.findAll();
    return res.status(200).json({
      data: plants,
    });
  } catch (err) {
    return res.status(500).send("plants err:", err);
  }
});

router.get("/plant/:id", async (req, res, next) => {
  try {
    if (!!req.params.id) {
      let plant = await Plant.findOne({
        where: { id: req.params.id },
      });
      if (!!plant) {
        return res.status(200).json({ success: true, data: plant });
      } else {
        return res.status(200).json({ success: true, data: {} });
      }
    }
  } catch (err) {
    return res.status(500).send("plant err:", err);
  }
});

router.get("/humidity/:id", async (req, res) => {
  try {
    if (!!req.params.id) {
      let humidityInfos = await Humidity.findAll({
        where: { PlantId: req.params.id },
      });
      if (!!humidityInfos) {
        return res.status(200).json({ success: true, data: humidityInfos });
      } else {
        return res.status(200).json({ success: true, data: {} });
      }
    } else {
      return res.status(404).send("url 오류");
    }
  } catch (err) {
    return res.status(500).send("humidityInfo err:", err);
  }
});

module.exports = router;
