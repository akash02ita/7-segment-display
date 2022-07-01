#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#include <src/mylib/initGPIO.h>
#include <src/mylib/initGPIO.c>
#include <src/mylib/my_gpio_assist.h>
#include <src/mylib/my_gpio_assist.c>

#include <src/main.h>

void initialize_gpio_pins()
{
    // input mode
    Init_GPIO(LEFT_BUTTON_PIN_NUM, 0);
    Init_GPIO(RIGHT_BUTTON_PIN_NUM, 0);

    // output mode
    Init_GPIO(BAR_a_PIN_NUM, 1);
    Init_GPIO(BAR_b_PIN_NUM, 1);
    Init_GPIO(BAR_c_PIN_NUM, 1);
    Init_GPIO(BAR_d_PIN_NUM, 1);
    Init_GPIO(BAR_e_PIN_NUM, 1);
    Init_GPIO(BAR_f_PIN_NUM, 1);
    Init_GPIO(BAR_g_PIN_NUM, 1);
}

void output_digit(const int digit)
{
    if (digit == 0 || digit == 4 || digit == 5 || digit == 6 || digit == 8 || digit == 9)
        write_pin(BAR_a_PIN_NUM, 1);
    else
        write_pin(BAR_a_PIN_NUM, 0);

    if (digit == 0 || digit == 2 || digit == 6 || digit == 8)
        write_pin(BAR_b_PIN_NUM, 1);
    else
        write_pin(BAR_b_PIN_NUM, 0);

    if (digit == 0 || digit == 1 || digit == 2 || digit == 3 || digit == 4 || digit == 7 || digit == 8 || digit == 9)
        write_pin(BAR_c_PIN_NUM, 1);
    else
        write_pin(BAR_c_PIN_NUM, 0);

    if (digit == 0 || digit == 1 || digit == 3 || digit == 4 || digit == 5 || digit == 6 || digit == 7 || digit == 8 || digit == 9)
        write_pin(BAR_d_PIN_NUM, 1);
    else
        write_pin(BAR_d_PIN_NUM, 0);

    if (digit == 0 || digit == 2 || digit == 3 || digit == 5 || digit == 6 || digit == 7 || digit == 8 || digit == 9)
        write_pin(BAR_e_PIN_NUM, 1);
    else
        write_pin(BAR_e_PIN_NUM, 0);

    if (digit == 2 || digit == 3 || digit == 4 || digit == 5 || digit == 6 || digit == 8 || digit == 9)
        write_pin(BAR_f_PIN_NUM, 1);
    else
        write_pin(BAR_f_PIN_NUM, 0);

    if (digit == 0 || digit == 2 || digit == 3 || digit == 5 || digit == 6 || digit == 8 || digit == 9)
        write_pin(BAR_g_PIN_NUM, 1);
    else
        write_pin(BAR_g_PIN_NUM, 0);
   
}

void turn_off()
{
    write_pin(BAR_a_PIN_NUM, 0);
    write_pin(BAR_b_PIN_NUM, 0);
    write_pin(BAR_c_PIN_NUM, 0);
    write_pin(BAR_d_PIN_NUM, 0);
    write_pin(BAR_e_PIN_NUM, 0);
    write_pin(BAR_f_PIN_NUM, 0);
    write_pin(BAR_g_PIN_NUM, 0);
    sleep(1);
}
int update_digit(int *digit, int *left_pressed, int *right_pressed)
{
    /* note: keeping track of button pressed status does not really help as probably the signal from button to gpio reading pin is not always continuosly on when button is pressed
    Although it somewhat helps, with use of usleep() function, to have too much speed in changing values */

    // decrement
    if (read_pin(LEFT_BUTTON_PIN_NUM) && *digit > 0 && !(*left_pressed))
    {
        *left_pressed = 1;
        (*digit)--;
        return 1;
    }
    else
        *left_pressed = 0;

    // increment
    if (read_pin(RIGHT_BUTTON_PIN_NUM) && *digit < 9 && !(*right_pressed))
    {
        *right_pressed = 1;
        (*digit)++;
        return 1;
    }
    else
        *right_pressed = 0;

    return 0;
}


void * thread_digit_displayer(void *arg)
{
    // display the digit that can be modified interactive until the thread is not cancelled
    printf("To halt the program press enter on the terminal\n.");
    printf("\nWELCOME!\nHere the simple way to interact with the breadboard:\n\t[left button]: decrement digit if greater than 0\n\t[right button]: increment digit less than 9\n");
    int digit = 0; // start
    int left_pressed = 0;
    int right_pressed = 0;
    output_digit(digit);
    while (1)
    {
        // only write to pin (so do fewer gpio memory calls) when a new digit is there
        if (update_digit(&digit, &left_pressed, &right_pressed))
                output_digit(digit);
        usleep(100000);
    }
}


int main()
{
    // initialize gpio MEMORY address exactly once
    init_base_gpio();
    // initialize the pins
    initialize_gpio_pins();

    pthread_t digit_displayer_thread;
    pthread_create(&digit_displayer_thread, NULL, thread_digit_displayer, NULL);

    // keep running the thread until user presses enter on the terminal
    getchar();
    int status  = pthread_cancel(digit_displayer_thread);
    // sleep(1);
    printf("The status of cancel is %d\n", status);
    turn_off();
    return 0;
}
