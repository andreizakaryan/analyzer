#include "Parser.h"

void Parser::dec ( type_of_lex type ) 
{
  int i;
  while ( !st_int.is_empty()) 
  {
    i = st_int.pop();
    if ( TID[i].get_declare() ) 
      throw "twice";
    else 
    {
      TID[i].put_declare();
      TID[i].put_type(type);
    }
  }
}
 
void Parser::check_id () 
{
  if ( TID[c_val].get_declare() )
    st_lex.push ( TID[c_val].get_type() );
  else 
    throw "not declared";
}
 
void Parser::check_op () 
{
  type_of_lex t1, t2, op, t = LEX_INT, r = LEX_BOOL;
 
  t2 = st_lex.pop();
  op = st_lex.pop();
  t1 = st_lex.pop();
  if (op == LEX_PLUS || op == LEX_MINUS || op == LEX_TIMES || op == LEX_SLASH)
    r = LEX_INT;
  if (op == LEX_OR || op == LEX_AND)
    t = LEX_BOOL;
  if (t1 == t2  &&  t1 == t) 
    st_lex.push(r);
  else
    throw "wrong types are in operation";
  prog.put_lex (Lex (op) );
}
 
void Parser::check_not () 
{
  if (st_lex.pop() != LEX_BOOL)
    throw "wrong type is in not";
  else 
  {
    st_lex.push (LEX_BOOL);
    prog.put_lex (Lex (LEX_NOT));
  }
}
 
void Parser::eq_type () 
{
  if (st_lex.pop() != st_lex.pop())
    throw "wrong types are in :=";
}
 
void Parser::eq_bool () 
{
  if ( st_lex.pop() != LEX_BOOL )
    throw "expression is not boolean";
}

void Parser::eq_int()
{
    if (st_lex.pop() != LEX_INT) 
        throw "expression is not integer";
}

void Parser::check_id_in_read ()
{
  if ( !TID [c_val].get_declare() )
    throw "not declared";
}

void Parser::pbeg(vertex& v)
{
	if (c_type == LEX_PROGRAM){
		v = P1;
		gl();
	}
	else {
		throw "'program' expected";
	}
}

void Parser::p1(vertex& v)
{
	st_l.push("(PY");
    v = Ybeg;
}

void Parser::ybeg(vertex& v)
{
	if (c_type == LEX_VAR){
		v = Y1;
		gl();
	}
	else {
		throw "'var' expected";
	}
}

void Parser::y1(vertex& v)
{
	st_l.push("(YD");
    v = Dbeg;
}

void Parser::dbeg(vertex& v)
{
	if (c_type == LEX_ID){
		v = D1;
        st_int.push(c_val);
		gl();
	}
	else {
		throw "identificator expected";
	}
}

void Parser::d1(vertex& v)
{
	if (c_type == LEX_COLON){
		v = D2;
		gl();
	}
	else if (c_type == LEX_COMMA){
		v = Dbeg;
		gl();
	}
	else {
		throw "colon or comma expected";
	}
}

void Parser::d2(vertex& v)
{
	if (c_type == LEX_BOOL || c_type == LEX_INT){
		v = Dend;
        dec(c_type);
		gl();
	}
	else {
		throw "'bool' or 'int' expected";
	}
}

void Parser::dend(vertex& v)
{
	if (st_l.top() == "(YD") {
        st_l.pop();
        v = Yend;
    }
    else {
        throw "Wrong (YD";
    }
}

void Parser::yend(vertex& v)
{
	if (c_type == LEX_COMMA) {
		v = Y1;
		gl();
	}
    else if (st_l.top() == "(PY") {
        st_l.pop();
        v = P2;
    }
    else {
        throw "Wrong (PY";
    }
}

void Parser::p2(vertex& v)
{
	if (c_type == LEX_SEMICOLON) {
		v = P3;
		gl();
	}
    else {
        throw "semicolon expected";
    }
}

void Parser::p3(vertex& v) 
{
	st_l.push("(PB");
    v = Bbeg;
}

void Parser::bbeg(vertex& v)
{
	if (c_type == LEX_BEGIN) {
		v = B1;
		gl();
	}
    else {
        throw "'begin' expected";
    }
}

void Parser::b1(vertex& v) 
{
	st_l.push("(BS");
    v = Sbeg;
}

void Parser::b2(vertex& v)
{
	if (c_type == LEX_SEMICOLON) {
		v = B1;
		gl();
	}
	else if (c_type == LEX_END) {
		v = Bend;
		gl();
	}
    else {
        throw "'end' or semicolon expected";
    }
}

