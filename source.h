#ifndef CIS330P3C_SOURCE_H
#define CIS330P3C_SOURCE_H

#include "image.h"
#include <time.h>

class Source
{
public:
	Source();
	virtual	void	Execute() = 0;
	virtual	void	Update() = 0;
	virtual	void	Update(long long TimeStamp) = 0;
	Source *		GetOutput();
	Image *			GetImage();
	long long		GetLastUpdateTime();
	void			SetLastUpdateTime(long long TimeStamp);

protected:
	Image			_Img;
	long long		_LastUpdateTime;
};
#endif		//CIS330P3C_SOURCE_H