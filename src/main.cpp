#include "classes/VM.class.hpp"
#include <iostream>
#include <string>
#include <exception>
#include <fstream>
#include <deque>
#include <FlexLexer.h>
#include "../lexer/lex_tokens.hpp"
#include "unix_colors.h"

void	parse_line(VM *vm, std::deque<int> *tokens, std::deque<std::string> *strs);

int	main(int argc, char **argv)
{
	VM			*vm = new VM();
	FlexLexer*	lexer = new yyFlexLexer();
	if (argc > 1)
	{
		std::ifstream* filestream = new std::ifstream(argv[1]);
		if (filestream->good() == 0)
		{
			perror("Can't open file");
			return (0);
		}
		lexer->switch_streams(filestream);
	}

	int	tkn;
	std::deque<int>			tokens;
	std::deque<std::string>	strs;
	bool					exit_flag = false;
	while ((tkn = lexer->yylex()) && (tkn != (int)septype::EndStream))
	{
		if (tkn == (int)septype::Space)
			;
		else
		{
			tokens.push_back(tkn);
			strs.push_back(lexer->YYText());
			if (tkn == (int)commandtype::Exit)
				exit_flag = true;
		}
	}
	if (exit_flag == false)
	{
		std::cout << B_RED << BOLD << "Error: " << COLOR_OFF
						<< B_RED << "No exit command given" << COLOR_OFF << std::endl;
	}

	while (!tokens.empty())
	{
		try
		{
			parse_line(vm, &tokens, &strs);
		}
		catch (std::exception& e)
		{
			std::cout << B_RED << BOLD << "Error: " << COLOR_OFF
						<< B_RED << e.what() << COLOR_OFF << std::endl;
		}
	}

}