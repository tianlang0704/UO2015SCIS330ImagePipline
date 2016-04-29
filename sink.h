#ifndef CIS330P3C_SINK_H
#define CIS330P3C_SINK_H

#include "source.h"

class Sink
{
public:
	Sink();
	void SetInput(Source *pObj);
	void SetInput2(Source *pObj);

protected:
	Source *_pSrc1, *_pSrc2;
};
#endif		//CIS330P3C_SINK_H