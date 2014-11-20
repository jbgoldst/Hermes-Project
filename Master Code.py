from Room import Room
from string import *
from priodict import priorityDictionary
from time import *
import math

class Robot (object):
	def __init__(self, direction, x, y):
    	self.dir = direction
    	self.x = x
    	self.y = y

	def getX(self):
    	return self.x

	def getY(self):
    	return self.y

	def getDir(self):
    	return self.dir

	def setX(self, newX):
    	self.x = newX

	def setY(self, newY):
    	self.y = newY

	def setDir(self, newDirection):
    	self.dir = newDirection

	def forward(): #moves the robot forward
    	outMove("be", 0)

	def adjustLeft(): #turns left (until condition met in adjustDir)
    	pass

	def adjustRight():
    	pass

	def turnLeft():
    	pass

	def turnRight():
    	pass

	def stop():
    	outStop()

	def adjustDir(newDir): #makes robot turn to specific direction, based on what direction it is aiming for
    	self.dir = inCompass()
    	difference = newDir - self.dir
    	if math.fabs(difference)> 2:
        	if 0 < difference < 180:
            	adjustLeft()
        	if 180 < difference < 360:
            	adjustRight()
        	if -180 < difference < 0:
            	adjustRight()
        	if -360 < difference < -180:
            	adjustLeft()


	def turnAtEndpoint(newDir): #makes robot turn to specific direction, based on what direction it is aiming for
    	self.dir = inCompass()
    	difference = newDir - self.dir
    	if math.fabs(difference)> 2:
        	if 0 < difference < 180:
            	turnLeft()
        	if 180 < difference < 360:
            	turnRight()
        	if -180 < difference < 0:
            	turnRight()
        	if -360 < difference < -180:
            	turnLeft()

	def moveToward(room): #moves toward a room
    	self.dir = inCompass()
    	direction = math.atan2(self.y, self.x)
    	self.adjustDir(direction)

	def isAt(room):
    	if (math.fabs(self.x - room.getX()) < 0 and math.fabs(self.y-room.getY())):
        	return True;
    	else:
        	return False;

def readMap(): #reads the data to be used for Djikstra's
	data = open("Room_List_Djikstra.txt", "r", encoding = 'utf-16')
	roomList = []
	for line in data:
    	roomData = line.split()
    	temp = Room(str(roomData[0]), float(roomData[1]), float(roomData[2]), roomData[3:])
    	roomList.append(temp)
	roomDict = {}
	for room in roomList:
    	roomDict[room.getName()] = room
	return roomDict


def shortestPath(G,start,end):
	D,P = Dijkstra(G,start,end)
	Path = []
	while 1:
    	Path.append(end)
    	if end == start: break
    	end = P[end].getName()
	Path.reverse()
	return Path

def Dijkstra(G,start,end=None):
	D = {}    # dictionary of final distances, key is String (room name), value is distance
	P = {}    # dictionary of predecessors
	Q = priorityDictionary()   # est.dist. of non-final vert.
	Q[start] = 0

	for v in Q: #v is a string
    	D[v] = Q[v]
    	if v == end: break

    	for w in G[v].adjacentRooms(): #w is a room
        	vwLength = D[v] + G[v].distanceTo(G[w])
        	if w in D:
            	if vwLength < D[w]:
                	raise ValueError("Dijkstra: found better path to already-final vertex")
        	elif w not in Q or vwLength < Q[w]:
            	Q[w] = vwLength
            	P[w] = G[v]
	return (D,P)


def main():
	roomList = readMap() #reads text file
	start = input("Enter starting location: "); #asks for start/end places
	end = input("Enter ending location: ");
	P = shortestPath(roomList, start, end) #finds path
	print(P)
	direction = inCompass()
	encoderStart = inEncoders()
	hermes = Robot(direction, roomList[start].getX(), roomList[start].getY()) #robot instantiation


	startTime = clock() #start time, used for the end
	arrived = False #checks if the robot has arrived at destination
	step = 10 #step for time
	while (not arrived):
    	nextRoom = roomList[P[0]] #(next room)
    	hermes.moveTowards(nextRoom)
    	if hermes.isAt(nextRoom):
        	if len(P) == 1:
            	arrived = True
        	else:
            	hermes.turnAtEndpoint()
        	P = P[1:]
    	time.sleep(step)
	print ("Time taken = " + clock()-startTime())

if __name__ == '__main__':
	main()
