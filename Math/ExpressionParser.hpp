#ifndef _EXPRESSION_PARSER_HPP
#define _EXPRESSION_PARSER_HPP 1

#include <string>
#include "VariableList.hpp"

template<typename T>
bool evaluatePlus(T a, T b, T& res)
{
	res = a + b;
	return true;
}

template<typename T>
bool evaluateMinus(T a, T b, T& res)
{
	res = a - b;
	return true;
}

template<typename T>
bool evaluateMultiply(T a, T b, T& res)
{
	res = a * b;
	return true;
}

template<typename T>
bool evaluateDivide(T a, T b, T& res)
{
	bool l_ret(false);
	if (b != 0)
	{
		res = a / b;
		l_ret = true;
	}
	return l_ret;
}

template<typename T>
bool evaluatePower(T a, T b, T& res)
{
	res = std::pow((double)a, (double)b);
	return true;
}

template<typename T>
bool evaluateModulo(T a, T b, T& res)
{
	res = a%b;
	return true;
}

template<typename T>
class ExpressionParser
{
public:
	ExpressionParser()
	{
		m_operators['+'] = Operator<T>('+', 1, OP_AS_LEFT, 0, &evaluatePlus);
		m_operators['-'] = Operator<T>('-', 1, OP_AS_LEFT, 0, &evaluateMinus);
		m_operators['*'] = Operator<T>('*', 2, OP_AS_LEFT, 1, &evaluateMultiply);
		m_operators['/'] = Operator<T>('/', 2, OP_AS_LEFT, 1, &evaluateDivide);
		m_operators['^'] = Operator<T>('^', 3, OP_AS_RIGHT, 1, &evaluatePower);
		m_operators['%'] = Operator<T>('%', 3, OP_AS_LEFT, 1, &evaluateModulo);
		m_operators['('] = Operator<T>('(', 0, OP_AS_LEFT, 0, nullptr);
	}

	bool parse(const std::string& expression, const VariableList& var_list)
	{
		bool l_ret(true);
		std::string numeric_expression(expression);
		std::string var_name;
		std::string::size_type var_pos;
		std::string var_value;

		/** Transform variables into their values **/
		for (auto it = numeric_expression.begin(); (l_ret == true) && (it != numeric_expression.end()); it++)
		{
			if (isWhiteSpace(*it) == false)
			{
				if ((isOperator(*it) == false) && (*it != ')') && ((*it > '9') || (*it < '0')))
				{
					var_name.push_back(*it);
				}
				else if (var_name.size() != 0)
				{
					l_ret = var_list.getVariable(var_name, var_value);
					if (l_ret == true)
					{
						var_pos = numeric_expression.find(var_name);
						numeric_expression.erase(var_pos, var_name.size());
						numeric_expression.insert(var_pos, var_value);
						it = numeric_expression.begin();
						var_name.resize(0);
					}
					else
					{
						m_error = "Unknown variable : \"" + var_name + "\"";
					}
				}
			}
		}

		if (var_name.size() != 0)
		{
			l_ret = var_list.getVariable(var_name, var_value);
			if (l_ret == true)
			{
				var_pos = numeric_expression.find(var_name);
				numeric_expression.erase(var_pos, var_name.size());
				numeric_expression.insert(var_pos, var_value);
				var_name.resize(0);
			}
			else
			{
				m_error = "Unknown variable : \"" + var_name + "\"";
			}
		}

		if (l_ret == true)
			l_ret = parse(numeric_expression);

		return l_ret;
	}

