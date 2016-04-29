#include "filter.h"

void filter::Update()
{
	long long T;

	time((time_t*)&T);
	SetLastUpdateTime(T);

	if (_pSrc1)
		_pSrc1->Update(GetLastUpdateTime());

	if (_pSrc2)
		_pSrc1->Update(GetLastUpdateTime());

	Execute();
}

void filter::Update(long long TimeStamp)
{
	if (GetLastUpdateTime() == TimeStamp)
		return;

	if (_pSrc1)
		_pSrc1->Update(TimeStamp);

	if (_pSrc2)
		_pSrc1->Update(TimeStamp);

	Execute();

	SetLastUpdateTime(TimeStamp);
}