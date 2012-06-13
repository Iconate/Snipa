from definitions import *
import sys, pprint
from pyparsing import *
import operator

class symTable(object):
    def __init__(self):
	self.symTab = [];

    def printTable(self):
	print "No | VarName |     Kind     |   Type   | Parameters"
	print "="*50
	for i in range(0,len(self.symTab)):
		print i , " |   ", self.symTab[i][0], "   | ",self.symTab[i][1], " | ",self.symTab[i][2], " | ",self.symTab[i][3]

    def checkList(self, n):
	for i in range(0,len(self.symTab)):
	    if n == self.symTab[i][0]:
	        return True
	return False


    def checkType(self, n , ntype):
	for i in range(0,len(self.symTab)):
		if n == self.symTab[i][0]:
			if(ntype == self.symTab[i][2]):
				return True
			else:
				return False

    def addElemt(self,name,kind,ntype, para):
	self.symTab.append([name,kind,ntype,para])

class luatype(object):
    def __init__(self):
 	#==========================================================================================================================
	#Types
	self.intnumber = Word(nums).setParseAction(lambda t: int(t[0]))
	self.floatnumber = Word(nums+'.'+nums).setParseAction(lambda t: float(t[0]))
	self.expnumber = ((self.intnumber ^ self.floatnumber) + oneOf("e E") + Optional(Literal("-")) + self.intnumber)

	self.hexnumber = (Literal('0x') + Word("0123456789abcdef"))
	self.number = self.intnumber ^ self.floatnumber ^ self.expnumber ^ self.hexnumber
	self.number.setParseAction(self.returnNumType)

	self.name  = Word(alphas+"_", alphanums+"_")
	self.name.setParseAction(self.returnNamType)

	self.hexdigit = oneOf("0 1 2 3 4 5 6 7 8 9 0 a b c d e f") 

	self.unicodeEscape = Literal('\\') + Literal('u') + self.hexdigit + self.hexdigit + self.hexdigit + self.hexdigit

	self.octalEscape = Literal('\\') + oneOf("0 1 2 3") + oneOf("0 1 2 3 4 5 6 7") + oneOf("0 1 2 3 4 5 6 7") ^\
		Literal('\\') + oneOf("0 1 2 3 4 5 6 7") + Optional(oneOf("0 1 2 3 4 5 6 7"))

	self.escapeseq = Literal('\\') + oneOf("b t n f r \" \' \\") ^ self.unicodeEscape ^ self.octalEscape

	self.normalstring = Literal('"') + Word(alphas+"_", nums+"_") + Literal('"') 
	self.charstring = Literal('\'')  + self.escapeseq + NotAny(Literal('\\') ^ Literal('\'')) + Literal('\'') 
	self.longstring = Literal('[') + Word("=") + Literal('[') + self.escapeseq + NotAny(Literal('\\') ^ Literal(']'))  + Literal(']') + Word("=") + Literal(']')
	self.string = self.normalstring ^ self.charstring ^ self.longstring
	self.string.setParseAction(self.returnStrType)
	
	self.ws = Literal(' ') ^ Literal('\t') ^ Literal('\u000C')

	self.newline = Optional('\r') + Literal('\n')

	self.boolean = Literal("false") ^ Literal("true")
	self.boolean.setParseAction(self.returnBooType)
	
	self.type = self.boolean ^ self.number ^ self.string ^ self.name

    def returnBooType(self):
	return "BOOLEAN"

    def returnNumType(self):
	return "NUMBER"

    def returnNamType(self):
	return "NAME"

    def returnStrType(self):
	return "STRING"

    def parse_type(self, t):
	if not isinstance(t, type([])):
		if isinstance(t, str):
			ntype = self.type.parseString(t)
			print ntype
			return ntype
		ntype = self.type.parseString(str(t))
		return ntype
	elif(t[1] == "\"" and t[2] == "\""):
		return ['STRING']
	elif(self.parse_type(t[1])[0] == self.parse_type(t[2])[0]):
		return self.parse_type(t[2])
	else:
		print "Type Conflict"
		exit(3)
	
