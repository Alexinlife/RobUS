#include <Arduino.h>
#include <LibRobus.h>

void setup()
{
  Serial.begin(9600);
  BoardInit();
}

/*
==========================
Boucle de controle PID
==========================
*/
long PID(long PreviousTime, float TargetSpeed)
{
  float pid = 0;
  float Kp = 0.001;
  float Ki = 1;
  float Erreur = 0;
  float sec = 7000;
  unsigned int dT = 100;
  long CurrentTime = millis();
  unsigned int TimeSample = CurrentTime - PreviousTime;

  if (TimeSample >= dT) //dT est une constante de temps systeme definit plus haut
  {

    int encodeur_0 = ENCODER_Read(0);
    int encodeur_1 = ENCODER_Read(1);
    Erreur = encodeur_0 - encodeur_1;
    //Serial.println(Erreur);
    pid = (Erreur * Kp) + ((Erreur * Ki) / sec) + TargetSpeed;
    //Serial.println(pid);
    PreviousTime = CurrentTime;
    MOTOR_SetSpeed(1, pid);
  }
  return PreviousTime;
}

void Gauche(int32_t AngleG)
{
  ENCODER_Reset(0);
  ENCODER_Reset(1);
  AngleG = -AngleG;
  MOTOR_SetSpeed(0, 0);
  MOTOR_SetSpeed(1, 0.5);
  uint32_t dm = ((120 * AngleG) / 360);
  Serial.print(dm, DEC);
  long int cycle = (3200L * dm) / 24;
  Serial.print(cycle, DEC);

  bool i = true;
  while (i)
  {
    if (ENCODER_Read(1) >= cycle)
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
  ENCODER_Reset(0);
  ENCODER_Reset(1);
  MOTOR_SetSpeed(0, 0.5);
  MOTOR_SetSpeed(1, 0);
  uint32_t dm = ((120 * AngleD) / 360);
  Serial.print(dm, DEC);
  long int cycle = (3200L * dm) / 24;
  Serial.print(cycle, DEC);

  bool i = true;
  while (i)
  {
    if (ENCODER_Read(0) >= cycle)
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
  DistanceA = DistanceA * 3200L / 24;

  /*for(float i = 0; i < speed0; i += 0.01){
        delay(5);
        MOTOR_SetSpeed(0, i);
        MOTOR_SetSpeed(1, i);
       }*/

  bool i = true;

  while (i)
  {
    if (speed0 <= speed1)
    {
      speed0 += .01;
      delay(5);
      MOTOR_SetSpeed(0, speed0);
      MOTOR_SetSpeed(1, speed0);
    }

    PreviousTime = PID(PreviousTime, speed0);
    if ((ENCODER_Read(0) >= DistanceA) && (ENCODER_Read(1) >= DistanceA))
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
  MOTOR_SetSpeed(0, -0.34);
  MOTOR_SetSpeed(1, -0.34);
  bool i = true;
  while (i)
  {
    if ((ENCODER_Read(0) <= DistanceR) && (ENCODER_Read(1) <= DistanceR))
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
  ENCODER_Reset(0);
  ENCODER_Reset(1);
  MOTOR_SetSpeed(0, .3);
  MOTOR_SetSpeed(1, -.3);
  bool i = true;
  int F0 = 0;
  int F1 = 0;
  while (i)
  {
    if (ENCODER_Read(0) >= 3985)
    {
      MOTOR_SetSpeed(0, 0);
      F0 = 1;
    }
    if (ENCODER_Read(1) <= -3985)
    {
      MOTOR_SetSpeed(1, 0);
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

/*int32_t * InverserTableau(int32_t * mouvements)
{
  int32_t * inverse[9][2];

  for (int i = 0; i < 9; i++) {
    inverse[i][0] = mouvements[8-i][0];
    inverse[i][1] = -mouvements[8-i][1];
  }
  return inverse;
}*/

void Sequence(int32_t mouvements[9][2])
{

  for (int i = 0; i < 9; i++)
  {

    // Valeur de déplacement à la position i
    if (mouvements[i][0] != 0)
    {

      if (mouvements[i][0] < 0)
      {
        Reculer((int32_t)mouvements[i][0]);
      }
      else
      {
        Avancer((int32_t)mouvements[i][0]);
      }
      delay(50);
    }
    // Valeur de rotation à la position i
    if (mouvements[i][1] != 0)
    {

      if (mouvements[i][1] < 0)
      {
        Gauche((int32_t)mouvements[i][1]);
      }
      else
      {
        Droite((int32_t)mouvements[i][1]);
      }
      delay(50);
    }
  }
}

void loop()
{
  int32_t mouvements[9 /* Nombre de mouvements */][2] = {
      {220, -90},
      {25, 90},
      {30, 90},
      {40, -90},
      {10, 45},
      {30, -85},
      {55, 45},
      {10, 15},
      {120, 0}};

  int32_t inverse[9 /* Nombre de mouvements */][2] = {
      {120, 0},
      {10, -15},
      {55, -45},
      {30, 85},
      {10, -45},
      {40, 90},
      {30, -90},
      {25, -90},
      {220, 90}};

  Sequence(mouvements);
  uTurn();
  Sequence(inverse);
  while (1)
  {
    Arreter();
  }
  /*while (1)
  {
    Avancer(100);
    delay(2000);
    Reculer(-3200);
    delay(40);
    Gauche(-90);
    delay(40);
    Droite(180);
    delay(40);
    uTurn();
    delay(40);
    
  }*/
}