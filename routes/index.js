var express = require('express');
var router = express.Router();
var log;
var temp;
var level;

router.get('/', function (req, res, next){

    res.render('index', {title:'Fire!, Fire!', log: log});

});

router.post('/log', function (req, res, next) {

	temp = parseInt(req.body.file);

	console.log(temp);


	 if(temp >= 60 && temp < 80){

    log = "Normal";

	}

	if(temp >= 80 && temp < 110){

		log = "Warm";
	}
  
  if(temp >= 110 && temp <= 135){

		log = "Dangerous";
	}

	if(temp > 135){

		log = "Fire";
	}
	
    res.end();
});

router.get('/getlog',function (req, res, next) {

	res.send(log);

});



module.exports = router;
