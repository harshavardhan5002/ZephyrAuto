#include <Ultrasonic.h>
#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Servo.h>
#include <Wire.h>

//Pin Connection for Front Sensor
const int trigPinfr = 4;    
const int echoPinfr = 5;

//Pin Connection for Front Left Sensor    
const int trigPinfrleft = 6;    
const int echoPinfrleft = 7;

//Pin Connection for Front Right Sensor
const int trigPinfrright = 8;    
const int echoPinfrright = 9;

//Pin Connection for Back Sensor
const int trigPinbk = 10;    
const int echoPinbk = 11;

//Pin Connection for Back Left Sensor
const int trigPinbklt = 12;    
const int echoPinbklt = 13;

//Pin Connection for Back Right Sensor 
const int trigPinbkrt = 52;    
const int echoPinbkrt = 53;

const int leftIRPin = A1;  // Analog pin for left infrared sensor
const int rightIRPin = A2; // Analog pin for right infrared sensor

// Sensitivity of the voltage sensor (25mV per unit)
const float voltageSensitivity = 0.025; // 25mV per unit
// Battery parameters
const float fullVoltage = 13.00;  // Full battery voltage (when fully charged)
const float emptyVoltage = 10.0; // Voltage at which the battery is considered empty
const int voltageSensorPin = A0;

Ultrasonic ultrasonicfr(trigPinfr, echoPinfr);
Ultrasonic ultrasonicfrleft(trigPinfrleft, echoPinfrleft);
Ultrasonic ultrasonicfrright(trigPinfrright, echoPinfrright);
Ultrasonic ultrasonicbk(trigPinbk, echoPinbk);
Ultrasonic ultrasonicbklt(trigPinbklt, echoPinbklt);
Ultrasonic ultrasonicbkrt(trigPinbkrt, echoPinbkrt);

const int servoPin = 14;
Servo steer;

int motor1E = 2;  // E1 pin we havr to change the pins to pwm 
int motor2E = 3; // E2 pin 
int motor1I1 = A3; // I1 pin
int motor1I2 = A4; // I2 pin
int motor2I1 = A5; // I3 pin
int motor2I2 = A6; // I4 pin

int dist1 = 50.00; 
int dist2 = 30.00;
int dist3 = 20.00;
int dist4 = 10.00;

int distl = 15.00;
int distr = 15.00;

int anglelt = 120;
int anglert = 60;

const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns

char keys[ROWS][COLS] = 
{

  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}

};
// Connect keypad ROW0, ROW1, ROW2, ROW3 to these Arduino pins.
byte rowPins[ROWS] = {22, 23, 24, 25};
// Connect keypad COL0, COL1, COL2, COL3 to these Arduino pins.
byte colPins[COLS] = {26, 27, 28, 29};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

LiquidCrystal lcd(30, 31, 32, 33, 34, 35);

bool parkbool=false;//A
bool reversebool=false;//B
bool cruisebool=false;//C
bool drivebool=false;//D
bool lanebool=false;//*
bool lanekeepbool=false;//#
bool ACC;

bool inlanel = true; // Variable to track if the car is in the left lane
bool inlaner = true; 

//flag variables
int medflag = 0;
int extflag = 0;
int panflag=0;
bool fmotflag = 0;
bool bmotflag=0;

bool stopflag = 0;
bool revstopflag = 0;
int cruiseSpeed;
// Define the adaptive cruise control parameters
const float ACC_DISTANCE_THRESHOLD = 30.0; // Adjust this value based on your requirements (in cm)
const float MINIMUM_SPEED = 0; // Adjust this value based on your requirements


