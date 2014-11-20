CODE WITH FILTERING: 

/////////////////////////////////
#include <math.h> // (no semicolon)
//// VARS
byte CLK_pin = 10;
byte EN_pin = 9;
byte DIO_pin = 2;

int X_Data = 0;
int Y_Data = 0;
int angle;
int X_avg = 0;
int Y_avg = 0;
//// FUNCTIONS

void ShiftOut(int Value, int BitsCount) {
  for(int i = BitsCount; i >= 0; i--) {
    digitalWrite(CLK_pin, LOW);
    if ((Value & 1 << i) == ( 1 << i)) {
      digitalWrite(DIO_pin, HIGH);
      //Serial.print("1");
    }
    else {
      digitalWrite(DIO_pin, LOW);
      //Serial.print("0");
    }
    digitalWrite(CLK_pin, HIGH);
    delayMicroseconds(1);
  }
//Serial.print(" ");
}

int ShiftIn(int BitsCount) {
  int ShiftIn_result;
    ShiftIn_result = 0;
    pinMode(DIO_pin, INPUT);
    for(int i = BitsCount; i >= 0; i--) {
      digitalWrite(CLK_pin, HIGH);
      delayMicroseconds(1);
      if (digitalRead(DIO_pin) == HIGH) {
        ShiftIn_result = (ShiftIn_result << 1) + 1; 
     //   Serial.print("x");
      }
      else {
        ShiftIn_result = (ShiftIn_result << 1) + 0;
      //  Serial.print("_");
      }
      digitalWrite(CLK_pin, LOW);
      delayMicroseconds(1);
    }
 // Serial.print(":");

// below is difficult to understand:
// if bit 11 is Set the value is negative
// the representation of negative values you
// have to add B11111000 in the upper Byte of
// the integer.
// see: http://en.wikipedia.org/wiki/Two%27s_complement
  if ((ShiftIn_result & 1 << 11) == 1 << 11) {
    ShiftIn_result = (B11111000 << 8) | ShiftIn_result; 
  }


  return ShiftIn_result;
}

void HM55B_Reset() {
  pinMode(DIO_pin, OUTPUT);
  digitalWrite(EN_pin, LOW);
  ShiftOut(B0000, 3);
  digitalWrite(EN_pin, HIGH);
}

void HM55B_StartMeasurementCommand() {
  pinMode(DIO_pin, OUTPUT);
  digitalWrite(EN_pin, LOW);
  ShiftOut(B1000, 3);
  digitalWrite(EN_pin, HIGH);
}

int HM55B_ReadCommand() {
  int result = 0;
  pinMode(DIO_pin, OUTPUT);
  digitalWrite(EN_pin, LOW);
  ShiftOut(B1100, 3);
  result = ShiftIn(3);
  return result;
}


void setup() {
  Serial.begin(9600);
  pinMode(EN_pin, OUTPUT);
  pinMode(CLK_pin, OUTPUT);
  pinMode(DIO_pin, INPUT);

  HM55B_Reset();
}

void loop() {
  HM55B_StartMeasurementCommand(); // necessary!!
  Serial.print(HM55B_ReadCommand()); // read data and print Status
  Serial.print(" ");  
  for(int x = 0; x < 10; x++)
  {
    X_avg += ShiftIn(11); // Field strength in X
    Y_avg += ShiftIn(11); // and Y direction
    delay(100);
  }
  X_avg = (X_avg)/10.0;
  Y_avg = (Y_avg)/10.0;
  Serial.print(X_avg); // print X strength
  Serial.print(" ");
  Serial.print(Y_avg); // print Y strength
  Serial.print(" ");
  digitalWrite(EN_pin, HIGH); // ok deselect chip
  angle = 180 * (atan2(-1*Y_avg , X_avg) / M_PI);
  Serial.print("angle: ");
  Serial.print(angle); // print angle
  Serial.println("");

}


