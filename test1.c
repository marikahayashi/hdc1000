#include <stdio.h>
#include <unistd.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <hdc1000.h>

int main(void)
{
  int fd, ret;
  unsigned char aucRawdata[4];
  int nTdata, nHdata;
  
  fd = wiringPiI2CSetup(0x40);
  if (fd < 0) {
    perror("wiringPiI2CSetup");
    return -1;
  }

  if(wiringPiI2CWriteReg16(fd, 0x02, 0x0010) < 0) {
    perror("wiringPiI2CWriteReg16");
    return -1;
  }
  /*
  ret = wiringPiI2CReadReg16(fd, 0x02);
  if (ret < 0) {
    perror("wirintPiI2CReadReg16");
    return -1;
  }
  printf("0x02:%04x\n", ret);
  */

  while (1) {
    if (read_temp_humid(aucRawdata) < 0) {
      printf("read temperature/humidity failed\n");
    } else {
      nTdata = aucRawdata[0] << 8;
      nTdata |= aucRawdata[1];
      printf("temperature:%.2f ", ((nTdata / 65536.0 * 165.0) -40.0));
      nHdata = aucRawdata[2] << 8;
      nHdata |= aucRawdata[3];
      printf("humidity:%.2f\n", (nHdata / 65536.0 * 100));
    }
  }
  return 0;
}
