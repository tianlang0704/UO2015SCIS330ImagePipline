#ifndef CIS330P3C_PNMWRITER_H
#define CIS330P3C_PNMWRITER_H
#include "sink.h"

class PNMwriter : public Sink
{
public:
	void Write(const char *pFilename);
};

class PNMwriterCPP : public Sink
{
public:
	void Write(const char *pFilename);
};

#endif		//CIS330P3C_PNMWRITER_H