void setup() 
{

  Wire.begin();

  Wire.beginTransmission(9); // Address of the slave Arduino (change accordingly)
  Wire.write("9"); // Send a trigger command to the slave
  Wire.endTransmission();

  //motor pins
  pinMode(motor1E, OUTPUT);
  pinMode(motor2E, OUTPUT);
  pinMode(motor1I1, OUTPUT);
  pinMode(motor1I2, OUTPUT);
  pinMode(motor2I1, OUTPUT);
  pinMode(motor2I2, OUTPUT);
  analogWrite(motor1E, 225);
  analogWrite(motor2E, 225);

  analogWrite(motor1E, 225);
  analogWrite(motor2E, 225);
  analogWrite(motor1I1, LOW);
  digitalWrite(motor1I2, LOW);
  analogWrite(motor2I1, LOW);
  digitalWrite(motor2I2, LOW);
  lcd.begin(16, 2);

  int rawValue = analogRead(voltageSensorPin);
  float voltage = rawValue * voltageSensitivity;
  float batteryPercentage = map(voltage * 1000, emptyVoltage * 1000, fullVoltage * 1000, 0, 100);
  //lcd.clear();
  lcd.setCursor(0, 0); // Set cursor to the first row
  lcd.print("ZephyrAuto+");
  // Display battery level bar on the second line
  lcd.setCursor(0, 1);
  lcd.print("");
  int numBars = map(batteryPercentage, 0, 100, 0, 10);

  if(batteryPercentage>0){
  lcd.print("[");
  for (int i = 0; i < 10; i++) {
    lcd.print(i < numBars ? "=" : " ");
  }
  lcd.print("] ");
  lcd.print(batteryPercentage, 1);
  lcd.print("%");
  Serial.println(batteryPercentage);
  delay(10);}
  else
  {
    lcd.setCursor(0, 1);
    lcd.print("EV Not Connected");
  }

  //servo connect
  steer.attach(servoPin);
  Serial.begin(9600);

}

void loop() 
{
  char key = keypad.getKey();
  if (key == 'D') 
  {
    drivebool = true;
    reversebool = false;
    parkbool = false;
    cruisebool = false;
    fmotflag= false;
    bmotflag = false;
    lanebool = false;

    Serial.println("DRIVE");
  } 
  else if (key == 'B') 
  {
    drivebool = false;
    reversebool = true;
    parkbool = false;
    cruisebool = false;
    fmotflag= false;
    bmotflag = false;
    lanebool = false;

    Serial.println("REVERSE");
  }
  else if (key == 'A')
  {
    drivebool = false;
    reversebool = false;
    parkbool = true;
    cruisebool = false;
    fmotflag = false;
    bmotflag = false;
    lanebool = false;

    Serial.println("PARK");
  }
  else if (key == 'C')
  {
    drivebool = false;
    reversebool = false;
    parkbool = false;
    cruisebool = true;
    fmotflag = false;
    bmotflag = false;
    lanebool = false;

    Serial.println("CRUISE");
  }

  else if (key == '*')
  {
    drivebool = false;
    reversebool = false;
    parkbool = false;
    cruisebool = false;
    fmotflag = false;
    bmotflag = false;
    lanebool = !lanebool;
    if(!lanebool)
    {
      lanecenter();
    }

    Serial.println("Lanecenter");
  }
  else if (key == '#')
  {
    drivebool = false;
    reversebool = false;
    parkbool = false;
    cruisebool = false;
    fmotflag = false;
    bmotflag = false;
    lanekeepbool = !lanekeepbool;
    if(!lanekeepbool)
    {
      lanekeep();
    }

    Serial.println("Lanekeep");
  }

  if (drivebool) 
  {
    drive();
  } 
  else if (reversebool) 
  {
    reverse();
  }
  else if (parkbool) 
  {
    park();
  }
  else if (cruisebool) 
  {
    cruise();
  }
  else if(lanebool)
  {
    lanecenter();
  }
  else if(lanebool)
  {
    lanekeep();
  }
}

float readDistance(Ultrasonic &ultrasonic) 
{
  float distance_cm = ultrasonic.read(); // Measure distance in centimeters
  return distance_cm;
}

void lanecenter()
{

  int leftIRValue = analogRead(leftIRPin);
  int rightIRValue = analogRead(rightIRPin);

  // Calculate the error based on sensor readings
  int error = leftIRValue - rightIRValue;

  // Adjust the steering based on the error
  int steeringAngle = 90 + error / 5; // Adjust the sensitivity as needed

  // Constrain the steering angle to a reasonable range
  steeringAngle = constrain(steeringAngle, 60, 120);

  // Set the servo angle for steering
  steer.write(steeringAngle);

  // Print sensor values and steering angle for debugging
  Serial.print("Left IR: ");
  Serial.print(leftIRValue);
  Serial.print(" Right IR: ");
  Serial.print(rightIRValue);
  Serial.print(" Steering Angle: ");
  Serial.println(steeringAngle);


}

