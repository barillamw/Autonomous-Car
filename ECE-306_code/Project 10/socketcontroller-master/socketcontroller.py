#------------------------------------------------------------------------------------------#
#Created by Bill Pashby
#Edited by Sean Benoit
#Adjusted by Michael Barilla
#ECE 306 Project 10
#
#
#Client-Side controller to control IoT-equiped embedded system over a TCP socket
#
#------------------------------------------------------------------------------------------#

import socket
from inputs import get_gamepad
import math
import time
import sys


#------------------------------------------------------------------------------------------#
'''VARIABLES'''
#Socket setup vars
remote_ip = '10.153.58.153'#IP address of your IoT module
port = 7898                   #The port you opened on your IoT module

#Transmitted string setup
indichar = '~'              #Indicator character
code = '0208'               #4-digit security code
messages = ""               #The whole message - filled before transmission


#Controller input vars
analogvalueY = 0            #Value from left joystick (Y-axis)
analogvalueX = 0            #Value from right joystick (Y-axis)
analogvalueTR = 0
digitalvalueINCR = 0
digitalvalueDECR = 0
digitalvalueLINEL = 0
digitalvalueLINER = 0
sendvalueL = 0              #Remapped value from left joystick
sendvalueR = 0				#Remapped value from right joystick
sendValueC = 0							
sendstringL = ""            #Full string for left motor, including sign
sendstringR = ""            #Full string for left motor, including sign
sendstringC = ""

#Number ranges for input and output
maxtriggervalue = 255     #maximum value from a joystick
mintriggervalue = -255    #minimum value from a joystick
maxsendvalue = 399          #maximum value sent to server
minsendvalue = -399         #mimimum value sent to server
#------------------------------------------------------------------------------------------#


#------------------------------------------------------------------------------------------#
'''SOCKET SETUP'''
try:                                                        #Starts socket
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
except socket.error as msg:
    print ('Failed to create socket.')                      #Faliure in socket creation
    #sys.exit();                                             #Exits program
    
print ('Socket Created')                                    #Socket creation was successful

print ('Ip address is ' + remote_ip)
s.connect((remote_ip, port))                                #Connects client to car server
print ('Socket connection successful')
#------------------------------------------------------------------------------------------#


#------------------------------------------------------------------------------------------#
'''FUNCTIONS'''
#*****getinfo() will only return once there is a change in state on the gamepad*****

def getinfo():                      #Gets values from the gamepad every change of state
	events = get_gamepad()          #Updates the events data set with the current state
    
	for event in events:            #Operates on the most recent event, will not skip events
        
		stick = event.code          #Gets the input type
		stickval = event.state      #Gets the input value
        
		if stick == 'ABS_Y':        	#Y-axis joystick
			global analogvalueY     #Sets appropriate global value from joystick
			analogvalueY = stickval            
		elif stick =='ABS_X':       	#X-axis joystick
			global analogvalueX     #Sets appropriate global value from joystick
			analogvalueX = stickval
		elif stick =='ABS_RZ':   			#Right Trigger
			global analogvalueTR
			analogvalueTR = stickval
		elif stick =='BTN_SOUTH':       	#South Button
			global digitalvalueDECR			#Decrement
			digitalvalueDECR = stickval
		elif stick =='BTN_WEST':			#West Button
			global digitalvalueLINEL		#Black line command Left
			digitalvalueLINEL = stickval
		elif stick =='BTN_EAST':			#East Button
			global digitalvalueLINER
			digitalvalueLINER = stickval	#Follow Black Line Right
		elif stick == 'BTN_NORTH':			#North Button
			global digitalvalueINCR
			digitalvalueINCR = stickval		#Increment

def rangemap(analog,yval,xval, direction):                #Maps the joystick values to an interpretable range
	angle = math.atan2(yval,xval)
	mod = 0
	#Math to select what angle the joy stick is at and set modifier for PWM values in left and right motors 
	if xval != 128 and yval != 128:
		if direction == 1:
			if angle == math.pi/4:
				mod = 0
			elif angle > 0 and angle < math.pi/2: 
				mod = angle/math.pi +0.5
			elif angle >= math.pi/2 and angle < 3*math.pi/4:
				mod = (3*math.pi/4 - angle)/(math.pi/4)
			elif angle >= 3*math.pi/4 and angle <= math.pi:
				mod = (3*math.pi/4 - angle)/(math.pi/2)
			elif angle >= - math.pi and angle < -math.pi/2:
				mod = math.pi/(2*angle)
			elif angle >= -math.pi/2 and angle < -math.pi/4:
				mod = (math.pi/4 + angle)/(math.pi/4)
			elif angle > -math.pi/4 and angle < 0:
				mod = (math.pi/4 + angle)/(math.pi/2)

		elif direction == 2:
			if angle == -math.pi/4:
				mod = 0
			elif angle > 0 and angle < math.pi/4:
				mod = (angle - math.pi/4)/(math.pi/2)
			elif angle > math.pi/4 and angle < math.pi/2:
				mod = (angle - math.pi/4)/(math.pi/4)
			elif angle >= math.pi/2 and angle <= math.pi:
				mod = math.pi/(2* angle)
			elif angle >= -math.pi and angle < -3*math.pi/4:
				mod = (-3*math.pi/4 - angle)/(math.pi/2)
			elif angle >= -3*math.pi/4 and angle < -math.pi/2:
				mod = (-3*math.pi/4 - angle)/(math.pi/4)
			elif angle >= -math.pi/2 and angle < 0:
				mod = angle/math.pi - 0.5

	print(xval)
	print(yval)
	
	analog = mod*analog #sets final PWM values
	return (int)((analog-mintriggervalue)*(maxsendvalue-minsendvalue)/(maxtriggervalue-mintriggervalue)+minsendvalue)
#------------------------------------------------------------------------------------------#


#------------------------------------------------------------------------------------------#
'''MAIN LOOP'''
while True:
	getinfo()                                           #Updates the joystick values


	#remaps trigger values to a 3-digit positive value
	sendvalueL = rangemap(analogvalueTR, analogvalueY, analogvalueX, 1)
	sendvalueR = rangemap(analogvalueTR, analogvalueY, analogvalueX, 2)

	#Changes remapped values to strings, and adds a '+' for positive values
	if sendvalueL >= 0:
		sendstringL = '+' + str("%03d" % (sendvalueL,))
	else:
		sendstringL = str("%04d" % (sendvalueL,))
	if sendvalueR >= 0:
		sendstringR = '+' + str("%03d" % (sendvalueR,))
	else:
		sendstringR = str("%04d" % (sendvalueR,))
	if digitalvalueINCR == 1: 		#Sets command character output
		sendValueC = 'I'			#Increment command
	elif digitalvalueDECR == 1:
		sendValueC = 'D'			#Decrement command
	elif digitalvalueLINEL == 1:
		sendValueC = 'L'			#Black line enter/exit command
	elif digitalvalueLINER == 1:
		sendValueC = 'R'
	else:
		sendValueC = 'N'			#No command
	

	#concatenates various values into a single string
	message = (str(indichar) +                      #Indicator character
				str(code) +                          #4-digit security code
				sendstringL +        #Left motor PWM value
				sendstringR +        #Right motor PWM value
				sendValueC  +
				';'                  #End of string
				'\r\n'                               #Carriage return and line feed
				)
	s.sendall(message.encode(encoding='ascii'))     #Sends message after ascii-encoding
	print(message)                                  #Also prints message for debuggin
	#time.sleep(0.2)                                 #waits for 200 milliseconds
#------------------------------------------------------------------------------------------#
