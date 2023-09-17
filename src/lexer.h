//
// Created by boon4681 on 9/17/2023.
//

#ifndef KUB_LEXER_H
#define KUB_LEXER_H

bool is_A_to_Z(char a);

bool is_a_to_z(char a);

bool is_digit(char a);

bool is_digit_no_zero(char a);

int identifier(int shift, std::string text);

int whitespace(int shift, std::string text);

int string(int shift, std::string text);

int integer(int shift, std::string text);

int nfloat(int shift, std::string text);

int number(int shift, const std::string &text);

#endif //KUB_LEXER_H
