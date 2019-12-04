#include "classes/VM.class.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <deque>
#include <FlexLexer.h>
#include "../lexer/lex_tokens.hpp"
#include "unix_colors.h"

std::string op_str;
// ************************************************************************** //
//		non-terminating errors
// ************************************************************************** //
static void	error_nonterm(std::string str)
{
	try
	{
		throw std::invalid_argument(str);
	}
	catch (std::exception& e)
	{
		std::cout << B_RED << BOLD << "Error: " << COLOR_OFF
					<< B_RED << e.what() << COLOR_OFF << std::endl;
	}
}

static void	error_excess(int token, std::string str)
{
	std::string type = "command";
	if (IS_OP(token))
		type = "operand";
	error_nonterm("Excess " + type + " '" + str + "' will be ignored.");
}

// ************************************************************************** //
//		execute
// ************************************************************************** //
#define NEEDS_OP(x) (x == (int)commandtype::Push || x == (int)commandtype::Assert)

void	exec_line(VM *vm, int command, IOperand const* op)
{
	if ((command == 0) && op)
		throw std::invalid_argument("Operand missing command");

	void	(VM::*func_cmd[])(void) = {
		[(int)commandtype::Pop] = &VM::pop,
		[(int)commandtype::Dump] = &VM::dump,
		[(int)commandtype::Add] = &VM::add,
		[(int)commandtype::Sub] = &VM::sub,
		[(int)commandtype::Mul] = &VM::mul,
		[(int)commandtype::Div] = &VM::div,
		[(int)commandtype::Mod] = &VM::mod,
		[(int)commandtype::Print] = &VM::print,
		[(int)commandtype::Exit] = &VM::exit,
	};
	void	(VM::*arg_func_cmd[])(IOperand const *op) = {
		[(int)commandtype::Push] = &VM::push,
		[(int)commandtype::Assert] = &VM::assert,
	};

	if (command != 0)
	{
		if (NEEDS_OP(command))
		{
			if (op)
				(vm->*arg_func_cmd[command])(op);
			else
				throw std::invalid_argument("Command missing operand");
		}
		else
		{
			if (op)
				error_excess((int)optype::Int8, op_str);
			(vm->*func_cmd[command])();;
		}
	}
}

// ************************************************************************** //
//		parse
// ************************************************************************** //
static IOperand const*	parse_op(int token, std::string str)
{
	OperandFactory	factory;
	std::string		substr = str.substr(str.find("(") + 1, str.find(")"));
	switch (token)
	{
		case (int)optype::Int8:
			return (factory.createOperand(eOperandType::Int8, substr));
			break;
		case (int)optype::Int16:
			return (factory.createOperand(eOperandType::Int16, substr));
			break;
		case (int)optype::Int32:
			return (factory.createOperand(eOperandType::Int32, substr));
			break;
		case (int)optype::Float:
			return (factory.createOperand(eOperandType::Float, substr));
			break;
		case (int)optype::Double:
			return (factory.createOperand(eOperandType::Double, substr));
			break;
	}
	return (0);
}

void	parse_line(VM *vm, std::deque<int> *tokens, std::deque<std::string> *strs)
{
	int				tkn;
	commandtype		command = (commandtype)0;
	IOperand const*	op = 0;

	while ((tkn = tokens->front()) && (tkn != (int)septype::Newline))
	{
		if (tkn == (int)septype::Error)
			error_nonterm("Unknown '" + strs->front() + "'");
		else if (IS_COMMAND(tkn))
		{
			if ((int)command == 0)
				command = (commandtype)tkn;
			else
				error_excess(tkn, strs->front());
		}
		else if (IS_OP(tkn))
		{
			if (!op)
			{
				op = parse_op(tkn, strs->front());
				op_str = strs->front();
			}
			else
				error_excess(tkn, strs->front());
		}
		tokens->pop_front();
		strs->pop_front();
	}
	exec_line(vm, (int)command, op);
}
