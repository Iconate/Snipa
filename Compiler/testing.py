from luaparser import *
import sys, pprint
from pyparsing import *
import operator

#=====================================================================================================================================================
#Test
pretty = pprint.PrettyPrinter(width=50)
ast = AST()
test1 =  "if (x ==3) then x=6; y=6; elseif x==6 then a=2; b=3; elseif x==6 then c=1; d=2; elseif r==2 then r=2; s=4; else z=1; a=2; end"
ast.parse_text(test1)
print 'C-d to exit'
while 1:
    try:
	ast.parse_text(raw_input('> '))
        print 'AST', "="*50
        #pretty.pprint(ast.root)
        print 'solved', '='*47
        #print ast.solve()
    except EOFError:
        print
        sys.exit(0)        
    except ParseException, err:
        print err.line
        print " " * (err.column-1) + "^"
        print err
