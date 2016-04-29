#include "PNMreader.h"
#include <fstream>

using namespace std;

PNMreader::PNMreader()
{
	_pFilename = NULL;
}

PNMreader::PNMreader(const char *pFilename)
{
	SetFilename(pFilename);
}

PNMreader::~PNMreader()
{
	if (_pFilename)
		free(_pFilename);
}

void PNMreader::Execute()
{
	FILE *ImageFile;
	PNMP6Pixel *DataBuff;
	PNMP6Meta MetaBuff;
	int Width, Height;

	if (!(ImageFile = fopen(_pFilename, "rb"))) //Closing at the end of this function
	{
		printf("Error opening file!\n");
		return;
	}

	fscanf(ImageFile, "%s\n%d	%d\n%d\n",
		MetaBuff.MagicNum,
		&Width,
		&Height,
		&MetaBuff.Maxval);
	MetaBuff.MagicNum[2] = 0;
	_Img.SetMeta(MetaBuff);
	_Img.SetSize(Width, Height); //Using SetSize to allocate data space

	DataBuff = new PNMP6Pixel[_Img.GetRawSize()]; //Dealloc at the end
	if (_Img.GetRawSize() != fread(DataBuff, 1, _Img.GetRawSize(), ImageFile))
	{
		printf("Error reading image data!\n");
		fclose(ImageFile);
		return;
	}
	_Img.SetData(DataBuff, Width, Height);

	delete[] DataBuff;
	fclose(ImageFile);
}

void PNMreader::Update()
{
	long long T;

	time((time_t*)&T);
	SetLastUpdateTime(T);
	Execute();
}

void PNMreader::Update(long long TimeStamp)
{
	if (GetLastUpdateTime() == TimeStamp)
		return;

	Execute();

	SetLastUpdateTime(TimeStamp);

}

void PNMreader::SetFilename(const char *pFilename)
{
	_pFilename = (char*)malloc(strlen(pFilename) + 1);	//Dealloc in Dtor
	strcpy(_pFilename, pFilename);
}


PNMreaderCPP::PNMreaderCPP()
{
	_pFilename = NULL;
}

PNMreaderCPP::PNMreaderCPP(const char *pFilename)
{
	SetFilename(pFilename);
}

PNMreaderCPP::~PNMreaderCPP()
{
	if (_pFilename)
		free(_pFilename);
}

void PNMreaderCPP::Execute()
{
	ifstream InFile(_pFilename, ios::in | ios::binary);
	PNMP6Pixel *DataBuff;
	PNMP6Meta MetaBuff;
	int Width, Height;
	
	if (!InFile.good())
	{
		printf("Error opening file!\n");
		return;
	}

	InFile >> MetaBuff.MagicNum >> Width >> Height >> MetaBuff.Maxval;
	InFile.seekg(InFile.tellg() + streamoff(1));
	_Img.SetMeta(MetaBuff);
	_Img.SetSize(Width, Height); //Using SetSize to allocate data space

	
	DataBuff = new PNMP6Pixel[_Img.GetRawSize()]; //Dealloc at the end
	InFile.read((char *)DataBuff, _Img.GetRawSize());
	if (!InFile.good())
	{
		delete[] DataBuff;
		InFile.close();
		printf("Error opening file!\n");
		return;
	}

	_Img.SetData(DataBuff, Width, Height);

	delete[] DataBuff;
	InFile.close();
}

void PNMreaderCPP::Update()
{
	long long T;

	time((time_t*)&T);
	SetLastUpdateTime(T);
	Execute();
}

void PNMreaderCPP::Update(long long TimeStamp)
{
	if (GetLastUpdateTime() == TimeStamp)
		return;

	Execute();

	SetLastUpdateTime(TimeStamp);

}

void PNMreaderCPP::SetFilename(const char *pFilename)
{
	_pFilename = (char*)malloc(strlen(pFilename) + 1);	//Dealloc in Dtor
	strcpy(_pFilename, pFilename);
}