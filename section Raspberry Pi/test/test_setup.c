#include <stdio.h>
#include <unistd.h>

#include <src/mylib/initGPIO.h>
#include <src/mylib/initGPIO.c>
#include <src/mylib/my_gpio_assist.h>
#include <src/mylib/my_gpio_assist.c>

#include <src/main.h>

// global variables
const int pin_nums [TOTAL_PINS] = {
    LEFT_BUTTON_PIN_NUM, 
    RIGHT_BUTTON_PIN_NUM, 
    BAR_a_PIN_NUM, 
    BAR_b_PIN_NUM, 
    BAR_c_PIN_NUM, 
    BAR_d_PIN_NUM, 
    BAR_e_PIN_NUM, 
    BAR_f_PIN_NUM, 
    BAR_g_PIN_NUM};

const char * pin_names [TOTAL_PINS] = {
    "left button reading",
    "right button reading",
    "bar a",
    "bar b",
    "bar c",
    "bar d",
    "bar e",
    "bar f",
    "bar g",
};


// just for ease of readability
void print_dashes(const char * tag)
{
    printf("-----------------------%s-----------------------\n", tag);
}

// testing methods

void test_input_mode()
{
    print_dashes("START test_input_mode");
    printf("\nPlace the ground pin to the left button.\nWhen done hit enter: \n");
    while (getchar() != '\n'); // prevent next getchar to run again, in case letters are used
    printf("Place the 3v3 pin to the right button.\nWhen done hit enter: \n");
    while (getchar() != '\n');

    for (int i = 0; i < TOTAL_PINS; i++)
    {
        const int pin_num = pin_nums[i];
        const char * pin_name = pin_names[i];

        // set to input mode
        Init_GPIO(pin_num, 0);

        // check under 3.3v
        printf("Place the GPIO pin [%d], which is for [%s], to the RIGHT BUTTON\nWhen done hit enter: \n", pin_num, pin_name);
        while (getchar() != '\n');

        printf("The test will check every second for 10 times\n");
        for (int j = 0; j < 10; j++)
        {
            int pin_val = read_pin(pin_num);
            printf("The read value is %d\n", pin_val);
            sleep(1);
        }

        printf("\n");

        // check under ground
        printf("Place the same GPIO pin [%d], which is for [%s], to the LEFT button\nWhen done hit enter: \n", pin_num, pin_name);
        while (getchar() != '\n');

        printf("The test will check every second for 10 times\n");
        for (int j = 0; j < 10; j++)
        {
            int pin_val = read_pin(pin_num);
            printf("The read value is %d\n", pin_val);
            sleep(1);
        }

        printf("\n");
    }

    print_dashes("END test_input_mode");
}

void test_output_mode()
{
    print_dashes("START test_output_mode");
    printf("\nPlace the one LED light on breadboard. Ensure the cathode(-) is connected with the resistor that connected to the negative (ground) line on the breadboard. \nWhen done hit enter: \n");
    while (getchar() != '\n');
    printf("Place the ground pin to the line where the negative(ground) line of the breadboard.\nWhen done hit enter: \n");
    while (getchar() != '\n');

    
    for (int i = 0; i < TOTAL_PINS; i++)
    {
        
        const int pin_num = pin_nums[i];
        const char * pin_name = pin_names[i];

        // set to output mode
        Init_GPIO(pin_num, 1);
        printf("Place the GPIO pin [%d], which is for [%s], to the line where the anode(+) of LED is connected\nWhen done hit enter: \n", pin_num, pin_name);
        while (getchar() != '\n');

        printf("The test will bling LED for 5 times\n");
        for (int j = 0; j < 5; j++)
        {
            write_pin(pin_num, 1); // on
            sleep(1);
            write_pin(pin_num, 0); // off
            sleep(1);
        }
        
        printf("\n");
    }

    print_dashes("END test_output_mode");
    
}

void test_with_stdin_commands()
{
    print_dashes("START test_with_stdin_commands");
    int pin_num = 2;
    int write_val = 0;
    int mode = 0;
    char c;

    // keep the first pin ready
    Init_GPIO(pin_num, mode);
    while(1)
    {
        printf("\n\tStatus:\tGPIO pin: %d\tmode: %d\n", pin_num, mode);
        printf("\nHere the commands:\n\t[p]: select GPIO (p)in\n\t[s]: (s)wap input/output mode\n\t[w]: swap (w)rite on/off\n\t[r]: (r)ead value of pin\n\n\t[q]: 'q'uit\n");

        do // force to have non-new line input
        {
            c = getchar();
        } while (c == '\n');
        getchar(); // skip new line

        if (c == 'p')
        {
            printf("Enter a valid digit of GPIO pin between 2-27: ");
            int new_pin_num;
            scanf("%d", &new_pin_num);
            getchar(); // skip new line

            if (new_pin_num >= 2 && new_pin_num <= 27)
            {
                pin_num = new_pin_num;
                Init_GPIO(pin_num, mode);
                write_val = 0; // reset to 0 writing value
                printf("The new pin is %d, which is at mode \n", pin_num);
            }
            else
            {
                printf("\nINVALID pin number! The current pin_number is still %d, which is set to mode %d\n", pin_num, mode);
            }
        }
        else if (c == 's')
        {
            mode = !mode; // swap between 0 and 1
            Init_GPIO(pin_num, mode);
            printf("\tThe GPIO pin %d is set to %d mode\n", pin_num, mode);
        }
        else if (c == 'w')
        {
            write_val = !write_val; // swap between 0 and 1
            printf("\n\t%d is set to GPIO pin %d, which is in %d mode, with return code %d", write_val, pin_num, mode, write_pin(pin_num, write_val));
            
        }
        else if (c == 'r')
        {
            printf("\n\t%d is the read value from GPIO pin %d, which is in %d mode\n", read_pin(pin_num), pin_num, mode);
        }
        else if (c == 'q')
        {
            print_dashes("END test_with_stdin_commands");
            return;
        }
        else
        {
            printf("\nINVALID INPUT!\n");
        }
    }

}

int main()
{
    print_dashes("START main");
    // initialize gpio MEMORY address exactly once    
    init_base_gpio();

    // prompt user to follow selection
    while(1)
    {               
        printf("Here the options:\n\t[i]: test the pins in (i)input mode\n\t[o]: test the pins in (o)utput mode\n\t[c]: test with customized (c)ommands\n\n\t[q]: (q)uit\n");
        char c;
        do
        {
            c = getchar();
        } while (c == '\n');
        getchar(); // skip '\n'

        switch(c)
        {
            case 'i':
                test_input_mode();
                break;
            case 'o':
                test_output_mode();
                break;
            case 'c':
                test_with_stdin_commands();
                break;
            case 'q':
                print_dashes("END main");
                return 0;
            default:
                printf("\nINVALID option!\n");
                break;
        }
    }

    
}
