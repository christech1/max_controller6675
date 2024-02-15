/* 
#include <AccelStepper.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "max6675.h"
//Robojax.com heater/cooler with MAX6675 Thermocoupler
#define STEP_PIN 2
#define DIR_PIN 3
#define POT_PIN A0
int thermoCLK = 12;
int thermoCS = 11;
int thermoDO = 10;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);
LiquidCrystal_I2C lcd(0x27,16,2);
AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);
const int relayPin =4;
const int relayON = LOW;// do not change
const int relayOFF = HIGH; //do not chage 
int relayState = relayOFF;//initial state of relay

const int TEMPERATURE_UNIT =1;//1=Celsius, 2=Fahrenheit, 3=Keliven
const float START_TEMPERATURE = 190;//unit above
const float STOP_TEMPERATURE = 220;//unit above
const int CONTROL_TYPE = 1;// 1= heater, 2=cooler
float temperature;
unsigned long previousMillis1 = 0;
unsigned long interval1 = 1000; 
unsigned long previousMillis2 = 0;
unsigned long interval2 = 500; 
int speed;

void setup() {
  //Robojax.com heater/cooler with MAX6675 Thermocoupler
  Serial.begin(9600);
   stepper.setMaxSpeed(1000);
  stepper.setAcceleration(500);
  lcd.init();
  lcd.backlight();
  Serial.println("MAX6675 test with relay");
  // use Arduino pins 
   pinMode(POT_PIN, INPUT);
  pinMode(relayPin, OUTPUT);//pin for relay
  digitalWrite(relayPin, relayState);

  // wait for MAX chip to stabilize
  delay(500);
//Robojax.com heater/cooler with MAX6675 Thermocoupler  
}

void loop() {
   
    
    if (millis() - previousMillis1 >= interval1) {
    previousMillis1 = millis();
    tempp();
  }

  if (millis() - previousMillis2 >= interval2) {
    previousMillis2 = millis();
    motor();
  }

  
 
}//loop

void loadControl()
{
//Robojax.com heater/cooler with MAX6675 Thermocoupler  
     // Serial.print("Start: ");
     // Serial.print(START_TEMPERATURE);
     // Serial.print(" Stop: ");
      //Serial.println(STOP_TEMPERATURE);      
  if(CONTROL_TYPE ==1)
  {
    if(START_TEMPERATURE >= temperature && STOP_TEMPERATURE >=temperature)
    {
      relayControl(relayON);
    }
    if(STOP_TEMPERATURE <=temperature)
    {
      relayControl(relayOFF);
    }
  }else{
    if(START_TEMPERATURE >= temperature && STOP_TEMPERATURE >=temperature)
    {
      relayControl(relayOFF);
    }
    if(STOP_TEMPERATURE <=temperature)
    {
      relayControl(relayON);
    }
  }
    
//Robojax.com heater/cooler with MAX6675 Thermocoupler
}//loadControl()


void relayControl(int state)
{
  //Robojax.com heater/cooler with MAX6675 Thermocoupler
  if(state ==relayON)
  {
    digitalWrite(relayPin, relayON);
    Serial.println("Relay ON");   
  }else{
   digitalWrite(relayPin, relayOFF);    
    Serial.println("Relay OFF");   
  }
  //Robojax.com heater/cooler with MAX6675 Thermocoupler  

}//relayControl()



void readTemperature()
{
 //Robojax.com heater/cooler with MAX6675 Thermocoupler 

  if(TEMPERATURE_UNIT ==2)
   {
   temperature = thermocouple.readFahrenheit();//convert to Fahrenheit 
   }else if(TEMPERATURE_UNIT ==3)
   {
    temperature = thermocouple.readCelsius() + 273.15;//convert to Kelvin
   }else{
    temperature = thermocouple.readCelsius();// return Celsius
   }    
 //Robojax.com heater/cooler with MAX6675 Thermocoupler 
}// readTemperature()


void printTemperature()
{
//Robojax.com heater/cooler with MAX6675 Thermocoupler
stepper.setSpeed(speed);
    stepper.runSpeed();
   Serial.print(temperature);
   if (temperature )
   lcd.setCursor(0,0);
   lcd.print(temperature);
   lcd.setCursor(1,1);
   lcd.print("temperature");
    printDegree();    
  if(TEMPERATURE_UNIT ==2)
   {
     Serial.print("F");
    }else if(TEMPERATURE_UNIT ==3)
   {
     Serial.print("K");
   }else{
     Serial.print("C");
   }    
  Serial.println();
//Robojax.com heater/cooler with MAX6675 Thermocoupler  
}
//printTemperature()

void motor(){
    int potValue = analogRead(POT_PIN);
     speed = map(potValue, 0, 1023, 0, 1000);
    stepper.setSpeed(speed);
    stepper.runSpeed();
}

void tempp (){
   readTemperature();
   printTemperature();
   loadControl(); 
   if(temperature >=89.5)
   {
    ///
   }
  delay(1000);
}


void printDegree()
{
    Serial.print("\xC2"); 
    Serial.print("\xB0");  
}



*/



