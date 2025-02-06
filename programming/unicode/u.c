#include <stdio.h>
#include <wchar.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, ""); // Enable UTF-8 output

    wchar_t hearts = L'\u2665';
    wchar_t diamonds = L'\u2666';
    wchar_t spades = L'\u2660';
    wchar_t clubs = L'\u2663';

    wprintf(L"Hearts: %lc, Diamonds: %lc, Spades: %lc, Clubs: %lc\n", hearts, diamonds, spades, clubs);
    return 0;
}