void Parser::bend(vertex& v)
{
	if (st_l.top() == "(PB") {
        st_l.pop();
        v = P4;
    }
    else if (st_l.top() == "(SB") {
        st_l.pop();
        v = Send;
    }
    else {
        throw "Wrong (PB";
    }
}

void Parser::p4(vertex& v)
{
	if (c_type == LEX_FIN) {
		v = Pend;
	}
    else {
        throw "'@' expected";
    }
}

void Parser::sbeg(vertex& v)
{
	if (c_type == LEX_ID) {
		v = S1;
        check_id();
        prog.put_lex(Lex (POLIZ_ADDRESS, c_val));
		gl();
	}
	else if (c_type == LEX_IF) {
		v = S3;
		gl();
	}
	else if (c_type == LEX_WHILE) {
		v = S8;
		gl();
	}
	else if (c_type == LEX_READ) {
		v = S11;
		gl();
	}
	else if (c_type == LEX_WRITE) {
		v = S14;
		gl();
	}
    else if (c_type == LEX_FOR) {
        v = S17;
        gl();
    }
    else if (c_type == LEX_SEMICOLON || c_type == LEX_END) {
        v = Send;
    }
	else {
		st_l.push("(SB");
    	v = Bbeg;
	}
}

void Parser::s1(vertex& v)
{
	if (c_type == LEX_ASSIGN) {
		v = S2;
		gl();
	}
    else {
        throw "':=' expected";
    }
}

void Parser::s2(vertex& v) 
{
	st_l.push("(SE1");
    v = Ebeg;
}

void Parser::s3(vertex& v) 
{
	st_l.push("(SE2");
    v = Ebeg;
}

void Parser::s4(vertex& v) 
{
	if (c_type == LEX_THEN) {
		v = S5;
		gl();
	}
    else {
        throw "'then' expected";
    }
}

void Parser::s5(vertex& v) 
{
	st_l.push("(SS1");
    v = Sbeg;
}

void Parser::s6(vertex& v) 
{
	if (c_type == LEX_ELSE) {
		v = S7;
		gl();
	}
    else {
        throw "'else' expected";
    }
}

void Parser::s7(vertex& v) 
{
	st_l.push("(SS2");
    v = Sbeg;
}

void Parser::s8(vertex& v) 
{
	st_l.push("(SE3");
    temp.pl0 = prog.get_free();
    temp_st.push(temp);
    v = Ebeg;
}

void Parser::s9(vertex& v) 
{
	if (c_type == LEX_DO) {
		v = S10;
		gl();
	}
    else {
        throw "'do' expected";
    }
}

void Parser::s10(vertex& v) 
{
	st_l.push("(SS3");
    v = Sbeg;
}

void Parser::s11(vertex& v) 
{
	if (c_type == LEX_LPAREN) {
		v = S12;
		gl();
	}
	else {
		throw "'(' expected";
	}
}

void Parser::s12(vertex& v) 
{
	if (c_type == LEX_ID) {
		v = S13;
        check_id_in_read();
        prog.put_lex(Lex(POLIZ_ADDRESS, c_val));
		gl();
	}
	else {
		throw "identificator expected";
	}
}

void Parser::s13(vertex& v) 
{
	if (c_type == LEX_RPAREN) {
		v = Send;
        prog.put_lex(Lex(LEX_READ));
		gl();
	}
	else {
		throw "')' expected";
	}
}

void Parser::s14(vertex& v) 
{
	if (c_type == LEX_LPAREN) {
		v = S15;
		gl();
	}
	else {
		throw "'(' expected";
	}
}

void Parser::s15(vertex& v) 
{
	st_l.push("(SE4");
	v = Ebeg;
}

void Parser::s16(vertex& v) 
{
	if (c_type == LEX_RPAREN) {
		v = Send;
        prog.put_lex(Lex(LEX_WRITE));
		gl();
	}
	else {
		throw "')' expected";
	}
}

void Parser::s17(vertex& v) 
{
    if (c_type == LEX_ID) {
        v = S18;
        check_id();
        if (st_lex.vtop() != LEX_INT) {
            throw "expression is not int";
        }
        prog.put_lex(Lex(POLIZ_ADDRESS, c_val));
        prog.put_lex(Lex(POLIZ_ADDRESS, c_val));
        gl();
    }
    else {
        throw "id expected";
    }
}

void Parser::s18(vertex& v)
{
    if (c_type == LEX_ASSIGN) {
        v = S19;
        gl();
    }
    else {
        throw "':=' expected";
    }
}

