import pyttsx
import json
import urllib
import os

product = [
	"A0, Cheetos Crunchy, $1.00", "A2, Sun Chips Harvest Cheddar, $1.00", "A4, Lay's Original, $1.00", "A6, Lay's Original, $1.00", "A8, Doritos Nacho Cheese, $1.00"
	]
	
def TextToSpeech( input ):
	#for Linux
	"""
	input = "'" + input + "'"
	os.system("espeak -ven-us+f2 -s150 " + input)
	"""
	
	#for Windows
	engine = pyttsx.init()
	voices = engine.getProperty('voices')
	rate = engine.getProperty('rate')
	engine.setProperty('rate', rate-75)
	engine.setProperty('voice', voices[1].id)
	engine.say(input)
	engine.runAndWait()
	return
	
def GetProduct( input ):
	url = "http://localhost:3000/"
	response = urllib.urlopen(url)
	data = json.load(response)
	product = data.values()[0]
	#simple return for integer input
	#returnItem = str(product[input]);
	
	#for loop for text input
	slots = ["A0", "A2", "A4", "A6", "A8", "B0", "B2", "B4", "B6", "B8"]
	i = 0
	returnItem = "invalid"
	for item in slots:
		if input == item:
			returnItem = str(product[i])
		i += 1
	if returnItem == "invalid":
		print "Invalid input"
		return
	else:
		return returnItem
	
def GetInput() :
	while(1 != 2):
		cmd = raw_input("Please input a command")
		if len(cmd) != 2:
			print "Invalid input"
		else:
			string = GetProduct(cmd)
			print string
			TextToSpeech(string)

GetInput()