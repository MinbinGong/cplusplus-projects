// contadapt/Stack.hpp

/*
 * Stack.hpp
 * - safer and more convenient stack class
 */

#ifndef STACK_HPP
#define STACK_HPP

#include <deque>
#include <exception>

template <typename T>
class Stack {
protected:
	std::deque<T> c;

public:
	class ReadEmptyStack : public std::exception {
	public:
		virtual const char* what() const throw() {
			return "read empty stack";
		}
	};

	typename std::deque<T>::size_type size() const {
		return c.size();
	}

	bool empty() const {
		return c.empty();
	}

	void push(const T& elem) {
		c.push_back(elem);
	}

	T pop() {
		if (c.empty())
		{
			throw ReadEmptyStack();
		}

		T elem(c.back());
		c.pop_back();
		return elem;
	}

	T& top() {
		if (c.empty())
		{
			throw ReadEmptyStack();
		}
		return c.back();
	}
};
#endif // !STACK_HPP
