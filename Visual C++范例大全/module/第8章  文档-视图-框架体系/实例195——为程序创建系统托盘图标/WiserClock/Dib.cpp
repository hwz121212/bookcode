// Dib.cpp: implementation of the CDib class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "dib.h"

IMPLEMENT_DYNAMIC(CDib,  CObject)

CDib::CDib()
{
	Init();
}

CDib::CDib(const char* pszDibFileName)
{
	Init();
    LoadFile(pszDibFileName);
}


CDib::~CDib()
{
	ClearMemory();
}

void CDib::ClearMemory()
{
	if(m_hDIB != NULL)
		::GlobalFree(m_hDIB);
	m_hDIB = 0;
    m_pDibData = NULL;		
	m_pszFileName = NULL;
	m_pBitmapInfoHeader = NULL;
    m_pBitmapInfo = NULL;

	m_pRGBQuad = NULL;
	m_pBitmapFileHeader = NULL;
}

#ifdef _DEBUG
void CDib::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);
}

void CDib::AssertValid() const
{
	CObject::AssertValid();
	ASSERT(m_pszFileName != NULL);	
	ASSERT(m_hDIB != 0);	
}
#endif


void CDib::Init()
{
	m_pRGBQuad = NULL;		//RGBQUAD ����
    m_pDibData = NULL;		//λͼ��������
	m_nWidth = 0;			//���
	m_nHeight = 0;			//�߶�
	m_nBitCount = 0;		//ÿ������ռ�е�λ��
    m_nTotalColors = 0;		//��ɫ����
    m_pBitmapFileHeader = NULL;
    m_pBitmapInfoHeader = NULL;
    m_pBitmapInfo = NULL;
	m_hDIB = 0;
	m_pszFileName = NULL;
}

void CDib::LoadFile(const char* pszDibFileName)
{
	ASSERT(pszDibFileName);
	//������ھ��ͷ��ڴ�
	if(m_pBitmapInfo) ::GlobalFree(m_hDIB);
	//�ٴγ�ʼ��, ���ڶ�ζ�̬����
	Init();
	m_pszFileName = (char*)pszDibFileName;

	BITMAPFILEHEADER bitmapFileHeader;

	CFile dibFile(pszDibFileName,  CFile::modeRead);
	try
	{
		//����λͼ�ļ�ͷ��Ϣ
		UINT nBFHsize = dibFile.Read((void*)&bitmapFileHeader, sizeof(BITMAPFILEHEADER));
		if(nBFHsize != sizeof(BITMAPFILEHEADER))
		{
			m_bValid = FALSE;
			return;
		}
	}
	catch(CFileException* e)
	{
		e->Delete();
	}

	//���Ϊλͼ�ͽ�����һ���Ĵ���
    if (bitmapFileHeader.bfType == 0x4d42)
    {
		
		
		//�ļ�����
        DWORD dwFileLength = dibFile.GetLength();
		
		//λͼ��Ϣ��λͼ���ݵĴ�С(�ֽ�)
        DWORD dwSize = dwFileLength - sizeof(BITMAPFILEHEADER);
 

		//ΪDib����ȫ���ڴ�
		m_hDIB = (HGLOBAL) ::GlobalAlloc(GMEM_MOVEABLE,  dwSize);
		if (m_hDIB == 0)	m_bValid = FALSE;

		//ָ��Dibʵ���������ݵ�ָ��, 
		BYTE* pbyDib = (BYTE*)::GlobalLock(m_hDIB);
		if (pbyDib == NULL)	m_bValid = FALSE;
	 
		try
		{
			//�����ڴ�
			DWORD dwReadSize = dibFile.Read((void*)pbyDib,  dwSize);
			dibFile.Close();
			if(dwReadSize != dwSize)
			{
				m_bValid = FALSE;
				::GlobalUnlock(m_hDIB);
				::GlobalFree(m_hDIB);
				Init();
				return;
			}
		}
		catch(CFileException* e)
		{
			e->Delete();
		}

		//��ȡλͼ�ļ�ͷָ���λͼ�ļ�������Ϣָ��
        m_pBitmapInfo = (BITMAPINFO*) pbyDib;
		m_pBitmapInfoHeader = (BITMAPINFOHEADER*) pbyDib;
		
		//��Ⱥ͸߶�
		m_nWidth = m_pBitmapInfoHeader->biWidth;
		m_nHeight = m_pBitmapInfoHeader->biHeight;
		//ÿ���ص���ɫλ��
		m_nBitCount = (BYTE)m_pBitmapInfoHeader->biBitCount;
      
		//��ɫ��
		m_nTotalColors = GetColorNumber();
        if (m_pBitmapInfoHeader->biClrUsed == 0)
            m_pBitmapInfoHeader->biClrUsed = m_nTotalColors;

		//ָ��λͼ��ɫ���������ָ��, ���û����ɫ����, ���ֵΪNULL
        m_pRGBQuad = (RGBQUAD*)(pbyDib + m_pBitmapInfoHeader->biSize);
  
		//��ɫ������Ĵ�С(�ֽ�)
        DWORD dwColorTableSize = m_nTotalColors * sizeof(RGBQUAD);
        
		//ָ��λͼ���ݵ�ָ��
		m_pDibData = pbyDib + m_pBitmapInfoHeader->biSize + dwColorTableSize;
		
		//���û����ɫ������, ���ֵΪNULL
		if (m_pRGBQuad == (RGBQUAD*)m_pDibData) m_pRGBQuad = NULL;
       
		//λͼ�Ĵ�С(������ص�λ)
		m_pBitmapInfoHeader->biSizeImage = GetSize();
		::GlobalUnlock(m_hDIB);
		m_bValid = TRUE;
    }    
    else
    {
        AfxMessageBox("This is not a bitmap file!");
		m_bValid = FALSE;
    }
}