void Parser::s19(vertex& v)
{
    st_l.push("(SE5");
    v = Ebeg;
}

void Parser::s20(vertex& v)
{
    if (c_type == LEX_TO) {
        v = S21;
        gl();
    }   
    else {
        throw "'to' expected";
    }
}

void Parser::s21(vertex& v)
{
    st_l.push("(SE6");
    v = Ebeg;
}

void Parser::s22(vertex& v)
{
    if (c_type == LEX_DO) {
        v = S23;
        gl();
    }
    else {
        throw "'do' expected";
    }
}


void Parser::s23(vertex& v)
{
    st_l.push("(SS4");
    v = Sbeg;
}

void Parser::send(vertex& v)
{
	if (st_l.top() == "(BS") {
        st_l.pop();
        v = B2;
    }
    else if (st_l.top() == "(SS1") {
        st_l.pop();
        Temp tmp = temp_st.top();
        temp_st.pop();
        temp.pl1 = prog.get_free();
        temp_st.push(temp);
        prog.blank();
        prog.put_lex(Lex(POLIZ_GO));
        prog.put_lex(Lex(POLIZ_LABEL, prog.get_free()), tmp.pl0);
        v = S6;
    }
    else if (st_l.top() == "(SS2") {
        st_l.pop();
        Temp tmp = temp_st.top();
        temp_st.pop();
        prog.put_lex(Lex(POLIZ_LABEL, prog.get_free()), tmp.pl1);
        v = Send;
    }
    else if (st_l.top() == "(SS3") {
        st_l.pop();
        Temp tmp = temp_st.top();
        temp_st.pop();
        prog.put_lex(Lex(POLIZ_LABEL, tmp.pl0));
        prog.put_lex(Lex(POLIZ_GO));
        prog.put_lex(Lex(POLIZ_LABEL, prog.get_free()), tmp.pl1);
        v = Send;
    }
    else if (st_l.top() == "(SS4") {
        st_l.pop();
        v = Send;
    }
    else {
        throw "Wrong (BS";
    }
}

void Parser::ebeg(vertex& v) 
{
	st_l.push("(EX1");
    v = Xbeg;
}

void Parser::xbeg(vertex& v) 
{
	st_l.push("(XT");
    v = Tbeg;	
}

void Parser::tbeg(vertex& v) 
{
	st_l.push("(TF");
    v = Fbeg;
}


void Parser::x1(vertex& v)
{
    if (c_type == LEX_OR || c_type == LEX_PLUS || c_type == LEX_MINUS) {
        v = Tbeg;
        st_l.push("(XT2");
        st_lex.push(c_type);
        gl();
    }
    else {
        v = Xend;
    }
}

void Parser::t1(vertex& v) 
{
    if (c_type == LEX_AND || c_type == LEX_TIMES || c_type == LEX_SLASH) {
          v = Fbeg;
          st_l.push("(TF2");
          st_lex.push(c_type);
          gl();
    }   
    else {
        v = Tend;
    }
}

void Parser::fbeg(vertex& v) 
{
	if (c_type == LEX_LPAREN) {
        v = F1;
        gl();
    }
    else if (c_type == LEX_NOT) {
        v = F3;
        gl();
    }
    else if (c_type == LEX_ID) {
        v = Fend;
        check_id();
        prog.put_lex(curr_lex);
        gl();
    }
    else if (c_type == LEX_NUM) {
        v = Fend;
        st_lex.push(LEX_INT);
        prog.put_lex(curr_lex);
        gl();
    }
    else if (c_type == LEX_TRUE || c_type == LEX_FALSE) {
        v = Fend;
        st_lex.push(LEX_BOOL);
        prog.put_lex(curr_lex);
        gl();
    }
    else {
        throw "Wrong Lexeme";
    }
}

void Parser::f1(vertex& v) 
{
	st_l.push("(FE");
    v = Ebeg;
}

void Parser::f3(vertex& v) 
{
	st_l.push("(FF");
    v = Fbeg;
}

void Parser::fend(vertex& v) 
{
	if (st_l.top() == "(TF") {
        st_l.pop();
        v = T1;
    }
    else if (st_l.top() == "(FF") {
        st_l.pop();
        check_not();
        v = Fend;
    }
    else if (st_l.top() == "(TF2") {
        st_l.pop();
        check_op();
        v = T1;
    }
    else {
        throw "Wrong (TF";
    }
}

void Parser::tend(vertex& v) 
{
    if (st_l.top() == "(XT") {
        st_l.pop();
        v = X1;
    }
    else if (st_l.top() == "(XT2"){
        st_l.pop();
        check_op();
        v = X1;
    }
    else {
        throw "Wrong (XT";
    }
}

