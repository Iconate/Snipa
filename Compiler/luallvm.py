from llvm import *
from llvm.core import *

binop_module = Module.new('binop_mod')
ty_int = Type.int()
int2param_func = Type.function(ty_int, [ty_int, ty_int])
int1param_func = Type.function(ty_int, [ty_int])

class llvm(object):

	def add():
		f_add = binop_module.add_function(int2param_func, "add")
		f_add.args[0].name = "a"
		f_add.args[1].name = "b"
		bb = f_add.append_basic_block("entry")
		builder = Builder.new(bb)
		tmp = builder.add(f_add.args[0], f_add.args[1], "tmp")
		builder.ret(tmp)


	def sub():
		f_sub = binop_module.add_function(int2param_func, "sub")
		f_sub.args[0].name = "a"
		f_sub.args[1].name = "b"
		bb = f_sub.append_basic_block("entry")
		builder = Builder.new(bb)
		tmp = builder.sub(f_sub.args[0], f_sub.args[1], "tmp")
		builder.ret(tmp)

	def mult():
		f_mult = binop_module.add_function(int2param_func, "mult")
		f_mult.args[0].name = "a"
		f_mult.args[1].name = "b"
		bb = f_mult.append_basic_block("entry")
		builder = Builder.new(bb)
		tmp = builder.mul(f_mult.args[0], f_mult.args[1], "tmp")
		builder.ret(tmp)


	def div():
		f_div = binop_module.add_function(int2param_func, "div")
		f_div.args[0].name = "a"
		f_div.args[1].name = "b"
		bb = f_div.append_basic_block("entry")
		builder = Builder.new(bb)
		tmp = builder.udiv(f_div.args[0], f_div.args[1], "tmp")
		builder.ret(tmp)

	def neg():
		f_neg = binop_module.add_function(int1param_func, "div")
		f_neg.args[0].name = "a"
		bb = f_neg.append_basic_block("entry")
		builder = Builder.new(bb)
		tmp = builder.neg(f_neg.args[0], "tmp")
		builder.ret(tmp)
		




		

		

















