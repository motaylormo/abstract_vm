#ifndef MUTANTSTACK_HPP
# define MUTANTSTACK_HPP

#include <iostream>
#include <stack>
#include <deque>
#include <iterator>

template<typename T>
class MutantStack : public std::stack<T> {

public:

//	iterator declaration
	typedef typename std::stack<T>::container_type::iterator iterator;

	iterator	begin(void)	{ return (this->c.begin()); }
	iterator	end(void)	{ return (this->c.end()); }

//	reverse_iterator declaration
	typedef typename std::stack<T>::container_type::reverse_iterator reverse_iterator;

	reverse_iterator	rbegin(void)	{ return (this->c.rbegin()); }
	reverse_iterator	rend(void)		{ return (this->c.rend()); }

};

#endif