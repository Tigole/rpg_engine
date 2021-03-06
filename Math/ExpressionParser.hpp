#ifndef _EXPRESSION_PARSER_HPP
#define _EXPRESSION_PARSER_HPP 1

#include <string>
#include <cmath>
#include <algorithm>
#include <cctype>
#include "VariableList.hpp"

template<typename T>
bool fn_Evaluate_Plus(T a, T b, T& res)
{
	res = a + b;
	return true;
}

template<typename T>
bool fn_Evaluate_Minus(T a, T b, T& res)
{
	res = a - b;
	return true;
}

template<typename T>
bool fn_Evaluate_Multiply(T a, T b, T& res)
{
	res = a * b;
	return true;
}

template<typename T>
bool fn_Evaluate_Divide(T a, T b, T& res)
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
bool fn_Evaluate_Power(T a, T b, T& res)
{
	res = (T)std::pow((double)a, (double)b);
	return true;
}

template<typename T>
bool fn_Evaluate_Modulo(T a, T b, T& res)
{
	res = a%b;
	return true;
}

template<typename T>
class ExpressionParser
{
public:
	ExpressionParser()
	 :	m_error(),
		m_postfix_expression(),
		m_operators(),
		m_result()
	{
		m_operators['+'] = Operator<T>('+', 1, 0, &fn_Evaluate_Plus);
		m_operators['-'] = Operator<T>('-', 1, 0, &fn_Evaluate_Minus);
		m_operators['*'] = Operator<T>('*', 2, 1, &fn_Evaluate_Multiply);
		m_operators['/'] = Operator<T>('/', 2, 1, &fn_Evaluate_Divide);
		m_operators['^'] = Operator<T>('^', 3, 1, &fn_Evaluate_Power);
		m_operators['%'] = Operator<T>('%', 3, 1, &fn_Evaluate_Modulo);
		m_operators['('] = Operator<T>('(', 0, 0, nullptr);
	}

	bool mt_Parse(const std::string& expression, const VariableList& var_list)
	{
		bool l_ret(true);
		std::string numeric_expression(expression);
		std::string var_name;
		std::string::size_type var_pos;
		std::string var_value;

		/** Transform variables into their values **/
		for (auto it = numeric_expression.begin(); (l_ret == true) && (it != numeric_expression.end()); it++)
		{
			if (mt_Is_White_Space(*it) == false)
			{
				if ((mt_Is_Operator(*it) == false) && (*it != ')') && ((*it > '9') || (*it < '0')))
				{
					var_name.push_back(*it);
				}
				else if (var_name.size() != 0)
				{
					l_ret = var_list.mt_Get_Variable(var_name, var_value);
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
			l_ret = var_list.mt_Get_Variable(var_name, var_value);
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
			l_ret = mt_Parse(numeric_expression);

		return l_ret;
	}

	bool mt_Parse(const std::string& expression)
	{
		bool l_ret(true);
		std::stack<Operator<int>> stack;
		unsigned int i(0);
		typename std::map<char, Operator<int>>::iterator it;


		log().mt_Entrance_Function(FUNCTION_NAME);

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
				/*log().mt_Start_Block(&expression[i]);
				log() << "m_postfix_expression.size() : " << m_postfix_expression.size() << "\n";
				log() << "m_postfix_expression.back() : " << m_postfix_expression.back() << "\n";
				log() << "stack.size() : " << stack.size() << "\n";
				log() << "expression[i] : " << expression[i] << "\n";*/
				if (mt_Is_White_Space(expression[i]) == false)
				{
					if (std::isdigit(expression[i]))
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
				//log().mt_End_Block();
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

		for (auto l_it = m_postfix_expression.begin(); l_it != m_postfix_expression.end(); l_it++)
		{
			if (l_it->size() == 0)
			{
				l_it = m_postfix_expression.erase(l_it) - 1;
			}
		}

		log().mt_Exit_Function();

		return l_ret;
	}

	const std::string& mt_Get_Error(void) const
	{
		return m_error;
	}

	bool mt_Get_Result(T& res)
	{
		std::stack<std::string> operands;
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
			if (mt_Is_Operator(*it) == true)
			{
				auto l_it = m_operators.find((*it)[0]);

				str_b = operands.top();
				operands.pop();
				if (operands.size() < 1)	/** "-6+5" -> "6 - 5 +" -> "0 6 - 5 +" -> "0-6+5" **/
				{
					str_a = misc::fn_Number_To_String(l_it->second.m_null_element);
				}
				else
				{
					str_a = operands.top();
					operands.pop();
				}

				mt_String_To_T(str_a, t_a);
				mt_String_To_T(str_b, t_b);

				l_ret = l_it->second.m_evaluate(t_a, t_b, res);
				if (l_ret == true)
				{
					mt_T_To_String(res, str_a);
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
		mt_String_To_T(operands.top(), res);
		return l_ret;
	}

private:
	bool mt_Is_White_Space(char c)
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

	template<typename Type>
	struct Operator
	{
		Operator() : m_char('\0'), m_priority(-1), m_null_element(), m_evaluate(nullptr){}
		Operator(	char op,
					int priority,
					Type null_element,
					bool(*evaluate)(Type a, Type b, Type& res))
			: 	m_char(op),
				m_priority(priority),
				m_null_element(null_element),
				m_evaluate(evaluate)
		{}
		char m_char;
		int m_priority;
		Type m_null_element;
		bool(*m_evaluate)(Type a, Type b, Type& res);
	};

	bool mt_Is_Operator(char c) const
	{
		return (m_operators.find(c) != m_operators.end());
	}

	bool mt_Is_Operator(const std::string& str) const
	{
		bool l_ret(false);
		if (str.size() == 1)
			l_ret = mt_Is_Operator(str[0]);
		return l_ret;
	}

	void mt_String_To_T(const std::string& str, T& t) const
	{
		std::stringstream ss;
		ss << str;
		ss >> t;
	}

	void mt_T_To_String(T t, std::string& str) const
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
