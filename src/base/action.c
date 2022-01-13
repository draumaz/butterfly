#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "./../header/tool.h"
#include "./../header/save_io.h"
#include "./../header/record_io.h"
#include "./../header/gtool.h"
#include "./../header/stat_gen.h"
#include "./../header/screen.h"

int spare() {
    int result = 1;
    int * sav = save_reader();
    printf("\nYou attempt to spare the %s", race_display(sav[3],1,1));
    for (int i = 0; i < 3; i++) {
        printf(".");
        fflush(stdout);
        game_sleep(500);
    } game_sleep(750);
    if (sav[1] >= sav[4]) {
        record_writer(2);
        printf("\n\nIt worked!");
        result = 0;
    } else if (sav[1] <= sav[4]) {
        printf("\n\nIt didn't work.");
        result = 1;
    } fflush(stdout); game_sleep(1000); return result;
}

int items() {
    int item_used = 1;
    int * sav = save_reader();
    item_options_screen();
    switch (user_input_int(1, 4)) {
        case 1:
            if (sav[7] > 0) { // use potion
                item_used = 0;
                save_writer(7, 0);
                save_writer(1, (sav[1]+10));
                screen_clear();
                board_header_screen(0);
                printf("\nACTION >> 2\n");
                item_options_screen();
                printf("\nACTION >> 1\n\nYou drink the potion, recovering 10HP!");
            } else { // no potions
                item_used = 1;
                printf("\nYou don't have any potions left.");
            }
            break;
        case 2:
            if (sav[8] > 0) { // use spear
                item_used = 0;
                save_writer(8, 0);
                save_writer(4, (sav[4]-9));
                screen_clear();
                board_header_screen(0);
                printf("\nACTION >> 2\n");
                item_options_screen();
                printf("\nACTION >> 2\n\nYou throw the spear, dealing 9HP!");
                
            } else { // no spears
                item_used = 1;
                printf("\nYou don't have any spears left.");
            }
            break;
        case 3:
            if (sav[9] > 0) { // use poison
                item_used = 0;
                save_writer(9, 0); // poison thrown
                save_writer(10, 1); // poison loop active
                screen_clear();
                board_header_screen(0);
                printf("\nACTION >> 3\n");
                item_options_screen();
                printf("\nACTION >> 2\n\nYou throw the poison! The %s feels the pain...", race_display(sav[3],1,1));
            } else {
                item_used = 1;
                printf("\nYou don't have any more poison.");
            }
            break;
        case 4: // leave now
            return item_used;
    } fflush(stdout); game_sleep(1000); return item_used;
}

void attack(int dir) {
    srand(time(0));
    float ran = ((float)rand())/(float)RAND_MAX;
    screen_clear();
    int * sav = save_reader();
    switch (dir) {
        case 0: { // attack enemy
            int dam_to_enemy = round(sav[2]/(ran*(4.1-3.2)+3.2)); // Randomization needs to be fixed
            save_writer(4, sav[4]-dam_to_enemy);
            board_header_screen(0);
            if (sav[4] <= 0) {
                printf("\nYou deal the death blow, attacking with %d damage!\n"
                ,dam_to_enemy);
            } else {
                printf("\nYou attack the %s, dealing %d damage!\n",
                race_display(sav[3],1,1),dam_to_enemy);
            } break; }
        case 1: { // get attacked
            int dam_to_player = round(sav[5]/(ran*(4.1-3.2)+3.2)); // before next release
            save_writer(1, sav[1]-dam_to_player);
            board_header_screen(0);
            if (sav[1] <= 0) {
                printf("\nThe %s deals the death blow, attacking with %d damage!\n",
                race_display(sav[3],1,1),dam_to_player);
            } else {
                printf("\nThe %s attacks you, dealing %d damage!\n",
                race_display(sav[3],1,1),dam_to_player);
            } break; }
    } fflush(stdout); game_sleep(1000);
}
