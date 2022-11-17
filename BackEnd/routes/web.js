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

//습도 측정
router.patch("/measure", async (req, res) => {
  try {
    // const post = await Post.create({
    //   title: req.body.title

    // });
    console.log(req.body);
    if (req.body.number === 1) {
      console.log("1값이 들어왔어유");
      // await Plant.update(
      //   { watering_status: false },
      //   { where: { id: req.body.id } } //listparams에서 가져올 것, body에 id 값 넣어서 던질 것!!!!!!!
    }

    return res.sendStatus(201).send("측정 성공");
  } catch (error) {
    return res.sendStatus(500);
  }
});

//물주기
router.patch("/watering", async (req, res) => {
  try {
    console.log(req.body);
    // await Plant.update(
    //   { motor_status: false },
    //   { where: { id: req.body.id } }
    return res.sendStatus(201).send("물주기 성공");
  } catch (error) {
    return res.sendStatus(500);
  }
});

module.exports = router;
