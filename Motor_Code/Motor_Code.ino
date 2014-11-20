/* 
 
 Use the motorGo(uint8_t motor, uint8_t direct, uint8_t pwm) 
 function to get motors going in either CW, CCW, BRAKEVCC, or 
 BRAKEGND. Use motorOff(int motor) to turn a specific motor off.
 
 The motor variable in each function should be either a 0 or a 1.
 pwm in the motorGo function should be a value between 0 and 255.
 */
#define BRAKEVCC 0
#define CW   1
#define CCW  2
#define BRAKEGND 3
#define CS_THRESHOLD 100

/*  VNH2SP30 pin definitions
 xxx[0] controls '1' outputs
 xxx[1] controls '2' outputs */
int inApin[2] = {7, 4};  // INA: Clockwise input
int inBpin[2] = {8, 9}; // INB: Counter-clockwise input
int pwmpin[2] = {5, 6}; // PWM input
int cspin[2] = {2, 3}; // CS: Current sense ANALOG input
int enpin[2] = {0, 1}; // EN: Status of switches output (Analog pin)
int speedVar = 0;
int statpin = 13; 
char inData[20]; // Allocate some space for the string
char d1;
char d2;
char d3;
char inChar; // Where to store the character read
byte index = 0; // Index into array; where to store the character

void setup()
{
  Serial.begin(9600);
  
  pinMode(statpin, OUTPUT);

  // Initialize digital pins as outputs
  for (int i=0; i<2; i++)
  {
    pinMode(inApin[i], OUTPUT);
    pinMode(inBpin[i], OUTPUT);
    pinMode(pwmpin[i], OUTPUT);
  }
  // Initialize braked
  for (int i=0; i<2; i++)
  {
    digitalWrite(inApin[i], LOW);
    digitalWrite(inBpin[i], LOW);
  }
  for(int i = 0; i < 20; i++)
{  
  inData[i] = 'n';
}
}



void loop()
{
//0 - motor - m, n, b for both, s for stop, l turn left, r turn right
//1 - orientation - w cw, c ccw, 
//2 - speed, depending on orientation..time for turn is 100ms

index = 0;
while(Serial.available() > 0) // Don't read unless
// there you know there is data
   {
       if(index < 19) // One less than the size of the array
       {
           inChar = Serial.read(); // Read a character
           inData[index] = inChar; // Store it
           index++; // Increment where to write next
          // Serial.print("Read" + inChar); 
       }
   }

 if(inData[0] != 'n')
{
   Serial.print(" InData");
   d1 = inData[0];
   d2 = inData[1];
   d3 = inData[2];
   String d33 = (String)d3;
   int t = d33.toInt();
   //Serial.print(t + "t");
   speedVar = (t * 10)+10;
   Serial.print(d33 + "");
   //Serial.print("d1 "+ (String)d1 + "d2 "+(String)d2+ "d3 "+ (String)d3 + "spd " + speedVar);
   if(d1 == 'c')
   {  
      if(d2 == 's')
      {
          motorGo(1, CW, speedVar);
          Serial.print("*cw 1");
       }
      if(d2 == 'w')
      {
          motorGo(1, CCW, speedVar);
           Serial.print("*ccw 1");
      }
       if(d2 == 'r')
      {
          motorGo(1, CCW, 1000);
          motorGo(0, CCW, 1000);
           Serial.print("*ccw full b");
      }
      if(d2 == 'f')
      {
          motorGo(1, CW, 1000);
          motorGo(0, CW, 1000);
           Serial.print("*ccw full b");
      }
   }
   if(d1 == 'z')
   {  
      if(d2 == 's')
      {
          motorGo(0, CW, speedVar);
           Serial.print("*cw 0");
      }
      if(d2 == 'w')
      {
          motorGo(0, CCW, speedVar);
           Serial.print("*ccw 0");
      }
      if(d2 == 'r')
      {
          motorGo(1, CCW, 1000);
          motorGo(0, CCW, 1000);
           Serial.print("*ccw full b");
      }
      if(d2 == 'f')
      {
          motorGo(1, CW, 1000);
          motorGo(0, CW, 1000);
           Serial.print("*ccw full b");
      }
   }

      if(d1 == 's')
      {
          motorGo(1, CW, speedVar);
          motorGo(0, CW, speedVar);
           Serial.print("*cw b");
      }
      if(d1 == 'w')
      {
          motorGo(1, CCW, speedVar);
          motorGo(0, CCW, speedVar);
           Serial.print("*ccw b");
      }
      if(d1 == 'r')
      {
          motorGo(1, CCW, 1000);
          motorGo(0, CCW, 1000);
           Serial.print("*ccw full b");
      }
      if(d1 == 'f')
      {
          motorGo(1, CW, 1000);
          motorGo(0, CW, 1000);
           Serial.print("*ccw full b");
      }
   if(d1 == 'd')
   {  
       motorGo(1, CW, 70);
       motorGo(0, CCW, 70);
        Serial.print("*left");
       delay(100);
   }
   if(d1 == 'a')
   {  
       motorGo(0, CW, 70);
       motorGo(1, CCW, 70);
        Serial.print("*right");
       delay(100);
   }
   if(d1 == 'x')
   {  
       motorGo(0, CW, 0);
       motorGo(1, CW, 0);
       Serial.print(" * off");
   }
}


index = 0;
for(int i = 0; i < 20; i++)
{  
  inData[i] = 'n';
}
  if ((analogRead(cspin[0]) < CS_THRESHOLD) && (analogRead(cspin[1]) < CS_THRESHOLD))
    digitalWrite(statpin, HIGH);
}



void motorOff(int motor)
{
  // Initialize braked
  for (int i=0; i<2; i++)
  {
    digitalWrite(inApin[i], LOW);
    digitalWrite(inBpin[i], LOW);
  }
  analogWrite(pwmpin[motor], 0);
}

/* motorGo() will set a motor going in a specific direction
 the motor will continue going in that direction, at that speed
 until told to do otherwise.
 
 motor: this should be either 0 or 1, will selet which of the two
 motors to be controlled
 
 direct: Should be between 0 and 3, with the following result
 0: Brake to VCC
 1: Clockwise
 2: CounterClockwise
 3: Brake to GND
 
 pwm: should be a value between ? and 1023, higher the number, the faster
 it'll go
 */
void motorGo(uint8_t motor, uint8_t direct, uint8_t pwm)
{
  if (motor <= 1)
  {
    if (direct <=4)
    {
      // Set inA[motor]
      if (direct <=1)
        digitalWrite(inApin[motor], HIGH);
      else
        digitalWrite(inApin[motor], LOW);

      // Set inB[motor]
      if ((direct==0)||(direct==2))
        digitalWrite(inBpin[motor], HIGH);
      else
        digitalWrite(inBpin[motor], LOW);

      analogWrite(pwmpin[motor], pwm);
    }
  }
}


