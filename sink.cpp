#include "sink.h"

Sink::Sink()
{
	_pSrc1 = NULL;
	_pSrc2 = NULL;
}

void Sink::SetInput(Source *pObj)
{
	_pSrc1 = pObj;
}

void Sink::SetInput2(Source *pObj)
{
	_pSrc2 = pObj;

}