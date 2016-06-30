#ifndef _RESETABLE_HPP
#define _RESETABLE_HPP 1

#include <string>
#include <sstream>
#include <tinyxml.h>


#ifdef _MSC_VER
#define FUNCTION_NAME __FUNCSIG__
#else
#define FUNCTION_NAME __PRETTY_FUNCTION__
#endif // _MSC_VER

#define UNUSED_PARAMETER(x) (void)(x)

namespace misc
{

	/** \class Resetable
		\brief Base class for objects that can be reset by an external event

		\fn bool reset(void)
		\brief Method used to reset the object
		\return true on success, false otherwise
	**/
	class Resetable
	{
	public:
		virtual ~Resetable(){}

		virtual bool reset(void) = 0;
	};


	/** \class Clonable
		\brief Base class for objects that need to be cloned

		\fn Clonable* clone(void) const
		\brief Method used to clone the object
		\return A copy of the object itself dynamically created
	**/
	class Clonable
	{
	public:
		virtual ~Clonable(){}

		virtual Clonable* clone(void) const = 0;
	};

	template<typename T>
	struct Gauge
	{
		Gauge(const T& actual_value, const T& max_value) : m_actual_value(actual_value), m_max_value(max_value){}
		Gauge(const T& values) : m_actual_value(values), m_max_value(values){}
		Gauge(const Gauge<T>& copy) : m_actual_value(copy.m_actual_value), m_max_value(copy.m_max_value){}
		Gauge();

		void restore(void) { m_actual_value = m_max_value; }
		bool isEmpty(void) const { return m_actual_value <= 0; }
		bool isFull(void) const { return m_actual_value == m_max_value; }

		T m_actual_value;
		T m_max_value;
	};

	template<typename T>
	Gauge<T>& operator+=(Gauge<T>& g, const T& t)
	{
		g.m_actual_value += t;
		if (g.m_actual_value > g.m_max_value)
			g.m_actual_value = g.m_max_value;
		return g;
	}

	template<typename T>
	Gauge<T>& operator-=(Gauge<T>& g, const T& t)
	{
		g.m_actual_value -= t;
		if (g.m_actual_value > g.m_max_value)
			g.m_actual_value = g.m_max_value;
		return g;
	}

	template<typename T>
	std::string numberToString(T number)
	{
		std::stringstream ss;
		ss << number;
		return ss.str();
	}

	std::string numberToString(unsigned char c);
	std::string numberToString(char c);

	template<typename T>
	std::string numberToHexDec(T number)
	{
		std::stringstream ss;
		std::string ret("[");

		ss << number;
		ret += ss.str();
		ss.str("");
		ss << number;
		ss << std::hex;
		ret += " | 0x" + ss.str();

		ret += "]";

		return ret;
	}

}


#endif // _RESETABLE_HPP