#=======================================================================================================================================================
#AST
class AST(object):
    def __init__(self):
	self.st = symTable()
        root = None
        opDict = {
            '+': lambda x, y: x + y,
            'u-': lambda x: -x,
            '-': lambda x, y: x - y,
            '*': lambda x, y: x * y,
            '/': lambda x, y: x / y,
            '^': lambda x, y: x ** y
            }
	
	#==========================================================================================================================
	#Grammar
	self.intnumber = Word(nums).setParseAction(lambda t: int(t[0]))
	self.floatnumber = Word(nums+'.'+nums).setParseAction(lambda t: float(t[0]))
	self.expnumber = ((self.intnumber ^ self.floatnumber) + oneOf("e E") + Optional(Literal("-")) + self.intnumber)

	self.hexnumber = (Literal('0x') + Word("0123456789abcdef"))
	self.number = self.intnumber ^ self.floatnumber ^ self.expnumber ^ self.hexnumber

	self.name  = Word(alphas+"_", alphanums+"_")

	self.hexdigit = oneOf("0 1 2 3 4 5 6 7 8 9 0 a b c d e f") 

	self.unicodeEscape = Literal('\\') + Literal('u') + self.hexdigit + self.hexdigit + self.hexdigit + self.hexdigit

	self.octalEscape = Literal('\\') + oneOf("0 1 2 3") + oneOf("0 1 2 3 4 5 6 7") + oneOf("0 1 2 3 4 5 6 7") ^\
		Literal('\\') + oneOf("0 1 2 3 4 5 6 7") + Optional(oneOf("0 1 2 3 4 5 6 7"))

	self.escapeseq = Literal('\\') + oneOf("b t n f r \" \' \\") ^ self.unicodeEscape ^ self.octalEscape

	self.normalstring = Literal('"') + Word(alphas+"_", alphanums+"_")  + Literal('"')
	self.charstring = Literal('\'')  + self.escapeseq + NotAny(Literal('\\') ^ Literal('\'')) + Literal('\'') 
	self.longstring = Literal('[') + Word("=") + Literal('[') + self.escapeseq + NotAny(Literal('\\') ^ Literal(']'))  + Literal(']') + Word("=") + Literal(']')
	self.string = self.normalstring ^ self.charstring ^ self.longstring

	self.ws = Literal(' ') ^ Literal('\t') ^ Literal('\u000C')

	self.newline = Optional('\r') + Literal('\n')

	self.unop = minus ^ Literal('not') ^ Literal('#')
	self.binop = add ^ minus ^ times ^ divide ^ power ^ percent ^ twodot ^ great ^ greate ^ lower ^ lowere ^ equality ^ notequal ^ Literal('and') ^ Literal('or')
	self.exp = Forward()
	self.fieldsep = coma ^ semi
	self.field = slpar + self.exp + srpar + equal + self.exp ^ self.name + equal + self.exp ^ self.exp
	self.fieldlist = self.field + ZeroOrMore(self.fieldsep + self.field) + Optional(self.fieldsep)

	self.tableconstructor = clpar + Optional(self.fieldlist) + crpar
	self.namelist = self.name + ZeroOrMore(coma + self.name)

	self.parlist1 = self.namelist + ZeroOrMore(coma + threedot) ^ threedot

	self.block = Forward()

	self.funcbody = lpar + Optional(self.parlist1) + rpar + self.block + end

	self.function = Literal('function') + self.funcbody

	self.explist1 = ZeroOrMore(self.exp + coma) + self.exp

	self.args = lpar + Optional(self.explist1) + rpar ^ self.tableconstructor ^ self.string

	self.nameAndArgs = Optional(colon + self.name) + self.args

	self.var = Forward()

	self.varSuffix = ZeroOrMore(self.nameAndArgs) + (slpar + self.exp + srpar ^ dot + self.name)

	self.varOrExp = self.var ^ lpar + self.exp + rpar

	self.functioncall = self.varOrExp + OneOrMore(self.nameAndArgs)

	self.prefixexp = self.varOrExp + ZeroOrMore(self.nameAndArgs)

	self.var << (self.name ^ lpar + self.exp + rpar + self.varSuffix) + ZeroOrMore(self.varSuffix)

	self.exp << (nil ^ false ^ true ^ self.number ^ self.string ^ threedot ^ self.function ^ self.prefixexp ^ self.tableconstructor ^ self.unop + self.exp) + ZeroOrMore(self.binop + self.exp)
	self.exp.setParseAction(self.makeExpressionNode)

	self.varlist1 = self.var + ZeroOrMore(coma + self.var)

	self.funcname = self.name + ZeroOrMore(dot + self.name) + Optional(semi + self.name)

	self.laststat = (Literal('return') + Optional(self.explist1)).setParseAction(self.makeEndNodes) ^ Literal('break')


	self.stat = (self.varlist1 + equal + self.explist1).setParseAction(self.makeVariableNode)^\
	(self.functioncall) ^\
	(do + self.block + end) ^\
	(Literal('while') + (self.exp).setParseAction(self.makeExpressionNode) + do + self.block + end).setParseAction(self.makeWhileNode) ^\
	(Literal('repeat') + self.block + Literal('until') + self.exp).setParseAction(self.makeRepeatNode) ^\
	(Literal('if') + self.exp + Literal('then') + self.block + ZeroOrMore(Literal('elseif') + self.exp + Literal('then') + self.block) + Optional(Literal('else') + self.block) + end).setParseAction(self.makeIfNode) ^\
	(Literal('for') + self.name + equal + self.exp + coma + self.exp + Optional(coma + self.exp) + do + self.block + end).setParseAction(self.makeForNode) ^\
	(Literal('for') + self.namelist + Literal('in') + self.explist1 + do + self.block + end).setParseAction(self.makeForInNode) ^\
	((Literal('function') + self.funcname + self.funcbody.setParseAction(self.makeExpressionNode))).setParseAction(self.addFunction) ^\
	(Literal('local') + self.namelist + Optional(equal + self.explist1)) ^\
	(Literal('local') + Literal('function') + self.name + self.funcbody)
	self.stat.setParseAction()

	self.chunk = ZeroOrMore(self.stat + Optional(semi)) + Optional(self.laststat + Optional(semi))
	self.chunk.setParseAction()

	self.block << self.chunk
	    
    def solve(self):
        def dfs(node):
            # not a list
            if not isinstance(node, type([])):
                return node
            # call the lambda, keyed on the operator
            if node[0] == 'u-':
                return opDict[self.node[0]](dfs(self.node[1]))
            else:
                return opDict[self.node[0]](dfs(self.node[1]),
                                            dfs(self.node[2]))
        return dfs(self.root [0])

    def makeUnopNode(self, t):
        if len(t[1:]) > 1:
            operand = t[1:]
        else:
            operand = t[1]
        if t[0] == '-' or (t[0] == 'not'):
            return [['u-', operand]]
        return [operand]
  
    def makeBinopNode(self, t):
        if t:
            return self.makeNodes(t)
  
    def makeExpressionNode(self, t):
	if t:
		self.root = self.makeNodes(t)
		return self.root   

	#make new thing for input of 4 things
	#check on last node

    def makeNodes(self, t):
        node = t[0]
        for op, operand in zip(t[1::2], t[2::2]):
            node = [op, node, operand]
        return [node]

    def makeTypeNode(self, t):
        node = t[0]
	lt = luatype()
        for op, operand in zip(t[1::2], t[2::2]):
            node = [op, node, operand]
	    print "DOING CHECK"
	    if(symTable.checkType(node[1], lt.parse_type(operand))):
		print "CHECK"
	    else:
		print "Type Conflict"
		exit(3)
        return [node]
    
    def makeEndNodes(self, t):
	print "N:", t
	node = t[0]
        for branch in (t[1::1]):
	    print node , "     " , branch
            node = [node, branch]
	    #add type checking here
        return [node]
    
    def makeVariableNode(self, t):
	if t:
		lt = luatype()
		self.root = self.makeNodes(t)
		
		vtype = lt.parse_type(self.root[0][2])
				
		if(self.st.checkList(self.root[0][1])):
			if(self.st.checkType(self.root[0][1],vtype[0])):
				print "Type Correct"
			else:
				print "Type Conflict"
				exit(3)
		else:
			print "ADD: ", t 
			self.st.addElemt(self.root[0][1],"GLOBAL_VAR",vtype[0],"None")
			self.st.printTable()
		return self.root

    def makeRepeatNode(self, t):
	print "Repeat :", t
	node = [t[0]]
	i = 1	
	while(t[i+1] == ';' or t[i+1] == 'until'):
		node.append(t[i])
		if(t[i+1] == 'until'):
			break
		i = i + 2
	node.append("until")	
	node.append(t[len(t)-1])	
	return node

    def elseIf(self, t, i, node):
	print "Init Vals: ", i, " ", t[i]	
	elseif = []
	#Recursive else if statements
	elseif.append(t[i])
	i = i + 1
		
	while(t[i+1] == ';' or t[i+1] == 'then'):	
		elseif.append(t[i])
		print "plus 1 ", t[i+1] 
		if (t[i+1] == 'else' or t[i+2] == 'else'):
			break		
		if(t[i+1] == 'then'):
			elseif.append(t[i+1])	
		i = i + 2
	node.append(elseif)
	while(t[i] != 'else' and t[i] != 'elseif'):
		print t[i]		
		i = i + 1
	
	print "We are here, i is", i, "t[i] is", t[i]
	if (t[i] == 'elseif'):
		node, i = self.elseIf(t, i, node)
	return node, i

    def makeIfNode(self, t):
	print "If :", t
	node = [t[0]]
	node.append(t[1])
	node.append(t[2])
	firstif = []
	elseif = []
	lastelse = []
	i = 3
	#Primary if X then Y
	while(t[i+1] == ';' or t[i+1] == 'else' or t[i+1] == 'elseif' or t[i+1] == 'end'):
		firstif.append(t[i])
		
		if (t[i+1] == 'else' or t[i+1] == 'elseif' or t[i+1] == 'end' or t[i+2] == 'else' or t[i+2] == 'elseif' or t[i+2] == 'end'):
			break		
		i = i + 2

	node.append(firstif)

	while(t[i] != 'else' and t[i] != 'elseif'):
		print t[i]		
		i = i + 1


    	# Multiple elseifs
	if(t[i] == 'elseif'):
		elseif, i = self.elseIf(t, i, node)
	
	
	node.append(t[i])
	i = i + 1

	#LastElse
	while(t[i+1] == ';' or t[i+1] == 'end'):
		lastelse.append(t[i])
		if (t[i+1] == 'end' or t[i+2] == 'end'):
			break
		i = i + 2

	node.append(lastelse)
	print node	
	return node

    def makeWhileNode(self, t):

	self.root  = [t[0],t[1]]
	i = 3
	self.root.append(t[i])
	while(t[i+1] == ';' or t[i+1] == 'end'):
		self.root.append(t[i])
		if (t[i+1] == 'end' or t[i+2] == 'end'):
			break
		i = i+2
	print self.root
	return self.root

    def makeForInNode(self, t):
	print "ForIn: ", t
	node = [t[0]]
	i=1
	namelist = []
	explist = []
	block = []
	while(t[i+1] != 'in'):
		namelist.append(t[i])
		i = i + 1
	namelist.append(t[i])
	node.append(namelist)
	i = i + 1
	while(t[i+1] != 'do'):
		explist.append(t[i])
		i = i + 1
	explist.append(t[i])
	node.append(explist)
	i = i + 2
	print "Current :", t[i]
	while(t[i+1] == ';' or t[i+1] == 'end'):
		block.append(t[i])
		if (t[i+1] == 'end' or t[i+2] == 'end'):
			break
		i = i+2
	node.append(block)
	print "ForIn :", node
	return node

    def makeForNode(self, t):
	print "For: " ,t
	i = 3
	node = [t[0], t[1]]
	var = []
	if (t[2] != '='):
		print "Expected ="
		exit(3)
	while(t[i] != 'do'):
		if ( i == 6):
			print "Too many parameters "
			exit(3)
		var.append(t[i])
		i = i + 1
	i = i + 1
	node.append(var)

	while(t[i+1] == ';' or t[i+1] == 'end'):
		node.append(t[i])
		if (t[i+1] == 'end' or t[i+2] == 'end'):
			break
		i = i+2
	print "Returning from For ", node
	return node


    def addFunction(self, t):
	param = len(t[2])-1
	print param
	if t:
		lt = luatype()
		vtype = lt.parse_type(t[2][0])
		if(self.st.checkList(t[1])):
			if(self.st.checkType(t[1],'FUNCTION')):
				print "Type Correct"
			else:
				print "Type Conflict"
				exit(3)
		else:
			print "ADD: ", t 
			self.st.addElemt(t[1],'GLOBAL_FUNCTION','UNKNOWN',("Params=",param))
			self.st.printTable()

    def parse_text(self,text):
	self.block.parseString(text)
	