void lanekeep()
{

  int leftIRValue = analogRead(leftIRPin);
  int rightIRValue = analogRead(rightIRPin);

  // Define threshold values for "in lane" and "out of lane"
  int inLaneThreshold = 500;    // Adjust this value as needed
  int outOfLaneThreshold = 100; // Adjust this value as needed

  if (leftIRValue < inLaneThreshold && rightIRValue < inLaneThreshold) {
    // The car is in the lane
    inlanel = true;
    inlaner = true;
  } else {
    // The car is out of the lane
    inlanel = false;
    inlaner = false;
  }

  if (!inlaner) {
    steer.write(60); // Steer right
    Serial.println("Right Lane Keeping");
    delay(100);
    steer.write(90); // Return to the center
  }

  if (!inlanel) {
    steer.write(120); // Steer left
    Serial.println("Left Lane Keeping");
    delay(100);
    steer.write(90); // Return to the center
  }

}



void drive()
{
  if(lanebool)
  {
    lanecenter();
  }
  if(ACC)
  {
    adaptiveCruiseControl();
  }
  if(!stopflag)
  {
    moveForward();
  }

  float distancefront = readDistance(ultrasonicfr);
  float distancefleft = readDistance(ultrasonicfrleft);
  float distancefright = readDistance(ultrasonicfrright);

  float distanceback = readDistance(ultrasonicbk);
  float distancebleft = readDistance(ultrasonicbklt);
  float distancebright = readDistance(ultrasonicbkrt);

  //steer.write(90);

  Serial.print("Distance from Sensor 23 front pin: ");
  Serial.print(distancefront, 2); // 2 decimal places
  Serial.println(" cm");

  Serial.print("Distance from Sensor 45 frontleft pin: ");
  Serial.print(distancefleft, 2); // 2 decimal places
  Serial.println(" cm");

  Serial.print("Distance from Sensor 67 frontright pin: ");
  Serial.print(distancefright, 2); // 2 decimal places
  Serial.println(" cm");

  Serial.print("Distance from Sensor 89 back pin: ");
  Serial.print(distanceback, 2); // 2 decimal places
  Serial.println(" cm");

  Serial.print("Distance from Sensor 1011 backleft pin: ");
  Serial.print(distancebleft, 2); // 2 decimal places
  Serial.println(" cm");

  Serial.print("Distance from Sensor 1213 backright pin: ");
  Serial.print(distancebright, 2); // 2 decimal places
  Serial.println(" cm");

  lcd.clear();
  lcd.setCursor(0, 0); // Set cursor to the first row
  lcd.print("Gear : D");

  //lcd.setCursor(0, 1); // Set cursor to the second row
  //lcd.print("Lead Clear");

  //FRONT -----------------------------------------------------------

  if(distancefront>dist1)
  {
    //LCD in CODE 1
    /*lcd.clear();
    lcd.setCursor(0, 0); // Set cursor to the first row
    lcd.print("Gear : D");

    lcd.setCursor(0, 1); // Set cursor to the second row
    lcd.print("Lead Clear");*/

    lcd.setCursor(0, 1); // Set cursor to the second row
    lcd.print("Lead Clear");

    Wire.beginTransmission(9); // Address of the slave Arduino (change accordingly)
    Wire.write("4"); // Send a trigger command to the slave
    Wire.endTransmission();

    Serial.println("Front Ext");
  }
  else if(distancefront<dist1 && distancefront>=dist2)
  {
    Serial.println("Front1");
    Wire.beginTransmission(9); // Address of the slave Arduino (change accordingly)
    Wire.write("1"); // Send a trigger command to the slave
    Wire.endTransmission();
  }
  else if(distancefront<dist2 and distancefront>dist3)
  {
    Serial.println("Front2");
    stopMotors();
    stopflag=1;
    Wire.beginTransmission(9); // Address of the slave Arduino (change accordingly)
    Wire.write("2"); // Send a trigger command to the slave
    Wire.endTransmission();
  }
  else if(distancefront<dist3)
  {
    Serial.println("front3");
    if(distancefleft>distl||distancefright>distr)
    {
      if(distancefleft>distancefright)
      {
        steer.write(180);
      }
      else if(distancefleft<distancefright)
      {
        steer.write(0);
      }
      else
      {
        steer.write(90);
      }
    }
    stopMotors();
    stopflag=1;
    Wire.beginTransmission(9); // Address of the slave Arduino (change accordingly)
    Wire.write("3"); // Send a trigger command to the slave
    Wire.endTransmission();
    
  }


  //FRONT LEFT -----------------------------------------------------------

  if(distancefleft>dist1)
  {
    //LCD in CODE 1
    /*lcd.clear();
    lcd.setCursor(0, 0); // Set cursor to the first row
    lcd.print("Gear : D");

    lcd.setCursor(0, 1); // Set cursor to the second row
    lcd.print("Lead Clear");*/

    Serial.println("Front left Ext");
    Wire.beginTransmission(9); // Address of the slave Arduino (change accordingly)
    Wire.write("4"); // Send a trigger command to the slave
    Wire.endTransmission();

  }
  else if(distancefleft<dist1 && distancefleft>=dist2)
  {
    Serial.println("Front Left");
    Wire.beginTransmission(9); // Address of the slave Arduino (change accordingly)
    Wire.write("1"); // Send a trigger command to the slave
    Wire.endTransmission();
  }
  else if(distancefleft<dist2 and distancefleft>dist3)
  {
    Serial.println("Front Left");
    Serial.println("Brakes Applied");
    Wire.beginTransmission(9); // Address of the slave Arduino (change accordingly)
    Wire.write("2"); // Send a trigger command to the slave
    Wire.endTransmission();
  }
  else if(distancefleft<dist4)
  {
    Serial.println("Front Left");
    steer.write(anglelt);
    delay(100);
    steer.write(90);
    stopMotors();
    stopflag=1;
    Wire.beginTransmission(9); // Address of the slave Arduino (change accordingly)
    Wire.write("3"); // Send a trigger command to the slave
    Wire.endTransmission();
  }


  //FRONT RIGHT -----------------------------------------------------------

  if(distancefright>dist1)
  {
    //LCD in CODE 1
    /*lcd.clear();
    lcd.setCursor(0, 0); // Set cursor to the first row
    lcd.print("Gear : D");

    lcd.setCursor(0, 1); // Set cursor to the second row
    lcd.print("Lead Clear");*/

    Serial.println("Front Right Ext");
    Wire.beginTransmission(9); // Address of the slave Arduino (change accordingly)
    Wire.write("4"); // Send a trigger command to the slave
    Wire.endTransmission();
  }
  else if(distancefright<dist1 && distancefright>=dist2)
  {
    Serial.println("Front Right");
    Wire.beginTransmission(9); // Address of the slave Arduino (change accordingly)
    Wire.write("1"); // Send a trigger command to the slave
    Wire.endTransmission();
  }
  else if(distancefright<dist2 and distancefright>dist3)
  {
    Serial.println("Front Right");
    Serial.println("Brakes Applied");
    Wire.beginTransmission(9); // Address of the slave Arduino (change accordingly)
    Wire.write("2"); // Send a trigger command to the slave
    Wire.endTransmission();
    
  }
  else if(distancefright<dist4)
  {
    Serial.println("Front Right");
    steer.write(anglert);
    delay(100);
    steer.write(90);
    stopMotors();
    stopflag=1;
    Wire.beginTransmission(9); // Address of the slave Arduino (change accordingly)
    Wire.write("3"); // Send a trigger command to the slave
    Wire.endTransmission();
  }

  //BACK LEFT -----------------------------------------------------------

  if(distancebleft>dist1)
  {
    //LCD in CODE 1
    /*lcd.clear();
    lcd.setCursor(0, 0); // Set cursor to the first row
    lcd.print("Gear : D");

    lcd.setCursor(0, 1); // Set cursor to the second row
    lcd.print("Lead Clear");*/

    Serial.println("Back Left Ext");
    Wire.beginTransmission(9); // Address of the slave Arduino (change accordingly)
    Wire.write("4"); // Send a trigger command to the slave
    Wire.endTransmission();
  }
  else if(distancebleft<dist1 && distancebleft>=dist2)
  {
    Serial.println("Back Left");
    Wire.beginTransmission(9); // Address of the slave Arduino (change accordingly)
    Wire.write("1"); // Send a trigger command to the slave
    Wire.endTransmission(); 
  }
  else if(distancebleft<dist2 and distancebleft>dist3)
  {
    Serial.println("Back Left");
    Serial.println("Brakes Applied");
    Wire.beginTransmission(9); // Address of the slave Arduino (change accordingly)
    Wire.write("2"); // Send a trigger command to the slave
    Wire.endTransmission();
  }
  else if(distancebleft<dist4)
  {
    Serial.println("Back Left");
    steer.write(anglelt);
    delay(100);
    steer.write(90);
    stopMotors();
    stopflag=1;
    Wire.beginTransmission(9); // Address of the slave Arduino (change accordingly)
    Wire.write("3"); // Send a trigger command to the slave
    Wire.endTransmission();
  }

  //BACK RIGHT -----------------------------------------------------------

  if(distancebright>dist1)
  {
    //LCD in CODE 1
    /*lcd.clear();
    lcd.setCursor(0, 0); // Set cursor to the first row
    lcd.print("Gear : D");

    lcd.setCursor(0, 1); // Set cursor to the second row
    lcd.print("Lead Clear");*/

    Serial.println("Back Right Ext");
    Wire.beginTransmission(9); // Address of the slave Arduino (change accordingly)
    Wire.write("4"); // Send a trigger command to the slave
    Wire.endTransmission();
  }
  else if(distancebright<dist1 && distancebright>=dist2)
  { 
    Serial.println("Back Right");
    Wire.beginTransmission(9); // Address of the slave Arduino (change accordingly)
    Wire.write("1"); // Send a trigger command to the slave
    Wire.endTransmission();
  }
  else if(distancebright<dist2 and distancebright>dist3)
  {

    Serial.println("Back Right");
    Wire.beginTransmission(9); // Address of the slave Arduino (change accordingly)
    Wire.write("2"); // Send a trigger command to the slave
    Wire.endTransmission();
    
  }
  else if(distancebright<dist4)
  {
    Serial.println("Back Right");
    steer.write(anglert);
    delay(100);
    steer.write(90);
    stopMotors();
    stopflag=1;
    Wire.beginTransmission(9); // Address of the slave Arduino (change accordingly)
    Wire.write("3"); // Send a trigger command to the slave
    Wire.endTransmission();
  }

}

