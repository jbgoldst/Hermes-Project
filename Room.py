import math
class Room(object):
	def __init__(self, name, x, y, data):
    	self.name = name
    	self.x = x
    	self.y = y
    	self.data = data #this has the data for adjacent rooms

	def __repr__(self):
    	return self.name

	def getName(self):
    	return self.name

	def getData(self):
    	return self.data

	def getX(self):
    	return self.x

	def getY(self):
    	return self.y

	def setX(self, newX):
    	self.x = newX

	def setY(self, newY):
    	self.y = newY

	def adjacentRooms(self): #returns adjacent room names
    	L = []
    	temp = self.data
    	while len(temp)!= 0: #while there is more data, adjacent rooms will continue to be added
        	L.append(temp[0])
        	temp = temp[3:]
    	return L

	def distanceTo(self, other):
    	return math.fabs(self.x-other.x) + math.fabs(self.y-other.y) #adds absolute value of x and y offsets

	#def __eq__(self, other):
    	#return self.x == other.x and self.y == other.y

	def direction(self, other): #determines direction to move in
    	xOffset = other.x-self.x
    	yOffset = other.y-self.y
    	if yOffset > 0:
        	dir = 90
    	if xOffset < 0:
        	dir = 180
    	if yOffset < 0:
        	dir = 180
    	return dir
