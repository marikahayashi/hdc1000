#include <stdio.h>
#include <unistd.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include "hdc1000.h"

static int hdc1000fd;
static unsigned char aucRawdata[4];

/*************************************
hdc1000_init
 initialize i2c
 Argument:
   ucAddr: device address ex. 0x40
 Return value:
 *************************************/
int hdc1000_init(unsigned char ucAddr)
{
  hdc1000fd = wiringPiI2CSetup(ucAddr);
  if (hdc1000fd < 0) {
    perror("hdc1000_init:wiringPiI2CSetup");
    return -1;
  }
  if(wiringPiI2CWriteReg16(hdc1000fd, 0x02, 0x0010) < 0) {
    perror("hdc1000_init:set configuration register");
    return -1;
  }
  return 0;
}


/*************************************
hdc1000_read_temp_humid
 start AD conversion, wait, then read 4 bytes.
 Argument:void
 Return value: status
 *************************************/
int hdc1000_read_temp_humid(void)
{
  int ret;
  unsigned char get_value[1];
  
  get_value[0] = 0x00;
  ret = write(hdc1000fd, get_value, 1);
  if (ret < 0) {
    perror("hdc1000_read_temp_humid:write get_value");
    return -1;
  }
  //wait for conversion
  // Temperature6.35msec+Humidity6.5msec=12.85msec
  // =13msec
  usleep(13000); 
  ret = read(hdc1000fd, aucRawdata, 4);
  if (ret < 0) {
    perror("hdc1000_read_temp_humid:read result");
    return -1;
  }
  
  return 0;
}


/*************************************
hdc1000_calc_physical_quantity()
 convert raw ad value to physical quantity
 Argument:
   pfTdata (o): temperature
   pfHdata (o): humidity
 Return value:void
 *************************************/
void hdc1000_calc_physical_quantity(float *pfTdata, float *pfHdata)
{
  int nTdata, nHdata;
  nTdata = aucRawdata[0] << 8;
  nTdata |= aucRawdata[1];
  *pfTdata = (nTdata / 65536.0 * 165.0) -40.0;
  nHdata = aucRawdata[2] << 8;
  nHdata |= aucRawdata[3];
  *pfHdata = nHdata / 65536.0 * 100;
  return;
}