UINT CDib::GetColorNumber() const
{
	UINT nColors = 0;

    if ((m_pBitmapInfoHeader->biClrUsed == 0) &&
          (m_pBitmapInfoHeader->biBitCount < 9))
	{
		switch (m_pBitmapInfoHeader->biBitCount)
		{
		    case 1: nColors = 2; break;
		    case 4: nColors = 16; break;
		    case 8: nColors = 256;break;
		}
	}
    else
		nColors = (UINT) m_pBitmapInfoHeader->biClrUsed;

    return nColors;
}

//��ȡ���ݻ������Ĵ�С       
DWORD CDib::GetSize()
{
    if (m_pBitmapInfoHeader->biSizeImage != 0)
        return (m_pBitmapInfoHeader->biSizeImage);
	else 
		return (DWORD)GetDibWidthBytes(m_nWidth, 24) * (DWORD)m_nHeight;
}

//ÿ�е��ֽڿ��
DWORD CDib::GetDibWidthBytes(int nWidth,  BYTE byBitCount)
{
	DWORD dwWidthBytes = (DWORD)nWidth;	//8-bits
	if(byBitCount == 1) dwWidthBytes = (nWidth + 7) / 8;
	else if(byBitCount == 4) dwWidthBytes = (nWidth + 1) / 2;
	else if(byBitCount == 24) dwWidthBytes = 3 * nWidth ;
	
	while((dwWidthBytes & 3) != 0)dwWidthBytes++;

	return dwWidthBytes;

}

BOOL CDib::IsValid() const
{
	return m_bValid;
}

