#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include <string>

bool estOperateur(char c);

bool expressionValideTableau(const std::string& expression);
bool expressionValideListe(const std::string& expression);

#endif