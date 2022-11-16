const express = require("express");

const router = express.Router();

const { Humidity, Plant } = require('../models');

router.post("/humidity/:id", async (req, res) => {
  let dataSet = req.rawHeaders[11];
  let jsonData = JSON.parse(dataSet);
  // console.log(req);
  // console.log(jsonData['hh']);
  // console.log(Object.values(jsonData)[0]);
  await Humidity.create({
    humidity_value: jsonData['humidity'],   
    PlantId: req.params.id    
  })
  try {
    return res.status(200).send('gg')
  } catch(error) {
    return res.sendStatus(400);
  }
})

router.get("/motor/:id", async (req, res,next) => {
  try {
    console.log('모터 get 들어오냐 ?')
    // if(!!req.params.id){
    //   let plant = await Plant.findOne({
    //     where: { id: req.params.id },
    //   })
    //   if(!!plant){
    //     return res.status(200).json({ success: true, data: plant })
    //   }
    //   else{
    //     return res.status(200).json({ success: true, data: {}})
    //   }
    // }
    return res.status(200).send('gg')

  } catch (err) {
    return res.status(500).send('plant err:', err)
  }
})

router.patch("/motor/:id", async (req, res,next) => {
  try {
    console.log('모터 patch 들어오냐 ?')
    // if(!!req.params.id){
    //   let plant = await Plant.findOne({
    //     where: { id: req.params.id },
    //   })
    //   if(!!plant){
    //     return res.status(200).json({ success: true, data: plant })
    //   }
    //   else{
    //     return res.status(200).json({ success: true, data: {}})
    //   }
    // }
    return res.status(200).send('gg')

  } catch (err) {
    return res.status(500).send('plant err:', err)
  }
})

module.exports = router;