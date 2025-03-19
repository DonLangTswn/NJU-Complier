.PHONY: test clean
 
zip:
	@ cd .. && make zip

lex.yy.c: lexical.l
	@ flex $<

syntax.tab.c: syntax.y lex.yy.c
	@ bison -d $<

scanner: lex.yy.c main.c
	@ gcc lex.yy.c main.c -lfl -o scanner

parser: IR.c semantic.c syntax.tab.c main.c
	@ gcc IR.c semantic.c syntax.tab.c main.c -lfl -ly -o parser

compiler: assemble.c IR.c semantic.c syntax.tab.c main.c
	@ gcc assemble.c IR.c semantic.c syntax.tab.c main.c -lfl -ly -o compiler

clean:
	@ rm -f compiler parser scanner lex.yy.c syntax.tab.c syntax.tab.h

# Run with my DIY test-case
test: compiler inputs/test.cmm out.asm
	@ ./compiler inputs/test.cmm out.asm

# Run with test-case whose filename is behind "-"
p-%: compiler inputs/%.cmm
	@ ./compiler inputs/$*.cmm out.ir
t-%: compiler inputs/%.cmm
	@ ./compiler inputs/$*.cmm out.asm
	
# Run and CHECK my result with the ANSWER
c-%: compiler inputs/%.cmm
	@ ./compiler inputs/$*.cmm out.asm
	@ echo ''
	@ diff out.asm expects/$*.exp
