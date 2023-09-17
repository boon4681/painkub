//
// Created by boon4681 on 9/16/2023.
//

#ifndef KUB_H
#define KUB_H

#include <string>
#include <vector>

enum class TokenType {
    IDENT,
    STRING,
    LET,
    WS,
    LPRNT,
    RPRNT,
    ASSIGN,
    NUMBER,
    ADD,
    SUB,
    DIV,
    MULT
};

struct Token {
    TokenType type;
    std::string value;
    int line;
    int column;
};

std::vector<Token> lex(const std::string &path);

#endif //KUB_H