	bool parse(const std::string& expression)
	{
		bool l_ret(true);
		std::stack<Operator<int>> stack;
		unsigned int i(0);
		std::map<char, Operator<int>>::iterator it;


		log().entranceFunction(FUNCTION_NAME);

		if (expression.size() == 0)
		{
			l_ret = false;
			m_error = "Expression is empty";
		}
		else if (std::count(expression.begin(), expression.end(), '(') != std::count(expression.begin(), expression.end(), '('))
		{
			l_ret = false;
			m_error = "Different number of \"(\" and \")\"";
		}

		m_postfix_expression.resize(1);
		m_postfix_expression.back() = "";

		/** Postfix expression **/
		if (l_ret)
		{
			while ((l_ret == true) && (i < expression.size()))
			{
				/*log().startBlock(&expression[i]);
				log() << "m_postfix_expression.size() : " << m_postfix_expression.size() << "\n";
				log() << "m_postfix_expression.back() : " << m_postfix_expression.back() << "\n";
				log() << "stack.size() : " << stack.size() << "\n";
				log() << "expression[i] : " << expression[i] << "\n";*/
				if (isWhiteSpace(expression[i]) == false)
				{
					if (std::isdigit(expression[i], std::locale()))
						m_postfix_expression.back() += expression[i];
					else
					{
						m_postfix_expression.push_back("");
						if ((expression[i] != ' ') && (expression[i] != '\t') && (expression[i] != '\n') && (expression[i] != '\r'))
						{
							if (expression[i] == ')')
							{
								bool stop_unstack(stack.size() == 0);
								while (stop_unstack == false)
								{
									char op(stack.top().m_char);
									stack.pop();
									if (op != '(')
										m_postfix_expression.push_back(std::string(1, op));
									m_postfix_expression.push_back("");

									stop_unstack = (stack.size() == 0) || (op == '(');
								}
								m_postfix_expression.push_back("");
							}
							else
							{
								it = m_operators.find(expression[i]);
								if (it != m_operators.end())
								{
									if (stack.size() != 0)
									{
										if (stack.top().m_priority < it->second.m_priority)
											stack.push(it->second);
										else
										{
											m_postfix_expression.back() = std::string(1, stack.top().m_char);
											m_postfix_expression.push_back("");
											stack.pop();
											stack.push(it->second);
										}
									}
									else
									{
										stack.push(it->second);
									}
								}
								else
								{
									l_ret = false;
									m_error = std::string("Operator unknown \"") + expression[i] + "\"";
								}
							}
						}
					}
				}
				i++;
				//log().endBlock();
			}

			bool stop_unstack(stack.size() == 0);
			while (stop_unstack == false)
			{
				char op(stack.top().m_char);
				stack.pop();
				if (op != '(')
					m_postfix_expression.push_back(std::string(1, op));
				m_postfix_expression.push_back("");

				stop_unstack = (stack.size() == 0) || (op == '(');
			}
			m_postfix_expression.push_back("");
		}

		for (auto it = m_postfix_expression.begin(); it != m_postfix_expression.end(); it++)
		{
			if (it->size() == 0)
			{
				it = m_postfix_expression.erase(it) - 1;
			}
		}

		log().exitFunction();

		return l_ret;
	}

	const std::string& getError(void) const
	{
		return m_error;
	}

	bool getResult(T& res)
	{
		std::stack<std::string> operands;
		auto it(m_operators.end());
		std::string str_a, str_b;
		T t_a, t_b;
		bool l_ret(true);

		if (m_postfix_expression.size() == 0)
		{
			l_ret = false;
			m_error = "No expression to evaluate";
		}

		for (auto it = m_postfix_expression.begin(); (it != m_postfix_expression.end()) && (l_ret == true); it++)
		{
			if (isOperator(*it) == true)
			{
				auto l_it = m_operators.find((*it)[0]);

				str_b = operands.top();
				operands.pop();
				if (operands.size() < 1)	/** "-6+5" -> "6 - 5 +" -> "0 6 - 5 +" -> "0-6+5" **/
				{
					str_a = misc::numberToString(l_it->second.m_null_element);
				}
				else
				{
					str_a = operands.top();
					operands.pop();
				}

				stringToT(str_a, t_a);
				stringToT(str_b, t_b);

				l_ret = l_it->second.m_evaluate(t_a, t_b, res);
				if (l_ret == true)
				{
					TtoString(res, str_a);
					operands.push(str_a);
				}
				else
				{
					m_error = "Failed to evaluate \"" + str_a + " " + l_it->second.m_char + " " + str_b;
				}
			}
			else
			{
				operands.push(*it);
			}
		}
		stringToT(operands.top(), res);
		return l_ret;
	}

private:
	bool isWhiteSpace(char c)
	{
		bool l_ret(false);

		if ((c == ' ')
			|| (c == '\t')
			|| (c == '\b')
			|| (c == '\n')
			|| (c == '\r'))
			l_ret = true;

		return l_ret;
	}

	enum OperatorAssociativity
	{
		OP_AS_LEFT,
		OP_AS_RIGHT
	};

	template<typename T>
	struct Operator
	{
		Operator() : m_char('\0'), m_priority(-1), m_associativity(OP_AS_LEFT){}
		Operator(char op, int priority, OperatorAssociativity associativity, T null_element, bool(*evaluate)(T a, T b, T& res)) : m_char(op), m_priority(priority), m_associativity(associativity), m_null_element(null_element), m_evaluate(evaluate){}
		char m_char;
		int m_priority;
		T m_null_element;
		OperatorAssociativity m_associativity;
		bool(*m_evaluate)(T a, T b, T& res);
	};

	bool isOperator(char c) const
	{
		return (m_operators.find(c) != m_operators.end());
	}

	bool isOperator(const std::string& str) const
	{
		bool l_ret(false);
		if (str.size() == 1)
			l_ret = isOperator(str[0]);
		return l_ret;
	}

	void stringToT(const std::string& str, T& t) const
	{
		std::stringstream ss;
		ss << str;
		ss >> t;
	}

	void TtoString(T t, std::string& str) const
	{
		std::stringstream ss;
		ss << t;
		ss >> str;
	}


	std::string m_error;
	std::vector<std::string> m_postfix_expression;
	std::map<char, Operator<int>> m_operators;

	T m_result;
};

#endif // !_EXPRESSION_PARSER_HPP
