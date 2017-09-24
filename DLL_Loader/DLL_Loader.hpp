#ifndef _DLL_LOADER_HPP
#define _DLL_LOADER_HPP 1

#include "Platform.h"

#include <string>
#include <map>

#if (PLATFORM == PLATFORM_WINDOWS)
#include <windows.h>
#elif (PLATFORM == PLATFORM_LINUX)
#include <dlfcn.h>
#endif

class DLL_Loader
{
public:
	~DLL_Loader();
	template <typename FunctionPointer>
	FunctionPointer mt_Get_Function(const std::string& dll_name, const std::string& function_name)
	{
		FunctionPointer l_ret(nullptr);
		NativeDllHandleType dll_handle(nullptr);

		dll_handle = mt_Get_Handle(dll_name);

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
#if (PLATFORM == PLATFORM_WINDOWS)
	typedef HINSTANCE NativeDllHandleType;
#elif (PLATFORM == PLATFORM_LINUX)
	typedef void* NativeDllHandleType;
#endif
	NativeDllHandleType mt_Get_Handle(const std::string& dll_name);

	std::map<std::string, NativeDllHandleType> m_dll;
};

#endif // _DLL_LOADER_HPP
