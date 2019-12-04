#include "Operand.class.hpp"
#include "OperandFactory.class.hpp"

//	for toString()
#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>      // std::stringstream

// ************************************************************************** //
//		Coplien's form
// ************************************************************************** //
template <class T>
Operand<T>::Operand(){}

template <class T>
Operand<T>::Operand(eOperandType type, T val) :
	_type(type), _value(val){}

template <class T>
Operand<T>::~Operand(){}

//	copy constructor
template <class T>
Operand<T>&		Operand<T>::operator = (Operand const &rhs)
{
	this->_type = rhs._type;
	this->_value = rhs._value;
	return (*this);
}

template <class T>
Operand<T>::Operand(Operand const & copy)
{
	*this = copy;
}

// ************************************************************************** //
//		getters
// ************************************************************************** //
template <class T>
int				Operand<T>::getPrecision(void) const
{
	return (this->_type);
}

template <class T>
eOperandType	Operand<T>::getType(void) const
{
	return (this->_type);
}

template <class T>
std::string const&	Operand<T>::toString(void) const
{
	std::stringstream ss;
	if (this->_type == Int8)//	int8 otherwise isn't counted right
		ss << (int)this->_value;
	else
		ss << this->_value;
	std::string const *str = new std::string(ss.str());
	return (*str);
}

// ************************************************************************** //
//		MATH
// ************************************************************************** //
#define GREATER(a, b)	((a > b) ? a : b)
#define	FP_OR_INT	((rhs.getType() == Float || rhs.getType() == Double) ? \
						str_to_longdouble(rhs.toString()) : \
						str_to_ssizet(rhs.toString()) )

template <class T>
IOperand const *	Operand<T>::operator + (IOperand const &rhs) const
{
	OperandFactory factory;
	return (factory.createOperand(
				GREATER(this->getType(), rhs.getType()),
				std::to_string(this->_value + FP_OR_INT)
			));
}

template <class T>
IOperand const *	Operand<T>::operator - (IOperand const & rhs) const
{
	OperandFactory factory;
	return (factory.createOperand(
				GREATER(this->getType(), rhs.getType()),
				std::to_string(this->_value - FP_OR_INT)
			));
}

template <class T>
IOperand const *	Operand<T>::operator * (IOperand const & rhs) const
{
	OperandFactory factory;
	return (factory.createOperand(
				GREATER(this->getType(), rhs.getType()),
				std::to_string(this->_value * FP_OR_INT)
			));
}

template <class T>
IOperand const *	Operand<T>::operator / (IOperand const & rhs) const
{
	OperandFactory factory;
	return (factory.createOperand(
				GREATER(this->getType(), rhs.getType()),
				std::to_string(this->_value / FP_OR_INT)
			));
}

template <class T>
IOperand const *	Operand<T>::operator % (IOperand const & rhs) const
{
	OperandFactory factory;
	return (factory.createOperand(
				GREATER(this->getType(), rhs.getType()),
				std::to_string((ssize_t)this->_value % str_to_ssizet(rhs.toString()))
			));
}

//Template HARD Define
template class Operand<int8_t>;
template class Operand<int16_t>;
template class Operand<int32_t>;
template class Operand<float>;
template class Operand<double>;