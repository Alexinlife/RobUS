#include <Arduino.h>
#include <LibRobus.h>

 void setup()
 {
   Serial.begin(9600);
   BoardInit();
   Serial.print("Depart du programme\n");

 }

/*
==========================
Boucle de controle PID
==========================
*/
 long PID(long PreviousTime,float TargetSpeed)
 {
   float pid = 0;
   float Kp = 0.001;
   float Ki = 1;
   float Erreur = 0;
   float sec = 7000;
   unsigned int dT = 100;
   long CurrentTime = millis();
   unsigned int TimeSample = CurrentTime-PreviousTime;

  if (TimeSample>=dT) //dT est une constante de temps systeme definit plus haut
  {

    int encodeur_0 = ENCODER_Read(0);
    int encodeur_1 = ENCODER_Read(1);
    Erreur = encodeur_0 - encodeur_1;
    Serial.println(Erreur);
    pid = (Erreur * Kp) + ((Erreur*Ki)/sec) + TargetSpeed;
    //Serial.println(pid); 
    PreviousTime=CurrentTime;
    MOTOR_SetSpeed(1,pid);
 
  } 
  return PreviousTime;
 }


     void Gauche(int32_t AngleG)
     {
       MOTOR_SetSpeed(0, 0);
       MOTOR_SetSpeed(1, 0.5);
       uint32_t dm = ((120 * AngleG) / 360);
       Serial.print(dm,DEC);
       long int cycle = (3200L*dm)/24;
       Serial.print(cycle, DEC);
       
       bool i = true;
       while(i)
       {
        if(ENCODER_Read(1) >= cycle)
        {
          MOTOR_SetSpeed(0, 0);
          MOTOR_SetSpeed(1, 0);
          ENCODER_Reset(0);
          ENCODER_Reset(1);
          i = false;
        }
       }
     }
     void Droite(int32_t AngleD)
     {
       MOTOR_SetSpeed(0, 0.5);
       MOTOR_SetSpeed(1, 0);
       uint32_t dm = ((120 * AngleD) / 360);
       Serial.print(dm,DEC);
       long int cycle = (3200L*dm)/24;
       Serial.print(cycle, DEC);

       bool i = true;
       while(i)
       {
        if(ENCODER_Read(0) >= cycle)
        {
          MOTOR_SetSpeed(0, 0);
          MOTOR_SetSpeed(1, 0);
          ENCODER_Reset(0);
          ENCODER_Reset(1);
          i = false;
        }
       }
     }
     
     void Avancer(int32_t DistanceA)
     {
       ENCODER_Reset(0);
       ENCODER_Reset(1);
       float PreviousTime = 0;
       float speed0 = 0;
       float speed1 = 0.35;
       
       /*for(float i = 0; i < speed0; i += 0.01){
        delay(5);
        MOTOR_SetSpeed(0, i);
        MOTOR_SetSpeed(1, i);
       }*/
       


       bool i = true;
       
       while(i)
       {
         if(speed0 <= speed1){
           speed0 += .01;
           delay(5);
           MOTOR_SetSpeed(0, speed0);
           MOTOR_SetSpeed(1, speed0);
         }
         
         
         PreviousTime = PID(PreviousTime, speed0);
        if((ENCODER_Read(0) >= DistanceA) && (ENCODER_Read(1) >= DistanceA))
        {
          MOTOR_SetSpeed(0, 0);
          MOTOR_SetSpeed(1, 0);
          ENCODER_Reset(0);
          ENCODER_Reset(1);
          i = false;
        }
       }
     }


     void Reculer(int32_t DistanceR)
     {   
       MOTOR_SetSpeed(0,-0.34);
       MOTOR_SetSpeed(1,-0.34);
       bool i = true;
       while(i)
       {
        if((ENCODER_Read(0) <= DistanceR) && (ENCODER_Read(1) <= DistanceR))
        {
          MOTOR_SetSpeed(0, 0);
          MOTOR_SetSpeed(1, 0);
          ENCODER_Reset(0);
          ENCODER_Reset(1);
          i = false;
        }
       }
     }

     void uTurn(void)
     {
       MOTOR_SetSpeed(0, .3);
       MOTOR_SetSpeed(1,-.3);
       bool i = true;
       int F0 = 0;
       int F1 = 0;
       while(i)
       {
        if(ENCODER_Read(0) >= 3985)
        {
          MOTOR_SetSpeed(0,0);
          F0 = 1;
        }
        if(ENCODER_Read(1) <= -3985)
        {
          MOTOR_SetSpeed(1,0);
          F1 = 1;
        }
        if ((F0 == 1) && (F1 == 1))
        {
          i = false;
        }
       }
      }

     void Arreter(void)
     {
       MOTOR_SetSpeed(0, 0);
       MOTOR_SetSpeed(1, 0);
     }



     


 void loop ()
 {
   Serial.print("Loop\n");


   while(1)
   {
     //Avancer(45000);
     //delay(5000);

   }
 }