void reverse()
{
  if(!revstopflag)
  moveBackward();

  float distanceback = readDistance(ultrasonicbk);
  float distancebleft = readDistance(ultrasonicbklt);
  float distancebright = readDistance(ultrasonicbkrt); 

  
  lcd.clear();
  lcd.setCursor(0, 0); // Set cursor to the first row
  lcd.print("Gear : R");

  //BACK -----------------------------------------------------------

  if(distanceback>dist1)
  {
    //LCD in CODE 1
    lcd.clear();
    lcd.setCursor(0, 0); // Set cursor to the first row
    lcd.print("Gear : R");
  
    lcd.setCursor(0, 1); // Set cursor to the second row
    lcd.print("Safe to Reverse");

    Serial.println("Back Ext");
    Wire.beginTransmission(9); // Address of the slave Arduino (change accordingly)
    Wire.write("10"); // Send a trigger command to the slave
    Wire.endTransmission();
    
  }
  else if(distanceback<dist1 && distanceback>=dist2)
  {
    Serial.println("Front");
    Wire.beginTransmission(9); // Address of the slave Arduino (change accordingly)
    Wire.write("1"); // Send a trigger command to the slave
    Wire.endTransmission(); 
  }
  else if(distanceback<dist3)
  {
    Serial.println("Back");
    Serial.println("Brakes Applied");
    stopMotors();
    revstopflag=1;
    Wire.beginTransmission(9); // Address of the slave Arduino (change accordingly)
    Wire.write("2"); // Send a trigger command to the slave
    Wire.endTransmission();
  }
  
//BACK LEFT -----------------------------------------------------------

  if(distancebleft>dist1)
  {
    //LCD in CODE 1
    lcd.clear();
    lcd.setCursor(0, 0); // Set cursor to the first row
    lcd.print("Gear : R");
  
    lcd.setCursor(0, 1); // Set cursor to the second row
    lcd.print("Safe to Reverse");

    Serial.println("Back Left Ext");
    Wire.beginTransmission(9); // Address of the slave Arduino (change accordingly)
    Wire.write("10"); // Send a trigger command to the slave
    Wire.endTransmission();
  }
  else if(distancebleft<dist1 && distancebleft>=dist2)
  {
    Serial.println("Back Left");
    Wire.beginTransmission(9); // Address of the slave Arduino (change accordingly)
    Wire.write("1"); // Send a trigger command to the slave
    Wire.endTransmission(); 
  }
  else if(distancebleft<dist3)
  {
    Serial.println("Back Left");
    Serial.println("Brakes Applied");
    stopMotors();
    revstopflag=1;
    Wire.beginTransmission(9); // Address of the slave Arduino (change accordingly)
    Wire.write("2"); // Send a trigger command to the slave
    Wire.endTransmission();
    
  }

  //BACK RIGHT -----------------------------------------------------------

  if(distancebright>dist1)
  {
    //LCD in CODE 1
    lcd.clear();
    lcd.setCursor(0, 0); // Set cursor to the first row
    lcd.print("Gear : R");
  
    lcd.setCursor(0, 1); // Set cursor to the second row
    lcd.print("Safe to Reverse");

    Serial.println("Back Right Ext");
    Wire.beginTransmission(9); // Address of the slave Arduino (change accordingly)
    Wire.write("10"); // Send a trigger command to the slave
    Wire.endTransmission();
  }
  else if(distancebright<dist1 && distancebright>=dist2)
  { 
    Serial.println("Back Right");
    Wire.beginTransmission(9); // Address of the slave Arduino (change accordingly)
    Wire.write("1"); // Send a trigger command to the slave
    Wire.endTransmission(); 
  }
  else if(distancebright<dist3)
  {

    Serial.println("Back Right");
    stopMotors();
    revstopflag=1;
    Wire.beginTransmission(9); // Address of the slave Arduino (change accordingly)
    Wire.write("2"); // Send a trigger command to the slave
    Wire.endTransmission();
    
  }

}

