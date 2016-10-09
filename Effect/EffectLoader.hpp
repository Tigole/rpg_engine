#ifndef _EFFECT_LOADER_HPP
#define _EFFECT_LOADER_HPP 1

#include "Loader\Loader.hpp"
#include <memory>

class IEffect;
class TiXmlElement;

class EffectLoader : public Loader
{
public:
	EffectLoader(const std::string& element_name);
	virtual ~EffectLoader();

	virtual std::unique_ptr<IEffect> load(const TiXmlElement& element) = 0;
};

#endif // !_EFFECT_LOADER_HPP