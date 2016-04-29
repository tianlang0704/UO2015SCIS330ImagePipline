#include "filters.h"
#include "image.h"

void Shrinker::Execute()
{
	Image *Img1 = _pSrc1->GetImage();
	int NewWidth = Img1->GetWidth() / 2;
	int NewHeight = Img1->GetHeight() / 2;
	PNMP6Pixel PixelBuff;

	_Img.CreateCompatibleImage(Img1, NewWidth, NewHeight);

 	for (int i = 1; i <= NewWidth; i++)
	{
		for (int j = 1; j <= NewWidth; j++)
		{
			Img1->GetPixel(2 * j - 1, 2 * i - 1, &PixelBuff);
			_Img.SetPixel(j, i, &PixelBuff);
		}
	}
}

void LRConcat::Execute()
{
	Image *Img1 = _pSrc1->GetImage();
	Image *Img2 = _pSrc2->GetImage();
	int LWidth = Img1->GetWidth();
	int LHeight = Img1->GetHeight();
	int RWidth = Img2->GetWidth();
	int RHeight = Img2->GetHeight();

	_Img.CreateCompatibleImage(Img1, LWidth + RWidth, LHeight > RHeight ? LHeight : RHeight);

	_Img.SetData(Img1, LWidth, LHeight);
	_Img.SetData(Img2, RWidth, RHeight, LWidth + 1, 1);
}

void TBConcat::Execute()
{
	Image *Img1 = _pSrc1->GetImage();
	Image *Img2 = _pSrc2->GetImage();
	int TWidth = Img1->GetWidth();
	int THeight = Img1->GetHeight();
	int BWidth = Img2->GetWidth();
	int BHeight = Img2->GetHeight();


	_Img.CreateCompatibleImage(Img1, TWidth > BWidth ? TWidth : BWidth, THeight + BHeight);

	_Img.SetData(Img1, TWidth, THeight);
	_Img.SetData(Img2, BWidth, BHeight, 1, THeight + 1);
}

Blender::Blender()
{
	SetFactor(1);
}

Blender::Blender(float Factor)
{
	SetFactor(Factor);
}

void Blender::Execute()
{
	Image *Img1 = _pSrc1->GetImage();
	Image *Img2 = _pSrc2->GetImage();
	int Width1 = Img1->GetWidth();
	int Height1 = Img1->GetHeight();
	int Width2 = Img2->GetWidth();
	int Height2 = Img1->GetHeight();
	int MaxWidth = Width1 > Width2 ? Width1 : Width2;
	int MaxHeight = Height1 > Height2 ? Height1 : Height2;
	float InvFactor = 1 - _Factor;
	PNMP6Pixel PixelBuff[3];


	_Img.CreateCompatibleImage(Img1, MaxWidth, MaxHeight);

	for (int i = 1; i <= MaxHeight; i++)
	{
		for (int j = 1; j <= MaxWidth; j++)
		{
			Img1->GetPixel(j, i, &PixelBuff[0]);
			Img2->GetPixel(j, i, &PixelBuff[1]);
			PixelBuff[2].R = (char)(PixelBuff[0].R * _Factor + PixelBuff[1].R * InvFactor);
			PixelBuff[2].G = (char)(PixelBuff[0].G * _Factor + PixelBuff[1].G * InvFactor);
			PixelBuff[2].B = (char)(PixelBuff[0].B * _Factor + PixelBuff[1].B * InvFactor);
			_Img.SetPixel(j, i, &PixelBuff[2]);
		}
	}
}

void Blender::SetFactor(float Factor)
{
	_Factor = Factor;
}