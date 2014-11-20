const byte encoder1pinA = 3; //A pin for left motors (blue)
const byte encoder1pinB = 4; //B pin for left motors (green)
const byte encoder2pinA = 5; //A pin for right motors (blue)
const byte encoder2pinB = 6; //B pin for right motors (green)
byte encoder1PinALast; //previous pin A value (used to determine direction of rotation)
char inChar; //characters read in from Serial
double numRotations = 0.00; //number of rotations
boolean isForward; //rotation direction 


void setup()
{  
  Serial.begin(9600);//Initialize the serial port
  EncoderInit();//Initialize the module
}

void loop()
{
  Serial.print("Number of Rotations:");
  Serial.println(numRotations/1540.0); //prints number of rotations
  Serial.print("Distance Traveled:");
  Serial.println(numRotations*15.12/1540.0); //prints distance in inches 
  if(Serial.available()) //reads in from Serial
  {
     inChar = Serial.read();
     if(inChar == 'r')
      {
          numRotations =0;
      }
  }
  delay(500);
}

void EncoderInit() //instantiates encoder pins
{
  isForward = true; //default -> Forward
  pinMode(encoder1pinA, INPUT);  
  pinMode(encoder1pinB, INPUT);  
  attachInterrupt(0, wheelSpeed, CHANGE);
}

void wheelSpeed() //checks every time the wheel has moved
{
  int Lstate = digitalRead(encoder1pinA);
  if(Lstate == HIGH && encoder1PinALast == LOW)
  {
    int val = digitalRead(encoder1pinB);
     if(val == LOW && isForward)
    {
      isForward = false; //Reverse
    }
    else if(val == HIGH && !isForward)
    {
      isForward = true;  //Forward
    }
  }
   encoder1PinALast = Lstate;

  if(!isForward)
  {
    numRotations= numRotations + 1.0; //if moving forward, add distance
  }
  else
  {  
    numRotations= numRotations - 1.0; //if moving backward, subtract distance
  }
}


