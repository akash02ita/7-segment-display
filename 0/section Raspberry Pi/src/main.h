/** The pins connected in the breadboard must exactly match in the following format of the macros **/

#define TOTAL_PINS 9

// input pins
#define LEFT_BUTTON_PIN_NUM 17
#define RIGHT_BUTTON_PIN_NUM 27

// output pins
#define BAR_a_PIN_NUM 6
#define BAR_b_PIN_NUM 13
#define BAR_c_PIN_NUM 12
#define BAR_d_PIN_NUM 16
#define BAR_e_PIN_NUM 19
#define BAR_f_PIN_NUM 20
#define BAR_g_PIN_NUM 26

/*

NOTE: every digit is formatted in 7 bars as follows:

       e
     ----
   a|    |c
    |  f |
     ----
   b|    |d
    |    |
     ----
       g
*/


/**
 * @brief initializes all pins defined in above macros
 * 
 */
void initialize_gpio_pins();


/**
 * @brief uses above macros to display the digit in the format specified above
 * 
 * @param digit must be between 0-9, inclusively
 */
void output_digit(const int digit);


/**
 * @brief if left or right button is pressed decrements or increments digit if it can stay between 0-9, inclusively
 * 
 * @param digit 
 * @param left_pressed 
 * @param right_pressed 
 * @return int [0: no updates/changes, 1: updates/changes occurred] 
 */
int update_digit(int *digit, int *left_pressed, int *right_pressed);


/**
 * @brief thread function that runs forever, unless cancelled by main thread.
 * Updates digit and displays on the output pins
 * 
 */
void * thread_digit_displayer(void *arg);


/**
 * @brief Function for the main thread.
 * 
 */
int main();