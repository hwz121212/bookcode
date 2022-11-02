//////////////////////////////////////////////////////////////
//Name:smooth.c
//Purpose: To perform smoothing and sharpening
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
BOOL TemplateOperation(HWND hWnd, int TemplateType);
BOOL MedianFilter(HWND hWnd,BOOL Hori);
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
//template array
float Template_Smooth_Box[9]={1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f};
float Template_Smooth_Gauss[9]={1.0f,2.0f,1.0f,2.0f,4.0f,2.0f,1.0f,2.0f,1.0f};
float Template_Sharpen_Laplacian[9]={-1.0f,-1.0f,-1.0f,-1.0f,9.0f,-1.0f,-1.0f,-1.0f,-1.0f};
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

	hWnd = CreateWindow ("phoenix ip system","Smoothing and Sharpening",
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
		case IDM_SMOOTHING_BOX:
			if(hImgData!=NULL){
				if(TemplateOperation(hWnd,TEMPLATE_SMOOTH_BOX))
					InvalidateRect(hWnd,NULL,TRUE);
			}
			else
				MessageBox(hWnd,"File not loaded yet!","Error Message",MB_OK|MB_ICONEXCLAMATION);
			break;
		case IDM_SMOOTHING_GAUSS:
			if(hImgData!=NULL){
				if(TemplateOperation(hWnd,TEMPLATE_SMOOTH_GAUSS))
					InvalidateRect(hWnd,NULL,TRUE);
			}
			else
				MessageBox(hWnd,"File not loaded yet!","Error Message",MB_OK|MB_ICONEXCLAMATION);
			break;
		case IDM_SHARPENING_LAPLACIAN:
			if(hImgData!=NULL){
				if(TemplateOperation(hWnd,TEMPLATE_SHARPEN_LAPLACIAN))
					InvalidateRect(hWnd,NULL,TRUE);
			}
			else
				MessageBox(hWnd,"File not loaded yet!","Error Message",MB_OK|MB_ICONEXCLAMATION);
			break;
		case IDM_HMEDIAN:
			if(hImgData!=NULL){
				if(MedianFilter(hWnd,TRUE))
					InvalidateRect(hWnd,NULL,TRUE);
			}
			else
				MessageBox(hWnd,"File not loaded yet!","Error Message",MB_OK|MB_ICONEXCLAMATION);
			break;
		case IDM_VMEDIAN:
			if(hImgData!=NULL){
				if(MedianFilter(hWnd,FALSE))
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
BOOL TemplateOperation(HWND hWnd, int TemplateType)
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
	float              coef;
	float              CoefArray[9];
	float              TempNum;
	char               filename[80];

	switch(TemplateType){
	case TEMPLATE_SMOOTH_BOX:
		coef=(float)(1.0/9.0);
		memcpy(CoefArray,Template_Smooth_Box,9*sizeof(float));
		strcpy(filename,"c:\\smbox.bmp");
		break;
	case TEMPLATE_SMOOTH_GAUSS:
		coef=(float)(1.0/16.0);
		memcpy(CoefArray,Template_Smooth_Gauss,9*sizeof(float));
		strcpy(filename,"c:\\smgauss.bmp");
		break;
	case TEMPLATE_SHARPEN_LAPLACIAN:
		coef=(float)1.0;
		memcpy(CoefArray,Template_Sharpen_Laplacian,9*sizeof(float));
		strcpy(filename,"c:\\shlaplac.bmp");
		break;
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

	lpPtr=(char *)lpImgData;
	lpTempPtr=(char *)lpTempImgData;

	memcpy(lpTempPtr,lpPtr,BufSize);

	for(y=1;y<bi.biHeight-1;y++)
			for(x=1;x<bi.biWidth-1;x++){
				lpPtr=(char *)lpImgData+(BufSize-LineBytes-y*LineBytes)+x;
				lpTempPtr=(char *)lpTempImgData+(BufSize-LineBytes-y*LineBytes)+x;
				TempNum=(float)((unsigned char)*(lpPtr+LineBytes-1))*CoefArray[0];
				TempNum+=(float)((unsigned char)*(lpPtr+LineBytes))*CoefArray[1];
				TempNum+=(float)((unsigned char)*(lpPtr+LineBytes+1))*CoefArray[2];
				TempNum+=(float)((unsigned char)*(lpPtr-1))*CoefArray[3];
				TempNum+=(float)((unsigned char)*lpPtr)*CoefArray[4];
				TempNum+=(float)((unsigned char)*(lpPtr+1))*CoefArray[5];
				TempNum+=(float)((unsigned char)*(lpPtr-LineBytes-1))*CoefArray[6];
				TempNum+=(float)((unsigned char)*(lpPtr-LineBytes))*CoefArray[7];
				TempNum+=(float)((unsigned char)*(lpPtr-LineBytes+1))*CoefArray[8];
				TempNum*=coef;
				if(TempNum>255.0) *lpTempPtr=(BYTE)255;
				else if(TempNum<0.0) 
					*lpTempPtr=(unsigned char)fabs(TempNum);
				else *lpTempPtr=(BYTE)TempNum;
		}

	hDc=GetDC(hWnd);
    if(hBitmap!=NULL)
	    DeleteObject(hBitmap);
	
	hBitmap=CreateDIBitmap(hDc,	(LPBITMAPINFOHEADER)lpTempImgData, (LONG)CBM_INIT,
				(LPSTR)lpTempImgData+sizeof(BITMAPINFOHEADER) +NumColors*sizeof(RGBQUAD),
   				(LPBITMAPINFO)lpTempImgData, DIB_RGB_COLORS);

	hf=_lcreat(filename,0);
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
BOOL MedianFilter(HWND hWnd,BOOL Hori)
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
	int                g,g1,g2,g3;

	OffBits=bf.bfOffBits-sizeof(BITMAPFILEHEADER);
	BufSize=bf.bfSize-sizeof(BITMAPFILEHEADER);

	if((hTempImgData=LocalAlloc(LHND,BufSize))==NULL)
    {
    	MessageBox(hWnd,"Error alloc memory!","Error Message",MB_OK|MB_ICONEXCLAMATION);
        return FALSE;
    }

    lpImgData=(LPBITMAPINFOHEADER)GlobalLock(hImgData);    
	lpTempImgData=(LPBITMAPINFOHEADER)LocalLock(hTempImgData);

	memcpy(lpTempImgData,lpImgData,BufSize);

	for(y=1;y<bi.biHeight-1;y++)
			for(x=1;x<bi.biWidth-1;x++){
				lpPtr=(char *)lpImgData+(BufSize-LineBytes-y*LineBytes)+x;
				lpTempPtr=(char *)lpTempImgData+(BufSize-LineBytes-y*LineBytes)+x;
				g2=(unsigned char)*(lpPtr);
				if(Hori){
					g1=(unsigned char)*(lpPtr-1);
					g3=(unsigned char)*(lpPtr+1);
				}
				else{
					g1=(unsigned char)*(lpPtr+LineBytes);
					g3=(unsigned char)*(lpPtr-LineBytes);
				}
				if(g1>g2){
					if(g2>g3) g=g2;
					else{
						if(g1>g3) g=g3;
						else g=g1;
					}
				}
				else{ //g1<=g2
					if(g1>g3) g=g1;
					else{ 
						if(g2>g3) g=g3;
						else g=g2;
					}
				}
				*lpTempPtr=(BYTE)g;
		}

	hDc=GetDC(hWnd);
    if(hBitmap!=NULL)
	    DeleteObject(hBitmap);
	
	hBitmap=CreateDIBitmap(hDc,	(LPBITMAPINFOHEADER)lpTempImgData, (LONG)CBM_INIT,
				(LPSTR)lpTempImgData+sizeof(BITMAPINFOHEADER) +NumColors*sizeof(RGBQUAD),
   				(LPBITMAPINFO)lpTempImgData, DIB_RGB_COLORS);

	if(Hori)
		hf=_lcreat("c:\\hmedian.bmp",0);
	else
		hf=_lcreat("c:\\vmedian.bmp",0);
	_lwrite(hf,(LPSTR)&bf,sizeof(BITMAPFILEHEADER)); 
	_lwrite(hf,(LPSTR)lpTempImgData,BufSize);
	_lclose(hf);

 	ReleaseDC(hWnd,hDc);
	LocalUnlock(hTempImgData);
	LocalFree(hTempImgData);
	GlobalUnlock(hImgData);
	return TRUE;
}
