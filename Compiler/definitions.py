from pyparsing import *

#=======================================================================================================================================================
#Definitions
#Boolean
true = Literal('true')
false = Literal('false')
nil = Literal('nil')

#Parenthesis
clpar, crpar = map(Suppress, "{}")
slpar, srpar = map(Suppress, "[]")
lpar,  rpar = map(Suppress, "()")

#Separators
dot = Literal('.')
twodot = Literal('..')
threedot = Literal('...')
coma = Suppress(Literal(','))
semi = Literal(';')
colon = Literal(':')

#Equations
minus = Literal('-')
add = Literal('+')
times = Literal('*')
divide = Literal('/')
power = Literal('^')
great = Literal('>')
percent = Literal('%')
greate = Literal('>=')
lower = Literal('<')
lowere = Literal('<=')
equal = Literal('=')
equality = Literal('==')
notequal = Literal('~=')


#commands
do = Literal('do')
end = Literal('end')