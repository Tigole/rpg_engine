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
	
	template<typename T>
	class PointerCollection
	{
	public:
		PointerCollection();

	};

	/*template<typename T>
	class DLL_Pointer
	{
	public:
		typedef void(*Deleter)(T*);
		DLL_Pointer() :	m_object(nullptr), m_deleter(nullptr){}
		DLL_Pointer(T* obj, void(*deleter)(T*)) : m_object(object), m_deleter(deleter){}
		DLL_Pointer(const DLL_Pointer<T>& other) : m_object(other.m_object), m_deleter(other.m_deleter){}
		DLL_Pointer& operator=(const DLL_Pointer<T>& other)
		{
			m_object = other.m_object;
			m_deleter = other.m_deleter;
			return *this;
		}

		T* get(void) const
		{
			return m_object;
		}

		Deleter getDeleter(void) const
		{
			return m_deleter;
		}

		/*void release(void)
		{
			m_object = nullptr;
		}*/

		/*void destroy(void)
		{
			m_deleter(m_object);
		}* /

	private:
		T* m_object;
		void(*m_deleter)(T*);
	};

	template<typename T>
	class DLL_SmartPointer
	{
	public:
		DLL_SmartPointer() : m_object(nullptr), m_deleter(nullptr) {}
		DLL_SmartPointer(T* object, void(*deleter)(T*)) : m_object(object), m_deleter(deleter) {}
		DLL_SmartPointer(const DLL_SmartPointer& other) = delete;/* : m_object(nullptr), m_deleter(other.m_deleter)
		{
			if (other.m_object != nullptr)
				m_object = other.m_object->clone();
		}* /
		~DLL_SmartPointer()
		{
			destroy();
		}
		/*DLL_SmartPointer<T>& operator=(const DLL_SmartPointer<T>& other)
		{
			m_deleter = other.m_deleter;
			if (other.m_object != nullptr)
				m_object = other.m_object->clone();
			return *this;
		}* /
		DLL_SmartPointer<T>& operator=(DLL_SmartPointer<T>& other)
		{
			from(other);
			return *this;
		}
		void from(DLL_SmartPointer<T>& other)
		{
			destroy();
			m_object = other.m_object;
			m_deleter = other.m_deleter;
			other.m_object = nullptr;
		}
		T* operator->(void) const
		{
			return m_object;
		}
		T* operator->(void)
		{
			return m_object;
		}
		T& operator*(void) const
		{
			return *m_object;
		}
		T& operator*(void)
		{
			return *m_object;
		}
		bool isValid(void)
		{
			return (m_object != nullptr);
		}
	private:
		void destroy(void)
		{
			if ((m_deleter != nullptr) && (m_object != nullptr))
				m_deleter(m_object);
		}
		T* m_object;
		void(*m_deleter)(T*);
	};*/

	/*template<typename T>
	using DLL_UniquePointer = std::unique_ptr<T, void(*)(T*)>;*/

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
		template <typename FunctionPointer>
		FunctionPointer getFunction(const std::string& dll_name, const std::string& function_name)
		{
			FunctionPointer ret(nullptr);
			NativeHandleType dll_handle(nullptr);
			std::map<std::string, NativeDllHandleType>::iterator it(m_dll.find(dll_name));

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
		typedef HINSTANCE NativeDllHandleType;
#elif PLATFORM == PLATFORM_LINUX
		typedef void* NativeHandleType;
#endif

		std::map<std::string, NativeDllHandleType> m_dll;
	};
}


#endif // _RESETABLE_HPP