//�����и�ʽ������ת����DDB--24λ����, �����lpbyDdb24
//���ػ�ȡ���ݵ�����.
DWORD  CDib::GetDdbData24(LPBYTE lpbyDdb24)
{
	ASSERT(lpbyDdb24);

	//����DIBλͼ��һ�е��ֽ���
	DWORD dwDibWidthBytes = GetDibWidthBytes(m_nWidth,  m_nBitCount);

	//ת����24λDDB��ÿ�еĴ�С, ע��ÿ�е��ֽ���ֻ��Ҫ��ż������
	DWORD dwDdbWidthBytes =  ((m_nWidth * 24 + 15) / 16) * 2;

	if(m_nBitCount == 1)
	{
		//ÿ��ʵ���ֽ���, 8�����ض�Ӧһ���ֽ�.
		LONG nLineBytes = (m_nWidth + 7) / 8;
		BYTE abyBitMask[] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
		
		//DIBλͼ���ݵ���ͷ
		DWORD dwDibBaseIndex = (m_nHeight - 1) * dwDibWidthBytes;
		
		//DDB 24λλͼ���ݵ���ͷ
		DWORD dwDdbBaseIndex = 0;

		for(LONG i = 0;i < m_nHeight;i++)
		{
			//ָ��DIB�����ݵ�ָ��
			BYTE* pbyDibRaw = m_pDibData + dwDibBaseIndex;
	
			//ָ�� DDB 24λλͼ�����ݵ�ָ��
			BYTE* pbyDdbRaw = lpbyDdb24 + dwDdbBaseIndex;
			for(LONG j = 0;j < nLineBytes;j++)
			{
				//8���������ݵ�����ֵ
				BYTE byBit8 =  *(pbyDibRaw++);
				for(int n = 0; n < 8;n++)
				{
					BYTE byBitSingle = (byBit8 & abyBitMask[n]) >> (7 - n);
					*(pbyDdbRaw++) = m_pRGBQuad[byBitSingle].rgbBlue;	//��ɫ
					*(pbyDdbRaw++) = m_pRGBQuad[byBitSingle].rgbGreen;	//��ɫ
					*(pbyDdbRaw++) = m_pRGBQuad[byBitSingle].rgbRed;	//��ɫ
				}
			}//end j
			dwDibBaseIndex -= dwDibWidthBytes;
			dwDdbBaseIndex += dwDdbWidthBytes;
		}//end i
		return (dwDdbWidthBytes * m_nHeight);
	}// end if(m_nBitCount == 1)
	else if(m_nBitCount == 4)
	{
		//ÿ��ʵ���ֽ���
		LONG nLineBytes = (m_nWidth + 1) / 2;

		//DIBλͼ���ݵ���ͷ
		DWORD dwDibBaseIndex = (m_nHeight - 1) * dwDibWidthBytes;
		
		//DDB 24λλͼ���ݵ���ͷ
		DWORD dwDdbBaseIndex = 0;

		for(LONG i = 0;i < m_nHeight;i++)
		{
			//ָ��DIB�����ݵ�ָ��
			BYTE* pbyDibRaw = m_pDibData + dwDibBaseIndex;
			
			//ָ�� DDB 24λλͼ�����ݵ�ָ��
			BYTE* pbyDdbRaw = lpbyDdb24 + dwDdbBaseIndex;
			for(LONG j = 0;j < nLineBytes;j++)
			{
				//�����������ݵ�����ֵ, ͨ������λ�͵���λ
				BYTE byBit8 =  *(pbyDibRaw++);
				BYTE byBitHigh = (byBit8 & 0xF0) >> 4;
				BYTE byBitLow = (byBit8 & 0x0F);

				*(pbyDdbRaw++) = m_pRGBQuad[byBitHigh].rgbBlue;		//��ɫ
				*(pbyDdbRaw++) = m_pRGBQuad[byBitHigh].rgbGreen;	//��ɫ
				*(pbyDdbRaw++) = m_pRGBQuad[byBitHigh].rgbRed;		//��ɫ

				*(pbyDdbRaw++) = m_pRGBQuad[byBitLow].rgbBlue;		//��ɫ
				*(pbyDdbRaw++) = m_pRGBQuad[byBitLow].rgbGreen;		//��ɫ
				*(pbyDdbRaw++) = m_pRGBQuad[byBitLow].rgbRed;		//��ɫ

			}//end j
			dwDibBaseIndex -= dwDibWidthBytes;
			dwDdbBaseIndex += dwDdbWidthBytes;
		}//end i
		return (dwDdbWidthBytes * m_nHeight);
	}// end if(m_nBitCount == 4)
	else if(m_nBitCount == 8)
	{
		//DIBλͼ���ݵ���ͷ
		DWORD dwDibBaseIndex = (m_nHeight - 1) * dwDibWidthBytes;
		
		//DDB 24λλͼ���ݵ���ͷ
		DWORD dwDdbBaseIndex = 0;
		for(LONG i = 0;i < m_nHeight;i++)
		{
			//ָ��DIB�����ݵ�ָ��
			BYTE* pbyDibRaw = m_pDibData + dwDibBaseIndex;
		
			//ָ�� DDB 24λλͼ�����ݵ�ָ��
			BYTE* pbyDdbRaw = lpbyDdb24 + dwDdbBaseIndex;
			for(LONG j = 0;j < m_nWidth;j++)
			{
				//һ���������ݵ�����ֵ
				BYTE byIndex = *(pbyDibRaw++);
	
				*(pbyDdbRaw++) = m_pRGBQuad[byIndex].rgbBlue;	//��ɫ
				*(pbyDdbRaw++) = m_pRGBQuad[byIndex].rgbGreen;	//��ɫ
				*(pbyDdbRaw++) = m_pRGBQuad[byIndex].rgbRed;	//��ɫ
			}//end j
			dwDibBaseIndex -= dwDibWidthBytes;
			dwDdbBaseIndex += dwDdbWidthBytes;
		}//end i
		return (dwDdbWidthBytes * m_nHeight);
	}// end if(m_nBitCount == 8)
	else if(m_nBitCount == 24)
	{
	
		DWORD dwLength = m_nWidth * 3;
		//ָ��DIB�����ݵ�ָ��
		BYTE* pbyDibRaw = m_pDibData + (m_nHeight - 1) * dwDibWidthBytes;;
		//ָ�� DDB 24λλͼ�����ݵ�ָ��
		BYTE* pbyDdbRaw = lpbyDdb24;

		//��ɫ--��ɫ--��ɫ
		for(LONG i = 0;i < m_nHeight;i++)
		{
			::CopyMemory(pbyDdbRaw, pbyDibRaw, dwLength);
			pbyDibRaw -= dwDibWidthBytes;		//from 
			pbyDdbRaw += dwDdbWidthBytes;		//to
		}//end i
		return (dwDdbWidthBytes * m_nHeight);
	}// end if(m_nBitCount == 24)

	return (m_nWidth * m_nHeight);
}