void stopMotors() 
{
  digitalWrite(motor1E, LOW);
  digitalWrite(motor2E, LOW);
}

// Function to start both motors
void startMotors() 
{
  int motorSpeed = map(cruiseSpeed, 0, 100, 0, 255); // Map 0-100 to 0-255
  analogWrite(motor1E, motorSpeed); // Set the speed using PWM
  analogWrite(motor2E, motorSpeed); // Set the speed using PWM
}
// Function to move the motors forward
void moveForward() 
{
  digitalWrite(motor1I1, HIGH);
  digitalWrite(motor1I2, LOW);
  digitalWrite(motor2I1, HIGH);
  digitalWrite(motor2I2, LOW);
  startMotors();
}

// Function to move the motors backward
void moveBackward() 
{
  digitalWrite(motor1I1, LOW);
  digitalWrite(motor1I2, HIGH);
  digitalWrite(motor2I1, LOW);
  digitalWrite(motor2I2, HIGH);
  startMotors();
}

void cruise()
{
  ACC = !ACC;
  if(ACC){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Cruise Enabled");


  lcd.setCursor(0, 1);
  lcd.print("Enter speed:");

  int tensDigit = 0;
  int onesDigit = 0;
  int digitPosition = 0; // 0 for tens digit, 1 for ones digit

  while (digitPosition < 2) {
    char key = keypad.getKey();
    
    if (key) {
      if (key >= '0' && key <= '9') {
        if (digitPosition == 0) {
          tensDigit = key - '0';
        } else if (digitPosition == 1) {
          onesDigit = key - '0';
        }
        digitPosition++;
        
        lcd.setCursor(12 + digitPosition, 1);
        lcd.print(key);
      }
    }
  }  
  delay(100);
  cruiseSpeed = tensDigit * 10 + onesDigit;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Cruise Speed:");
  lcd.setCursor(0, 1);
  lcd.print(cruiseSpeed);
  Serial.println(cruiseSpeed);
  }
  if(!ACC)
  {
  lcd.clear();
  lcd.setCursor(0, 0);
  cruiseSpeed = 0;
  lcd.print("Cruise Disabled");
  }
  
  delay(1000);
  cruisebool = false; // Display the cruise speed for 2 seconds before returning
}
void park()
{
  float distancebleft = readDistance(ultrasonicbklt);
  float distancebright = readDistance(ultrasonicbkrt);

  Serial.print("Distance from Sensor 1011 backleft pin: ");
  Serial.print(distancebleft, 2); // 2 decimal places
  Serial.println(" cm");

  Serial.print("Distance from Sensor 1213 backright pin: ");
  Serial.print(distancebright, 2); // 2 decimal places
  Serial.println(" cm");

  lcd.clear();
  lcd.setCursor(0, 0); // Set cursor to the first row
  lcd.print("Gear : P");
  delay(100);

  //BACK LEFT -----------------------------------------------------------

  if(distancebleft>dist1)
  {


    Serial.println("Back Left Ext");
    Wire.beginTransmission(9); // Address of the slave Arduino (change accordingly)
    Wire.write("6"); // Send a trigger command to the slave
    Wire.endTransmission();
  }
  else if(distancebleft<dist1 && distancebleft>=dist2)
  {
    Serial.println("Back Left1");
    Wire.beginTransmission(9); // Address of the slave Arduino (change accordingly)
    Wire.write("7"); // Send a trigger command to the slave
    Wire.endTransmission(); 
  }
  else if(distancebleft<dist3)
  {
    Serial.println("Back Left2");
    Wire.beginTransmission(9); // Address of the slave Arduino (change accordingly)
    Wire.write("8"); // Send a trigger command to the slave
    Wire.endTransmission();
    
  }

  //BACK RIGHT -----------------------------------------------------------

  if(distancebright>dist1)
  {


    Serial.println("Back Right Ext");
    /*Wire.beginTransmission(9); // Address of the slave Arduino (change accordingly)
    Wire.write("6"); // Send a trigger command to the slave
    Wire.endTransmission();*/
  }
  else if(distancebright<dist1 && distancebright>=dist2)
  { 
    Serial.println("Back Right1");
    Wire.beginTransmission(9); // Address of the slave Arduino (change accordingly)
    Wire.write("7"); // Send a trigger command to the slave
    Wire.endTransmission(); 
  }
  else if(distancebright<dist3)
  {

    Serial.println("Back Right2");
    Wire.beginTransmission(9); // Address of the slave Arduino (change accordingly)
    Wire.write("8"); // Send a trigger command to the slave
    Wire.endTransmission();
    
  } 

  stopflag=0;
  int rawValue = analogRead(voltageSensorPin);
  float voltage = rawValue * voltageSensitivity;

  lcd.clear();
  lcd.setCursor(0, 0); // Set cursor to the first row
  lcd.print("Gear : P");
  float batteryPercentage = map(voltage * 1000, emptyVoltage * 1000, fullVoltage * 1000, 0, 100);
  lcd.clear();
 
  lcd.setCursor(0, 1);
  lcd.print("");
  int numBars = map(batteryPercentage, 0, 100, 0, 10);
  if(batteryPercentage>0){
  lcd.print("[");
  for (int i = 0; i < 10; i++) 
  {
    lcd.print(i < numBars ? "=" : " ");
  }
  lcd.print("]");
  lcd.print(batteryPercentage, 1);
  lcd.print("%");
  Serial.println(batteryPercentage);
  delay(10);}
  else
  {
    lcd.setCursor(0, 1);
    lcd.print("Battery error");
  }
  
  analogWrite(motor1E, 225);
  analogWrite(motor2E, 225);
  analogWrite(motor1I1, 0);
  digitalWrite(motor1I2, LOW);
  analogWrite(motor2I1, 0);
  digitalWrite(motor2I2, LOW);

  
}


void adaptiveCruiseControl() {
  float distanceFront = readDistance(ultrasonicfr);

  if (distanceFront < ACC_DISTANCE_THRESHOLD) {
    // Calculate the new cruise speed based on the distance to the vehicle in front
    int newCruiseSpeed = map(distanceFront, 0, ACC_DISTANCE_THRESHOLD, 0, cruiseSpeed);

    // Ensure the new cruise speed is above the minimum speed
    if (newCruiseSpeed < MINIMUM_SPEED) {
      newCruiseSpeed = MINIMUM_SPEED;
    }

    // Adjust the cruise speed
    if (cruiseSpeed != newCruiseSpeed) {
      cruiseSpeed = newCruiseSpeed;
      Serial.print("Adaptive Cruise Control - Adjusted cruise speed to: ");
      Serial.println(cruiseSpeed);
    }
  }
}