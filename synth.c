#include <stdio.h>
#include <stdint.h>
#define N 2

int8_t xp, yp, dt;

// xp/dt >= 5/2

int main(int argc, char **argv){
  xp = 120;
  yp = 0;
  dt = 30;
  for(int i=0; i<(N*dt*6); ++i){
    yp += xp / dt;
    xp -= yp / dt;
    printf("%d, %d\r\n", xp, yp);
  }
  return 0;
}

