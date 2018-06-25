#ifndef _RESETABLE_HPP
#define _RESETABLE_HPP 1

#include <string>
#include <sstream>
#include <tinyxml.h>
#include <vector>
#include <memory>
#include <map>
#include <unordered_map>

#include "Platform.h"
#include <SFML/System/Vector2.hpp>

#if (PLATFORM == PLATFORM_WINDOWS)
#define FUNCTION_NAME __FUNCSIG__
#elif (PLATFORM == PLATFORM_LINUX)
#define FUNCTION_NAME __PRETTY_FUNCTION__
#endif // PLATFORM

#if PLATFORM == PLATFORM_WINDOWS
#include <windows.h>
#undef min
#undef max
#elif PLATFORM == PLATFORM_LINUX
#include <dlfcn.h>
#endif

#define UNUSED_PARAMETER(x) (void)(x)

#include "Exception/Exception.hpp"


class TiXmlElement;
class ILogger;

namespace misc
{
	template<typename T>
	class BitField
	{
	public:
		bool mt_Get_Bit(T position)
		{
			//
		}
		void mt_Set_Bit(T position, bool value)
		{
			//
		}
	private:
		std::vector<T> m_bits;
	};
	/** \class Resetable
		\brief Base class for objects that can be reset by an external event

		\fn bool mt_Reset(void)
		\brief Method used to reset the object
		\return true on success, false otherwise
	**/
	class Resetable
	{
	public:
		virtual ~Resetable(){}

		virtual bool mt_Reset(void) = 0;
	};

	template<typename T>
	class Grid
	{
	public:
		Grid() : m_data() {}
		Grid(const Grid& cp) : m_data(cp.m_data) {}
		void mt_Insert(unsigned int col, unsigned int row, const T& data)
		{
			unsigned int l_col(m_data.size()), l_row(0);
			if (m_data.size() != 0)
				l_row = m_data[0].size();
			if ((l_col == 0) && (l_row == 0))
			{
				l_col = 1;
				l_row = 1;
				mt_Resize(l_col, l_row);
			}
			if ((col >= l_col) || (row >= l_row))
			{
				if (col >= l_col)
					l_col = col + 1;
				if (row >= l_row)
					l_row = row + 1;
				mt_Resize(l_col, l_row);
			}
			m_data[col][row] = data;
		}
		std::vector<T>& operator[](unsigned int col)
		{
			return m_data[col];
		}
		sf::Vector2u mt_Size() const
		{
			sf::Vector2u l_ret(0, 0);

			l_ret.x = m_data.size();
			if (l_ret.x != 0)
				l_ret.y = m_data[0].size();

			return l_ret;
		}
		const T& mt_At(unsigned int col, unsigned int row) const
		{
			return m_data[col][row];
		}
		T& mt_At(unsigned int col, unsigned int row)
		{
			return m_data[col][row];
		}
	private:
		void mt_Resize(unsigned int col, unsigned int row)
		{
			m_data.resize(col);
			for (auto& a : m_data)
			{
				a.resize(row);
			}
		}
		std::vector<std::vector<T>> m_data;
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

		virtual std::unique_ptr<T> mt_Clone(void) const = 0;

	};

	template<typename T>
	std::string fn_Number_To_String(T number)
	{
		std::stringstream ss;
		ss << number;
		return ss.str();
	}

	template<typename T>
	std::string fn_Number_To_HexDec(T number)
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

	#if (PLATFORM == PLATFORM_LINUX)
	struct EnumClassHash
	{
		template<typename T>
		std::size_t operator()(const T& t) const
		{
			return static_cast<std::size_t>(t);
		}
		template<typename T>
		bool operator()(const T& a, const T& b) const
		{
			return (a < b);
		}
	};

	template<typename Key>
	using HashType = typename std::conditional<std::is_enum<Key>::value, EnumClassHash, std::hash<Key>>::type;

	template<typename Key, typename Value>
	using UnorderedMap = std::unordered_map<Key, Value, HashType<Key>>;
	template<typename Key, typename Value>
	using Map = std::map<Key, Value>;
	#else

	template<typename Key, typename Value>
	using UnorderedMap = std::unordered_map<Key, Value>;
	template<typename Key, typename Value>
	using Map = std::map<Key, Value>;

	#endif

	template <typename FunctionPointer>
	class DLL_Loader
	{
	public:
		DLL_Loader() : m_dll(){/** Nothing **/}
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
		FunctionPointer mt_Get_Function(const std::string& dll_name, const std::string& function_name)
		{
			FunctionPointer l_ret(nullptr);
			NativeDllHandleType dll_handle(nullptr);
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

			return l_ret;
		}

	protected:
#if PLATFORM == PLATFORM_WINDOWS
		typedef HINSTANCE NativeDllHandleType;
#elif PLATFORM == PLATFORM_LINUX
		typedef void* NativeDllHandleType;
#endif

		std::map<std::string, NativeDllHandleType> m_dll;
	};
}


#endif // _RESETABLE_HPP
