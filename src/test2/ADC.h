#ifndef ADC_H
#define ADC_H

typedef enum{
             joy_x = 1,
             joy_y = 2,
             slider_r = 3,
             slider_l = 4,
            } Device;
uint8_t init_ADC(void);
uint8_t analogRead(Device device);



#endif


