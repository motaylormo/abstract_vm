#ifndef OPERANDFACTORY_HPP
# define OPERANDFACTORY_HPP

# include "IOperand.class.hpp"
# include "Operand.class.hpp"

class OperandFactory
{
	public:
		IOperand const * createOperand( eOperandType type, std::string const & value ) const;

	private:
		IOperand const *createInt8( std::string const & value ) const;
		IOperand const *createInt16( std::string const & value ) const;
		IOperand const *createInt32( std::string const & value ) const;
		IOperand const *createFloat( std::string const & value ) const;
		IOperand const *createDouble( std::string const & value ) const;
};


ssize_t		str_to_ssizet(std::string const &str);
long double	str_to_longdouble(std::string const &str);

#endif