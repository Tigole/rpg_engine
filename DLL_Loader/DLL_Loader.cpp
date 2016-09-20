#include "DLL_Loader/DLL_Loader.hpp"

DLL_Loader::~DLL_Loader()
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

DLL_Loader::NativeDllHandleType DLL_Loader::getHandle(const std::string& dll_name)
{
	DLL_Loader::NativeDllHandleType l_ret(nullptr);
	auto l_it(m_dll.find(dll_name));

	if (l_it != m_dll.end())
		l_ret = l_it->second;
	else
	{
#if PLATFORM == PLATFORM_WINDOWS
		l_ret = LoadLibrary(dll_name.c_str());
#elif PLATFORM == PLATFORM_LINUX
		l_ret = dlopen(dll_name.c_str(), RTLD_LAZY);
#endif
		if (l_ret != nullptr)
			m_dll[dll_name] = l_ret;
	}

	return l_ret;
}
