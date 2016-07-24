#ifndef _RESETABLE_HPP
#define _RESETABLE_HPP 1

#include <string>
#include <sstream>
#include <tinyxml.h>
#include <vector>
#include <memory>
#include <map>

#if defined(_WIN32)
#define PLATFORM PLATFORM_WINDOWS
#elif defined(__gnu_linux__)
#define PLATFORM PLATFORM_LINUX
#else
#error Your platform is not usable for now
#endif

#if PLATFORM == PLATFORM_WINDOWS
#define FUNCTION_NAME __FUNCSIG__
#elif PLATFORM == PLATFORM_LINUX
#define FUNCTION_NAME __PRETTY_FUNCTION__
#endif // PLATFORM

#if PLATOFORM == PLATFORM_WINDOWS
#include <windows.h>
#endif

#define UNUSED_PARAMETER(x) (void)(x)

class TiXmlElement;
class ILogger;

namespace misc
{
	class Dumpable
	{
	public:
		virtual ~Dumpable(){ /** Nothing **/ }
		virtual void dump(ILogger& l) = 0;
	};
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

		\fn T* clone(void) const
		\brief Method used to clone the object
		\return A copy of the object itself dynamically created
	**/
	template<typename T>
	class Clonable
	{
	public:
		virtual ~Clonable(){}

		virtual std::unique_ptr<T> clone(void) const = 0;
	};

	template<typename T>
	struct Gauge
	{
		Gauge(const T& actual_value, const T& max_value) : m_actual_value(actual_value), m_max_value(max_value){ /** Nothing **/ }
		Gauge(const T& values) : m_actual_value(values), m_max_value(values){ /** Nothing **/ }
		Gauge(const Gauge<T>& copy) : m_actual_value(copy.m_actual_value), m_max_value(copy.m_max_value){ /** Nothing **/ }
		Gauge() : m_actual_value(), m_max_value() { /** Nothing **/ }

		void restore(void) { m_actual_value = m_max_value; }
		bool isEmpty(void) const { return m_actual_value <= (T)0; }
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

	/*std::string numberToString(unsigned char c);
	std::string numberToString(char c);*/

	template<typename T>
	std::string numberToHexDec(T number)
	{
		std::stringstream ss;
		std::string ret("[");

		ss << number;
		ret += ss.str();
		ss.str("");
		ss << std::hex;
		ss << number;
		ret += " | 0x" + ss.str();

		ret += "]";

		return ret;
	}

	class ILoader
	{
	public:
		ILoader();
		virtual ~ILoader();
	protected:
		bool checkAttributes(const TiXmlElement& element, const std::vector<std::string>& attributes);
	};

	class Loader : public ILoader
	{
	public:
		Loader(const std::string& element_name);
		virtual ~Loader();

		const std::string& getElementName(void) const;
	protected:
		std::string m_element_name;
	};

	template <typename FunctionPointer>
	class DLL_Loader
	{
	public:
		~DLL_Loader()
		{
			for (auto& dll : m_dll)
			{
#if PLATFORM == PLATFORM_WINDOWS
				FreeLibrary(dll.second);
#elif PLATFORM == PLATFORM_LINUX
				dlclose(dll.second);
#endif
			}
		}
		FunctionPointer getFunction(const std::string& dll_name, const std::string& function_name)
		{
			FunctionPointer ret(nullptr);
			NativeHandleType dll_handle(nullptr);
			std::map<std::string, NativeHandleType>::iterator it(m_dll.find(dll_name));

			if (it != m_dll.end())
				dll_handle = it->second;
			else
			{
#if PLATFORM == PLATFORM_WINDOWS
				dll_handle = LoadLibrary(dll_name.c_str());
#elif PLATFORM == PLATFORM_LINUX
				dll_handle = dlopen(dll_name.c_str(), RTLD_LAZY);
#endif
				if (dll_handle != nullptr)
				{
					m_dll[dll_name] = dll_handle;
				}
			}

			if (dll_handle != nullptr)
			{
#if PLATFORM == PLATFORM_WINDOWS
				l_ret = (FunctionPointer)GetProcAddress(dll_handle, function_name.c_str());
#elif PLATFORM == PLATFORM_LINUX
				l_ret = (FunctionPointer)dlsym(dll_handle, function_name.c_str());
#endif
			}

			return ret;
		}

	protected:
#if PLATFORM == PLATFORM_WINDOWS
		typedef HINSTANCE NativeHandleType;
#elif PLATFORM == PLATFORM_LINUX
		typedef void* NativeHandleType;
#endif

		std::map<std::string, NativeHandleType> m_dll;
	};
}


#endif // _RESETABLE_HPP
