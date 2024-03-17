//add case 5 for breaks(reverse)
#include <Wire.h>
#include <LiquidCrystal.h>
const int ldrPin1 = A8;     // Connect LDR to analog pin A0
const int ldrPin2 = A7;
const int ledPin1 = 52;      // Connect LED to digital pin 9
const int ledPin2 = 53;
const int ledPinindi = 12;
const int ledPintail = 11;
const int threshold = 12;
const int threshold2 = 18;
const int buzzerPin = 13; 

LiquidCrystal lcd(22, 23, 24, 25, 26, 27);

bool commandR = false;
String receivedCommand = "";

void setup() 
{
  Wire.begin(9); // Initialize I2C communication as slave with address 9
  Wire.onReceive(receiveEvent); // Set up a function to receive data
  Serial.begin(9600); // Initialize serial communication for debugging
  lcd.begin(16,2);
  lcd.clear();
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPinindi, OUTPUT);
  pinMode(ledPintail, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  
// Initialize serial communication at 9600 baud
  // You might need to calibrate the threshold value based o
}

void loop() {
  // Your slave code (if any) goes here
  int ldrValue1 = analogRead(ldrPin1); // Read the LDR sensor
  int ldrValue2 = analogRead(ldrPin2);
  //Serial.print("LDR Value: ");
  //Serial.println(ldrValue1); // Print LDR value to Serial Monitor
  Serial.println(ldrValue1); 

  if (ldrValue1 < threshold) {
    digitalWrite(ledPin1, HIGH); // Turn on the LED if light level is below threshold
  } else {
    digitalWrite(ledPin1, LOW); // Turn off the LED if light level is above threshold
  }

  if (ldrValue2 < threshold2) {
    digitalWrite(ledPin2, HIGH); // Turn on the LED if light level is below threshold
  } else {
    digitalWrite(ledPin2, LOW); // Turn off the LED if light level is above threshold
  }

  if(commandR)
  {
    handleCommand();
    commandR = false;
  }

  delay(10);
  
}


void handleCommand() {
  if (receivedCommand == "4") {
    // ...
    Serial.println("Safe");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Drive");
    lcd.setCursor(0,1);
    lcd.print("->....<-");
    delay(100);
  } else if (receivedCommand == "1") {
    // ...
    Serial.println("moderate");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Caution !!");
    lcd.setCursor(0,1);
    lcd.print("->...<-");
    delay(100);
    for (int i = 0; i < 3; i++) 
    { // Will produce 3 beeps
      digitalWrite(ledPintail, HIGH);
      digitalWrite(ledPinindi, HIGH);
      digitalWrite(LED_BUILTIN, HIGH); // Turn on the warning buzzer
      delay(60); // Beep duration (adjust the delay value for the desired beep duration)
      digitalWrite(ledPintail, LOW);
      digitalWrite(ledPinindi, LOW);
      digitalWrite(LED_BUILTIN, LOW); // Turn off the warning buzzer
      delay(35); // Delay between beeps (adjust the delay value for the desired pause between beeps)
    }
  } else if (receivedCommand == "2") {
    // ...
    Serial.println("close");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Brakes Applied !");
    lcd.setCursor(0,1);
    lcd.print("->..<-");
    delay(100);
    for (int i = 0; i < 5; i++) 
    { // Will produce 5 beeps
      digitalWrite(ledPintail, HIGH);
      digitalWrite(ledPinindi, HIGH);
      digitalWrite(LED_BUILTIN, HIGH); // Turn on the warning buzzer
      delay(43); // Beep duration (adjust the delay value for the desired beep duration)
      digitalWrite(ledPintail, LOW);
      digitalWrite(ledPinindi, LOW);
      digitalWrite(LED_BUILTIN, LOW); // Turn off the warning buzzer
      delay(20); // Delay between beeps (adjust the delay value for the desired pause between beeps)
    }
  } else if (receivedCommand == "3") {
    // ...
    Serial.println("panic");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("AEM Active");
    lcd.setCursor(0,1);
    lcd.print("->.<-");
    delay(100);
    for (int i = 0; i < 1; i++) 
    { // Will produce 1 beep
      digitalWrite(ledPintail, HIGH);
      digitalWrite(ledPinindi, HIGH);
      digitalWrite(LED_BUILTIN, HIGH); // Turn on the warning buzzer
      delay(2000); // Beep duration (adjust the delay value for the desired beep duration)
      digitalWrite(ledPintail, LOW);
      digitalWrite(ledPinindi, LOW);
      digitalWrite(LED_BUILTIN, LOW); // Turn off the warning buzzer
      delay(50); // Delay between beeps (adjust the delay value for the desired pause between beeps)
    } 
  } else if (receivedCommand == "5") {
    // ...
    Serial.println("breaks applied");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Breaks Applied");
    lcd.setCursor(0,1);
    lcd.print("->.<-");
    delay(100);
    digitalWrite(ledPintail, HIGH);
    digitalWrite(ledPinindi, HIGH);
    digitalWrite(LED_BUILTIN, HIGH); // Turn on the warning buzzer
    delay(100); // Beep duration (adjust the delay value for the desired beep duration)
    digitalWrite(ledPintail, LOW);
    digitalWrite(ledPinindi, LOW);
    digitalWrite(LED_BUILTIN, LOW); // Turn off the warning buzzer
  } else if (receivedCommand == "10") {
    // ...
    Serial.println("Reverse Clear");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Reverse");
    lcd.setCursor(0,1);
    lcd.print("->....<-");
    delay(100);
  } else if (receivedCommand == "6") {
    // ...
    Serial.println("sew warn sf");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Check Traffic");
    lcd.setCursor(0,1);
    lcd.print("Safe to Exit");
    delay(100);
  } else if (receivedCommand == "7") {
    // ...
    Serial.println("sew warn 2");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Cross Traffic !!");
    lcd.setCursor(0,1);
    lcd.print("SEW Level 2");
    delay(100);
  } else if (receivedCommand == "8") {
    // ...
    Serial.println("sew warn 3");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Cross Traffic !!");
    lcd.setCursor(0,1);
    lcd.print("SEW Level 3");
    delay(100);
  } else if (receivedCommand == "9") {
    // ...
    Serial.println("Initializing...");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("System Active");
    lcd.setCursor(0,1);
    lcd.print("EV On");
    delay(100);
    for (int i = 0; i < 2; i++) 
    { 
      //digitalWrite(ledPin1, HIGH);
      //digitalWrite(ledPin2, HIGH);
      digitalWrite(ledPinindi, HIGH);
      digitalWrite(LED_BUILTIN, HIGH); // Turn on the warning buzzer
      delay(200); // Beep duration (adjust the delay value for the desired beep duration)
      //digitalWrite(ledPin1, LOW);
      //digitalWrite(ledPin2, LOW);
      digitalWrite(ledPinindi, LOW);
      digitalWrite(LED_BUILTIN, LOW); // Turn off the warning buzzer
      delay(200); // Delay between beeps (adjust the delay value for the desired pause between beeps)
    }
  }
}


void receiveEvent(int bytes) 
{
  receivedCommand = "";
  while (Wire.available()) {
    char c = Wire.read(); // Read the incoming data from the master
    receivedCommand += c;
  }
  commandR = true;
}