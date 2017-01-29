
int hdc1000_init(unsigned char ucAddr);
int hdc1000_read_temp_humid(void);
void hdc1000_calc_physical_quantity(float *pfTdata, float *pfHdata);
