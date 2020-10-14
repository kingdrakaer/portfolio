#include <Brain.h>

Brain brain(Serial); //set up brain parser

const int focus = 40; //set the threshold for the Mindflex
const int strength = 700; //set the threshold for the MyoWare Muscle Sensors
const int analogInPin1 = A0; //MyoWare Muscle Sensor input pin #1
const int analogInPin2 = A1; //MyoWare Muscle Sensor input pin #2
const int analogInPin3 = A2; //MyoWare Muscle Sensor input pin #3
const int analogInPin4 = A3; //MyoWare Muscle Sensor input pin #4
const int led1 = 2;
const int led2 = 3;
const int led3 = 4;
const int led4 = 5;
const int led5 = 6;
int sensorValue1 = 0; //Set sensor variable integers
int sensorValue2 = 0;
int sensorValue3 = 0;
int sensorValue4 = 0;
int attention = 0; 


int mindflex = 0;



void setup() 
{
pinMode(mindflex, INPUT); //set pin 0 as input
pinMode(led1,OUTPUT);
pinMode(led2,OUTPUT);
pinMode(led3,OUTPUT);
pinMode(led4,OUTPUT);
pinMode(led5,OUTPUT);
 Serial.begin(9600); //open serial port
}

void loop() 
{ //read input on pin A0
  sensorValue1 = analogRead(A0); //muscle value from emg sensor #1
  sensorValue2 = analogRead(A1); //muscle value from emg sensor #2
  sensorValue3 = analogRead(A2); //muscle value from emg sensor #3
  sensorValue4 = analogRead(A3); //muscle value from emg sensor #4
  if (brain.update()){
    //Serial.println(brain.readErrors());
    //Serial.println(brain.readCSV());
    attention = brain.readAttention(); //attention value from mindflex
    
  } //perform outputs based on binary inputs (this is essentially the truth table)
  if ((attention > focus)) {
  digitalWrite(led1,HIGH);
} else if ((sensorValue1 > strength) && (sensorValue2 < strength) && (sensorValue3 < strength) && (sensorValue4 < strength)) { //turns on led if threshold is met
  digitalWrite(led2,HIGH);
} else if ((sensorValue1 < strength) && (sensorValue2 > strength) && (sensorValue3 < strength) && (sensorValue4 < strength)) {
  digitalWrite(led3,HIGH);
} else if ((sensorValue1 < strength) && (sensorValue2 < strength) && (sensorValue3 > strength) && (sensorValue4 < strength)) {
  digitalWrite(led4,HIGH);
} else if ((sensorValue1 < strength) && (sensorValue2 < strength) && (sensorValue3 < strength) && (sensorValue4 > strength)) {
  digitalWrite(led5,HIGH);
} else if ((sensorValue1 < strength) && (sensorValue2 < strength) && (sensorValue3 < strength) && (sensorValue4 < strength)) {
  digitalWrite(led1,LOW);
  digitalWrite(led2,LOW);
  digitalWrite(led3,LOW);
  digitalWrite(led4,LOW);
  digitalWrite(led5,LOW);
}
delay(10);
}
