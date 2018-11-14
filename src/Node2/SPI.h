
#ifndef SPI_H_
#define SPI_H_

#include <avr/io.h>
#include <avr/interrupt.h>



char SPI_Read(void);
void SPI_Send(char cData);
void SPI_MasterInit(void);




#endif /* SPI_H_ */