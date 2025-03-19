.PHONY: test clean
 
zip:
	@ cd .. && make zip

lex.yy.c: lexical.l
	@ flex $<

syntax.tab.c: syntax.y lex.yy.c
	@ bison -d $<

scanner: lex.yy.c main.c
	@ gcc lex.yy.c main.c -lfl -o scanner

parser: syntax.tab.c semantic.c main.c
	@ gcc syntax.tab.c semantic.c main.c -lfl -ly -o parser

test-scanner: scanner test.cmm
	@ ./scanner test.cmm
	
clean:
	@ rm -f scanner lex.yy.c syntax.tab.c syntax.tab.h

# Run with my DIY test-case
test: parser inputs/test.cmm
	@ ./parser inputs/test.cmm

# Run with test-case whose filename is behind "-"
t-%: parser inputs/%.cmm
	@ ./parser inputs/$*.cmm
	
# Run and output the result into file "out.txt"
io-%: parser inputs/%.cmm
	@ ./parser inputs/$*.cmm > out.txt

# Run and CHECK my result with the ANSWER
c-%: parser inputs/%.cmm
	@ ./parser inputs/$*.cmm > out.txt
	@ echo ''
	@ diff out.txt expects/$*.exp

# Run bison in Debug-Mode
debug-%: syntax.y lex.yy.c main.c inputs/test-%.cmm
	@ bison -d -t syntax.y
	@ gcc syntax.tab.c main.c -lfl -ly -o parser
	@ echo ''
	@ ./parser inputs/test-$*.cmm