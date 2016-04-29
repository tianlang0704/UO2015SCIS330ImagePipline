#ifndef CIS330P3C_FILTER_H
#define CIS330P3C_FILTER_H
#include "source.h"
#include "sink.h"

class filter : public Source, public Sink
{
public:
	virtual void Execute() = 0;
	virtual void Update();
	virtual void Update(long long TimeStamp);
};

#endif		//CIS330P3C_FILTER_H