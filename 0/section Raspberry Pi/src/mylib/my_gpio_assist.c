/**
 * @file my_gpio_assist.c
 * @author Akashdeep Singh
 * @brief Functions that assist in reading or writing on GPIO pins
 * @date 2022-06-30
 * This code comes from Assignment 3 of CPSC 359
 * 
 */


void init_base_gpio()
{
    gpio = getGPIOPtr();
}


int Init_GPIO(int pin_num, int mode)
{
    // assume pin_num is valid
    if (mode == 0)
    {
        // call inp gpio macro
        INP_GPIO(pin_num);
        return 0;
    }
    else if (mode == 1)
    {
        // set to input first: for reset purpopses
        INP_GPIO(pin_num);

        // then to output
        OUT_GPIO(pin_num);
        return 0;
    }

    // at the moment and within scope of assignment ALT functions are not supported
    return -1;
}

int write_pin(int pin_num, int bit)
{
    if (bit == 0)
    {
        // use gpioclr0
        gpio[GPCLR0] = 1 << pin_num;

        return 0;
    }
    else if (bit == 1)
    {
        // use gpioset0
        gpio[GPSET0] = 1 << pin_num;
        return 0;
    }

    return -1;
}


int read_pin(int pin_num)
{
    int v;
    v = (gpio[GPLEV0] >> pin_num) & 1;
    return v;
}