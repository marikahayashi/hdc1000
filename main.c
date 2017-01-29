#include <stdio.h>
#include <unistd.h>
#include "hdc1000.h"

int main(void)
{
  float fTdata, fHdata;

  hdc1000_init(0x40);

  while (1) {
    if (hdc1000_read_temp_humid() < 0) {
      printf("read temperature/humidity failed\n");
    } else {
      hdc1000_calc_physical_quantity(&fTdata, &fHdata);
      printf("t:%.2f  ", fTdata);
      printf("h:%.2f\n", fHdata);
    }
  }
  return 0;
}
