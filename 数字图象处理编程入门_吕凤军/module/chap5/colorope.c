//////////////////////////////////////////////////////////////
//Name:colorope.c
//Purpose: histogram and color operation
//Author: phoenix, CS, TshingHua, Beijing, P.R.C.
//Email: bjlufengjun@www.163.net or lufengjun@hotmail.com
//Date:April 3, 1998

//header file
#include "bmp.h"
#include "memory.h"
#include "math.h"
#include "stdio.h"
//macro definition
#define WIDTHBYTES(i)    ((i+31)/32*4)
//function declaration
int PASCAL WinMain (HANDLE, HANDLE, LPSTR, int);
LRESULT CALLBACK MainWndProc(HWND , UINT,WPARAM, LPARAM);
BOOL LoadBmpFile (HWND hWnd,char *BmpFileName);
BOOL CALLBACK InputBox( HWND hDlg, UINT message,WPARAM wParam, LPARAM lParam );
BOOL Histogram(HWND hWnd);
long FAR PASCAL PopupWndProc (HWND,UINT,WPARAM,LPARAM);
BOOL ColortoGrayScale(HWND hWnd);
BOOL Trueto256(HWND hWnd);
BOOL Invert(HWND hWnd);
BOOL ContrastStretch(HWND hWnd);
BOOL Cliping(HWND hWnd);
BOOL Thresholding(HWND hWnd);
BOOL Slice(HWND hWnd,BOOL WithBack);
BOOL HistogramEqua(HWND hWnd);
//global variable declaration
BITMAPFILEHEADER   bf;
BITMAPINFOHEADER   bi;
HPALETTE           hPalette=NULL;
HBITMAP            hBitmap=NULL;
HGLOBAL            hImgData=NULL;
DWORD              NumColors;
DWORD              LineBytes;
HINSTANCE          ghInst;
DWORD              ImgWidth=0 , ImgHeight=0;
int GrayTable[256];
int MaxGrayNum;
int MinGrayNum;
int FirstPoint=0, SecondPoint=255;
float StretchRatio=2.0f;
int EquaScale;
///////////////////////////////////////////////////////////
int PASCAL WinMain (HANDLE hInstance, HANDLE hPrevInstance,
		    LPSTR lpszCmdLine, int nCmdShow)
{
	MSG       msg;
	WNDCLASS  wndclass;
	HWND      hWnd;

	ghInst=hInstance;
	if ( ! hPrevInstance ){
		wndclass.style = CS_HREDRAW | CS_VREDRAW;
		wndclass.lpfnWndProc = MainWndProc;
		wndclass.cbClsExtra = 0;
		wndclass.cbWndExtra = 0;
		wndclass.hInstance = hInstance;
		wndclass.hIcon = LoadIcon (NULL, IDI_APPLICATION);
		wndclass.hCursor = LoadCursor (NULL, IDC_ARROW);
		wndclass.hbrBackground = GetStockObject (WHITE_BRUSH);
		wndclass.lpszMenuName =  "BMPMENU";
		wndclass.lpszClassName = "phoenix ip system";
    }

    if ( ! RegisterClass (&wndclass) )
	    return FALSE;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = PopupWndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = ghInst;
    wndclass.hIcon = NULL;
    wndclass.hCursor = LoadCursor (NULL, IDC_ARROW);
    wndclass.hbrBackground = GetStockObject (WHITE_BRUSH);
    wndclass.lpszMenuName =  NULL;
    wndclass.lpszClassName = "PopupWindowClass";

    if ( ! RegisterClass (&wndclass) )
		return FALSE;
 
	hWnd = CreateWindow ("phoenix ip system","Color Operation",
						 WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,
						 CW_USEDEFAULT,	CW_USEDEFAULT, NULL,NULL,
						 hInstance,	NULL);
	if (!hWnd)
		return FALSE;
	ShowWindow (hWnd, SW_SHOWMAXIMIZED);
	UpdateWindow (hWnd);
	
	while ( GetMessage (&msg, NULL, 0, 0) ){
		TranslateMessage (&msg);
		DispatchMessage (&msg);
    }
	return msg.wParam;
}
////////////////////////////////////////////////////////////////
LRESULT CALLBACK MainWndProc(HWND hWnd, UINT message,WPARAM wParam, LPARAM lParam)
{
    static  HDC    hDC,hMemDC;
    PAINTSTRUCT    ps;

    switch (message){
    case WM_PAINT:
	{         
		hDC = BeginPaint(hWnd, &ps);
		if (hBitmap)
		{ 
			hMemDC = CreateCompatibleDC(hDC);
			if (hPalette)
			{           
				SelectPalette (hDC, hPalette, FALSE); 
				SelectPalette (hMemDC, hPalette, FALSE);
				RealizePalette (hDC);
			}   
			SelectObject(hMemDC, hBitmap); 
			BitBlt(hDC, 0, 0, ImgWidth,ImgHeight, hMemDC, 0, 0, SRCCOPY);
			DeleteDC(hMemDC);
		}
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_DESTROY: //注意释放内存和位图，调色板句柄
        if(hBitmap!=NULL)
	        DeleteObject(hBitmap);
	    
		if(hPalette!=NULL)                     
	        DeleteObject(hPalette);
		
		if(hImgData!=NULL){
			GlobalUnlock(hImgData);
			GlobalFree(hImgData);
		}	        
	    PostQuitMessage (0);
	    return 0;
	case WM_COMMAND:
	    switch (wParam){
	    case IDM_LOADBMP: 
			//注意重新分配内存和调色板，位图句柄时，先释放原来的
	        if(hBitmap!=NULL){     
				DeleteObject(hBitmap);
	            hBitmap=NULL;
	        }
	        if(hPalette!=NULL){                     
				DeleteObject(hPalette);
	            hPalette=NULL;
	        }
			if(hImgData!=NULL){
				GlobalUnlock(hImgData);
				GlobalFree(hImgData);  
				hImgData=NULL;
			}	        
			if(LoadBmpFile(hWnd,"c:\\test.bmp")) //成功，则重画窗口
                InvalidateRect(hWnd,NULL,TRUE);
	        break;
		case IDM_HISTOGRAM:
			if(hImgData!=NULL){
				if(Histogram(hWnd))
					InvalidateRect(hWnd,NULL,TRUE);
			}
			else
				MessageBox(hWnd,"File not loaded yet!","Error Message",MB_OK|MB_ICONEXCLAMATION);
			break;
		case IDM_TRUE256:
			if(hImgData!=NULL){
				if(Trueto256(hWnd))
					InvalidateRect(hWnd,NULL,TRUE);
			}
			else
				MessageBox(hWnd,"File not loaded yet!","Error Message",MB_OK|MB_ICONEXCLAMATION);
			break;
		case IDM_CLRGRAY:
			if(hImgData!=NULL){
				if(ColortoGrayScale(hWnd))
					InvalidateRect(hWnd,NULL,TRUE);
			}
			else
				MessageBox(hWnd,"File not loaded yet!","Error Message",MB_OK|MB_ICONEXCLAMATION);
			break;
		case IDM_INVERT:
			if(hImgData!=NULL){
				if(Invert(hWnd))
					InvalidateRect(hWnd,NULL,TRUE);
			}
			else
				MessageBox(hWnd,"File not loaded yet!","Error Message",MB_OK|MB_ICONEXCLAMATION);
			break;
		case IDM_CONTSTRETCH:
			if(hImgData!=NULL){
				if (ContrastStretch(hWnd))
					InvalidateRect(hWnd,NULL,TRUE);
			}
			else
				MessageBox(hWnd,"File not loaded yet!","Error Message",MB_OK|MB_ICONEXCLAMATION);
			break;
		case IDM_CLIPING:
			if(hImgData!=NULL){
				if(Cliping(hWnd))
					InvalidateRect(hWnd,NULL,TRUE);
			}
			else
				MessageBox(hWnd,"File not loaded yet!","Error Message",MB_OK|MB_ICONEXCLAMATION);
			break;
		case IDM_THRESHOLD:
			if(hImgData!=NULL){
				if(Thresholding(hWnd))
					InvalidateRect(hWnd,NULL,TRUE);
			}
			else
				MessageBox(hWnd,"File not loaded yet!","Error Message",MB_OK|MB_ICONEXCLAMATION);
			break;
		case IDM_SLICEWITHOUTBACK:
			if(hImgData!=NULL){
				if(Slice(hWnd,FALSE))
					InvalidateRect(hWnd,NULL,TRUE);
			}
			else
				MessageBox(hWnd,"File not loaded yet!","Error Message",MB_OK|MB_ICONEXCLAMATION);
			break;
		case IDM_SLICEWITHBACK:
			if(hImgData!=NULL){
				if(Slice(hWnd,TRUE))
					InvalidateRect(hWnd,NULL,TRUE);
			}
			else
				MessageBox(hWnd,"File not loaded yet!","Error Message",MB_OK|MB_ICONEXCLAMATION);
			break;
		case IDM_HISTOGRAMEQUA:
			if(hImgData!=NULL){
				if(HistogramEqua(hWnd))
					InvalidateRect(hWnd,NULL,TRUE);
			}
			else
				MessageBox(hWnd,"File not loaded yet!","Error Message",MB_OK|MB_ICONEXCLAMATION);
			break;
		case IDM_EXIT:
	        SendMessage(hWnd,WM_DESTROY,0,0L);
	        break;
	    }
	break;                
    }
    return DefWindowProc (hWnd, message, wParam, lParam);
}
////////////////////////////////////////////////////////////////
BOOL LoadBmpFile (HWND hWnd,char *BmpFileName)
{   
    HFILE              hf;
    LPBITMAPINFOHEADER lpImgData;
    LOGPALETTE         *pPal;
    LPRGBQUAD          lpRGB;
    HPALETTE           hPrevPalette; 
    HDC                hDc;
	HLOCAL             hPal;
	DWORD 		       ImgSize;
	DWORD              i;

    if((hf=_lopen(BmpFileName,OF_READ))==HFILE_ERROR){
        MessageBox(hWnd,"File c:\\test.bmp not found!","Error Message",MB_OK|MB_ICONEXCLAMATION);
        return FALSE;
	}
	_lread(hf,(LPSTR)&bf,sizeof(BITMAPFILEHEADER)); 
	_lread(hf,(LPSTR)&bi,sizeof(BITMAPINFOHEADER));
	ImgWidth=bi.biWidth;
	ImgHeight=bi.biHeight;
	LineBytes=(DWORD)WIDTHBYTES(bi.biWidth*bi.biBitCount);
	ImgSize=(DWORD)LineBytes*bi.biHeight;
    if(bi.biClrUsed!=0)
		NumColors=(DWORD)bi.biClrUsed;
	else
        switch(bi.biBitCount){
	       	case 1:
        	    NumColors=2;
        	    break;
        	case 4:
        	    NumColors=16;
        	    break;
        	case 8:
        	    NumColors=256;
        	    break;
        	case 24:
        	    NumColors=0;
        	    break;
              default:
                  MessageBox(hWnd,"Invalid color numbers!","Error Message",MB_OK|MB_ICONEXCLAMATION);
                  _lclose(hf);
                  return FALSE; 
        }
	if(bf.bfOffBits!=(DWORD)(NumColors*sizeof(RGBQUAD)+sizeof(BITMAPFILEHEADER)
							+sizeof(BITMAPINFOHEADER)))
	{
    	MessageBox(hWnd,"Invalid color numbers!","Error Message" ,MB_OK|
	               MB_ICONEXCLAMATION);
		_lclose(hf);
		return FALSE; 
	}
	bf.bfSize=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+NumColors*sizeof(RGBQUAD)+ImgSize;
	if((hImgData=GlobalAlloc(GHND,(DWORD)(sizeof(BITMAPINFOHEADER)+
						     NumColors*sizeof(RGBQUAD)+ImgSize)))==NULL)
	{
    	MessageBox(hWnd,"Error alloc memory!","ErrorMessage",MB_OK|
                   MB_ICONEXCLAMATION);
	    _lclose(hf);
		return FALSE;
	}
  
	lpImgData=(LPBITMAPINFOHEADER)GlobalLock(hImgData); 
    _llseek(hf,sizeof(BITMAPFILEHEADER),FILE_BEGIN);
	_hread(hf,(char *)lpImgData,(long)sizeof(BITMAPINFOHEADER)
           +(long)NumColors*sizeof(RGBQUAD)+ImgSize);
	_lclose(hf);
    if(NumColors!=0)
	{                    
	    hPal=LocalAlloc(LHND,sizeof(LOGPALETTE) + NumColors* sizeof(PALETTEENTRY));
	    pPal =(LOGPALETTE *)LocalLock(hPal);
	    pPal->palNumEntries =(WORD) NumColors;
		pPal->palVersion    = 0x300;
	    lpRGB = (LPRGBQUAD)((LPSTR)lpImgData + (DWORD)sizeof(BITMAPINFOHEADER));
		for (i = 0; i < NumColors; i++) {
     		pPal->palPalEntry[i].peRed=lpRGB->rgbRed;
			pPal->palPalEntry[i].peGreen=lpRGB->rgbGreen;
			pPal->palPalEntry[i].peBlue=lpRGB->rgbBlue;
			pPal->palPalEntry[i].peFlags=(BYTE)0;
			lpRGB++;
		}
		hPalette=CreatePalette(pPal);
		LocalUnlock(hPal);
		LocalFree(hPal);
	}
	hDc=GetDC(hWnd);
	if(hPalette){
        hPrevPalette=SelectPalette(hDc,hPalette,FALSE);
		RealizePalette(hDc);
	}
	hBitmap=CreateDIBitmap(hDc,	(LPBITMAPINFOHEADER)lpImgData, (LONG)CBM_INIT,
				(LPSTR)lpImgData+sizeof(BITMAPINFOHEADER) +NumColors*sizeof(RGBQUAD),
   				(LPBITMAPINFO)lpImgData, DIB_RGB_COLORS);
	if(hPalette && hPrevPalette){
		SelectPalette(hDc,hPrevPalette,FALSE);
		RealizePalette(hDc);
	}
 
	ReleaseDC(hWnd,hDc);
	GlobalUnlock(hImgData);
	return TRUE; 
}
////////////////////////////////////////////////////////////////
BOOL CALLBACK InputBox( HWND hDlg, UINT message,WPARAM wParam, LPARAM lParam )
{ 	
	char str[80];

   	switch  ( message ){
    case WM_INITDIALOG:		   
     	SetDlgItemText(hDlg,ID_FIRSTPOINT,"0");
     	SetDlgItemText(hDlg,ID_SECONDPOINT,"0");
     	SetDlgItemText(hDlg,ID_STRETCHRATIO,"2.0");
     	SetDlgItemText(hDlg,ID_EQUASCALE,"128");
    	return TRUE;
   	case WM_COMMAND:		   
    	if ( wParam == IDOK || wParam == IDCANCEL )
       	{
        	GetDlgItemText(hDlg,ID_FIRSTPOINT,str,80);
			FirstPoint=atoi(str);
        	GetDlgItemText(hDlg,ID_SECONDPOINT,str,80);
			SecondPoint=atoi(str);
        	GetDlgItemText(hDlg,ID_STRETCHRATIO,str,80);
			StretchRatio=(float)atof(str);
        	GetDlgItemText(hDlg,ID_EQUASCALE,str,80);
			EquaScale=atoi(str);
            EndDialog ( hDlg, TRUE );
            return  TRUE;
       	}
        break;
   		}
	return FALSE;			     
}
////////////////////////////////////////////////////////////////
BOOL ColortoGrayScale(HWND hWnd)
{
	DWORD              SrcBufSize,DstBufSize,DstLineBytes;
    LPBITMAPINFOHEADER lpImgData;
	LPSTR              lpPtr;
	HLOCAL             hTempImgData;
	LPBITMAPINFOHEADER lpTempImgData;
	LPSTR              lpTempPtr;
	HDC                hDc;
	HFILE              hf;
	LONG               x,y;
	BITMAPFILEHEADER   DstBf;
	BITMAPINFOHEADER   DstBi;
    LOGPALETTE         *pPal;
    HPALETTE           hPrevPalette; 
	HLOCAL             hPal;
	DWORD			   NewNumColors;
	WORD			   NewBitCount;
	float              Y;
	DWORD              i;
	unsigned char      Red,Green,Blue,Gray;

	NewNumColors=NumColors;
	NewBitCount=bi.biBitCount;
	if(NumColors==0) //true color
	{
		NewNumColors=256;
		NewBitCount=8;
	}

	DstLineBytes=(DWORD)WIDTHBYTES(bi.biWidth*NewBitCount);
	DstBufSize=(DWORD)(sizeof(BITMAPINFOHEADER)+NewNumColors*sizeof(RGBQUAD)+(DWORD)DstLineBytes*bi.biHeight);
	memcpy((char *)&DstBf,(char *)&bf,sizeof(BITMAPFILEHEADER));
	memcpy((char *)&DstBi,(char *)&bi,sizeof(BITMAPINFOHEADER));
	DstBf.bfSize=DstBufSize+sizeof(BITMAPFILEHEADER);
	DstBf.bfOffBits=(DWORD)(NewNumColors*sizeof(RGBQUAD)+sizeof(BITMAPFILEHEADER)
							+sizeof(BITMAPINFOHEADER));
	DstBi.biClrUsed=0;
	DstBi.biBitCount=NewBitCount;

	SrcBufSize=bf.bfSize-sizeof(BITMAPFILEHEADER);

	if((hTempImgData=LocalAlloc(LHND,DstBufSize))==NULL)
    {
    	MessageBox(hWnd,"Error alloc memory!","Error Message",MB_OK|MB_ICONEXCLAMATION);
        return FALSE;
    }

    lpImgData=(LPBITMAPINFOHEADER)GlobalLock(hImgData);    
	lpTempImgData=(LPBITMAPINFOHEADER)LocalLock(hTempImgData);

	//copy image data
	memcpy(lpTempImgData,lpImgData,DstBufSize);
	//overwrite bitmapinfoheader with the new one
	memcpy(lpTempImgData,(char *)&DstBi,sizeof(BITMAPINFOHEADER));

	lpPtr=(char *)lpImgData+sizeof(BITMAPINFOHEADER);
	lpTempPtr=(char *)lpTempImgData+sizeof(BITMAPINFOHEADER);

    hPal=LocalAlloc(LHND,sizeof(LOGPALETTE) + NewNumColors* sizeof(PALETTEENTRY));
    pPal =(LOGPALETTE *)LocalLock(hPal);
    pPal->palNumEntries =(WORD) NewNumColors;
	pPal->palVersion    = 0x300;

	if(NumColors==0) //true color
		for (i = 0; i < 256; i++) {
     		pPal->palPalEntry[i].peRed=(BYTE)i;
			pPal->palPalEntry[i].peGreen=(BYTE)i;
			pPal->palPalEntry[i].peBlue=(BYTE)i;
			pPal->palPalEntry[i].peFlags=(BYTE)0;
			*(lpTempPtr++)=(unsigned char)i;
			*(lpTempPtr++)=(unsigned char)i;
			*(lpTempPtr++)=(unsigned char)i;
			*(lpTempPtr++)=0;
		}
	else 
		for (i = 0; i < NewNumColors; i++) {
			Blue=(unsigned char )(*lpPtr++);
			Green=(unsigned char )(*lpPtr++);
			Red=(unsigned char )(*lpPtr++);
			Y=(float)(Red*0.299+Green*0.587+Blue*0.114);
			Gray=(BYTE)Y;
			lpPtr++;
     		pPal->palPalEntry[i].peRed=Gray;
			pPal->palPalEntry[i].peGreen=Gray;
			pPal->palPalEntry[i].peBlue=Gray;
			pPal->palPalEntry[i].peFlags=0;
			*(lpTempPtr++)=(unsigned char)Gray;
			*(lpTempPtr++)=(unsigned char)Gray;
			*(lpTempPtr++)=(unsigned char)Gray;
			*(lpTempPtr++)=0;
		}

	if(hPalette!=NULL)                     
        DeleteObject(hPalette);
		
	hPalette=CreatePalette(pPal);
	LocalUnlock(hPal);
	LocalFree(hPal);

	hDc=GetDC(hWnd);
	if(hPalette){
        hPrevPalette=SelectPalette(hDc,hPalette,FALSE);
		RealizePalette(hDc);
	}
	
	if(NumColors==0)
		for(y=0;y<bi.biHeight;y++){
			lpPtr=(char *)lpImgData+(SrcBufSize-LineBytes-y*LineBytes);
			lpTempPtr=(char *)lpTempImgData+(DstBufSize-DstLineBytes-y*DstLineBytes);
			for(x=0;x<bi.biWidth;x++){
				Blue=(unsigned char )(*lpPtr++);
				Green=(unsigned char )(*lpPtr++);
				Red=(unsigned char )(*lpPtr++);
				Y=(float)(Red*0.299+Green*0.587+Blue*0.114);
				Gray=(BYTE)Y;
				*(lpTempPtr++)=(unsigned char)Gray;
			}
		}

    if(hBitmap!=NULL)
	    DeleteObject(hBitmap);
	
	hBitmap=CreateDIBitmap(hDc,	(LPBITMAPINFOHEADER)lpTempImgData, (LONG)CBM_INIT,
				(LPSTR)lpTempImgData+sizeof(BITMAPINFOHEADER) +NewNumColors*sizeof(RGBQUAD),
   				(LPBITMAPINFO)lpTempImgData, DIB_RGB_COLORS);

	if(hPalette && hPrevPalette){
		SelectPalette(hDc,hPrevPalette,FALSE);
		RealizePalette(hDc);
	}

    hf=_lcreat("c:\\gray.bmp",0);
	_lwrite(hf,(LPSTR)&DstBf,sizeof(BITMAPFILEHEADER)); 
	_lwrite(hf,(LPSTR)lpTempImgData,DstBufSize);
	_lclose(hf);

 	ReleaseDC(hWnd,hDc);
	LocalUnlock(hTempImgData);
	LocalFree(hTempImgData);
	GlobalUnlock(hImgData);
	return TRUE;
}
////////////////////////////////////////////////////////////////
BOOL Invert(HWND hWnd)
{
	DWORD              BufSize;
    LPBITMAPINFOHEADER lpImgData;
	LPSTR              lpPtr;
	HLOCAL             hTempImgData;
	LPBITMAPINFOHEADER lpTempImgData;
	LPSTR              lpTempPtr;
	HDC                hDc;
	HFILE              hf;
	LONG               x,y;
    LOGPALETTE         *pPal;
    HPALETTE           hPrevPalette=NULL; 
	HLOCAL             hPal;
	DWORD              i;
	unsigned char      Red,Green,Blue;

	BufSize=bf.bfSize-sizeof(BITMAPFILEHEADER);

	if((hTempImgData=LocalAlloc(LHND,BufSize))==NULL)
    {
    	MessageBox(hWnd,"Error alloc memory!","Error Message",MB_OK|MB_ICONEXCLAMATION);
        return FALSE;
    }

    lpImgData=(LPBITMAPINFOHEADER)GlobalLock(hImgData);    
	lpTempImgData=(LPBITMAPINFOHEADER)LocalLock(hTempImgData);

	//copy image data
	memcpy(lpTempImgData,lpImgData,BufSize);

	hDc=GetDC(hWnd);
	if(NumColors!=0){
		lpPtr=(char *)lpImgData+sizeof(BITMAPINFOHEADER);
		lpTempPtr=(char *)lpTempImgData+sizeof(BITMAPINFOHEADER);
	    hPal=LocalAlloc(LHND,sizeof(LOGPALETTE) + NumColors* sizeof(PALETTEENTRY));
		pPal =(LOGPALETTE *)LocalLock(hPal);
		pPal->palNumEntries =(WORD) NumColors;
		pPal->palVersion    = 0x300;
		for (i = 0; i < NumColors; i++) {
			Blue=(unsigned char )(*lpPtr++);
			Green=(unsigned char )(*lpPtr++);
			Red=(unsigned char )(*lpPtr++);
			lpPtr++;
     		pPal->palPalEntry[i].peRed=(BYTE)(255-Red);
			pPal->palPalEntry[i].peGreen=(BYTE)(255-Green);
			pPal->palPalEntry[i].peBlue=(BYTE)(255-Blue);
			pPal->palPalEntry[i].peFlags=0;
			*(lpTempPtr++)=(unsigned char)(255-Blue);
			*(lpTempPtr++)=(unsigned char)(255-Green);
			*(lpTempPtr++)=(unsigned char)(255-Red);
			*(lpTempPtr++)=0;
		}

		if(hPalette!=NULL)                     
			DeleteObject(hPalette);
		hPalette=CreatePalette(pPal);
		LocalUnlock(hPal);
		LocalFree(hPal);
		if(hPalette){
			hPrevPalette=SelectPalette(hDc,hPalette,FALSE);
			RealizePalette(hDc);
		}
	}
	else{
		for(y=0;y<bi.biHeight;y++){
			lpPtr=(char *)lpImgData+(BufSize-LineBytes-y*LineBytes);
			lpTempPtr=(char *)lpTempImgData+(BufSize-LineBytes-y*LineBytes);
			for(x=0;x<bi.biWidth;x++){
				Blue=(unsigned char )(*lpPtr++);
				Green=(unsigned char )(*lpPtr++);
				Red=(unsigned char )(*lpPtr++);
				*(lpTempPtr++)=(unsigned char)(255-Blue);
				*(lpTempPtr++)=(unsigned char)(255-Green);
				*(lpTempPtr++)=(unsigned char)(255-Red);
			}
		}
	}

    if(hBitmap!=NULL)
	    DeleteObject(hBitmap);
	
	hBitmap=CreateDIBitmap(hDc,	(LPBITMAPINFOHEADER)lpTempImgData, (LONG)CBM_INIT,
				(LPSTR)lpTempImgData+sizeof(BITMAPINFOHEADER) +NumColors*sizeof(RGBQUAD),
   				(LPBITMAPINFO)lpTempImgData, DIB_RGB_COLORS);

	if(hPalette && hPrevPalette){
		SelectPalette(hDc,hPrevPalette,FALSE);
		RealizePalette(hDc);
	}

    hf=_lcreat("c:\\invert.bmp",0);
	_lwrite(hf,(LPSTR)&bf,sizeof(BITMAPFILEHEADER)); 
	_lwrite(hf,(LPSTR)lpTempImgData,BufSize);
	_lclose(hf);

 	ReleaseDC(hWnd,hDc);
	LocalUnlock(hTempImgData);
	LocalFree(hTempImgData);
	GlobalUnlock(hImgData);
	return TRUE;
}
////////////////////////////////////////////////////////////////
BOOL Histogram(HWND hWnd)
{
	DWORD              OffBits,BufSize;
    LPBITMAPINFOHEADER lpImgData;
	LPSTR              lpPtr;
	int				   x,y;
	int                grayindex;
	HWND			   hPopupWnd;
	int                temp;
	
	for(grayindex=0;grayindex<256;grayindex++)
		GrayTable[grayindex]=0;

	OffBits=bf.bfOffBits-sizeof(BITMAPFILEHEADER);
	BufSize=bf.bfSize-sizeof(BITMAPFILEHEADER);
    lpImgData=(LPBITMAPINFOHEADER)GlobalLock(hImgData);

	for(y=0;y<bi.biHeight;y++){
		lpPtr=(char *)lpImgData+(BufSize-LineBytes-y*LineBytes);
		for(x=0;x<bi.biWidth;x++){
			grayindex=(unsigned char)*(lpPtr++);
			GrayTable[grayindex]++;
		}
	}

	MaxGrayNum=0;
	MinGrayNum=65535;

	for(grayindex=0;grayindex<256;grayindex++){
		temp=GrayTable[grayindex];
		if(temp>MaxGrayNum)
			MaxGrayNum=temp;
		if( (temp<MinGrayNum) && (temp>0) )
			MinGrayNum=temp;
	}

	GlobalUnlock(hImgData);
    hPopupWnd = CreateWindow (
							  "PopupWindowClass",
							  "Histogram Statistic Window",
    						  WS_OVERLAPPEDWINDOW,
    						  50,80,550,350,
    						  hWnd,NULL,ghInst,NULL
    						  );
	if (hPopupWnd){
		ShowWindow (hPopupWnd, SW_SHOW);
   		UpdateWindow (hPopupWnd);
   	}
	return TRUE;
}
////////////////////////////////////////////////////////////////
long FAR PASCAL PopupWndProc (HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	HDC 			hdc;
	PAINTSTRUCT 	ps;   
	DWORD		 	i;
	int             xstart;   
	static LOGPEN   blp={PS_SOLID,1,1,RGB(0,0,255)};
	HPEN            bhp;
	float           a,b,temp;
	char            str[10];
	
	a=(float)(265.0 /( MaxGrayNum - MinGrayNum) );
	b=(float) (270.0-a* MaxGrayNum);
    switch (message)
    	{
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
	    bhp = CreatePenIndirect(&blp);
		SelectObject(hdc,bhp);
        MoveToEx(hdc,2,270,NULL);
        LineTo(hdc,518,270);
        xstart=2;
        for(i=0;i<256;i++){
        	MoveToEx(hdc,xstart,270,NULL);
			if (GrayTable[i]!=0) 
				temp=(float)(a*GrayTable[i]+b);
			else temp=0.0f;
        	LineTo(hdc,xstart,270-(int)temp);
			if (i%16 ==0){
        		MoveToEx(hdc,xstart,270,NULL);
        		LineTo(hdc,xstart,280);
				_itoa(i,str,10);
				TextOut(hdc,xstart,285,str,strlen(str));
			}
        	xstart+=2;
        }
   		MoveToEx(hdc,xstart,270,NULL);
   		LineTo(hdc,xstart,280);
		TextOut(hdc,xstart,285,"256",strlen("256"));
        EndPaint(hWnd,&ps);	
        DeleteObject(bhp);
        break;
    default:
    	break;
    	}	
    return DefWindowProc (hWnd, message, wParam, lParam);
}
////////////////////////////////////////////////////////////////
BOOL Trueto256(HWND hWnd)
{
	DWORD              SrcBufSize,OffBits,DstBufSize,DstLineBytes;
    LPBITMAPINFOHEADER lpImgData;
	LPSTR              lpPtr;
	HLOCAL             hTempImgData;
	LPBITMAPINFOHEADER lpTempImgData;
	LPSTR              lpTempPtr;
	HDC                hDc;
	HFILE              hf;
	LONG               x,y;
	BITMAPFILEHEADER   DstBf;
	BITMAPINFOHEADER   DstBi;
    LOGPALETTE         *pPal;
    HPALETTE           hPrevPalette; 
	HLOCAL             hPal;
	WORD               i,j;
	int				   Red,Green,Blue,ClrIndex;
	DWORD              ColorHits[4096];
	WORD               ColorIndex[4096];
	DWORD              PalCounts,temp;
	long			   ColorError1,ColorError2;

	if(NumColors!=0){
    	MessageBox(hWnd,"Must be a true color bitmap!","Error Message",MB_OK|MB_ICONEXCLAMATION);
        return FALSE;
    }

	DstLineBytes=(DWORD)WIDTHBYTES(bi.biWidth*8);
	DstBufSize=(DWORD)(sizeof(BITMAPINFOHEADER)+256*sizeof(RGBQUAD)+(DWORD)DstLineBytes*bi.biHeight);
	memcpy((char *)&DstBf,(char *)&bf,sizeof(BITMAPFILEHEADER));
	memcpy((char *)&DstBi,(char *)&bi,sizeof(BITMAPINFOHEADER));
	DstBf.bfSize=DstBufSize+sizeof(BITMAPFILEHEADER);
	DstBf.bfOffBits=(DWORD)(256*sizeof(RGBQUAD)+sizeof(BITMAPFILEHEADER)
							+sizeof(BITMAPINFOHEADER));
	DstBi.biClrUsed=0;
	DstBi.biBitCount=8;

	OffBits=bf.bfOffBits-sizeof(BITMAPFILEHEADER);
	SrcBufSize=bf.bfSize-sizeof(BITMAPFILEHEADER);
	
	if((hTempImgData=LocalAlloc(LHND,DstBufSize))==NULL)
    {
    	MessageBox(hWnd,"Error alloc memory!","Error Message",MB_OK|MB_ICONEXCLAMATION);
        return FALSE;
    }

    lpImgData=(LPBITMAPINFOHEADER)GlobalLock(hImgData);    
	lpTempImgData=(LPBITMAPINFOHEADER)LocalLock(hTempImgData);

	//copy image data
	memcpy(lpTempImgData,lpImgData,OffBits);
	//overwrite bitmapinfoheader with the new one
	memcpy(lpTempImgData,(char *)&DstBi,sizeof(BITMAPINFOHEADER));

	memset(ColorHits,0,4096*sizeof(DWORD));
	memset(ColorIndex,0,4096*sizeof(WORD));
	for(y=0;y<bi.biHeight;y++){
		lpPtr=(unsigned char *)lpImgData+(SrcBufSize-LineBytes-y*LineBytes);
		for(x=0;x<bi.biWidth;x++){
			Blue=(int)(*(lpPtr++) & 0xf0);
			Green=(int)(*(lpPtr++) & 0xf0);
			Red=(int)(*(lpPtr++) & 0xf0);
			ClrIndex=(Blue<<4) + Green +(Red >>4);
			ColorHits[ClrIndex]++;
		}
	}

	PalCounts=0;
	//pack the color table
    for (ClrIndex = 0; ClrIndex < 4096; ClrIndex++)
    {
		if(ColorHits[ClrIndex]!=0){
			ColorHits[PalCounts]=ColorHits[ClrIndex];
			ColorIndex[PalCounts]=ClrIndex;
			PalCounts++;
		}
	}
    //sort the color table downsize
    for (i = 0; i < PalCounts-1; i++)
		for (j = i + 1; j < PalCounts; j++){
			if (ColorHits[j] > ColorHits[i]){
				temp = ColorHits[i];
				ColorHits[i] = ColorHits[j];
				ColorHits[j] = temp;  
	            temp = ColorIndex[i];
		        ColorIndex[i] = ColorIndex[j];
			    ColorIndex[j] = (WORD)temp;
			}
		}
	
    hPal=LocalAlloc(LHND,sizeof(LOGPALETTE) + 256* sizeof(PALETTEENTRY));
    pPal =(LOGPALETTE *)LocalLock(hPal);
    pPal->palNumEntries =(WORD) 256;
	pPal->palVersion    = 0x300;

	lpTempPtr=(char *)lpTempImgData+sizeof(BITMAPINFOHEADER);
	for (i = 0; i < 256; i++) {
   		pPal->palPalEntry[i].peRed=(BYTE)((ColorIndex[i] & 0x00f) << 4);
		pPal->palPalEntry[i].peGreen=(BYTE)((ColorIndex[i] & 0x0f0));
		pPal->palPalEntry[i].peBlue=(BYTE)((ColorIndex[i] & 0xf00) >> 4);
		pPal->palPalEntry[i].peFlags=(BYTE)0;
		*(lpTempPtr++)=(unsigned char)((ColorIndex[i] & 0xf00) >> 4);
		*(lpTempPtr++)=(unsigned char)((ColorIndex[i] & 0x0f0));
		*(lpTempPtr++)=(unsigned char)((ColorIndex[i] & 0x00f) << 4);
		*(lpTempPtr++)=0;
		ColorHits[i]=i;
	}

	//其余的颜色依据最小平方差近似为前256中最接近的一种
    if (PalCounts > 256){
		for (i = 256; i < PalCounts; i++){
			ColorError1=1000000000;
			Blue = (long)((ColorIndex[i] & 0xf00) >> 4);
			Green = (long)((ColorIndex[i] & 0x0f0));
			Red = (long)((ColorIndex[i] & 0x00f) << 4);
			ClrIndex = 0;
			for (j = 0; j < 256; j++){
				ColorError2=(long)(Blue-pPal->palPalEntry[j].peBlue)*(Blue-pPal->palPalEntry[j].peBlue)+ 
                        (long)(Green-pPal->palPalEntry[j].peGreen)*(Green-pPal->palPalEntry[j].peGreen)+
                        (long)(Red-pPal->palPalEntry[j].peRed)*(Red-pPal->palPalEntry[j].peRed); 
                if (ColorError2 < ColorError1){
					ColorError1 = ColorError2;
					ClrIndex = j;
                }
			}                        
			ColorHits[i] = ClrIndex;
		}
	}                

	if(hPalette!=NULL)                     
        DeleteObject(hPalette);
	
	//create new logic palette		
	hPalette=CreatePalette(pPal);
	LocalUnlock(hPal);
	LocalFree(hPal);

	hDc=GetDC(hWnd);
	if(hPalette){
        hPrevPalette=SelectPalette(hDc,hPalette,FALSE);
		RealizePalette(hDc);
	}

	for(y=0;y<bi.biHeight;y++){
		lpPtr=(char *)lpImgData+(SrcBufSize-LineBytes-y*LineBytes);
		lpTempPtr=(char *)lpTempImgData+(DstBufSize-DstLineBytes-y*DstLineBytes);
		for(x=0;x<bi.biWidth;x++){
			Blue=(int)(*(lpPtr++) & 0xf0);
			Green=(int)(*(lpPtr++) & 0xf0);
			Red=(int)(*(lpPtr++) & 0xf0);
			ClrIndex=(Blue<<4) + Green +(Red >>4);
            for (i = 0; i < PalCounts;i++)
				if (ClrIndex == ColorIndex[i]){
					*(lpTempPtr++)=(unsigned char)ColorHits[i];
                    break;
				}
		}
	}

    if(hBitmap!=NULL)
	    DeleteObject(hBitmap);
	
	hBitmap=CreateDIBitmap(hDc,	(LPBITMAPINFOHEADER)lpTempImgData, (LONG)CBM_INIT,
				(LPSTR)lpTempImgData+sizeof(BITMAPINFOHEADER) +256*sizeof(RGBQUAD),
   				(LPBITMAPINFO)lpTempImgData, DIB_RGB_COLORS);

	if(hPalette && hPrevPalette){
		SelectPalette(hDc,hPrevPalette,FALSE);
		RealizePalette(hDc);
	}

    hf=_lcreat("c:\\256.bmp",0);
	_lwrite(hf,(LPSTR)&DstBf,sizeof(BITMAPFILEHEADER)); 
	_lwrite(hf,(LPSTR)lpTempImgData,DstBufSize);
	_lclose(hf);

 	ReleaseDC(hWnd,hDc);
	LocalUnlock(hTempImgData);
	LocalFree(hTempImgData);
	GlobalUnlock(hImgData);
	return TRUE;
}
////////////////////////////////////////////////////////////////
BOOL ContrastStretch(HWND hWnd)
{
	DLGPROC            dlgInputBox = NULL;
	DWORD              BufSize;
    LPBITMAPINFOHEADER lpImgData;
	LPSTR              lpPtr;
	HLOCAL             hTempImgData;
	LPBITMAPINFOHEADER lpTempImgData;
	LPSTR              lpTempPtr;
	HDC                hDc;
	HFILE              hf;
    LOGPALETTE         *pPal;
    HPALETTE           hPrevPalette=NULL; 
	HLOCAL             hPal;
	DWORD              i;
	unsigned char      Gray;
	float              a,g1,g2,g;

	if( NumColors!=256){
    	MessageBox(hWnd,"Must be a 256 grayscale bitmap!","Error Message",MB_OK|MB_ICONEXCLAMATION);
        return FALSE;
    }

	dlgInputBox = (DLGPROC) MakeProcInstance ( (FARPROC)InputBox, ghInst );
	DialogBox (ghInst, "INPUTBOX", hWnd, dlgInputBox);
	FreeProcInstance ( (FARPROC) dlgInputBox );

	if( StretchRatio*(SecondPoint-FirstPoint) > 255.0){
    	MessageBox(hWnd,"StretchRatio*(SecondPoint-FirstPoint)  can not be larger than 255!","Error Message",MB_OK|MB_ICONEXCLAMATION);
        return FALSE;
    }
	if( (SecondPoint-FirstPoint) >=255){
    	MessageBox(hWnd,"The area you selected can not be the whole scale!","Error Message",MB_OK|MB_ICONEXCLAMATION);
        return FALSE;
    }
	a=(float)((255.0-StretchRatio*(SecondPoint-FirstPoint))/(255.0-(SecondPoint-FirstPoint))); 
	g1=a*FirstPoint;
	g2=StretchRatio*(SecondPoint-FirstPoint)+g1;

	BufSize=bf.bfSize-sizeof(BITMAPFILEHEADER);

	if((hTempImgData=LocalAlloc(LHND,BufSize))==NULL)
    {
    	MessageBox(hWnd,"Error alloc memory!","Error Message",MB_OK|MB_ICONEXCLAMATION);
        return FALSE;
    }

    lpImgData=(LPBITMAPINFOHEADER)GlobalLock(hImgData);    
	lpTempImgData=(LPBITMAPINFOHEADER)LocalLock(hTempImgData);

	//copy image data
	memcpy(lpTempImgData,lpImgData,BufSize);

	hDc=GetDC(hWnd);

	lpPtr=(char *)lpImgData+sizeof(BITMAPINFOHEADER);
	lpTempPtr=(char *)lpTempImgData+sizeof(BITMAPINFOHEADER);
	hPal=LocalAlloc(LHND,sizeof(LOGPALETTE) + NumColors* sizeof(PALETTEENTRY));
	pPal =(LOGPALETTE *)LocalLock(hPal);
	pPal->palNumEntries =(WORD) NumColors;
	pPal->palVersion    = 0x300;
	for (i = 0; i < 256; i++) {
		Gray=(unsigned char )*lpPtr;
		lpPtr+=4;
		if(Gray<FirstPoint) g=(float)(a*Gray);
		else if (Gray<SecondPoint) g=g1+StretchRatio*(Gray-FirstPoint);
		else g=g2+a*(Gray-SecondPoint);
   		pPal->palPalEntry[i].peRed=(BYTE)g;
		pPal->palPalEntry[i].peGreen=(BYTE)g;
		pPal->palPalEntry[i].peBlue=(BYTE)g;
		pPal->palPalEntry[i].peFlags=0;
		*(lpTempPtr++)=(unsigned char)g;
		*(lpTempPtr++)=(unsigned char)g;
		*(lpTempPtr++)=(unsigned char)g;
		*(lpTempPtr++)=0;
	}

	if(hPalette!=NULL)                     
		DeleteObject(hPalette);
	hPalette=CreatePalette(pPal);
	LocalUnlock(hPal);
	LocalFree(hPal);
	if(hPalette){
		hPrevPalette=SelectPalette(hDc,hPalette,FALSE);
		RealizePalette(hDc);
	}

    if(hBitmap!=NULL)
	    DeleteObject(hBitmap);
	
	hBitmap=CreateDIBitmap(hDc,	(LPBITMAPINFOHEADER)lpTempImgData, (LONG)CBM_INIT,
				(LPSTR)lpTempImgData+sizeof(BITMAPINFOHEADER) +NumColors*sizeof(RGBQUAD),
   				(LPBITMAPINFO)lpTempImgData, DIB_RGB_COLORS);

	if(hPalette && hPrevPalette){
		SelectPalette(hDc,hPrevPalette,FALSE);
		RealizePalette(hDc);
	}

    hf=_lcreat("c:\\stretch.bmp",0);
	_lwrite(hf,(LPSTR)&bf,sizeof(BITMAPFILEHEADER)); 
	_lwrite(hf,(LPSTR)lpTempImgData,BufSize);
	_lclose(hf);

 	ReleaseDC(hWnd,hDc);
	LocalUnlock(hTempImgData);
	LocalFree(hTempImgData);
	GlobalUnlock(hImgData);
	return TRUE;
}
////////////////////////////////////////////////////////////////
BOOL Cliping(HWND hWnd)
{
	DLGPROC            dlgInputBox = NULL;
	DWORD              BufSize;
    LPBITMAPINFOHEADER lpImgData;
	LPSTR              lpPtr;
	HLOCAL             hTempImgData;
	LPBITMAPINFOHEADER lpTempImgData;
	LPSTR              lpTempPtr;
	HDC                hDc;
	HFILE              hf;
    LOGPALETTE         *pPal;
    HPALETTE           hPrevPalette=NULL; 
	HLOCAL             hPal;
	DWORD              i;
	unsigned char      Gray;
	float              a,g;

	if( NumColors!=256){
    	MessageBox(hWnd,"Must be a 256 grayscale bitmap!","Error Message",MB_OK|MB_ICONEXCLAMATION);
        return FALSE;
    }

	dlgInputBox = (DLGPROC) MakeProcInstance ( (FARPROC)InputBox, ghInst );
	DialogBox (ghInst, "INPUTBOX", hWnd, dlgInputBox);
	FreeProcInstance ( (FARPROC) dlgInputBox );

	if( (SecondPoint-FirstPoint) >255){
    	MessageBox(hWnd,"The area you selected must be within [0-255]!","Error Message",MB_OK|MB_ICONEXCLAMATION);
        return FALSE;
    }
	a=(float)(255.0/(SecondPoint-FirstPoint)); 

	BufSize=bf.bfSize-sizeof(BITMAPFILEHEADER);

	if((hTempImgData=LocalAlloc(LHND,BufSize))==NULL)
    {
    	MessageBox(hWnd,"Error alloc memory!","Error Message",MB_OK|MB_ICONEXCLAMATION);
        return FALSE;
    }

    lpImgData=(LPBITMAPINFOHEADER)GlobalLock(hImgData);    
	lpTempImgData=(LPBITMAPINFOHEADER)LocalLock(hTempImgData);

	//copy image data
	memcpy(lpTempImgData,lpImgData,BufSize);

	hDc=GetDC(hWnd);

	lpPtr=(char *)lpImgData+sizeof(BITMAPINFOHEADER);
	lpTempPtr=(char *)lpTempImgData+sizeof(BITMAPINFOHEADER);
	hPal=LocalAlloc(LHND,sizeof(LOGPALETTE) + NumColors* sizeof(PALETTEENTRY));
	pPal =(LOGPALETTE *)LocalLock(hPal);
	pPal->palNumEntries =(WORD) NumColors;
	pPal->palVersion    = 0x300;
	for (i = 0; i < 256; i++) {
		Gray=(unsigned char )*lpPtr;
		lpPtr+=4;
		if(Gray<FirstPoint) g=0.0f;
		else if (Gray<SecondPoint) g=a*(Gray-FirstPoint);
		else g=255.0f;
   		pPal->palPalEntry[i].peRed=(BYTE)g;
		pPal->palPalEntry[i].peGreen=(BYTE)g;
		pPal->palPalEntry[i].peBlue=(BYTE)g;
		pPal->palPalEntry[i].peFlags=0;
		*(lpTempPtr++)=(unsigned char)g;
		*(lpTempPtr++)=(unsigned char)g;
		*(lpTempPtr++)=(unsigned char)g;
		*(lpTempPtr++)=0;
	}

	if(hPalette!=NULL)                     
		DeleteObject(hPalette);
	hPalette=CreatePalette(pPal);
	LocalUnlock(hPal);
	LocalFree(hPal);
	if(hPalette){
		hPrevPalette=SelectPalette(hDc,hPalette,FALSE);
		RealizePalette(hDc);
	}

    if(hBitmap!=NULL)
	    DeleteObject(hBitmap);
	
	hBitmap=CreateDIBitmap(hDc,	(LPBITMAPINFOHEADER)lpTempImgData, (LONG)CBM_INIT,
				(LPSTR)lpTempImgData+sizeof(BITMAPINFOHEADER) +NumColors*sizeof(RGBQUAD),
   				(LPBITMAPINFO)lpTempImgData, DIB_RGB_COLORS);

	if(hPalette && hPrevPalette){
		SelectPalette(hDc,hPrevPalette,FALSE);
		RealizePalette(hDc);
	}

    hf=_lcreat("c:\\cliping.bmp",0);
	_lwrite(hf,(LPSTR)&bf,sizeof(BITMAPFILEHEADER)); 
	_lwrite(hf,(LPSTR)lpTempImgData,BufSize);
	_lclose(hf);

 	ReleaseDC(hWnd,hDc);
	LocalUnlock(hTempImgData);
	LocalFree(hTempImgData);
	GlobalUnlock(hImgData);
	return TRUE;
}
////////////////////////////////////////////////////////////////
BOOL Thresholding(HWND hWnd)
{
	DLGPROC            dlgInputBox = NULL;
	DWORD              BufSize;
    LPBITMAPINFOHEADER lpImgData;
	LPSTR              lpPtr;
	HLOCAL             hTempImgData;
	LPBITMAPINFOHEADER lpTempImgData;
	LPSTR              lpTempPtr;
	HDC                hDc;
	HFILE              hf;
    LOGPALETTE         *pPal;
    HPALETTE           hPrevPalette=NULL; 
	HLOCAL             hPal;
	DWORD              i;
	unsigned char      Gray;

	if( NumColors!=256){
    	MessageBox(hWnd,"Must be a 256 grayscale bitmap!","Error Message",MB_OK|MB_ICONEXCLAMATION);
        return FALSE;
    }
	dlgInputBox = (DLGPROC) MakeProcInstance ( (FARPROC)InputBox, ghInst );
	DialogBox (ghInst, "INPUTBOX", hWnd, dlgInputBox);
	FreeProcInstance ( (FARPROC) dlgInputBox );
	if( FirstPoint >255){
    	MessageBox(hWnd,"The point you selected must be within [0-255]","Error Message",MB_OK|MB_ICONEXCLAMATION);
        return FALSE;
    }
	BufSize=bf.bfSize-sizeof(BITMAPFILEHEADER);
	if((hTempImgData=LocalAlloc(LHND,BufSize))==NULL)
    {
    	MessageBox(hWnd,"Error alloc memory!","Error Message",MB_OK|MB_ICONEXCLAMATION);
        return FALSE;
    }
    lpImgData=(LPBITMAPINFOHEADER)GlobalLock(hImgData);    
	lpTempImgData=(LPBITMAPINFOHEADER)LocalLock(hTempImgData);
	//copy image data
	memcpy(lpTempImgData,lpImgData,BufSize);

	hDc=GetDC(hWnd);

	lpPtr=(char *)lpImgData+sizeof(BITMAPINFOHEADER);
	lpTempPtr=(char *)lpTempImgData+sizeof(BITMAPINFOHEADER);
	hPal=LocalAlloc(LHND,sizeof(LOGPALETTE) + NumColors* sizeof(PALETTEENTRY));
	pPal =(LOGPALETTE *)LocalLock(hPal);
	pPal->palNumEntries =(WORD) NumColors;
	pPal->palVersion    = 0x300;
	for (i = 0; i < 256; i++) {
		Gray=(unsigned char )*lpPtr;
		lpPtr+=4;
		if(Gray<FirstPoint) Gray=0;
		else Gray=255;
   		pPal->palPalEntry[i].peRed=Gray;
		pPal->palPalEntry[i].peGreen=Gray;
		pPal->palPalEntry[i].peBlue=Gray;
		pPal->palPalEntry[i].peFlags=0;
		*(lpTempPtr++)=(unsigned char)Gray;
		*(lpTempPtr++)=(unsigned char)Gray;
		*(lpTempPtr++)=(unsigned char)Gray;
		*(lpTempPtr++)=0;
	}

	if(hPalette!=NULL)                     
		DeleteObject(hPalette);
	hPalette=CreatePalette(pPal);
	LocalUnlock(hPal);
	LocalFree(hPal);
	if(hPalette){
		hPrevPalette=SelectPalette(hDc,hPalette,FALSE);
		RealizePalette(hDc);
	}

    if(hBitmap!=NULL)
	    DeleteObject(hBitmap);
	
	hBitmap=CreateDIBitmap(hDc,	(LPBITMAPINFOHEADER)lpTempImgData, (LONG)CBM_INIT,
				(LPSTR)lpTempImgData+sizeof(BITMAPINFOHEADER) +NumColors*sizeof(RGBQUAD),
   				(LPBITMAPINFO)lpTempImgData, DIB_RGB_COLORS);

	if(hPalette && hPrevPalette){
		SelectPalette(hDc,hPrevPalette,FALSE);
		RealizePalette(hDc);
	}

    hf=_lcreat("c:\\threshold.bmp",0);
	_lwrite(hf,(LPSTR)&bf,sizeof(BITMAPFILEHEADER)); 
	_lwrite(hf,(LPSTR)lpTempImgData,BufSize);
	_lclose(hf);

 	ReleaseDC(hWnd,hDc);
	LocalUnlock(hTempImgData);
	LocalFree(hTempImgData);
	GlobalUnlock(hImgData);
	return TRUE;
}
////////////////////////////////////////////////////////////////
BOOL Slice(HWND hWnd,BOOL WithBack)
{
	DLGPROC            dlgInputBox = NULL;
	DWORD              BufSize;
    LPBITMAPINFOHEADER lpImgData;
	LPSTR              lpPtr;
	HLOCAL             hTempImgData;
	LPBITMAPINFOHEADER lpTempImgData;
	LPSTR              lpTempPtr;
	HDC                hDc;
	HFILE              hf;
    LOGPALETTE         *pPal;
    HPALETTE           hPrevPalette=NULL; 
	HLOCAL             hPal;
	DWORD              i;
	unsigned char      Gray;

	if( NumColors!=256){
    	MessageBox(hWnd,"Must be a 256 grayscale bitmap!","Error Message",MB_OK|MB_ICONEXCLAMATION);
        return FALSE;
    }
	dlgInputBox = (DLGPROC) MakeProcInstance ( (FARPROC)InputBox, ghInst );
	DialogBox (ghInst, "INPUTBOX", hWnd, dlgInputBox);
	FreeProcInstance ( (FARPROC) dlgInputBox );

	if( (SecondPoint-FirstPoint) >255){
    	MessageBox(hWnd,"The area you selected must be within [0-255]!","Error Message",MB_OK|MB_ICONEXCLAMATION);
        return FALSE;
    }
	BufSize=bf.bfSize-sizeof(BITMAPFILEHEADER);
	if((hTempImgData=LocalAlloc(LHND,BufSize))==NULL)
    {
    	MessageBox(hWnd,"Error alloc memory!","Error Message",MB_OK|MB_ICONEXCLAMATION);
        return FALSE;
    }
    lpImgData=(LPBITMAPINFOHEADER)GlobalLock(hImgData);    
	lpTempImgData=(LPBITMAPINFOHEADER)LocalLock(hTempImgData);
	//copy image data
	memcpy(lpTempImgData,lpImgData,BufSize);

	hDc=GetDC(hWnd);
	lpPtr=(char *)lpImgData+sizeof(BITMAPINFOHEADER);
	lpTempPtr=(char *)lpTempImgData+sizeof(BITMAPINFOHEADER);
	hPal=LocalAlloc(LHND,sizeof(LOGPALETTE) + NumColors* sizeof(PALETTEENTRY));
	pPal =(LOGPALETTE *)LocalLock(hPal);
	pPal->palNumEntries =(WORD) NumColors;
	pPal->palVersion    = 0x300;
	for (i = 0; i < 256; i++) {
		Gray=(unsigned char )*lpPtr;
		lpPtr+=4;
		if(WithBack){
			if( (Gray>=FirstPoint) && (Gray<=SecondPoint))
				Gray=255;
		}
		else{
			if(Gray<FirstPoint) Gray=0;
			else if (Gray<SecondPoint) Gray=255;
			else Gray=0;
		}
   		pPal->palPalEntry[i].peRed=Gray;
		pPal->palPalEntry[i].peGreen=Gray;
		pPal->palPalEntry[i].peBlue=Gray;
		pPal->palPalEntry[i].peFlags=0;
		*(lpTempPtr++)=(unsigned char)Gray;
		*(lpTempPtr++)=(unsigned char)Gray;
		*(lpTempPtr++)=(unsigned char)Gray;
		*(lpTempPtr++)=0;
	}

	if(hPalette!=NULL)                     
		DeleteObject(hPalette);
	hPalette=CreatePalette(pPal);
	LocalUnlock(hPal);
	LocalFree(hPal);
	if(hPalette){
		hPrevPalette=SelectPalette(hDc,hPalette,FALSE);
		RealizePalette(hDc);
	}

    if(hBitmap!=NULL)
	    DeleteObject(hBitmap);
	
	hBitmap=CreateDIBitmap(hDc,	(LPBITMAPINFOHEADER)lpTempImgData, (LONG)CBM_INIT,
				(LPSTR)lpTempImgData+sizeof(BITMAPINFOHEADER) +NumColors*sizeof(RGBQUAD),
   				(LPBITMAPINFO)lpTempImgData, DIB_RGB_COLORS);

	if(hPalette && hPrevPalette){
		SelectPalette(hDc,hPrevPalette,FALSE);
		RealizePalette(hDc);
	}

	if(WithBack)
		hf=_lcreat("c:\\sliceb.bmp",0);
	else
		hf=_lcreat("c:\\slice.bmp",0);

	_lwrite(hf,(LPSTR)&bf,sizeof(BITMAPFILEHEADER)); 
	_lwrite(hf,(LPSTR)lpTempImgData,BufSize);
	_lclose(hf);

 	ReleaseDC(hWnd,hDc);
	LocalUnlock(hTempImgData);
	LocalFree(hTempImgData);
	GlobalUnlock(hImgData);
	return TRUE;
}
////////////////////////////////////////////////////////////////
BOOL HistogramEqua(HWND hWnd)
{
	DLGPROC            dlgInputBox = NULL;
	DWORD              BufSize,OffBits;
    LPBITMAPINFOHEADER lpImgData;
	LPSTR              lpPtr;
	HLOCAL             hTempImgData;
	LPBITMAPINFOHEADER lpTempImgData;
	LPSTR              lpTempPtr;
	HDC                hDc;
	HFILE              hf;
	LONG               x,y;
    LOGPALETTE         *pPal;
    HPALETTE           hPrevPalette; 
	HLOCAL             hPal;
	WORD               i;
	int  			   Gray;
	DWORD              GrayHits[256];
	int				   GrayIndex[256];
	float              s[256];

	if( NumColors!=256){
    	MessageBox(hWnd,"Must be a 256 grayscale bitmap!","Error Message",MB_OK|MB_ICONEXCLAMATION);
        return FALSE;
    }
	dlgInputBox = (DLGPROC) MakeProcInstance ( (FARPROC)InputBox, ghInst );
	DialogBox (ghInst, "INPUTBOX", hWnd, dlgInputBox);
	FreeProcInstance ( (FARPROC) dlgInputBox );
	if( EquaScale >=255){
    	MessageBox(hWnd,"The new scale can not be larger than 255","Error Message",MB_OK|MB_ICONEXCLAMATION);
        return FALSE;
    }

	OffBits=bf.bfOffBits-sizeof(BITMAPFILEHEADER);
	BufSize=bf.bfSize-sizeof(BITMAPFILEHEADER);
	
	if((hTempImgData=LocalAlloc(LHND,BufSize))==NULL)
    {
    	MessageBox(hWnd,"Error alloc memory!","Error Message",MB_OK|MB_ICONEXCLAMATION);
        return FALSE;
    }

    lpImgData=(LPBITMAPINFOHEADER)GlobalLock(hImgData);    
	lpTempImgData=(LPBITMAPINFOHEADER)LocalLock(hTempImgData);

	//copy image data
	memcpy(lpTempImgData,lpImgData,OffBits);

	memset(GrayHits,0,256*sizeof(DWORD));
	memset(GrayIndex,0,256*sizeof(WORD));
	for(y=0;y<bi.biHeight;y++){
		lpPtr=(unsigned char *)lpImgData+(BufSize-LineBytes-y*LineBytes);
		for(x=0;x<bi.biWidth;x++){
			Gray=(unsigned char )*(lpPtr++);
			GrayHits[Gray]++;
		}
	}

	for(i=0;i<256;i++)
		s[i]=(float)GrayHits[i]/((float)bi.biWidth*(float)bi.biHeight);
	
	for(i=1;i<256;i++)
		s[i]+=s[i-1];

	for(i=0;i<256;i++)
		GrayIndex[i]=(int)(s[i]*(EquaScale-1));

    hPal=LocalAlloc(LHND,sizeof(LOGPALETTE) + 256* sizeof(PALETTEENTRY));
    pPal =(LOGPALETTE *)LocalLock(hPal);
	memset(pPal,0,sizeof(LOGPALETTE) + 256* sizeof(PALETTEENTRY));
    pPal->palNumEntries =(WORD) 256;
	pPal->palVersion    = 0x300;
	lpTempPtr=(char *)lpTempImgData+sizeof(BITMAPINFOHEADER);
	for (i = 0; i < EquaScale; i++) {
		Gray=(int)(i*255.0/(EquaScale-1));
   		pPal->palPalEntry[i].peRed=(BYTE)Gray;
		pPal->palPalEntry[i].peGreen=(BYTE)Gray;
		pPal->palPalEntry[i].peBlue=(BYTE)Gray;
		pPal->palPalEntry[i].peFlags=(BYTE)0;
		*(lpTempPtr++)=(unsigned char)Gray;
		*(lpTempPtr++)=(unsigned char)Gray;
		*(lpTempPtr++)=(unsigned char)Gray;
		*(lpTempPtr++)=0;
	}
	if(hPalette!=NULL)                     
        DeleteObject(hPalette);
	
	//create new logic palette		
	hPalette=CreatePalette(pPal);
	LocalUnlock(hPal);
	LocalFree(hPal);

	hDc=GetDC(hWnd);
	if(hPalette){
        hPrevPalette=SelectPalette(hDc,hPalette,FALSE);
		RealizePalette(hDc);
	}

	for(y=0;y<bi.biHeight;y++){
		lpPtr=(char *)lpImgData+(BufSize-LineBytes-y*LineBytes);
		lpTempPtr=(char *)lpTempImgData+(BufSize-LineBytes-y*LineBytes);
		for(x=0;x<bi.biWidth;x++){
			Gray=(unsigned char )*(lpPtr++);
			Gray=GrayIndex[Gray];
			*(lpTempPtr++)=(unsigned char)Gray;
		}
	}

    if(hBitmap!=NULL)
	    DeleteObject(hBitmap);
	
	hBitmap=CreateDIBitmap(hDc,	(LPBITMAPINFOHEADER)lpTempImgData, (LONG)CBM_INIT,
				(LPSTR)lpTempImgData+sizeof(BITMAPINFOHEADER) +256*sizeof(RGBQUAD),
   				(LPBITMAPINFO)lpTempImgData, DIB_RGB_COLORS);

	if(hPalette && hPrevPalette){
		SelectPalette(hDc,hPrevPalette,FALSE);
		RealizePalette(hDc);
	}

    hf=_lcreat("c:\\equa.bmp",0);
	_lwrite(hf,(LPSTR)&bf,sizeof(BITMAPFILEHEADER)); 
	_lwrite(hf,(LPSTR)lpTempImgData,BufSize);
	_lclose(hf);

 	ReleaseDC(hWnd,hDc);
	LocalUnlock(hTempImgData);
	LocalFree(hTempImgData);
	GlobalUnlock(hImgData);
	return TRUE;
}
