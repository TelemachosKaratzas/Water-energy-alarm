/********************************************************************/
// First we include the libraries
#include <OneWire.h> 
#include <DallasTemperature.h>
#include "VirtuinoBluetooth.h"                           // Include VirtuinoBluetooth library to your code

// Code to use SoftwareSerial
#include <SoftwareSerial.h>                              //  Disable this line if you want to use hardware serial 
SoftwareSerial bluetoothSerial =  SoftwareSerial(4,5);   // arduino RX pin=2  arduino TX pin=3    connect the arduino RX pin to bluetooth module TX pin   -  connect the arduino TX pin to bluetooth module RX pin.  Disable this line if you want to use hardware serial 
VirtuinoBluetooth virtuino(bluetoothSerial);       // Set SoftwareSerial baud rate.  -  Disable this line if you want to use hardware serial

/********************************************************************/
// Data wire is plugged into pin 2 on the Arduino 
#define ONE_WIRE_BUS 3 
/********************************************************************/
// Setup a oneWire instance to communicate with any OneWire devices  
// (not just Maxim/Dallas temperature ICs) 
OneWire oneWire(ONE_WIRE_BUS); 
/********************************************************************/
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);
/********************************************************************/ 


double halleffect;
bool var1;
bool var2;
int period = 500;
unsigned long time_now = 0;
bool reset_bt;

void setup() 
{ virtuino.DEBUG=true;               // set this value TRUE to enable the serial monitor status
 
  // Start up the library                                   
bluetoothSerial.begin(9600);
sensors.begin(); 

    halleffect = 0;
    
    pinMode(2,INPUT);
    pinMode(0,OUTPUT);
    virtuino.vPinMode(3,INPUT);
} 
void loop() 
{   var1 = digitalRead(2);
    if (var1 > var2){halleffect += 1;} 
    var2 = var1; 
    virtuino.run();
    reset_bt=virtuino.vMemoryRead(3);
    if (reset_bt)
    {halleffect = 0;}
    if (halleffect>2000)
    {digitalWrite(0,1);}
    else
    {digitalWrite(0,0);}
    if(millis() > time_now + period){
    time_now = millis();
    sensors.requestTemperatures(); // Send the command to get temperature readings 

    virtuino.vMemoryWrite(1,(halleffect / 470));
    virtuino.vMemoryWrite(2,sensors.getTempCByIndex(0));
    

}}
