/****************************************************
* [File Name]: common_macros.h
* [Description]: Commonly used Macros
* [Author]: taha Khaled
****************************************************/

#ifndef COMMON_MACROS_H
#define COMMON_MACROS_H

/* Set a certain bit in any register */
#define SET_BIT(REG,NUM) (REG = REG | (1 << NUM))

/* Clear a certain bit in any register */
#define CLEAR_BIT(REG,NUM) (REG &= ~(1 << NUM))

/* Toggle a certain bit in any register */
#define TOGGLE_BIT(REG,NUM) (REG^=(1 << NUM))

/* Rotate right the value in register with specific number */
#define ROR(REG,NUM) (REG = (REG >> (NUM)) | (REG << (8-NUM))

/* Rotate left the value in register with specific number */
#define ROL(REG,NUM) (REG = (REG << NUM) | (REG >> (8-NUM)))

/* Check bit is set in specific register or not */
#define BIT_IS_SET(REG,NUM) (REG & (1 << NUM))

/* Check bit is cleared in specific register or not */
#define BIT_IS_CLEAR(REG,NUM) (!(REG & (1 << NUM)))

#define GET_BIT(REG,NUM) ((REG & (1<<NUM)) >> NUM)

#endif /* COMMON MACROS_H */






