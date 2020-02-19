#ifndef __IDENT_H__
#define __IDENT_H__

#include "Lexeme.h"
#include <cstring>

class Ident
{
    char* name;
    bool declare;
    type_of_lex type;
    bool assign;
    int value;
public:
    Ident() { declare = false; assign = false; }
    char* get_name() { return name; }
    void put_name(const char *n)
    {
        name = new char[ strlen(n)+1];
        strcpy(name,n);
    }
    bool get_declare() { return declare; }
    void put_declare() { declare = true; }
    type_of_lex get_type() { return type; }
    void put_type(type_of_lex t) { type = t; }
    bool get_assign() { return assign; }
    void put_assign() { assign = true; }
    int get_value() { return value; }
    void put_value(int v) { value = v; }
};

#endif