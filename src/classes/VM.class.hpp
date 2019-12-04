# include "IOperand.class.hpp"
# include "OperandFactory.class.hpp"
# include "Operand.class.hpp"
# include "MutantStack.class.hpp"

#undef assert

class VM
{

public:
		void	push(IOperand const *v);
		void	pop(void);
		void	dump(void);
		void	assert(IOperand const *v);
		void	print(void);
		void	exit(void);

		void	add(void);
		void	sub(void);
		void	mul(void);
		void	div(void);
		void	mod(void);


	private:
		MutantStack<IOperand const*>	_stack;


		bool	error_EmptyStack(std::string str);
		bool	error_StackSize(MutantStack<IOperand const*>::iterator &e1,
								MutantStack<IOperand const*>::iterator &e2);
		bool	error_By0(IOperand const *op2, std::string str);

};