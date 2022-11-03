// Dib.h: interface for the CDib class.
//
//////////////////////////////////////////////////////////////////////
#ifndef _CDIB_H
#define _CDIB_H

class CDib: public CObject  
{
	DECLARE_DYNAMIC(CDib)
protected:

	BOOL m_bValid;			//�Ƿ���Ч
    RGBQUAD* m_pRGBQuad;	//RGBQUAD ����
    BYTE* m_pDibData;		//λͼ��������

	BYTE m_nBitCount;		//ÿ������ռ�е�λ��
    UINT m_nTotalColors;	//��ɫ����
	char* m_pszFileName;
    BITMAPFILEHEADER* m_pBitmapFileHeader;
    BITMAPINFOHEADER* m_pBitmapInfoHeader;
    BITMAPINFO* m_pBitmapInfo;
	HGLOBAL m_hDIB;
public:
	LONG m_nWidth;			//���
	LONG m_nHeight;			//�߶�
	CDib();
    CDib(const char* pszDibFileName);
    ~CDib();

	BOOL IsValid() const ;
	UINT GetColorNumber() const;
	DWORD GetSize();
	DWORD GetDibWidthBytes(int nWidth,  BYTE byBitCount);
	DWORD GetDdbData24(LPBYTE lpbyDdb24);
	DWORD GetDdbData32(LPBYTE lpbyDdb24);
	HPALETTE CreateBitmapPalette();
	int Draw(HDC hdc,  int XDest,  int YDest,  int nDestWidth,  int nDestHeight,  int XSrc,  int YSrc,  int nSrcWidth,  int nSrcHeight,  UINT iUsage,  DWORD dwRop);
    BYTE GetBitCount() const;
	BITMAPINFO* GetBmpInfo() const;
	BYTE* GetDibData() const;
	RGBQUAD* GetRGBQuad() const;
public:
	void ClearMemory();

#ifdef _DEBUG
	virtual void Dump(CDumpContext& dc) const;
	virtual void AssertValid() const;
#endif

protected:   
	void LoadFile(const char* pszDibFileName);
private:
	void Init();

};

#endif 