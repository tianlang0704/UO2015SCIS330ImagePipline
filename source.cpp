#include "source.h"

Source::Source()
{
	SetLastUpdateTime(0);
}

Source * Source::GetOutput()
{
	return this;
}

Image * Source::GetImage()
{
	return &_Img;
}

long long Source::GetLastUpdateTime()
{
	return _LastUpdateTime;
}
void Source::SetLastUpdateTime(long long TimeStamp)
{
	_LastUpdateTime = TimeStamp;
}