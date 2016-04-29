#ifndef CIS330P3B_IMAGE_H
#define CIS330P3B_IMAGE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	char MagicNum[3];
	int Maxval;
} PNMP6Meta;

typedef struct
{
	unsigned char R, G, B;
} PNMP6Pixel;

class Image
{
public:
	Image();
	/*Image(const char *Filename);*/
	Image(const Image &Obj);
	virtual ~Image();

	bool	IsEmpty() const;
	int 	GetWidth() const;
	int 	GetHeight() const;
	int 	GetRawSize() const;
	//SetSize Will set image dimension and buffer size
	void	SetSize(int Width, int Height);
	PNMP6Meta	GetMeta() const;
	void	SetMeta(PNMP6Meta NewMeta);
	void	GetData(PNMP6Pixel *pOutput) const;
	bool	GetData(PNMP6Pixel *pOutput, int Size, int X = 1, int Y = 1) const;
	bool	GetData(PNMP6Pixel *pOutput, int Width, int Height, int X = 1, int Y = 1) const;
	bool	SetData(const PNMP6Pixel *pObj, int Width, int Height, int X = 1, int Y = 1);
	bool	SetData(const Image *pObj, int Width, int Height, int X = 1, int Y = 1);
	bool	GetPixel(int X, int Y, PNMP6Pixel *pOutput) const;
	bool	SetPixel(int X, int Y, const PNMP6Pixel *pObj);
	void	CreateCompatibleImage(const Image *pObj);
	void	CreateCompatibleImage(const Image *pObj, int Width, int Height);
	void	CopyImage(Image *pObj);

	//void ReadFile(const char *pFilename);
	//void WriteFile(const char *pFilename);

private:
	void	Initialize();
	void	AllocDataSpace(int Size);
	void	DeallocDataSpace();
	int  	CordToIndex(int X, int Y) const;
	void	IndexToCord(int Index, int *pX, int *pY) const;

private:
	int		_Width;
	int		_Height;
	int		_RawSize;			//Raw data size in byte;
	PNMP6Pixel	*_pData;
	PNMP6Meta	_Meta;
};
#endif		//CIS330P3B_IMAGE_H