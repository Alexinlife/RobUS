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
  int mouvements[9 /* Nombre de mouvements */][2] = {
      {1,1},
      {1,1},
      {1,1},
      {1,1},
      {1,1},
      {1,1}, 
      {1,1},
      {1,1},
      {1,0}
    };

  for (int i = 0; i < sizeof(mouvements); i++) {

    // Valeur de déplacement à la position i
    if (mouvements[i,0] != 0) {

      if (mouvements[i,0] < 0) {

      } else {

      }
    }
    // Valeur de rotation à la position i
    if (mouvements[i, 1] != 0) {
      
      if (mouvements[i,1] < 0) {

      } else {
        
      }
    }
  }
}