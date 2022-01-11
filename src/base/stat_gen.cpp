#include <time.h>
#include <math.h>

#include "./../header/save_io.hpp"

const char* race_display(int race, int type, bool cap) {
    const char* out = NULL;
    if (type == 0) {
        switch (race) {
            case 1:
                if (cap == true) {
                    out = "Vuleen";
                } else { out = "vuleen"; }
                break;
            case 2:
                if (cap == true) {
                    out = "Aradi";
                } else { out = "aradi"; }
                break;
            case 3:
                if (cap == true) {
                    out = "Human";
                } else { out = "human"; }
                break;
            case 4:
                if (cap == true) {
                    out = "Lycan";
                } else { out = "lycan"; }
                break;
            case 5:
                if (cap == true) {
                    out = "Jodum";
                } else { out = "jodum"; }
                break;
        }
    } else if (type == 1) {
        switch (race) {
            case 1:
                if (cap == true) {
                    out = "Darak";
                } else { out = "darak"; }
                break;
            case 2:
                if (cap == true) {
                    out = "Goblin";
                } else { out = "Goblin"; }
                break;
            case 3:
                if (cap == true) {
                    out = "Arcran";
                } else { out = "arcran"; }
                break;
            case 4:
                if (cap == true) {
                    out = "Sleech";
                } else { out = "sleech"; }
                break;
            case 5:
                if (cap == true) {
                    out = "Wimble";
                } else { out = "wimble"; }
                break;
        }
    } return out;
}

void stats_randomize() {
    int * stat = save_reader();
    for (int i = 1; i < 6; i++) {
        if (i == 1 || i == 2 || i == 4 || i == 5) {
            save_writer(i, round(stat[i] / (0.8 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(1.2-0.8))))));
        }
    }
}

int * player_stats_gen(int i) {
    switch (i) {
        case 1:
            static int vuleen[3] = {1, 20, 10};
            return vuleen;
        case 2:
            static int aradi[3] = {2, 30, 15};
            return aradi;
        case 3:
            static int human[3] = {3, 20, 7};
            return human;
        case 4:
            static int lycan[3] = {4, 16, 32};
            return lycan;
        case 5:
            static int jodum[3] = {5, 24, 16};
            return jodum;
    } static int err[3] = {0, 0, 0}; return err;
}

int * enemy_stats_gen(int i) {
    switch (i) {
        case 1:
            static int darak[3] = {1, 25, 10};
            return darak;
        case 2:
            static int goblin[3] = {2, 12, 7};
            return goblin;
        case 3:
            static int arcran[3] = {3, 30, 5};
            return arcran;
        case 4:
            static int sleech[3] = {5, 12, 36};
            return sleech;
        case 5:
            static int wimble[3] = {6, 27, 10};
            return wimble;
    } static int err[3] = {0, 0, 0}; return err;
}

void stats_write() {
    srand(time(0));
    int * stat = player_stats_gen((rand()%4)+1);
    int * stat2 = enemy_stats_gen((rand()%4)+1);
    for (int i = 0; i < 6; i++) {
        if (i <= 2) {
            save_writer(i, stat[i]);
        } else if (i >= 3) {
            save_writer(i, stat2[i-3]);
        }
    }
}
