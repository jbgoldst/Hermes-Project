## import the serial library
import serial
import time
import string

def encode(a):
    value = 0
    byte = 2
    for i in range(0,2):
        value <<= 6
        value &= ~0x3f
        value |= a[i] - 0x30
            ##  printf(" evalue: %d", value);
    return value;




## Boolean variable that will represent
## whether or not the arduino is connected
a = False
b = False
## open the serial port that your ardiono
## is connected to
serin = ""
serin2 = ""
sleeptime = 1
ser = serial.Serial("/dev/tty.usbmodem1421", 19200)
print "connected"
##connect transmittion
##ser.write("r")
print "transmittin"

ser.write("SCIP2.0\r")




time.sleep(sleeptime)
ser.write("BM\r")
print "comp: talking to lrf"
time.sleep(sleeptime)


time.sleep(sleeptime)
ser.write("BM\r")
print "comp: talking to lrf"
time.sleep(sleeptime)



time.sleep(sleeptime)
ser.write("GS0050071807\r")
time.sleep(sleeptime)
print ser.readline()
print ser.readline()

print ser.readline()
print ser.readline()

print ser.readline()
print ser.readline()

print ser.readline()
print ser.readline()
print ser.readline()
print ser.readline()
print ser.readline()
print ser.readline()
serin3 = ser.readline()
serin4 = ser.readline()
serin5 = ser.readline()

codes0 = ""
codes1 = ""
codes2 = ""

for i in range(0,64):
    codes0 = codes0 + serin3[i]
print "ser 3: " + codes0
for i in range(0,64):
    codes1 = codes1 + serin4[i]
print "ser 4: " + codes1
for i in range(0,64):
    codes2 = codes2 + serin5[i]
print "ser 5: " + codes2

codes0 = serin3
codes1 = serin4
codes2 = serin5
code = 0
fullstring =""
code = 0
val = []
i = 0
while i < 32:
    a = 2*i
    b = a+1
    if code == 0:
        fullstring = codes0[a]
        fullstring = fullstring + codes0[b]
    if code == 1:
        fullstring = codes1[a]
        fullstring = fullstring + codes1[b]
    if code == 2:
        fullstring = codes2[a]
        fullstring = fullstring + codes2[b]
##   printf(" cvalue: %c", codes2[a]);
##   printf(" cvalue: %c", codes2[b]);

##   printf(" fvalue: %c", fullstring[0]);
##   printf(" fvalue: %c", fullstring[1]);
##   printf(" cvalue: %c", codes[a]);
##   printf(" cvalue: %c", codes[b])
                        
    value = 0
    byte = 2

    for j in range(0,2):
        value <<= 6
        value &= ~0x3f
        value = ord(fullstring[j]) - int("0x30",16)
    ##  printf(" evalue: %d", value);
    count = ((32*code)+(i+1))
    print count, ": ", value
    fullstring = '\0'
    value = 0
    i = i + 1
    if i == 31 and code < 2:
        code = code + 1
        i = 0