//�����и�ʽ������ת����DDB--32λ����, �����lpbyDdb32
//���ػ�ȡ���ݵ�����.
//32λDDB���ݰ��ֽ�˳��:��ɫ--��ɫ--��ɫ--�����ֽ�--
DWORD  CDib::GetDdbData32(LPBYTE lpbyDdb32)
{
	ASSERT(lpbyDdb32);

	//����DIBλͼ��һ�е��ֽ���
	DWORD dwDibWidthBytes = GetDibWidthBytes(m_nWidth,  m_nBitCount);

	//ת����32λDDB��ÿ�еĴ�С, ע��ÿλ4�ֽ�
	DWORD dwDdbWidthBytes =  m_nWidth * 4;

	if(m_nBitCount == 1)
	{
		//ÿ��ʵ���ֽ���, 8�����ض�Ӧһ���ֽ�.
		LONG nLineBytes = (m_nWidth + 7) / 8;
		BYTE abyBitMask[] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
		
		//DIBλͼ���ݵ���ͷ
		DWORD dwDibBaseIndex = (m_nHeight - 1) * dwDibWidthBytes;
		
		//DDB 32λλͼ���ݵ���ͷ
		DWORD dwDdbBaseIndex = 0;

		for(LONG i = 0;i < m_nHeight;i++)
		{
			//ָ��DIB�����ݵ�ָ��
			BYTE* pbyDibRaw = m_pDibData + dwDibBaseIndex;
	
			//ָ�� DDB 32λλͼ�����ݵ�ָ��
			BYTE* pbyDdbRaw = lpbyDdb32 + dwDdbBaseIndex;
			for(LONG j = 0;j < nLineBytes;j++)
			{
				//8���������ݵ�����ֵ
				BYTE byBit8 =  *(pbyDibRaw++);
				for(int n = 0; n < 8;n++)
				{
					BYTE byBitSingle = (byBit8 & abyBitMask[n]) >> (7 - n);
					
					*(pbyDdbRaw++) = m_pRGBQuad[byBitSingle].rgbBlue;	//��ɫ
					*(pbyDdbRaw++) = m_pRGBQuad[byBitSingle].rgbGreen;	//��ɫ
					*(pbyDdbRaw++) = m_pRGBQuad[byBitSingle].rgbRed;	//��ɫ
					pbyDdbRaw++;										//����**
				}
			}//end j
			dwDibBaseIndex -= dwDibWidthBytes;
			dwDdbBaseIndex += dwDdbWidthBytes;
		}//end i
		return (dwDdbWidthBytes * m_nHeight);
	}// end if(m_nBitCount == 1)
	else if(m_nBitCount == 4)
	{
		//ÿ��ʵ���ֽ���
		LONG nLineBytes = (m_nWidth + 1) / 2;

		//DIBλͼ���ݵ���ͷ
		DWORD dwDibBaseIndex = (m_nHeight - 1) * dwDibWidthBytes;
		
		//DDB 32λλͼ���ݵ���ͷ
		DWORD dwDdbBaseIndex = 0;

		for(LONG i = 0;i < m_nHeight;i++)
		{
			//ָ��DIB�����ݵ�ָ��
			BYTE* pbyDibRaw = m_pDibData + dwDibBaseIndex;
			
			//ָ�� DDB 32λλͼ�����ݵ�ָ��
			BYTE* pbyDdbRaw = lpbyDdb32 + dwDdbBaseIndex;
			for(LONG j = 0;j < nLineBytes;j++)
			{
				//�����������ݵ�����ֵ, ͨ������λ�͵���λ
				BYTE byBit8 =  *(pbyDibRaw++);
				BYTE byBitHigh = (byBit8 & 0xF0) >> 4;
				BYTE byBitLow = (byBit8 & 0x0F);
				
				*(pbyDdbRaw++) = m_pRGBQuad[byBitHigh].rgbBlue;		//��ɫ
				*(pbyDdbRaw++) = m_pRGBQuad[byBitHigh].rgbGreen;	//��ɫ
				*(pbyDdbRaw++) = m_pRGBQuad[byBitHigh].rgbRed;		//��ɫ
				pbyDdbRaw++;

				*(pbyDdbRaw++) = m_pRGBQuad[byBitLow].rgbBlue;		//��ɫ
				*(pbyDdbRaw++) = m_pRGBQuad[byBitLow].rgbGreen;		//��ɫ
				*(pbyDdbRaw++) = m_pRGBQuad[byBitLow].rgbRed;		//��ɫ
				pbyDdbRaw++;

			}//end j
			dwDibBaseIndex -= dwDibWidthBytes;
			dwDdbBaseIndex += dwDdbWidthBytes;
		}//end i
		return (dwDdbWidthBytes * m_nHeight);
	}// end if(m_nBitCount == 4)
	else if(m_nBitCount == 8)
	{
		//DIBλͼ���ݵ���ͷ
		DWORD dwDibBaseIndex = (m_nHeight - 1) * dwDibWidthBytes;
		
		//DDB 32λλͼ���ݵ���ͷ
		DWORD dwDdbBaseIndex = 0;
		for(LONG i = 0;i < m_nHeight;i++)
		{
			//ָ��DIB�����ݵ�ָ��
			BYTE* pbyDibRaw = m_pDibData + dwDibBaseIndex;
		
			//ָ�� DDB 32λλͼ�����ݵ�ָ��
			BYTE* pbyDdbRaw = lpbyDdb32 + dwDdbBaseIndex;
			for(LONG j = 0;j < m_nWidth;j++)
			{
				//һ���������ݵ�����ֵ
				BYTE byIndex = *(pbyDibRaw++);
	
				*(pbyDdbRaw++) = m_pRGBQuad[byIndex].rgbBlue;	//��ɫ
				*(pbyDdbRaw++) = m_pRGBQuad[byIndex].rgbGreen;	//��ɫ
				*(pbyDdbRaw++) = m_pRGBQuad[byIndex].rgbRed;	//��ɫ
				pbyDdbRaw++;
			}//end j
			dwDibBaseIndex -= dwDibWidthBytes;
			dwDdbBaseIndex += dwDdbWidthBytes;
		}//end i
		return (dwDdbWidthBytes * m_nHeight);
	}// end if(m_nBitCount == 8)
	else if(m_nBitCount == 24)
	{
		//DIBλͼ���ݵ���ͷ
		DWORD dwDibBaseIndex = (m_nHeight - 1) * dwDibWidthBytes;
		
		//DDB 32λλͼ���ݵ���ͷ
		DWORD dwDdbBaseIndex = 0;
		for(LONG i = 0;i < m_nHeight;i++)
		{
						//ָ��DIB�����ݵ�ָ��
			BYTE* pbyDibRaw = m_pDibData + dwDibBaseIndex;
		
			//ָ�� DDB 32λλͼ�����ݵ�ָ��
			BYTE* pbyDdbRaw = lpbyDdb32 + dwDdbBaseIndex;
			for(LONG j = 0;j < m_nWidth;j++)
			{
				*(pbyDdbRaw++) = *(pbyDibRaw++);	//��ɫ
				*(pbyDdbRaw++) = *(pbyDibRaw++);	//��ɫ
				*(pbyDdbRaw++) = *(pbyDibRaw++);	//��ɫ
				pbyDdbRaw++;						
			}//end j			
			dwDibBaseIndex -= dwDibWidthBytes;
			dwDdbBaseIndex += dwDdbWidthBytes;
		}//end i
		return (dwDdbWidthBytes * m_nHeight);
	}// end if(m_nBitCount == 24)


	return (m_nWidth * m_nHeight);
}

