var express = require('express');
var app = express();
var jsonfile = require('jsonfile');
var bodyParser = require('body-parser');
var json_path= './vending.json';

app.use(bodyParser.json());

app.use('/config', express.static(__dirname + '/public'));
app.use('/static', express.static(__dirname + '/static'));

app.get('/', function (req, res) {
	console.dir(jsonfile.readFileSync(json_path));
	res.send(jsonfile.readFileSync(json_path));
});

app.post('/', function (req, res) {
  res.send('Got a POST request');
  console.log(req.body);
  if (json_path) {
    jsonfile.writeFile(json_path, req.body, function (err) {
      console.error(err)
    })
  }
});

app.get('/locations/:id', function(req, res) {
  res.send("location: " + req.params.id);
  console.log(req.params.id)
  // Fetch product from database using location id
  // Use TTS library to "speak" product name and price
});

app.listen(80, function () {
  console.log('Data interpreter listening on port 80!');
});
