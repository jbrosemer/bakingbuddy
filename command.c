#include “uart.h”
#include <stdlib.h>
#include <inttypes.h>
#include <p32xxxx.h>
#include “motors.h”
#include “tft_master.h”
#include “tft_gfx.h”
#include “scale.h”

unsigned char j; //simple counter
char cmd[80]; //two variables to hold characters
uint8_t buffer[80];
float total;
signed long weight; //reads HX711
float new_weight; //gets added when something gets put on the scale
float ing_weight; //ingredient weight
float old_weight; //holds old value to compare
float bowl_weight; //weight of bowl
uint8_t cnt = 0;
uint32_t port = 0;
float gain = 0.00326328; //calculated gain to callibrate load cell scale
float offset = 466818; //offset value of empty scale reading
void amount_command(float bowl_weight, int i, float old_weight);
void ingredient_command(float bowl_weight, float old_weight);

void command(){ //command interface for user to place bowl on scale to tare it, calls on other commands
for(;;){
total = 0;
char_to_string(“Welcome to the Baking Buddy! Please place your bowl on the scale\n\r”);
char_to_string(“When finished, choose ‘d’ for done\n\r”);
char_to_string(“Otherwise, choose ‘q’ to quit\n\r”);
uart_read_string(cmd);
switch(cmd[0]){
case ‘d’:
char_to_string(“\n\rThank You. Please wait one moment.\n\r”);
bowl_weight = Convert(); //holds and remembers the value of the bowl weight
// weight = ReadCount();
// sprintf(buffer, “%ld”, weight);
// char_to_string(buffer);
ingredient_command(bowl_weight, 0); //begins ingredient command function
break;
case ‘q’:
char_to_string(“Program Terminated\n\r”);
return;
break;
}
}
}
void ingredient_command(float bowl_weight, float old_weight){ //command interface for user to select desired ingredient
for (;;) {
char_to_string(“\n\rPlease choose an ingredient:\n\r”);
char_to_string(“p: Baking Powder\n\rs: Salt\n\ro: Oats\n\rf: Flour\n\rb: Baking Soda\n\rg: Granulated Sugar\n\rq: Quit\n\r”);
uart_read_string(cmd);
switch (cmd[0]) {
case ‘p’: //analog test
char_to_string(“\n\rBaking Powder Selected\n\r”);
port = 0x1;
amount_command(bowl_weight, 1, old_weight);
break;
case ‘s’: //encoder test
char_to_string(“\n\rSalt Selected\n\r”);
port= 0x2;
amount_command(bowl_weight, 2, old_weight);
break;
case ‘o’: //code version
char_to_string(“\n\rOats Selected\n\r”);
port = 0x04;
amount_command(bowl_weight, 3, old_weight);
break;
case ‘f’: //matrix test
char_to_string(“\n\rFlour Test\n\r”);
port = 0x08;
amount_command(bowl_weight, 4, old_weight);
break;
case ‘b’: //quit program
char_to_string(“\n\rBaking Soda Selected\n\r”);
port = 0x10;
amount_command(bowl_weight, 5, old_weight);
break;
case ‘g’: //gluten free flour
char_to_string(“\n\rGranulated Sugar Selected\n\r”);
port = 0x20;
amount_command(bowl_weight, 6, old_weight);
break;
case ‘q’:
char_to_string(“\n\rProgram terminated\n\r”);
return;
break;
default:
char_to_string(“\n\rIncorrect Command\n\r”);
break;
}
}
}

void amount_command(float bowl_weight, int i, float old_weight){ //command interface for user to select amount of desired ingredient
for(;;){
int proportion;
char_to_string(“Please specify how much you want:\n\r”);
char_to_string(“c: Cup\n\rb: Tablespoon\n\rt: Teaspoon\n\ri: Change Ingredient\n\rq: quit\n\r”);
uart_read_string(cmd);
switch(cmd[0]) {
case’c’: //cup test
char_to_string(“\n\rCup Selected\n\r”);
proportion = 1;
for(;;){
pulse(port);
new_weight = Convert();
pulse(port);
ing_weight = (new_weight – bowl_weight – old_weight);
dispense_done(bowl_weight, ing_weight, i, proportion, old_weight); //calls on dispense done to determine if it is above the threshold weight
// if(uart_read_ready())
// break;
}
break;
case ‘b’: //Tablespoon Test
char_to_string(“\n\rTablespoon Selected\n\r”);
proportion = 2;
for(;;){
pulse(port);
new_weight = Convert();
pulse(port);
ing_weight = (new_weight – bowl_weight – old_weight);
dispense_done(bowl_weight, ing_weight, i, proportion, old_weight);
// if(uart_read_ready())
// break;
}
break;
case ‘t’: //Teaspoon Test
char_to_string(“\n\rTeaspoon Selected\n\r”);
proportion = 3;
for(;;){
pulse(port);
new_weight = Convert();
pulse(port);
ing_weight = (new_weight – bowl_weight – old_weight);
dispense_done(bowl_weight, ing_weight, i, proportion, old_weight);
// if(uart_read_ready())
// break;
}
break;
case ‘i’:
ingredient_command(bowl_weight, old_weight);
break;
case ‘q’:
char_to_string(“Program terminated”);
return;
break;
default:
char_to_string(“Incorrect Command\n\r”);
break;
}

}
}