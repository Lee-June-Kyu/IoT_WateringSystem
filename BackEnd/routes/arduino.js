const express = require("express");

const router = express.Router();

const { Humidity, Plant } = require('../models');

router.post("/:id", async (req, res) => {
  let dataSet = req.rawHeaders[11];
  let jsonData = JSON.parse(dataSet);
  // console.log(req);
  // console.log(jsonData['hh']);
  // console.log(Object.values(jsonData)[0]);
  await Humidity.create({
    // measuring_date: '2022-11-14',   // 없애고 createdAt으로 대체 가능할듯 ?
    humidity_value: jsonData['hh'],
    PlantId: req.params.id    // 아두이노 코드에서 id 설정하기
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