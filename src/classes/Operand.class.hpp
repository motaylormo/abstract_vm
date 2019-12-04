#ifndef OPERAND_HPP
# define OPERAND_HPP

# include "IOperand.class.hpp"
# include "OperandFactory.class.hpp"
# include <string>

template <class T>
class Operand : public IOperand
{

	public:
	//	Coplien's form
		Operand(void);
		Operand(eOperandType type, T val);
		virtual ~Operand();
		Operand(Operand const & copy);
		Operand&	operator=(Operand const & rhs);

	//	getters
		int					getPrecision(void) const;
		eOperandType		getType(void) const;
		std::string const&	toString(void) const;

	//	math
		IOperand const* operator+(IOperand const & rhs) const;
		IOperand const* operator-(IOperand const & rhs) const;
		IOperand const* operator*(IOperand const & rhs) const;
		IOperand const* operator/(IOperand const & rhs) const;
		IOperand const* operator%(IOperand const & rhs) const;

	private:
		eOperandType	_type;
		T				_value;

};

#endif