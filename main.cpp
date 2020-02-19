#include <iostream>
#include <cstring>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <stack>
#include <string>
#include "Lexeme.h"
#include "Ident.h"
#include "Tabl_ident.h"
#include "Scanner.h"
#include "Parser.h"
#include "Interpretator.h"

using namespace std;

Tabl_ident TID(1000);

int main (int argc , char ** argv)
{
	if (argc != 2) 
	{
		cout << "Pass the file name as argument" << endl;
		return 1;
	}
  	try
  	{
		Interpretator I (argv[1]);
        I.interpretation ();
    	/*Parser P("program.txt");
    	P.analyze ();*/
    	return 0;
  	}
  	catch (char c)
  	{
    	cout << "unexpected symbol " << c << endl;
    	return 1;
  	}
  	catch (Lex l)
  	{
    	cout << "unexpected lexeme";
    	cout << l;
    	return 1;
  	}
  	catch ( const char *source )
  	{
    	cout << source << endl;
    	return 1;
  	}
}
