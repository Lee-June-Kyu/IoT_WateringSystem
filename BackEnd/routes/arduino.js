const express = require("express");

const router = express.Router();

const { Humidity, Plant } = require('../models');

router.post("/", async (req, res) => {
  let dataSet = req.rawHeaders[11];
  let jsonData = JSON.parse(dataSet);
  // console.log(req);
  // console.log(jsonData['hh']);
  // console.log(Object.values(jsonData)[0]);
  await Humidity.create({
    measuring_date: '2022-11-14',
    humidity_value: jsonData['hh'],
    PlantId: 1
  })
  try {
    return res.status(200).json(
      console.log('성공!')
    );
  } catch(error) {
    return res.sendStatus(400);
  }
})

module.exports = router;