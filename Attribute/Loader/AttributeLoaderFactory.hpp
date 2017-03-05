#ifndef _ATTRIBUTE_LOADER_FACTORY_HPP
#define _ATTRIBUTE_LOADER_FACTORY_HPP 1

#include "Loader/LoaderFactory.hpp"

class AttributeLoader;

class AttributeLoaderFactory : public LoaderFactory<AttributeLoader>
{
public:
	AttributeLoaderFactory();
};

#endif // !_ATTRIBUTE_LOADER_FACTORY_HPP
