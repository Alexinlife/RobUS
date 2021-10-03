#include <Arduino.h>
#include <LibRobus.h>

 void setup()
 {
   Serial.begin(9600);
   BoardInit();
   Serial.print("Depart du programme\n");

 }
     void Gauche(int32_t AngleG)
     {
       MOTOR_SetSpeed(0, 0);
       MOTOR_SetSpeed(1, 0.5);
       int dm = (120 * AngleG) / 360;
       int cycle = (dm * 3200) / 24;
       
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
       MOTOR_SetSpeed(0, 0.5);
       MOTOR_SetSpeed(1, 0.484);
       bool i = true;
       while(i)
       {
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
     Droite(180);
     delay(4000);
   }
 }