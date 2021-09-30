#include <Arduino.h>
#include <LibRobus.h>

void setup()
{
  // put your setup code here, to run once:
}

void loop()
{
  sequence();
}

void sequence()
{
  int nbLignes = 9;
  int nbRotations = 8;
  int lignes[nbLignes] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  int rotations[nbRotations] = {0, 0, 0, 0, 0, 0, 0, 0};

  for (int i = 0; i < nbLignes; i++) {

    if (i < nbRotations) {
      
    }
  }
}