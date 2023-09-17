#include "kub.h"
#include <iostream>

int main() {
    std::vector<Token> tokens = lex("../test/t1.kub");
    try {
        std::cout << "output tokens \n";
        for (const Token &token: tokens) {
            std::cout << token.value << " " << token.line << ":" << token.column << "\n";
        }

    } catch (...) {
        return 1;
    }
    return 0;
}
