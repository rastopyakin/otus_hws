#include <iostream>
#include <cctype>

int char2price(char ch) {
    if (std::isalpha(ch)) {
        int alphabet_number = ch - 'a';
        return alphabet_number % 3 + 1;
    }
    else switch (ch) {
        case '.': return 1;
            break;
        case ',': return 2;
            break;
        case '!': return 3;
            break;
        case ' ': return 1;
            break;
        default:
            return 0;
            break;
        }
}

int main(int argc, char *argv[]) {
    char ch;
    int price = 0;
    while ((ch = std::getchar()) != '\n') {
        price += char2price(ch);
    }
    std::cout << price << std::endl;
    return 0;
}
