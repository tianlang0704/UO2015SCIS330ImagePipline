#include "PNMwriter.h"
#include <fstream>

using namespace std;

void PNMwriter::Write(const char *pFilename)
{
	PNMP6Pixel *PixelBuff;
	FILE *NewImageFile;
	Image *Img = _pSrc1->GetImage();
	int RawSize = Img->GetRawSize();

	if (!(NewImageFile = fopen(pFilename, "wb"))) //Closing at the end
	{
		printf("Error creating file!\n");
		return;
	}

	fprintf(NewImageFile, "%s\n%d\x20%d\n%d\n",
		Img->GetMeta().MagicNum,
		Img->GetWidth(),
		Img->GetHeight(),
		Img->GetMeta().Maxval);
	PixelBuff = new PNMP6Pixel[RawSize];  //dealloc at the end
	Img->GetData(PixelBuff);

	if (Img->GetRawSize() != fwrite(PixelBuff, 1, RawSize, NewImageFile))
	{
		printf("Error writing image data!\n");
		return;
	}

	delete[] PixelBuff;
	fclose(NewImageFile);
}

void PNMwriterCPP::Write(const char *pFilename)
{
	PNMP6Pixel *PixelBuff;
	ofstream OutFile(pFilename, ios::out | ios::binary);
	Image *Img = _pSrc1->GetImage();
	int RawSize = Img->GetRawSize();

	if (!OutFile.good()) //Closing at the end
	{
		printf("Error creating file!\n");
		return;
	}

	OutFile << Img->GetMeta().MagicNum << "\n"
		<< Img->GetWidth() << "\x20" << Img->GetHeight() << "\n"
		<< Img->GetMeta().Maxval << endl;

	PixelBuff = new PNMP6Pixel[RawSize];  //dealloc at the end
	Img->GetData(PixelBuff);

	OutFile.write((char *)PixelBuff, Img->GetRawSize());
	if (!OutFile.good())
	{
		delete[] PixelBuff;
		OutFile.close();
		printf("Error writing image data!\n");
		return;
	}

	delete[] PixelBuff;
	OutFile.close();
}