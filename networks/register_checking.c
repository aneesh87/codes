#include <stdio.h>

#define ERROR_CHECK 0x1
#define ERROR_CLEAR (0x1<<7)
#define MAX_DELAY 3600
#define RESET_SEC 3600*24

int delay = 0;

void clear_err (uint8_t reg) {
  reg = reg | ERROR_CLEAR;
  set_register(reg);
  delay = min(MAX_DELAY, delay*2);
}

void test_for_error () {
  time_t   curtime = 0;
  bool     err_occurred = false;
  time_t   time_of_err = 0;
  uint_8_t reg = 0x0;
  
  while (1) {
    reg = read_register();
    curtime = get_timestamp();
    
    if (!err_occurred) {
        if (reg & ERROR_CHECK) {
            err_occurred = true;
            time_of_err = curtime;
         } else {
            if (curtime - time_of_err >= RESET_SEC) {
                delay = 60;
            }
         }
    } else {
        if (curtime - time_of_err  >= delay) {
            clear_err(reg);
            err_occurred = false;
        }
     }
  }
}
  
int main(int agrc, char **argv) {
   test_for_err();
   return 0;
}