#include <AccelStepper.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "max6675.h"

#define STEP_PIN 2
#define DIR_PIN 3
#define POT_PIN A0

int thermoCLK = 12;
int thermoCS = 11;
int thermoDO = 10;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);
LiquidCrystal_I2C lcd(0x27, 16, 2);
AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);

const int relayPin = 4;
const int relayON = LOW;
const int relayOFF = HIGH;
int relayState = relayOFF;

const int TEMPERATURE_UNIT = 1;
const float START_TEMPERATURE = 20;
const float STOP_TEMPERATURE = 230;
const int CONTROL_TYPE = 1;
float temperature;

unsigned long previousMillisTemp = 0;
unsigned long intervalTemp = 1000; // Temperature reading interval

void setup() {
  Serial.begin(9600);
  stepper.setMaxSpeed(1000);
  stepper.setAcceleration(500);
  lcd.init();
  lcd.backlight();
  pinMode(POT_PIN, INPUT);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, relayState);
}

void loop() {
  // Perform temperature reading and control every intervalTemp milliseconds
  unsigned long currentMillisTemp = millis();
  if (currentMillisTemp - previousMillisTemp >= intervalTemp) {
    previousMillisTemp = currentMillisTemp;
    readTemperature();
    printTemperature();
    loadControl();
  }

  // Stepper motor control
  int potValue = analogRead(POT_PIN);
  int speed = map(potValue, 0, 1023, 0, 1000);
  stepper.setSpeed(speed);
  stepper.runSpeed();
}

void loadControl() {
  if (CONTROL_TYPE == 1) {
    if (temperature >= START_TEMPERATURE && temperature <= STOP_TEMPERATURE) {
      relayControl(relayON);
    } else {
      relayControl(relayOFF);
    }
  } else {
    if (temperature >= START_TEMPERATURE && temperature <= STOP_TEMPERATURE) {
      relayControl(relayOFF);
    } else {
      relayControl(relayON);
    }
  }
}

void relayControl(int state) {
  if (state == relayON) {
    digitalWrite(relayPin, relayON);
    Serial.println("Relay ON");
  } else {
    digitalWrite(relayPin, relayOFF);
    Serial.println("Relay OFF");
  }
}

void readTemperature() {
  if (TEMPERATURE_UNIT == 2) {
    temperature = thermocouple.readFahrenheit();
  } else if (TEMPERATURE_UNIT == 3) {
    temperature = thermocouple.readCelsius() + 273.15;
  } else {
    temperature = thermocouple.readCelsius();
  }
}

void printTemperature() {
  Serial.print(temperature);
  lcd.setCursor(0, 0);
  lcd.print(temperature);
  lcd.setCursor(0, 1);
  lcd.print("Temperature");

  if (TEMPERATURE_UNIT == 2) {
    Serial.print("F");
  } else if (TEMPERATURE_UNIT == 3) {
    Serial.print("K");
  } else {
    Serial.print("C");
  }
  Serial.println();
}
