#include "VM.class.hpp"

// ************************************************************************** //
//		errors
// ************************************************************************** //

//	If the number of values on the stack is strictly inferior to 2,
//		the program execution must stop with an error.
bool	VM::error_StackSize(MutantStack<IOperand const*>::iterator &e1,
							MutantStack<IOperand const*>::iterator &e2)
{
	if (this->_stack.size() < 2)
	{
		throw std::length_error("Stack composed of less that two values when arithmetic instruction executed");
		return (true);
	}
	e1 = this->_stack.begin();
	e2 = e1 + 1;
	this->_stack.pop();
	this->_stack.pop();
	return (false);
}

//	If the divisor is equal to 0,
//		the program execution must stop with an error.
bool	VM::error_By0(IOperand const *op2, std::string str)
{
	if (str_to_longdouble(op2->toString()) == 0)
	{
		throw std::invalid_argument(str + " by 0");
		return (true);
	}
	return (false);
}

bool	VM::error_EmptyStack(std::string str)
{
	if (this->_stack.size() < 1)
	{
		throw std::invalid_argument("Instruction " + str + " on an empty stack");
		return (true);
	}
	return (false);
}

// ************************************************************************** //
//		basics
// ************************************************************************** //
void	VM::push(IOperand const *v)
{
	this->_stack.push(v);
}

void	VM::pop(void)
{
	if (!this->error_EmptyStack("pop"))
		this->_stack.pop();
}

//	 Displays each value of the stack,
//		from the most recent one to the oldest one
//		WITHOUT CHANGING the stack.
//	Each value is separated from the next one by a newline.
void	VM::dump(void)
{
	this->error_EmptyStack("dump");

	for (MutantStack<IOperand const*>::reverse_iterator
		it = this->_stack.rbegin(); it != this->_stack.rend(); ++it)
	{
		std::cout << (*it)->toString() << std::endl;
	}
}

//	 Asserts that the value at the top of the stack is equal
//		to the one passed as parameter for this instruction.
//	If it is not the case, the program execution must stop with an error.
static std::string		opStr(IOperand const *v)
{
	std::string	type_name[] = {
		[Int8] = "int8",
		[Int16] = "int16",
		[Int32] = "int32",
		[Float] = "float",
		[Double] = "double",
	};
	return (type_name[v->getType()] + "(" + v->toString() + ")");
}

void	VM::assert(IOperand const *v)
{
	this->error_EmptyStack("assert");

	IOperand const *	top_op = this->_stack.top();
	if ((v->toString()).compare(top_op->toString()) != 0)
	{
		throw std::invalid_argument("Assert false: stack "
			+ opStr(top_op) + " vs parameter " + opStr(v));
	}
}

//	Asserts that the value at the top of the stack is an 8-bit integer.
//	(If not, see the instruction assert),
//	then interprets it as an ASCII value and
//		displays the corresponding character on the standard output.
void	VM::print(void)
{
	this->error_EmptyStack("print");

	IOperand const *	top_op = this->_stack.top();
	if (top_op->getType() == Int8)
	{
		char c = stoi(top_op->toString());
		std::cout << c << std::endl;
	}
	else
		throw std::invalid_argument("Assert false: print not int8");
}

void	VM::exit(void)
{
    std::exit(EXIT_FAILURE);
}

// ************************************************************************** //
//		math
// ************************************************************************** //
void	VM::add(void)
{
	MutantStack<IOperand const*>::iterator e1, e2;
	if (!this->error_StackSize(e1, e2))
		this->_stack.push( *(*e1) + *(*e2) );
}
void	VM::sub(void)
{
	MutantStack<IOperand const*>::iterator e1, e2;
	if (!this->error_StackSize(e1, e2))
		this->_stack.push( *(*e1) - *(*e2) );
}
void	VM::mul(void)
{
	MutantStack<IOperand const*>::iterator e1, e2;
	if (!this->error_StackSize(e1, e2))
		this->_stack.push( *(*e1) * *(*e2) );
}

void	VM::div(void)
{
	MutantStack<IOperand const*>::iterator e1, e2;
	if (!this->error_StackSize(e1, e2)
		&& !this->error_By0(*e2, "Division"))
			this->_stack.push( *(*e1) / *(*e2) );
}
void	VM::mod(void)
{
	MutantStack<IOperand const*>::iterator e1, e2;
	if (!this->error_StackSize(e1, e2)
		&& !this->error_By0(*e2, "Modulo"))
			this->_stack.push( *(*e1) % *(*e2) );
}