HPALETTE CDib::CreateBitmapPalette()
{
	if((m_pRGBQuad == NULL) || !IsValid())return NULL;
    struct
    {
        WORD palVersion;
        WORD palNumEntries;
        PALETTEENTRY palPalEntry[256];
    } palette = { 0x300,  256 };
    
    LPRGBQUAD pRGBTable = m_pRGBQuad;

    for(UINT i = 0; i < m_nTotalColors; ++i)
    {
        palette.palPalEntry[i].peRed =   pRGBTable[i].rgbRed;
        palette.palPalEntry[i].peGreen = pRGBTable[i].rgbGreen;
        palette.palPalEntry[i].peBlue =  pRGBTable[i].rgbBlue;
        palette.palPalEntry[i].peFlags = 0;
    }

    HPALETTE hPalette = ::CreatePalette((LPLOGPALETTE)&palette);

    return hPalette;

}

//the return value is the number of scan lines copied.
int CDib::Draw(HDC hdc,  int XDest,  int YDest,  int nDestWidth,  int nDestHeight,  int XSrc,  int YSrc,  int nSrcWidth,  int nSrcHeight,  UINT iUsage,  DWORD dwRop)
{
	
	if (m_pRGBQuad) // Has a color table
	{
        HPALETTE hPalette = CreateBitmapPalette();
        HPALETTE hOldPalette = ::SelectPalette(hdc,  hPalette,  FALSE);
        ::RealizePalette(hdc);

		int nScanLines = StretchDIBits(hdc, 
										XDest, YDest, nDestWidth, nDestHeight, 
										XSrc, YSrc, nSrcWidth, nSrcHeight, 
										m_pDibData, m_pBitmapInfo, iUsage, dwRop);

        ::SelectPalette(hdc,  hOldPalette,  FALSE);
        ::DeleteObject(hPalette);
		return nScanLines;
	}
	else
        return StretchDIBits(hdc, 
							XDest, YDest, nDestWidth, nDestHeight, 
							XSrc, YSrc, nSrcWidth, nSrcHeight, 
							m_pDibData, m_pBitmapInfo, iUsage, dwRop);

}

BYTE CDib::GetBitCount() const
{
	return m_nBitCount;
}

BITMAPINFO* CDib::GetBmpInfo() const
{
    return m_pBitmapInfo;
}

BYTE* CDib::GetDibData() const
{
    return m_pDibData;
}

RGBQUAD* CDib::GetRGBQuad() const
{
    return m_pRGBQuad;
}