void Parser::xend(vertex& v) 
{
	if (c_type == LEX_OR || c_type == LEX_PLUS || c_type == LEX_MINUS) {
        v = Xbeg;
        gl();
    }
    else if (st_l.top() == "(EX1") {
        st_l.pop();
        v = E1;
    }
    else if (st_l.top() == "(EX2") {
        st_l.pop();
        check_op();
        v = Eend;
    }
    else {
        throw "Wrong (EX1 or (EX2";
    }
}

void Parser::e1(vertex& v) 
{
	if (c_type == LEX_EQ || c_type == LEX_LSS || c_type == LEX_GTR||
        c_type == LEX_NEQ || c_type == LEX_LEQ || c_type == LEX_GEQ) {
        v = E2;
        st_lex.push(c_type);
        gl();
    }
    else {
        v = Eend;
    }
}

void Parser::e2(vertex& v) 
{
	st_l.push("(EX2");
    v = Xbeg;
}

void Parser::eend(vertex& v) 
{
	if (st_l.top() == "(PE") {
        st_l.pop();
        v = Pend;
    }
    else if (st_l.top() == "(FE") {
        st_l.pop();
        v = F2;
    }
    else if (st_l.top() == "(SE1") {
        st_l.pop();
        eq_type();
        prog.put_lex(LEX_ASSIGN);
        v = Send;
    }
    else if (st_l.top() == "(SE2") {
        st_l.pop();
        //cout << "a\n";
        eq_bool();
        //cout << "b\n";
        temp.pl0 = prog.get_free();
        prog.blank();
        prog.put_lex(POLIZ_FGO);
        temp_st.push(temp);
        v = S4;
    }
    else if (st_l.top() == "(SE3") {
        st_l.pop();
        eq_bool();
        temp.pl1 = prog.get_free();
        prog.blank();
        prog.put_lex(Lex(POLIZ_FGO));
        temp_st.push(temp);
        v = S9;
    }
    else if (st_l.top() == "(SE4") {
        st_l.pop();
        st_lex.pop();
        v = S16;
    }
    else if (st_l.top() == "(SE5") {
        st_l.pop();
        eq_type();
        prog.put_lex(Lex(LEX_ASSIGN));
        v = S20;
    }
    else if (st_l.top() == "(SE6") {
        st_l.pop();
        eq_int();

        v = S22;
    }
    else {
        while (!st_l.empty()) {
            //cout << st_l.top() << endl;
            st_l.pop();
        }
        throw "Wrong (PE";
    }
}

void Parser::f2(vertex& v) 
{
	if (c_type == LEX_RPAREN) {
        v = Fend;
        gl();
    }
    else {
        throw "Wrong Lexeme";
    }
}

void Parser::pend(vertex& v) 
{
}


void Parser::analyze ()
{
  	gl();
  	st_l.push("(st");
  	vertex v = Pbeg;
  	fptr arr[] = {&Parser::pbeg, &Parser::pend , &Parser::ebeg, &Parser::e1,
  	 			  &Parser::e2, &Parser::eend, &Parser::xbeg, &Parser::xend, 
  	 			  &Parser::tbeg, &Parser::tend, &Parser::fbeg, &Parser::f1, 
    		 	  &Parser::f2, &Parser::f3, &Parser::fend, &Parser::p1, &Parser::p2, 
    		 	  &Parser::p3, &Parser::p4, &Parser::bbeg, &Parser::b1, &Parser::b2, 
                  &Parser::bend, &Parser::ybeg, &Parser::y1, &Parser::yend, 
                  &Parser::dbeg, &Parser::d1, &Parser::d2, &Parser::dend, 
                  &Parser::sbeg, &Parser::s1, &Parser::s2, &Parser::s3, 
                  &Parser::s4, &Parser::s5, &Parser::s6, &Parser::s7, &Parser::s8,
                  &Parser::s9, &Parser::s10, &Parser::s11, &Parser::s12, &Parser::s13,
                  &Parser::s14, &Parser::s15, &Parser::s16, &Parser::s17, &Parser::s18,
                  &Parser::s19, &Parser::s20, &Parser::s21, &Parser::s22, &Parser::s23,
                  &Parser::send, &Parser::t1, &Parser::x1};
  	do {
        //cout << v << " ";
  		(this->*arr[v])(v);
  	} while (v != Pend);
  	if (st_l.top() != "(st") {
    	throw "L_Stack is not empty";
  	}
  	else {
    	st_l.pop();
  	}
}
