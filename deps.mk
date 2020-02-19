main.o: main.cpp Lexeme.h Ident.h Tabl_ident.h Scanner.h Parser.h Stack.h \
 Poliz.h Interpretator.h Executer.h
Parser.o: Parser.cpp Parser.h Lexeme.h Scanner.h Tabl_ident.h Ident.h \
 Stack.h Poliz.h
Scanner.o: Scanner.cpp Scanner.h Lexeme.h Tabl_ident.h Ident.h
Tabl_ident.o: Tabl_ident.cpp Tabl_ident.h Ident.h Lexeme.h
Interpretator.o: Interpretator.cpp Interpretator.h Executer.h Lexeme.h \
 Poliz.h Parser.h Scanner.h Tabl_ident.h Ident.h Stack.h
