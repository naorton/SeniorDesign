To run backend server:
1) Install Node.js
2) Run Node.js command prompt, navigate to folder
3) Run command 'node app.js'
 - command prompt should respond with "Data interpreter listening on port 3000!"
4) Open http://localhost:3000/config

Change text input to integer input:
1) Comment out line 58
2) Uncomment lines 31-32 in vending.py
3) Comment out lines 35-46
You can call function GetProduct(input) in Nathen's python file when you press a sensor
GetProduct(0) for A0, GetProduct(1) for A2, etc etc

Change Windows TTS to Linux TTS:
1) Uncomment lines 12-13
2) Comment out lines 16-22
Changing the params in line 13 will adjust the voice