#include "OperandFactory.class.hpp"
#include <sstream>

// ************************************************************************** //
//		private
// ************************************************************************** //
template <typename T>
static void	error_OverflowUnderflow(long double val)
{
	if (val > std::numeric_limits<T>::max())
		throw std::overflow_error("Value overflow");
	if (val < std::numeric_limits<T>::lowest())//	loweest
		throw std::underflow_error("Value underflow");
}


IOperand const* OperandFactory::createInt8(std::string const &str) const
{
	ssize_t val = str_to_ssizet(str);
	error_OverflowUnderflow<int8_t>(val);
	return (new Operand<int8_t>(Int8, val));
}

IOperand const* OperandFactory::createInt16(std::string const &str) const
{
	ssize_t val = str_to_ssizet(str);
	error_OverflowUnderflow<int16_t>(val);
	return (new Operand<int16_t>(Int16, val));
}

IOperand const* OperandFactory::createInt32(std::string const &str) const
{
	ssize_t val = str_to_ssizet(str);
	error_OverflowUnderflow<int32_t>(val);
	return (new Operand<int32_t>(Int32, val));
}

IOperand const* OperandFactory::createFloat(std::string const &str) const
{
	long double val = str_to_longdouble(str);
	error_OverflowUnderflow<float>(val);
	return (new Operand<float>(Float, val));
}

IOperand const* OperandFactory::createDouble(std::string const &str) const
{
	long double val = str_to_longdouble(str);
	error_OverflowUnderflow<double>(val);
	return (new Operand<double>(Double, val));
}

// ************************************************************************** //
//		public
// ************************************************************************** //
IOperand const* OperandFactory::createOperand(eOperandType type, std::string const &str) const
{
	IOperand const* (OperandFactory::*func[])(std::string const &str) const = {
		[Int8] = &OperandFactory::createInt8,
		[Int16] = &OperandFactory::createInt16,
		[Int32] = &OperandFactory::createInt32,
		[Float] = &OperandFactory::createFloat,
		[Double] = &OperandFactory::createDouble
	};
	return ( (this->*func[type])(str) );
}

// ************************************************************************** //
//		convert
// ************************************************************************** //
ssize_t	str_to_ssizet(std::string const &str)
{
	std::stringstream ss = std::stringstream(str);
	ssize_t val;
	ss >> val;
	return (val);

/*	std::string::size_type sz = 0;
	long long val = std::stoll(str, &sz, 10);
	return (val);*/
}

long double	str_to_longdouble(std::string const &str)
{
	std::stringstream ss = std::stringstream(str);
	long double val;
	ss >> val;
	return (val);
}