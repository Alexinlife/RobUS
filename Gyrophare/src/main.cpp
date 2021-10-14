#include <Arduino.h>
#define LED1 12
#define LED2 11
#define LED3 10
#define LED4 9

int Alarme = 0;

// the setup function runs once when you press reset or power the board
void setup() 
{
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(9600);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);

  int mystr[10]; //Initialized variable to store recieved data
}
int ReceiveSerialData(void)
{
  int Level = 1;
  
  return Level;
}

 void allumerLED(void)
 {
   digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
   digitalWrite(11, LOW);   
   digitalWrite(10, LOW);   
   digitalWrite(9, LOW);   
   delay(100); 
   digitalWrite(12, LOW);   // turn the LED on (HIGH is the voltage level)
   digitalWrite(11, HIGH);   
   digitalWrite(10, LOW);   
   digitalWrite(9, LOW);  
   delay(100);                       // wait for a second
   digitalWrite(12, LOW);   // turn the LED on (HIGH is the voltage level)
   digitalWrite(11, LOW);   
   digitalWrite(10, HIGH);   
   digitalWrite(9, LOW); 
   delay(100);  
   digitalWrite(12, LOW);   // turn the LED on (HIGH is the voltage level)
   digitalWrite(11, LOW);   
   digitalWrite(10, LOW);   
   digitalWrite(9, HIGH); 
   delay(100);
 }

 void loop () 
{
Alarme = ReceiveSerialData();
  
  if(Alarme == 1)
 {
   allumerLED();
 }
 else
 {
  Alarme = 0;
 }
}