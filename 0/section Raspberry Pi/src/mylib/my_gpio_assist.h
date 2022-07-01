/**
 * @file my_gpio_assist.h
 * @author Akashdeep Singh
 * @brief Header file containing macros and prototype functions that assist in reading or writing on GPIO pins
 * @date 2022-06-30
 * This code comes from Assignment 3 of CPSC 359
 * 
 */

static unsigned *gpio;
// GPIO setup macros. Always use INP_GPIO(x) before using OUT_GPIO(x) or SET_GPIO_ALT(x,y)
#define INP_GPIO(g) *(gpio + ((g) / 10)) &= ~(7 << (((g) % 10) * 3))
#define OUT_GPIO(g) *(gpio + ((g) / 10)) |= (1 << (((g) % 10) * 3))
#define SET_GPIO_ALT(g, a) *(gpio + (((g) / 10))) |= (((a) <= 3 ? (a) + 4 : (a) == 4 ? 3  \
                                                                                     : 2) \
                                                      << (((g) % 10) * 3))

/**
 * @brief initialize gpio global var pointer
 * 
 */
void init_base_gpio();

/**
 * @brief initiliazes a gpio pin given to the desidered mode
 * [NOTE1]: at the moment only modes 0 and 1 are allowed
 * 
 * @param pin_num 
 * @param mode [0 = input, 1 = output]
 * @return [0]: successful
 * [-1]: wrong mode
 */
int Init_GPIO(int pin_num, int mode);

#define GPSET0 7  // 28/4
#define GPCLR0 10 // 40/4

/**
 * @brief 
 * 
 * @param pin_num 
 * @param bit 
 * @return [0]: successful
 * [-1]: wrong bit
 */
int write_pin(int pin_num, int bit);

#define GPLEV0 13

/**
 * @brief 
 * 
 * @param pin_num 
 * @return int: a bit 0 or 1 
 */
int read_pin(int pin_num);