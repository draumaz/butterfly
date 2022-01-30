#include <time.h>
#include <stdlib.h>
#include <math.h>

#include "./../header/save_io.h"

char* race_display(int race, int type, int cap) {
    char* out = NULL;
    if (type == 0) {
        switch (race) {
            case 1:
                if (cap == 0) {
                    out = "Vuleen";
                } else { out = "vuleen"; }
                break;
            case 2:
                if (cap == 0) {
                    out = "Aradi";
                } else { out = "aradi"; }
                break;
            case 3:
                if (cap == 0) {
                    out = "Human";
                } else { out = "human"; }
                break;
            case 4:
                if (cap == 0) {
                    out = "Lycan";
                } else { out = "lycan"; }
                break;
            case 5:
                if (cap == 0) {
                    out = "Jodum";
                } else { out = "jodum"; }
                break;
        }
    } else if (type == 1) {
        switch (race) {
            case 1:
                if (cap == 0) {
                    out = "Darak";
                } else { out = "darak"; }
                break;
            case 2:
                if (cap == 0) {
                    out = "Goblin";
                } else { out = "Goblin"; }
                break;
            case 3:
                if (cap == 0) {
                    out = "Arcran";
                } else { out = "arcran"; }
                break;
            case 4:
                if (cap == 0) {
                    out = "Sleech";
                } else { out = "sleech"; }
                break;
            case 5:
                if (cap == 0) {
                    out = "Wimble";
                } else { out = "wimble"; }
                break;
        }
    } return out;
}

int * player_stats_gen(int i) {
    switch (i) {
        case 1: {
            static int vuleen[3] = {1, 20, 10};
            return vuleen; }
        case 2: {
            static int aradi[3] = {2, 30, 15};
            return aradi; }
        case 3: {
            static int human[3] = {3, 20, 7};
            return human; }
        case 4: {
            static int lycan[3] = {4, 16, 32};
            return lycan; }
        case 5: {
            static int jodum[3] = {5, 24, 16};
            return jodum; }
    }
    static int err[3] = {0, 0, 0};
    return err;
}

int * enemy_stats_gen(int i) {
    switch (i) {
        case 1: {
            static int darak[3] = {1, 25, 10};
            return darak; }
        case 2: {
            static int goblin[3] = {2, 12, 7};
            return goblin; }
        case 3: {
            static int arcran[3] = {3, 30, 5};
            return arcran; }
        case 4: {
            static int sleech[3] = {5, 12, 36};
            return sleech; }
        case 5: {
            static int wimble[3] = {6, 27, 10};
            return wimble; }
    }
    static int err[3] = {0, 0, 0};
    return err;
}

void stats_deploy() {
    srand(time(0));
    int * stat = save_reader();
    float ran = ((float)rand())/(float)RAND_MAX;
    int * e_stat = enemy_stats_gen((rand()%4)+1);
    int * p_stat = player_stats_gen((rand()%4)+1);
    for (int i = 0; i < 6; i++) {
        if (i <= 2) {
            save_writer(i, p_stat[i]);
        } else if (i >= 3) {
            save_writer(i, e_stat[i-3]);
        }
    }
    for (int i = 1; i < 6; i++) {
        if (i == 1 || i == 2 || i == 4 || i == 5) {
            save_writer(i, round(stat[i]/(ran*(1.12-0.96)+0.96)));
        }
    }
    save_writer(7, 1); // potion set to 1x
    save_writer(8, 1); // spear set to 1x
    save_writer(9, 1); // poison set to 1x
    save_writer(10, 0); // reset poison effects
}
