#ifndef __PARSER_H__
#define __PARSER_H__

#include <stack>
#include "Lexeme.h"
#include "Scanner.h"
#include "Stack.h"
#include "Poliz.h"

extern Tabl_ident TID;

class Parser 
{
    struct Temp {
        int pl0;
        int pl1;
    };
    enum vertex {Pbeg, Pend, Ebeg, E1, E2, Eend, Xbeg, Xend, Tbeg, Tend,
    			 Fbeg, F1, F2, F3, Fend, P1, P2, P3, P4, Bbeg, B1, B2, 
                 Bend, Ybeg, Y1, Yend, Dbeg, D1, D2, Dend, Sbeg, S1, S2,
                 S3, S4, S5, S6, S7, S8, S9, S10, S11, S12, S13, S14, S15,
                 S16, S17, S18, S19, S20, S21, S22, S23, Send, T1, X1};
	typedef void (Parser::*fptr)(vertex&);
    Lex curr_lex;
    Temp temp;
    type_of_lex c_type;
    int c_val;
    Scanner scan;
    Stack<int,100> st_int;
    Stack<type_of_lex, 100>  st_lex;
    stack<string> st_l;
    stack<Temp> temp_st;
    void gl()
    {
        curr_lex = scan.get_lex();
        c_type = curr_lex.get_type();
        c_val = curr_lex.get_value();
    }
    void pbeg(vertex&);
    void pend(vertex&);
    void ebeg(vertex&);
    void e1(vertex&);
    void e2(vertex&);
    void eend(vertex&);
    void xbeg(vertex&);
    void xend(vertex&);
    void tbeg(vertex&);
    void tend(vertex&);
    void fbeg(vertex&);
    void f1(vertex&);
    void f2(vertex&);
    void f3(vertex&);
    void fend(vertex&);
    void p1(vertex&);
    void p2(vertex&);
    void p3(vertex&);
    void p4(vertex&);
    void bbeg(vertex&);
    void b1(vertex&);
    void b2(vertex&);
    void bend(vertex&);
    void ybeg(vertex&);
    void y1(vertex&);
    void yend(vertex&);
    void dbeg(vertex&);
    void d1(vertex&);
    void d2(vertex&);
    void dend(vertex&);
    void sbeg(vertex&);
    void s1(vertex&);
    void s2(vertex&);
    void s3(vertex&);
    void s4(vertex&);
    void s5(vertex&);
    void s6(vertex&);
    void s7(vertex&);
    void s8(vertex&);
    void s9(vertex&);
    void s10(vertex&);
    void s11(vertex&);
    void s12(vertex&);
    void s13(vertex&);
    void s14(vertex&);
    void s15(vertex&);
    void s16(vertex&);
    void s17(vertex&);
    void s18(vertex&);
    void s19(vertex&);
    void s20(vertex&);
    void s21(vertex&);
    void s22(vertex&);
    void s23(vertex&);
    void t1(vertex&);
    void x1(vertex&);
    void send(vertex&);
    void dec(type_of_lex type);
    void check_id ();
    void check_op ();
    void check_not ();
    void eq_type ();
    void eq_bool ();
    void eq_int();
    void check_id_in_read ();
public:
    Poliz prog;
    Parser (const char *program ) : scan (program), prog (1000) {}
    void analyze();
};

#endif
