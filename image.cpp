//include <image.h>
#include "image.h"

Image::Image()
{
	Initialize();
}

//Image::Image(const char *Filename)
//{
//	Initialize();
//	ReadFile(Filename);
//}

Image::Image(const Image &Obj)
{
	SetMeta(Obj.GetMeta());
	SetSize(Obj.GetWidth(), Obj.GetHeight());
	if (!Obj.IsEmpty())
		Obj.GetData(_pData);
}

Image::~Image()
{
	DeallocDataSpace();	
}

bool Image::IsEmpty() const
{
	return _pData == NULL;
}

int Image::GetWidth() const
{
	return _Width;
}

int Image::GetHeight() const
{
	return _Height;
}

int Image::GetRawSize() const 
{
	return _RawSize;
}

PNMP6Meta Image::GetMeta() const 
{
	return _Meta;
}

void Image::SetMeta(PNMP6Meta NewMeta)
{
	_Meta = NewMeta;
}

void Image::GetData(PNMP6Pixel *pOutput) const
{
	GetData(pOutput, GetRawSize());
}

bool Image::GetData(PNMP6Pixel *pOutput, int Size, int X, int Y) const
{
	int Index = CordToIndex(X, Y);
	if (Index + Size > GetRawSize())
		return false;

	memcpy(pOutput, &_pData[Index], Size);

	return true;
}

bool Image::GetData(PNMP6Pixel *pOutput, int Width, int Height, int X, int Y) const
{
	int Index = CordToIndex(X, Y);
	int Size = Width * Height;
	if (Index + Size > GetRawSize())
		return false;
	
	for (int i = 0; i < Height; i++)
	{
		memcpy(&pOutput[i * Width], 
			&_pData[CordToIndex(X, Y + i)], 
			Size * sizeof(PNMP6Pixel));
	}
	
	return true;
}

bool Image::SetData(const PNMP6Pixel *pObj, int Width, int Height, int X, int Y)
{
	int YBound = Y + Height - 1;
	int XBound = X + Width - 1;

	if (YBound > GetHeight() || XBound > GetWidth())
		return false;

	for (int i = 0; i < Height; i++)
		for (int j = 0; j < Width; j++)
			_pData[CordToIndex(X + j, Y + i)] = pObj[i * Width + j];

	return true;
}

bool Image::SetData(const Image *pObj, int Width, int Height, int X, int Y)
{
	bool result;
	PNMP6Pixel *PixelBuff = new PNMP6Pixel[pObj->GetRawSize()];

	pObj->GetData(PixelBuff);
	result = SetData(PixelBuff, Width, Height, X, Y);

	delete [] PixelBuff;
	return result;
}

bool Image::GetPixel(int X, int Y, PNMP6Pixel *pOutput) const
{
	if (X > GetWidth() || Y > GetHeight() || X < 1 || Y < 1)
		return false;

	memcpy(pOutput, &_pData[CordToIndex(X, Y)], sizeof(PNMP6Pixel));

	return true;
}

bool Image::SetPixel(int X, int Y, const PNMP6Pixel *pObj)
{
	if (X > GetWidth() || Y > GetHeight() || X < 1 || Y < 1)
		return false;

	memcpy(&_pData[CordToIndex(X, Y)], pObj, sizeof(PNMP6Pixel));

	return true;
}

void Image::CreateCompatibleImage(const Image *pObj)
{
	CreateCompatibleImage(pObj, pObj->GetWidth(), pObj->GetHeight());
}

void Image::CreateCompatibleImage(const Image *pObj, int Width, int Height)
{
	SetMeta(pObj->GetMeta());
	SetSize(Width, Height);
}

void Image::CopyImage(Image *pObj)
{
	SetMeta(pObj->GetMeta());
	SetSize(pObj->GetWidth(), pObj->GetHeight());
	pObj->GetData(_pData);
}

//void Image::ReadFile(const char *pFilename)
//{
//	FILE *ImageFile; 
//
//	if (!(ImageFile = fopen(pFilename, "rb"))) //Closing at the end of this function
//	{
//		printf("Error opening file!\n");
//		return;
//	}
//
//	fscanf(ImageFile, "%s\n%d	%d\n%d\n",
//		_Meta.MagicNum,
//		&_Width,
//		&_Height,
//		&_Meta.Maxval);
//	_Meta.MagicNum[2] = 0;
//
//	SetSize(_Width, _Height); //Using SetSize to allocate data space
//
//	if (_RawSize != fread(_pData, 1, _RawSize, ImageFile))
//	{
//		printf("Error reading image data!\n");
//		fclose(ImageFile);
//		return;
//	}
//
//	fclose(ImageFile);
//}

//void Image::WriteFile(const char *pFilename)
//{
//	FILE *NewImageFile;
//	if (!(NewImageFile = fopen(pFilename, "wb"))) //Closing at the end of this function
//	{
//		printf("Error creating file!\n");
//		return;
//	}
//	
//	fprintf(NewImageFile, "%s\n%d\x20%d\n%d\n",
//		_Meta.MagicNum,
//		_Width,
//		_Height,
//		_Meta.Maxval);
//	if (_RawSize != fwrite(_pData, 1, _RawSize, NewImageFile))
//	{
//		printf("Error writing image data!\n");
//		return;
//	}
//
//	fclose(NewImageFile);
//}

void Image::Initialize()
{
	_Meta.MagicNum[0] = 0;
	_Meta.Maxval = 0;
	_Width = 0;
	_Height = 0;
	_RawSize = 0;
	_pData = NULL;
}

void Image::AllocDataSpace(int Size)
{
	_pData = (PNMP6Pixel*)malloc(Size); //Deallocates in desctructor
	memset(_pData, 0, Size);
}

void Image::DeallocDataSpace()
{
	if (_pData)
		free(_pData);
}

void Image::SetSize(int Width, int Height)
{
	_Width = Width;
	_Height = Height;
	_RawSize = sizeof(PNMP6Pixel) * Width * Height;
	if (_pData)
	{
		DeallocDataSpace();
		_pData = NULL;
	}
	AllocDataSpace(_RawSize);
}

int	Image::CordToIndex(int X, int Y) const 
{
	return (Y - 1) * GetWidth() + X - 1;
}

void Image::IndexToCord(int Index, int *pX, int *pY) const
{
	*pY = Index / GetWidth() + 1;
	*pX = Index % GetWidth() + 1;
}