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

void	lexed_to_deque(char *file, std::deque<int> *tokens, std::deque<std::string> *strs)
{
	FlexLexer*	lexer = new yyFlexLexer();
	int			tkn;
	bool		exit_flag = false;

	if (file)
	{
		std::ifstream* filestream = new std::ifstream(file);
		if (filestream->good() == 0)
		{
			perror("Can't open file");
			exit(0);
		}
		lexer->switch_streams(filestream);
	}

	while ((tkn = lexer->yylex()))
	{
		if (tkn == (int)septype::EndStream)
			break;
		if (tkn == (int)septype::Space)
			;
		else
		{
			tokens->push_back(tkn);
			strs->push_back(lexer->YYText());
			if (tkn == (int)commandtype::Exit)
				exit_flag = true;
		}
	}
	if (exit_flag == false)
	{
		std::cout << B_RED << BOLD << "Error: " << COLOR_OFF
						<< B_RED << "No exit command given" << COLOR_OFF << std::endl;
	}

}

int	main(int argc, char **argv)
{
	VM			*vm = new VM();
	std::deque<int>			tokens;
	std::deque<std::string>	strs;

	lexed_to_deque(argc > 1 ? argv[1] : 0, &tokens, &strs);

	while (!tokens.empty())
	{
		if (tokens.front() == (int)septype::Newline)
		{
			tokens.pop_front();
			strs.pop_front();
			if (tokens.empty())
				break;
		}
		try
		{
			parse_line(vm, &tokens, &strs);
		}
		catch (std::exception& e)
		{
			std::cout << B_RED << BOLD << "Error: " << COLOR_OFF
						<< B_RED << e.what() << COLOR_OFF << std::endl;
			//	pop off until \n
			while (!tokens.empty() && (tokens.front() != (int)septype::Newline))
			{
				tokens.pop_front();
				strs.pop_front();
			}
		}
	}

}
