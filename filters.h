#ifndef CIS330P3C_FILTERS_H
#define CIS330P3C_FILTERS_H

#include "filter.h"

class Shrinker : public filter
{
public:
	virtual void Execute();
};

class LRConcat : public filter
{
public:
	virtual void Execute();
};

class TBConcat : public filter
{
public:
	virtual void Execute();
};

class Blender : public filter
{
public:
	Blender();
	Blender(float Factor);
	virtual void Execute();
	void SetFactor(float Factor);
private:
	float _Factor;
};

#endif		//CIS330P3C_FILTERS_H