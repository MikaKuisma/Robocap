#include <Wire.h>

int carCounter = 0;
String sensorFirst = ""; // sensor that was triggered first
int entranceWidth = 4; // Distance between sensors. To be modified.
int objectWidth = 0; // Width of the object to be calculated
int maxCapacity = 3; // Maximum capacity of the garage. To be modified.
int minCapacity = 0; // Minimum capacity of the garage

void setup()
{
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
}

void loop()
{
  String bothDistances; // received character data from slave device
  
  Wire.requestFrom(2, 8);  
  while(Wire.available())
  { 
    char received = Wire.read();
    bothDistances += received; // concatenate received characters to a string
  }
  int index = bothDistances.indexOf('.');
  String sensorDistance1 = bothDistances.substring(0, index);
  String sensorDistance2 = bothDistances.substring(index + 1, bothDistances.length() - 1);
  
  int distance1 = sensorDistance1.toInt(); // convert substring 1 to integer
  int distance2 = sensorDistance2.toInt(); // convert substring 2 to integer
  objectWidth = entranceWidth - distance1 - distance2; // calculate width of the object vehicle
  
  
  
  if (distance1 >= 2 && distance1 <= 15 && (distance2 < 2 || distance2 > 15))
  {
    sensorFirst = "s1";
    String s = String(distance1);
    Serial.println("Sensor 1: " + s + " cm");
  }
  else if (distance2 >= 2 && distance2 <= 15 && (distance1 < 2 || distance1 > 15))
  {
    sensorFirst = "s2";
    String s = String(distance2);
    Serial.println("Sensor 2: " + s + " cm");
  }
  else if (distance1 >= 2 && distance1 <= 15 && distance2 >= 2 && distance2 <= 15)
  {
    // checking of width of the object commented out. Value after ">" to be modified.
    if (sensorFirst == "s1" /*&& objectWidth > 2*/ && carCounter < maxCapacity)
    {
      carCounter++; // increase the amount of cars in garage by 1
      sensorFirst = ""; // reset directionchecker
    } else if (sensorFirst == "s2" /*&& objectWidth > 2*/ && carCounter > minCapacity)
    {
      carCounter--; // decrease the amount of cars in garage by 1
      sensorFirst = ""; // reset directionchecker
    }
    String s = String(distance1);
    String s2 = String(distance2);
    String s3 = String(carCounter);
    Serial.println("Sensor 1: " + s + " cm" " | " + "Sensor 2: " + s2 + " cm " + "| Vehicle count: " + s3);
    delay(750);
  }
  else
  {
    Serial.println("Out of range");
  }

  if (carCounter == maxCapacity)
  {
    digitalWrite(13, HIGH);
  }
  else 
  {
    digitalWrite(13, LOW);
  }
  delay(100);
}
