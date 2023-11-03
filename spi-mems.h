/*
* This include file describes the functions exported by spi-mems.h
*/
#ifndef __spimems_H
#define __spimems_H

/*
 * Definitions for functions being abstracted out
 */
uint16_t read_reg(int reg);
uint8_t read_xyz(int16_t vecs[3]);
void write_reg(uint8_t reg, uint8_t value);
void setup_mems(void);

#endif /* generic header protector */

