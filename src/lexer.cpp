//
// Created by boon4681 on 9/16/2023.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "kub.h"
#include "lexer.h"

#define keyword(b) \
    B = #b;         \
    bool b = false;           \
    if (text.at(i) == B.at(0) && !found) { \
        int m = 0; \
        for (; m < B.length(); m++) { \
            if(text.at(i+m) != B.at(m)) break; \
        } \
        if (m == B.length()) {     \
            std::cout << "FOUND \"" << B << "\" " << m << "\n"; \
            i+=m; \
            found = true;     \
            b = true; \
        } \
    } \
    if (found && b)

#define at_equal(i, c) \
    (text.at(i) == c)

#define token(typ, value, len) {TokenType::typ, value, ln, i - len}

#define eat(len) text.substr(i, len)
#define shift(len) i+=len; found=true

#define readable() if(i >= max) { break; } else

#define try_to_read(typ, char) if (at_equal(i, char) && !found) { \
    std::cout << "FOUND " << char << '\n'; \
    tokens.push_back(token(typ, eat(1), 0)); \
    shift(1); \
}

std::vector<Token> lex(const std::string &path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cout << "KUB LEX ERROR: FAILED TO OPEN \"" << path << "\"" << std::endl;
        return {};
    }
    std::string text;
    std::vector<Token> tokens;
    int ln = 1;
    while (std::getline(file, text)) {
        std::cout << text << "\n";
        int i = 0;
        size_t max = text.length();
        std::string B;
        bool found;
        while (i < max) {
            found = false;
            readable() {
                try_to_read(ASSIGN, '=')
            }
            readable() {
                try_to_read(LPRNT, '(')
            }
            readable() {
                try_to_read(RPRNT, ')')
            }
            readable() {
                try_to_read(ADD, '+')
            }
            readable() {
                try_to_read(SUB, '-')
            }
            readable() {
                try_to_read(MULT, '*')
            }
            readable() {
                try_to_read(DIV, '/')
            }
            readable() {
                int ws = whitespace(i, text);
                if (ws > 0) {
                    tokens.push_back(token(WS, eat(ws), 0));
                    shift(ws);
                }
            }
            readable() {
                keyword(let) {
                    tokens.push_back(token(LET, "let", 3));
                }
            }
            readable() {
                int ident = identifier(i, text);
                if (ident) {
                    tokens.push_back(token(IDENT, eat(ident), 0));
                    shift(ident);
                }
            }
            readable() {
                int num = number(i, text);
                if (num) {
                    tokens.push_back(token(NUMBER, eat(num), 0));
                    shift(num);
                }
            }
            readable() {
                int str = string(i, text);
                if (str) {
                    tokens.push_back(token(IDENT, eat(str), 0));
                    shift(str);
                }
            }
            if (!found) {
                std::cout << "ERROR: KUB Lexer Unknown syntax at " << "'" << text.at(i) << "' " << ln << ":" << i
                          << "\n";
                throw;
            }
        }
        ln++;
    }
    return tokens;
}

int identifier(int shift, std::string text) {
    // [a-zA-Z_][a-zA-Z_0-9]
    // 65 -- 90 A-Z
    // 97 -- 122 a-z
    // 48 -- 57 0-9
    // 95 _
    int i = 0;
    size_t max = text.length() - shift;
    int k = shift + i;
    char a = text.at(k);
    if (!(is_A_to_Z(a) || is_a_to_z(a) || a == 95)) {
        return 0;
    }
    i++;
    while (i < max) {
        k = shift + i;
        a = text.at(k);
        if (is_A_to_Z(a) || is_a_to_z(a) || a == 95 || is_digit(a)) {
            i++;
        } else {
            break;
        }
    }
    return i;
}

int string(int shift, std::string text) {
    int i = 0;
    int k = shift + i;
    size_t max = text.length() - shift;
    if (!at_equal(k, '"')) {
        return 0;
    }
    i++;
    while (i < max) {
        k = shift + i;
        if (at_equal(k, '\n') || at_equal(k, '\r')) {
            throw;
        }
        if (at_equal(k, '"')) {
            i++;
            break;
        }
        i++;
    }
    return i;
}

int number(int shift, const std::string &text) {
    int i = 0;
    i = integer(shift, text);
    if (i) return i;
    i = nfloat(shift, text);
    if (i) return i;
    return 0;
}

int integer(int shift, std::string text) {
    // [1-9][0-9]+ | [0-9]
    int i = 0;
    int k = shift + i;
    size_t max = text.length() - shift;
    char a = text.at(k);
    if (is_digit_no_zero(a)) {
        i++;
        while (i < max) {
            k = shift + i;
            a = text.at(k);
            if (!is_digit(a)) {
                break;
            }
            i++;
        }
        return i;
    }
    if (is_digit(a)) {
        return 1;
    }
    return 0;
}

int nfloat(int shift, std::string text) {
    // integer "." [0-9]+
    int n_int = integer(shift, text);
    if (n_int) {
        int i = n_int;
        if (!at_equal(shift + i, '.')) {
            throw;
        }
        i++;
        int tail = integer(shift + i, text);
        i += tail;
        if (tail) {
            return i;
        } else {
            throw;
        }
    }
    return 0;
}

int whitespace(int shift, std::string text) {
    // [ \t\n\r]*
    int k;
    int i = 0;
    size_t max = text.length() - shift;
    while (i < max) {
        k = shift + i;
        if (at_equal(k, ' ') ||
            at_equal(k, '\t') ||
            at_equal(k, '\r') ||
            at_equal(k, '\n')
                ) {
            i++;
        } else {
            break;
        }
    }
    return i;
}

bool is_A_to_Z(char a) {
    return a >= 65 && a <= 90;
}

bool is_a_to_z(char a) {
    return a >= 97 && a <= 122;
}

bool is_digit(char a) {
    return a >= 48 && a <= 57;
}

bool is_digit_no_zero(char a) {
    return a > 48 && a <= 57;
}