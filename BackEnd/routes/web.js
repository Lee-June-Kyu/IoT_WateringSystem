const express = require("express");
const router = express.Router();
const { Humidity, Plant } = require('../models');


router.get("/plant/:id", async (req, res,next) => {
  try {
    if(!!req.params.id){
      let plant = await Plant.findOne({
        where: { id: req.params.id },
      })
      if(!!plant){
        res.status(200).json({ success: true, data: plant })
      }
      else{
        res.status(200).json({ success: true, data: {}})
      }
    }

  } catch (err) {
    res.status(500).send('plant err:', err)
  }
})

router.get("/humidity/:id" , async (req, res)=> {
  try {
    if (!!req.params.id){
      let humidityInfos = await Humidity.findAll({
        where: { PlantId: req.params.id },
      })
      if(!!humidityInfos){
        res.status(200).json({ success: true, data: humidityInfos })
      }
      else {
        res.status(200).json({ success: true, data: {} })
      }
    }
    else {
      res.status(404).send('url 오류')
    }
  } catch (err) {
    res.status(500).send('humidityInfo err:', err)
  }
})

module.exports = router;