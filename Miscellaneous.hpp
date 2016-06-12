#ifndef _RESETABLE_HPP
#define _RESETABLE_HPP 1

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

}


#endif // _RESETABLE_HPP
