#include “uart.h”
#include <stdlib.h>
#include <inttypes.h>
#include <p32xxxx.h>
#include “command.h”

int bp_c = 230; int bp_tb = 14; int bp_ts = 4;//cup, tbsp, and tsp of baking powder in grams
int s_c = 273; int s_tb = 18; int s_ts = 4;//cup, tbsp, and tsp of salt in grams
int o_c = 90; int o_tb = 6; int o_ts = 2;//cup, tbsp, and tsp of oats in grams
int f_c = 124; int f_tb = 8; int f_ts = 3;//cup, tbsp, and tsp of flour in grams
int bs_c = 220; int bs_tb = 15; int bs_ts = 5;//cup, tbsp, and tsp of baking soda in grams
int gs_c = 200; int gs_tb = 12; int gs_ts = 4;//cup, tbsp, and tsp of granulated sugar in grams

//function that takes multiple parameters in order to determine if weight threshold has been crossed

void dispense_done(float bowl_weight,float ing_weight, int i, int proportion, float old_weight){
if (i == 1){ //uses i to determine which ingredient to use
if (proportion == 1){ //uses proportion to determine how much of each ingredient
if(ing_weight >= bp_c){ //if the weight is greater than the the threshold it calls ing command and stops the motors
ing_weight = ing_weight + old_weight;
ingredient_command(bowl_weight, ing_weight);
}else
return;
}
else if (proportion == 2){
if(ing_weight >= bp_tb){
ing_weight = ing_weight + old_weight;
ingredient_command(bowl_weight, ing_weight);
}else
return;
}
else {
if(ing_weight >= bp_ts){
ing_weight = ing_weight + old_weight;
ingredient_command(bowl_weight, ing_weight);
}else
return;
}
}else if (i == 2){
if (proportion == 1){
if(ing_weight >= s_c){
ing_weight = ing_weight + old_weight;
ingredient_command(bowl_weight, ing_weight);
}else
return;
}
else if (proportion == 2){
if(ing_weight >= s_tb){
ing_weight = ing_weight + old_weight;
ingredient_command(bowl_weight, ing_weight);
}else
return;
}
else {
if(ing_weight >= s_ts){
ing_weight = ing_weight + old_weight;
ingredient_command(bowl_weight, ing_weight);
}else
return;
}
}else if (i == 3){
if (proportion == 1){
if(ing_weight >= o_c){
ing_weight = ing_weight + old_weight;
ingredient_command(bowl_weight, ing_weight);
}else
return;
}
else if (proportion == 2){
if(ing_weight >= o_tb){
ing_weight = ing_weight + old_weight;
ingredient_command(bowl_weight, ing_weight);
}else
return;
}
else {
if(ing_weight >= o_ts){
ing_weight = ing_weight + old_weight;
ingredient_command(bowl_weight, ing_weight);
}else
return;
}
}
else if (i == 4){
if (proportion == 1){
if(ing_weight >= f_c){
ing_weight = ing_weight + old_weight;
ingredient_command(bowl_weight, ing_weight);
}else
return;
}
else if (proportion == 2){
if(ing_weight >= f_tb){
ing_weight = ing_weight + old_weight;
ingredient_command(bowl_weight, ing_weight);
}else
return;
}
else {
if(ing_weight >= f_ts){
ing_weight = ing_weight + old_weight;
ingredient_command(bowl_weight, ing_weight);
}else
return;
}
}
else if (i == 5){
if (proportion == 1){
if(ing_weight >= bs_c){
ing_weight = ing_weight + old_weight;
ingredient_command(bowl_weight, ing_weight);
}else
return;
}
else if (proportion == 2){
if(ing_weight >= bs_tb){
ing_weight = ing_weight + old_weight;
ingredient_command(bowl_weight, ing_weight);
}else
return;
}
else {
if(ing_weight >= bs_ts){
ing_weight = ing_weight + old_weight;
ingredient_command(bowl_weight, ing_weight);
}else
return;
}
}
else if (i == 6){
if (proportion == 1){
if(ing_weight >= gs_c){
ing_weight = ing_weight + old_weight;
ingredient_command(bowl_weight, ing_weight);
}else
return;
}
else if (proportion == 2){
if(ing_weight >= gs_tb){
ing_weight = ing_weight + old_weight;
ingredient_command(bowl_weight, ing_weight);
}else
return;
}
else {
if(ing_weight >= gs_ts){
ing_weight = ing_weight + old_weight;
ingredient_command(bowl_weight, ing_weight);
}else
return;
}
}
else
return;

}

 

