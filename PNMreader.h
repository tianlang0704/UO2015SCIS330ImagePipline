#ifndef CIS330P3C_PNMREADER_H
#define CIS330P3C_PNMREADER_H
#include "source.h"

class PNMreader : public Source
{
public:
	PNMreader();
	PNMreader(const char *pFilename);
	virtual ~PNMreader();
	virtual void Execute();
	virtual void Update();
	virtual void Update(long long TimeStamp);
	void SetFilename(const char *pFilename);

private:
	char *_pFilename;

};

class PNMreaderCPP : public Source
{
public:
	PNMreaderCPP();
	PNMreaderCPP(const char *pFilename);
	virtual ~PNMreaderCPP();
	virtual void Execute();
	virtual void Update();
	virtual void Update(long long TimeStamp);
	void SetFilename(const char *pFilename);

private:
	char *_pFilename;

};

#endif		//CIS330P3C_PNMREADER_H