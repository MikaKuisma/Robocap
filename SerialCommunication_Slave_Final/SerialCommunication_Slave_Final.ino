#include <Wire.h>

int trigPin = 4;
int echoPin = 5;
int trigPin2 = 8;
int echoPin2 = 9;

void setup() {
  
  Wire.begin(2);
  Wire.onRequest(requestEvent);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  
}

void loop()
{
  delay(100);
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent()
{
  long distance, distance2, duration, duration2;
  
  //First sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  
  //Second sensor
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = (duration2/2) / 29.1;
  
  String strDistance = String(distance);
  String strDistance2 = String(distance2);
  String combinedDist = strDistance + "." + strDistance2; //Concatenate distances for request reply

  char charArrayDist[8];
  combinedDist.toCharArray(charArrayDist, sizeof(charArrayDist)); //Convert distances to character array for delivery to master device
  
  Wire.write(charArrayDist);
}
