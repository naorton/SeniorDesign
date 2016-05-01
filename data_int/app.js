var express = require('express');
var app = express();
var jsonfile = require('jsonfile');
var bodyParser = require('body-parser');
var json_path= './vending.json';

app.use(bodyParser.json());

app.get('/', function (req, res) {
	console.dir(jsonfile.readFileSync(json_path));
	res.send(jsonfile.readFileSync(json_path));
});

app.get('/config', function (req, res) {
	res.sendFile(__dirname + '/vending.html');
});

app.get('/bootstrapcss', function(req, res) {
  res.sendFile(__dirname + '/boot/css/bootstrap.min.css')
});

app.get('/bootstrapjs', function(req, res) {
  res.sendFile(__dirname + '/boot/js/bootstrap.min.js')
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

app.listen(3000, function () {
  console.log('Data interpreter listening on port 3000!');
});