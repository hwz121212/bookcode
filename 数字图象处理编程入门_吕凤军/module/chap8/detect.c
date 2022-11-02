//////////////////////////////////////////////////////////////
//Name:detect.c
//Purpose: Image detection
//Author: phoenix, CS, TshingHua, Beijing, P.R.C.
//Email: bjlufengjun@www.163.net or lufengjun@hotmail.com
//Date:April 3, 1998

//header file
#include "bmp.h"
#include "memory.h"
#include "math.h"
#include "stdio.h"
//owner defined stack
typedef struct{
			  HGLOBAL hMem;
  			  POINT *lpMyStack;
			  LONG  ElementsNum;
			  LONG  ptr;
			  }MYSTACK;
//macro definition
#define WIDTHBYTES(i)    ((i+31)/32*4)

//function declaration
int PASCAL WinMain (HANDLE, HANDLE, LPSTR, int);
LRESULT CALLBACK MainWndProc(HWND , UINT,WPARAM, LPARAM);
BOOL LoadBmpFile (HWND hWnd,char *BmpFileName);
BOOL Projection(HWND hWnd,BOOL Hori);
BOOL Subtraction(HWND hWnd);
//global variable declaration
BITMAPFILEHEADER   bf;
BITMAPINFOHEADER   bi;
HPALETTE           hPalette=NULL;
HBITMAP            hBitmap=NULL;
HGLOBAL            hImgData=NULL;
DWORD              NumColors;
DWORD              LineBytes;
DWORD              ImgWidth=0 , ImgHeight=0;
///////////////////////////////////////////////////////////
int PASCAL WinMain (HANDLE hInstance, HANDLE hPrevInstance,
		    LPSTR lpszCmdLine, int nCmdShow)
{
	MSG       msg;
	WNDCLASS  wndclass;
	HWND      hWnd;

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
 
	hWnd = CreateWindow ("phoenix ip system","Image detection",
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
		case IDM_HPROJECTION:
			if(hImgData!=NULL){
				if(Projection(hWnd,TRUE))
					InvalidateRect(hWnd,NULL,TRUE);
			}
			else
				MessageBox(hWnd,"File not loaded yet!","Error Message",MB_OK|MB_ICONEXCLAMATION);
			break;
		case IDM_VPROJECTION:
			if(hImgData!=NULL){
				if(Projection(hWnd,FALSE))
					InvalidateRect(hWnd,NULL,TRUE);
			}
			else
				MessageBox(hWnd,"File not loaded yet!","Error Message",MB_OK|MB_ICONEXCLAMATION);
			break;
		case IDM_SUBTRACTION:
			if(hImgData!=NULL){
				MessageBox(hWnd,"Be sure that c:\\test.bmp and c:\\backgnd.bmp are both 256 grayscale bitmaps ! They must be same size and have same palette!","Important",MB_OK);
				if(Subtraction(hWnd))
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
BOOL Projection(HWND hWnd,BOOL Hori)
{
	DWORD              OffBits,BufSize;
    LPBITMAPINFOHEADER lpImgData;
	LPSTR              lpPtr;
	HLOCAL             hTempImgData;
	LPBITMAPINFOHEADER lpTempImgData;
	LPSTR              lpTempPtr;
	HDC                hDc;
	HFILE              hf;
	LONG               x,y;
	int				   num;

	if( NumColors!=256){
    	MessageBox(hWnd,"Must be a mono bitmap with grayscale palette!","Error Message",MB_OK|MB_ICONEXCLAMATION);
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
	memset(lpTempImgData,(BYTE)255,BufSize);
	memcpy(lpTempImgData,lpImgData,OffBits);

	if(Hori)
	{
		for(y=0;y<bi.biHeight;y++){
			lpPtr=(char *)lpImgData+(BufSize-LineBytes-y*LineBytes);
			num=0;
			for(x=0;x<bi.biWidth;x++)
				if(*(lpPtr++)!=0)
					num++;
			lpTempPtr=(char *)lpTempImgData+(BufSize-LineBytes-y*LineBytes);
			for(x=0;x<num;x++)
				*(lpTempPtr++)=0;
		}
	}
	else{
		for(x=0;x<bi.biWidth;x++){
			num=0;
			lpPtr=(char *)lpImgData+(BufSize-LineBytes)+x;
			for(y=0;y<bi.biHeight;y++){
				if(*lpPtr!=0)
					num++;
				lpPtr-=LineBytes;
			}
			
			lpTempPtr=(char *)lpTempImgData+OffBits+x;
			for(y=0;y<num;y++){
				*lpTempPtr=0;
				lpTempPtr+=LineBytes;
			}
		}
	}

    if(hBitmap!=NULL)
	    DeleteObject(hBitmap);
	hDc=GetDC(hWnd);	
	hBitmap=CreateDIBitmap(hDc,	(LPBITMAPINFOHEADER)lpTempImgData, (LONG)CBM_INIT,
				(LPSTR)lpTempImgData+sizeof(BITMAPINFOHEADER) +NumColors*sizeof(RGBQUAD),
   				(LPBITMAPINFO)lpTempImgData, DIB_RGB_COLORS);

	if(Hori)
		hf=_lcreat("c:\\hproject.bmp",0);
	else
		hf=_lcreat("c:\\vproject.bmp",0);

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
BOOL Subtraction(HWND hWnd)
{
	DWORD              OffBits,BufSize;
    LPBITMAPINFOHEADER lpImgData;
	LPSTR              lpPtr;
	HGLOBAL            hSecond;
	LPBITMAPINFOHEADER lpSecondImgData;
	LPSTR              lpSecondPtr;
	HLOCAL             hTempImgData;
	LPBITMAPINFOHEADER lpTempImgData;
	LPSTR              lpTempPtr;
	HDC                hDc;
	HFILE              hf;
	LONG               x,y;
	int                num,pos;

	if( NumColors!=256){
    	MessageBox(hWnd,"Must be a 256 grayscale bitmap!","Error Message",MB_OK|MB_ICONEXCLAMATION);
        return FALSE;
    }

    if((hf=_lopen("c:\\backgnd.bmp",OF_READ))==HFILE_ERROR){
        MessageBox(hWnd,"File c:\\backgnd.bmp not found!","Error Message",MB_OK|MB_ICONEXCLAMATION);
        return FALSE;
	}
	OffBits=bf.bfOffBits-sizeof(BITMAPFILEHEADER);
	BufSize=bf.bfSize-sizeof(BITMAPFILEHEADER);
	if((hSecond=GlobalAlloc(GHND,BufSize))==NULL)
    {
    	MessageBox(hWnd,"Error alloc memory!","Error Message",MB_OK|MB_ICONEXCLAMATION);
		_lclose(hf);
        return FALSE;
    }
    lpSecondImgData=(LPBITMAPINFOHEADER)GlobalLock(hSecond);
	_llseek(hf,sizeof(BITMAPFILEHEADER),FILE_BEGIN);
	_lread(hf,(LPSTR)lpSecondImgData,BufSize);
	_lclose(hf);

	if((hTempImgData=LocalAlloc(LHND,BufSize))==NULL)
    {
    	MessageBox(hWnd,"Error alloc memory!","Error Message",MB_OK|MB_ICONEXCLAMATION);
		GlobalUnlock(hSecond);
		GlobalFree(hSecond);
        return FALSE;
    }

    lpImgData=(LPBITMAPINFOHEADER)GlobalLock(hImgData);    
	lpTempImgData=(LPBITMAPINFOHEADER)LocalLock(hTempImgData);

	//copy image data
	memset(lpTempImgData,(BYTE)255,BufSize);
	memcpy(lpTempImgData,lpImgData,OffBits);

	for(y=0;y<bi.biHeight;y++){
		pos=(BufSize-LineBytes-y*LineBytes);
		lpPtr=(char *)lpImgData+pos;
		lpSecondPtr=(char *)lpSecondImgData+pos;
		lpTempPtr=(char *)lpTempImgData+pos;
		for(x=0;x<bi.biWidth;x++){
			num=(unsigned char)*(lpPtr++);
			num-=(unsigned char)*(lpSecondPtr++);
			*(lpTempPtr++)=(unsigned char)fabs(num);
		}
	}

    if(hBitmap!=NULL)
	    DeleteObject(hBitmap);
	hDc=GetDC(hWnd);	
	hBitmap=CreateDIBitmap(hDc,	(LPBITMAPINFOHEADER)lpTempImgData, (LONG)CBM_INIT,
				(LPSTR)lpTempImgData+sizeof(BITMAPINFOHEADER) +NumColors*sizeof(RGBQUAD),
   				(LPBITMAPINFO)lpTempImgData, DIB_RGB_COLORS);

	hf=_lcreat("c:\\subtract.bmp",0);

	_lwrite(hf,(LPSTR)&bf,sizeof(BITMAPFILEHEADER)); 
	_lwrite(hf,(LPSTR)lpTempImgData,BufSize);
	_lclose(hf);

 	ReleaseDC(hWnd,hDc);
	GlobalUnlock(hSecond);
	GlobalFree(hSecond);
	LocalUnlock(hTempImgData);
	LocalFree(hTempImgData);
	GlobalUnlock(hImgData);
	return TRUE;
}
