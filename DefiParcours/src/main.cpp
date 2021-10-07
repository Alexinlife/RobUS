#include <Arduino.h>
#include <LibRobus.h>

void setup()
{
}

void InverserTableau() {

}

void Gauche(int32_t AngleG)
{
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
  float speed0 = 0.5;
  float speed1 = 0.5;
  MOTOR_SetSpeed(0, speed0);
  MOTOR_SetSpeed(1, speed1);
  bool i = true;
  int timer = 0;
  while (i)
  {
    timer++;
    if (timer % 500 == 0)
    {
      if (speed0 < .70 || speed1 < .7)
      {
        speed0 -= .2;
        speed1 -= .2;
      }
      if (ENCODER_Read(0) < ENCODER_Read(1))
      {
        speed0 = (ENCODER_Read(1) * speed0) / ENCODER_Read(0);
        MOTOR_SetSpeed(0, speed0);
      }
      if (ENCODER_Read(1) < ENCODER_Read(0))
      {
        speed1 = (ENCODER_Read(0) * speed1) / ENCODER_Read(1);
        MOTOR_SetSpeed(1, speed1);
      }
    }
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

void Sequence()
{
  int32_t mouvements[9 /* Nombre de mouvements */][2] = {
      {1000, 90},
      {1000, 0},
      {-1000, -90},
      {500, -45},
      {500, 135},
      {500, -45},
      {-500, -45},
      {0, 0},
      {0, 0}};

  for (int i = 0; i < sizeof(mouvements); i++)
  {

    // Valeur de déplacement à la position i
    if (mouvements[i, 0] != 0)
    {

      if (mouvements[i, 0] < 0)
      {
        Reculer((int32_t)mouvements[i, 0]);
      }
      else
      {
        Avancer((int32_t)mouvements[i, 0]);
      }
    }
    // Valeur de rotation à la position i
    if (mouvements[i, 1] != 0)
    {

      if (mouvements[i, 1] < 0)
      {
        Gauche((int32_t)mouvements[i, 1]);
      }
      else
      {
        Droite((int32_t)mouvements[i, 1]);
      }
    }
  }
}

void loop()
{
  Sequence();
  uTurn();
}