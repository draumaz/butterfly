#include <iostream>
#include <cstdlib>
#include <cmath>
#include "./../header/tool.hpp"
#include "./../header/save_io.hpp"
#include "./../header/record_io.hpp"
#include "./../header/gtool.hpp"
#include "./../header/stat_gen.hpp"
#include "./../header/screen.hpp"

bool spare() {
    bool result = false;
    int * sav = save_reader();
    printf("\nYou attempt to spare the %s", race_display(sav[3],1,false));
    for (int i = 0; i < 3; i++) {
        printf(".");
        std::cout << std::flush;
        game_sleep(500);
    } game_sleep(750);
    if (sav[1] >= sav[4]) {
        record_writer(2);
        printf("\n\nIt worked!");
        result = true;
    } else if (sav[1] <= sav[4]) {
        printf("\n\nIt didn't work.");
        result = false;
    } std::cout << std::flush; game_sleep(1000); return result;
}

bool items() {
    bool item_used = false;
    int * sav = save_reader();
    item_options_screen();
    switch (user_input_int(1, 3)) {
        case 1:
            if (sav[7] > 0) { // use potion
                item_used = true;
                save_writer(7, 0);
                save_writer(1, (sav[1]+10));
                screen_clear();
                board_header_screen(true);
                printf("\nACTION >> 2\n");
                item_options_screen();
                printf("\nACTION >> 1\n\nYou drink the potion, recovering 10HP!");
            } else { // no potions
                item_used = false;
                printf("\nYou don't have any potions left.");
            }
            break;
        case 2:
            if (sav[8] > 0) { // use spear
                item_used = true;
                save_writer(8, 0);
                save_writer(4, (sav[4]-9));
                screen_clear();
                board_header_screen(true);
                printf("\nACTION >> 2\n");
                item_options_screen();
                printf("\nACTION >> 2\n\nYou throw the spear, dealing 9HP!");
                
            } else { // no spears
                item_used = false;
                printf("\nYou don't have any spears left.");
            }
            break;
        case 3: // leave now
            return item_used;
    } std::cout << std::flush; game_sleep(1000); return item_used;
}

void attack(int dir) {
    srand(time(0));
    screen_clear();
    int * sav = save_reader();
    switch (dir) {
        case 0: { // attack enemy
            int dam_to_enemy = round(sav[2]/(3.4+static_cast<float>(rand())/(static_cast<float>(RAND_MAX/(4.1-3.4)))));
            save_writer(4, sav[4]-dam_to_enemy);
            board_header_screen(true);
            if (sav[4] <= 0) {
                printf("\nYou deal the death blow, attacking with %d damage!\n"
                ,dam_to_enemy);
            } else {
                printf("\nYou attack the %s, dealing %d damage!\n",
                race_display(sav[3],1,false),dam_to_enemy);
            } break; }
        case 1: { // get attacked
            int dam_to_player = round(sav[5]/(3.4+static_cast<float>(rand())/(static_cast<float>(RAND_MAX/(4.1-3.4)))));
            save_writer(1, sav[1]-dam_to_player);
            board_header_screen(true);
            if (sav[1] <= 0) {
                printf("\nThe %s deals the death blow, attacking with %d damage!\n",
                race_display(sav[3],1,false),dam_to_player);
            } else {
                printf("\nThe %s attacks you, dealing %d damage!\n",
                race_display(sav[3],1,false),dam_to_player);
            } break; }
    } std::cout << std::flush;
    game_sleep(1000);
}
