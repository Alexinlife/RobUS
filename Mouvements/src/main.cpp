#include <Arduino.h>
#include <LibRobus.h>

void setup()
{
  BoardInit();
}

long PID(long PreviousTime, float TargetSpeed)
{
  float pid = 0;
  float Kp = 0.001;
  float Ki = 1;
  float Erreur = 0;
  float sec = 7000;
  unsigned int CT = 50;
  long CurrentTime = millis();
  unsigned int TimeSample = CurrentTime - PreviousTime;

  if (TimeSample >= CT) //CT est une constante de temps systeme definit plus haut
  {

    int encodeur_0 = ENCODER_Read(0);
    int encodeur_1 = ENCODER_Read(1);
    Erreur = encodeur_0 - encodeur_1;
    pid = (Erreur * Kp) + ((Erreur * Ki) / sec) + TargetSpeed;
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
  MOTOR_SetSpeed(1, 0.4);
  uint32_t dm = ((120 * AngleG) / 360);
  float cycle = (3200L * dm) / 23.9389;

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
  MOTOR_SetSpeed(0, 0.4);
  MOTOR_SetSpeed(1, 0);
  uint32_t dm = ((120 * AngleD) / 360);
  float cycle = (3200L * dm) / 23.9389;
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
  float speed1 = 0.7;   // Fonctionne bien a 0.95 robot prodige
  float distance = DistanceA * 3200L / 24;

  float speedMin = .2;
  float speedMax = 0;
  float a = 0;
  float b = 0;

  bool i = true;

  while (i)
  {
    if ((speed0 <= speed1) && ((ENCODER_Read(0)/distance) <= .4))
    {
      speed0 += .01;
      speedMax = speed0;
      delay(15);    //  Fonctionne bien a 5ms
      MOTOR_SetSpeed(0, speed0);
    }
    PreviousTime = PID(PreviousTime, speed0);
    if ((ENCODER_Read(0) >= distance) && (ENCODER_Read(1) >= distance))
    {
      MOTOR_SetSpeed(0, 0);
      MOTOR_SetSpeed(1, 0);
      ENCODER_Reset(0);
      ENCODER_Reset(1);
      i = false;
    }
    if(((ENCODER_Read(0)/distance) >=.6) && ((ENCODER_Read(1)/distance) >=.6))
    {
      a = (speedMin - speedMax)/(1-.6);
      b = speedMin - (a*1);

      speed0 = (a*(ENCODER_Read(0)/distance)+b);
      MOTOR_SetSpeed(0, speed0);      
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
  MOTOR_SetSpeed(0, -.3);
  MOTOR_SetSpeed(1, .3);
  bool i = true;
  int F0 = 0;
  int F1 = 0;
  while (i)
  {
    if (ENCODER_Read(0) <= -3950)
    {
      MOTOR_SetSpeed(0, 0);
      F0 = 1;
    }
    if (ENCODER_Read(1) >= 3750)
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
      delay(100);

  }
}

void loop()
{
  int32_t mouvements[9 /* Nombre de mouvements */][2] = {
      {215, -90},
      {30, 90},
      {30, 90},
      {30, -90},
      {25, 45},
      {25, -85},
      {60, 40},
      {50, 10},
      {80, 0}};

  int32_t inverse[9 /* Nombre de mouvements */][2] = {
      {90, -10},
      {40, -40},
      {50, 85},
      {25, -45},
      {20, 85},
      {40, -90},
      {30, -85},
      {30, 90},
      {240, 0}};

  Sequence(mouvements);
  uTurn();
  Sequence(inverse);
  uTurn();
  while (1)
  { 
    Arreter();
  }
}