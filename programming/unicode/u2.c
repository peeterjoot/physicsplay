#include <stdio.h>

int main() {
    // UTF-8 encoded symbols in a string
    const char *hearts = "\xE2\x99\xA5";
    const char *diamonds = "\xE2\x99\xA6";
    const char *spades = "\xE2\x99\xA0";
    const char *clubs = "\xE2\x99\xA3";

    printf("Hearts: %s, Diamonds: %s, Spades: %s, Clubs: %s\n", hearts, diamonds, spades, clubs);
    return 0;
}
