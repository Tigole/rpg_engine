#ifndef _BASIC_EFFECT_LOADER_HPP
#define _BASIC_EFFECT_LOADER_HPP 1

#include "Effect\EffectLoader.hpp"

class BasicEffectSetterLoader : public EffectLoader
{
public:
	BasicEffectSetterLoader();

	virtual std::unique_ptr<IEffect> load(const TiXmlElement& element);
};

class BasicEffectModifierLoader : public EffectLoader
{
public:
	BasicEffectModifierLoader();

	virtual std::unique_ptr<IEffect> load(const TiXmlElement& element);
};

class BasicEffectBufferLoader : public EffectLoader
{
public:
	BasicEffectBufferLoader();

	virtual std::unique_ptr<IEffect> load(const TiXmlElement& element);
};

#endif // !_BASIC_EFFECT_LOADER_HPP