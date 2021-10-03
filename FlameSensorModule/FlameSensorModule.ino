// lowest and highest sensor readings:
const int sensorMin = 0;     // sensor minimum
const int sensorMax = 1024;  // sensor maximum

void setup() {
  // initialize serial communication @ 9600 baud:
  Serial.begin(9600);  
}
void loop() {
  // read the sensor on analog A0:
  int sensorReading = analogRead(A0);
  // map the sensor range (four options):
  // ex: 'long int map(long int, long int, long int, long int, long int)'
  int range = map(sensorReading, sensorMin, sensorMax, 0, 3);

  int sensorReading1 = analogRead(A1);
  // map the sensor range (four options):
  // ex: 'long int map(long int, long int, long int, long int, long int)'
  int range1 = map(sensorReading1, sensorMin, sensorMax, 0, 3);
  
  int sensorReading2 = analogRead(A2);
  // map the sensor range (four options):
  // ex: 'long int map(long int, long int, long int, long int, long int)'
  int range2 = map(sensorReading2, sensorMin, sensorMax, 0, 3);
  
  // range value:
  switch (range) {
  case 0:    // A fire closer than 1.5 feet away.
    Serial.println("** Close Fire center **");
    break;
  case 1:    // A fire between 1-3 feet away.
    Serial.println("** Distant Fire center **");
    break;

  }
  switch (range1) {
  case 0:    // A fire closer than 1.5 feet away.
    Serial.println("** Close Fire from the left **");
    break;
  case 1:    // A fire between 1-3 feet away.
    Serial.println("** Distant Fire from the left **");
    break;

  }
  switch (range2){
  case 0:    // A fire closer than 1.5 feet away.
    Serial.println("** Close Fire to the right **");
    break;
  case 1:    // A fire between 1-3 feet away.
    Serial.println("** Distant Fire from the right **");
    break;

  }
  delay(500);  // delay between reads
}
