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

test-scanner: scanner test.cmm
	@ ./scanner test.cmm
	
clean:
	@ rm -f parser scanner lex.yy.c syntax.tab.c syntax.tab.h

# Run with my DIY test-case
test: parser inputs/test.cmm out.ir
	@ ./parser inputs/test.cmm out.ir

# Run with test-case whose filename is behind "-"
t-%: parser inputs/%.cmm
	@ ./parser inputs/$*.cmm out.ir
	
# Run and CHECK my result with the ANSWER
c-%: parser inputs/%.cmm
	@ ./parser inputs/$*.cmm out.ir
	@ echo ''
	@ diff out.ir expects/$*.exp
