//////////////////////////////////////////////////////////////
//Name:morph.c
//Purpose: To perform morphological operation
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
#define PI 3.1415926535
#define RADIAN(angle) ((angle)*PI/180.0) //convert angle to radian

//function declaration
int PASCAL WinMain (HANDLE, HANDLE, LPSTR, int);
LRESULT CALLBACK MainWndProc(HWND , UINT,WPARAM, LPARAM);
BOOL LoadBmpFile (HWND hWnd,char *BmpFileName);
BOOL Dilation(HWND hWnd,BOOL Hori);
BOOL Erosion(HWND hWnd,BOOL Hori);
BOOL MorphOpen(HWND hWnd,BOOL Hori);
BOOL MorphClose(HWND hWnd,BOOL Hori);
BOOL Thinning(HWND hWnd);
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
 
	hWnd = CreateWindow ("phoenix ip system","Morphological operation",
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
		case IDM_HDILATION:
			if(hImgData!=NULL){
				if(Dilation(hWnd,TRUE))
					InvalidateRect(hWnd,NULL,TRUE);
			}
			else
				MessageBox(hWnd,"File not loaded yet!","Error Message",MB_OK|MB_ICONEXCLAMATION);
			break;
		case IDM_VDILATION:
			if(hImgData!=NULL){
				if(Dilation(hWnd,FALSE))
					InvalidateRect(hWnd,NULL,TRUE);
			}
			else
				MessageBox(hWnd,"File not loaded yet!","Error Message",MB_OK|MB_ICONEXCLAMATION);
			break;
		case IDM_HEROSION:
			if(hImgData!=NULL){
				if(Erosion(hWnd,TRUE))
					InvalidateRect(hWnd,NULL,TRUE);
			}
			else
				MessageBox(hWnd,"File not loaded yet!","Error Message",MB_OK|MB_ICONEXCLAMATION);
			break;
		case IDM_VEROSION:
			if(hImgData!=NULL){
				if(Erosion(hWnd,FALSE))
					InvalidateRect(hWnd,NULL,TRUE);
			}
			else
				MessageBox(hWnd,"File not loaded yet!","Error Message",MB_OK|MB_ICONEXCLAMATION);
			break;
		case IDM_HOPEN:
			if(hImgData!=NULL){
				if(MorphOpen(hWnd,TRUE))
					InvalidateRect(hWnd,NULL,TRUE);
			}
			else
				MessageBox(hWnd,"File not loaded yet!","Error Message",MB_OK|MB_ICONEXCLAMATION);
			break;
		case IDM_VOPEN:
			if(hImgData!=NULL){
				if(MorphOpen(hWnd,FALSE))
					InvalidateRect(hWnd,NULL,TRUE);
			}
			else
				MessageBox(hWnd,"File not loaded yet!","Error Message",MB_OK|MB_ICONEXCLAMATION);
			break;
		case IDM_HCLOSE:
			if(hImgData!=NULL){
				if(MorphClose(hWnd,TRUE))
					InvalidateRect(hWnd,NULL,TRUE);
			}
			else
				MessageBox(hWnd,"File not loaded yet!","Error Message",MB_OK|MB_ICONEXCLAMATION);
			break;
		case IDM_VCLOSE:
			if(hImgData!=NULL){
				if(MorphClose(hWnd,FALSE))
					InvalidateRect(hWnd,NULL,TRUE);
			}
			else
				MessageBox(hWnd,"File not loaded yet!","Error Message",MB_OK|MB_ICONEXCLAMATION);
			break;
		case IDM_THINNING:
			if(hImgData!=NULL){
				if(Thinning(hWnd))
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
BOOL Erosion(HWND hWnd,BOOL Hori)
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
	unsigned char      num;
	int                i;

	if( NumColors!=256){
    	MessageBox(hWnd,"Must be a mono bitmap with grayscale palette!","Error Message",MB_OK|MB_ICONEXCLAMATION);
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
	if(Hori)
	{
		for(y=0;y<bi.biHeight;y++){
			lpPtr=(char *)lpImgData+(BufSize-LineBytes-y*LineBytes)+1;
			lpTempPtr=(char *)lpTempImgData+(BufSize-LineBytes-y*LineBytes)+1;
			for(x=1;x<bi.biWidth-1;x++){
				num=(unsigned char)*lpPtr;
				if (num==0){
					*lpTempPtr=(unsigned char)0;
					for(i=0;i<3;i++){
						num=(unsigned char)*(lpPtr+i-1);
						if(num==255){
							*lpTempPtr=(unsigned char)255;
							break;
						}
					}
				}
				else *lpTempPtr=(unsigned char)255;
				lpPtr++;
				lpTempPtr++;
			}
		}
	}
	else{
		for(y=1;y<bi.biHeight-1;y++){
			lpPtr=(char *)lpImgData+(BufSize-LineBytes-y*LineBytes);
			lpTempPtr=(char *)lpTempImgData+(BufSize-LineBytes-y*LineBytes);
			for(x=0;x<bi.biWidth;x++){
				num=(unsigned char)*lpPtr;
				if (num==0){
					*lpTempPtr=(unsigned char)0;
					for(i=0;i<3;i++){
						num=(unsigned char)*(lpPtr+(i-1)*LineBytes);
						if(num==255){
							*lpTempPtr=(unsigned char)255;
							break;
						}
					}
				}
				else *lpTempPtr=(unsigned char)255;
				lpPtr++;
				lpTempPtr++;
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
		hf=_lcreat("c:\\herosion.bmp",0);
	else
		hf=_lcreat("c:\\verosion.bmp",0);

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
BOOL Dilation(HWND hWnd,BOOL Hori)
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
	unsigned char      num;
	int                i;

	if( NumColors!=256){
    	MessageBox(hWnd,"Must be a mono bitmap with grayscale palette!","Error Message",MB_OK|MB_ICONEXCLAMATION);
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
	if(Hori)
	{
		for(y=0;y<bi.biHeight;y++){
			lpPtr=(char *)lpImgData+(BufSize-LineBytes-y*LineBytes)+1;
			lpTempPtr=(char *)lpTempImgData+(BufSize-LineBytes-y*LineBytes)+1;
			for(x=1;x<bi.biWidth-1;x++){
				num=(unsigned char)*lpPtr;
				if (num==255){
					*lpTempPtr=(unsigned char)255;
					for(i=0;i<3;i++){
						num=(unsigned char)*(lpPtr+i-1);
						if(num==0){
							*lpTempPtr=(unsigned char)0;
							break;
						}
					}
				}
				else *lpTempPtr=(unsigned char)0;
				lpPtr++;
				lpTempPtr++;
			}
		}
	}
	else{
		for(y=1;y<bi.biHeight-1;y++){
			lpPtr=(char *)lpImgData+(BufSize-LineBytes-y*LineBytes);
			lpTempPtr=(char *)lpTempImgData+(BufSize-LineBytes-y*LineBytes);
			for(x=0;x<bi.biWidth;x++){
				num=(unsigned char)*lpPtr;
				if (num==255){
					*lpTempPtr=(unsigned char)255;
					for(i=0;i<3;i++){
						num=(unsigned char)*(lpPtr+(i-1)*LineBytes);
						if(num==0){
							*lpTempPtr=(unsigned char)0;
							break;
						}
					}
				}
				else *lpTempPtr=(unsigned char)0;
				lpPtr++;
				lpTempPtr++;
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
		hf=_lcreat("c:\\hdilation.bmp",0);
	else
		hf=_lcreat("c:\\vdilation.bmp",0);

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
BOOL MorphOpen(HWND hWnd,BOOL Hori)
{
	DWORD              BufSize;
    LPBITMAPINFOHEADER lpImgData;
	LPSTR              lpPtr;
	HLOCAL             hTempImgData;
	LPBITMAPINFOHEADER lpTempImgData;
	LPSTR              lpTempPtr;
	HLOCAL             hTempImgData1;
	LPBITMAPINFOHEADER lpTempImgData1;
	LPSTR              lpTempPtr1;
	HDC                hDc;
	HFILE              hf;
	LONG               x,y;
	unsigned char      num;
	int                i;

	if( NumColors!=256){
    	MessageBox(hWnd,"Must be a mono bitmap with grayscale palette!","Error Message",MB_OK|MB_ICONEXCLAMATION);
        return FALSE;
    }
	BufSize=bf.bfSize-sizeof(BITMAPFILEHEADER);
	
	if((hTempImgData=LocalAlloc(LHND,BufSize))==NULL)
    {
    	MessageBox(hWnd,"Error alloc memory!","Error Message",MB_OK|MB_ICONEXCLAMATION);
        return FALSE;
    }

	if((hTempImgData1=LocalAlloc(LHND,BufSize))==NULL)
    {
    	MessageBox(hWnd,"Error alloc memory!","Error Message",MB_OK|MB_ICONEXCLAMATION);
		LocalFree(hTempImgData);
        return FALSE;
    }
	//step 1: erosion,the result is stored in lpTempImgData
    lpImgData=(LPBITMAPINFOHEADER)GlobalLock(hImgData);    
	lpTempImgData=(LPBITMAPINFOHEADER)LocalLock(hTempImgData);
	//copy image data
	memcpy(lpTempImgData,lpImgData,BufSize);
	if(Hori)
	{
		for(y=0;y<bi.biHeight;y++){
			lpPtr=(char *)lpImgData+(BufSize-LineBytes-y*LineBytes)+1;
			lpTempPtr=(char *)lpTempImgData+(BufSize-LineBytes-y*LineBytes)+1;
			for(x=1;x<bi.biWidth-1;x++){
				num=(unsigned char)*lpPtr;
				if (num==0){
					*lpTempPtr=(unsigned char)0;
					for(i=0;i<3;i++){
						num=(unsigned char)*(lpPtr+i-1);
						if(num==255){
							*lpTempPtr=(unsigned char)255;
							break;
						}
					}
				}
				else *lpTempPtr=(unsigned char)255;
				lpPtr++;
				lpTempPtr++;
			}
		}
	}
	else{
		for(y=1;y<bi.biHeight-1;y++){
			lpPtr=(char *)lpImgData+(BufSize-LineBytes-y*LineBytes);
			lpTempPtr=(char *)lpTempImgData+(BufSize-LineBytes-y*LineBytes);
			for(x=0;x<bi.biWidth;x++){
				num=(unsigned char)*lpPtr;
				if (num==0){
					*lpTempPtr=(unsigned char)0;
					for(i=0;i<3;i++){
						num=(unsigned char)*(lpPtr+(i-1)*LineBytes);
						if(num==255){
							*lpTempPtr=(unsigned char)255;
							break;
						}
					}
				}
				else *lpTempPtr=(unsigned char)255;
				lpPtr++;
				lpTempPtr++;
			}
		}
	}
	//step 2: dilation,the result is stored in lpTempImgData1
	//copy image data
	lpTempImgData1=(LPBITMAPINFOHEADER)LocalLock(hTempImgData1);
	//copy image data
	memcpy(lpTempImgData1,lpTempImgData,BufSize);
	if(Hori)
	{
		for(y=0;y<bi.biHeight;y++){
			lpTempPtr=(char *)lpTempImgData+(BufSize-LineBytes-y*LineBytes)+1;
			lpTempPtr1=(char *)lpTempImgData1+(BufSize-LineBytes-y*LineBytes)+1;
			for(x=1;x<bi.biWidth-1;x++){
				num=(unsigned char)*lpTempPtr;
				if (num==255){
					*lpTempPtr1=(unsigned char)255;
					for(i=0;i<3;i++){
						num=(unsigned char)*(lpTempPtr+i-1);
						if(num==0){
							*lpTempPtr1=(unsigned char)0;
							break;
						}
					}
				}
				else *lpTempPtr1=(unsigned char)0;
				lpTempPtr++;
				lpTempPtr1++;
			}
		}
	}
	else{
		for(y=1;y<bi.biHeight-1;y++){
			lpTempPtr=(char *)lpTempImgData+(BufSize-LineBytes-y*LineBytes);
			lpTempPtr1=(char *)lpTempImgData1+(BufSize-LineBytes-y*LineBytes);
			for(x=0;x<bi.biWidth;x++){
				num=(unsigned char)*lpTempPtr;
				if (num==255){
					*lpTempPtr1=(unsigned char)255;
					for(i=0;i<3;i++){
						num=(unsigned char)*(lpTempPtr+(i-1)*LineBytes);
						if(num==0){
							*lpTempPtr1=(unsigned char)0;
							break;
						}
					}
				}
				else *lpTempPtr1=(unsigned char)0;
				lpTempPtr++;
				lpTempPtr1++;
			}
		}
	}

    if(hBitmap!=NULL)
	    DeleteObject(hBitmap);
	hDc=GetDC(hWnd);	
	hBitmap=CreateDIBitmap(hDc,	(LPBITMAPINFOHEADER)lpTempImgData1, (LONG)CBM_INIT,
				(LPSTR)lpTempImgData1+sizeof(BITMAPINFOHEADER) +NumColors*sizeof(RGBQUAD),
   				(LPBITMAPINFO)lpTempImgData1, DIB_RGB_COLORS);

	if(Hori)
		hf=_lcreat("c:\\hmopen.bmp",0);
	else
		hf=_lcreat("c:\\vmopen.bmp",0);

	_lwrite(hf,(LPSTR)&bf,sizeof(BITMAPFILEHEADER)); 
	_lwrite(hf,(LPSTR)lpTempImgData1,BufSize);
	_lclose(hf);

 	ReleaseDC(hWnd,hDc);
	LocalUnlock(hTempImgData);
	LocalFree(hTempImgData);
	LocalUnlock(hTempImgData1);
	LocalFree(hTempImgData1);
	GlobalUnlock(hImgData);
	return TRUE;
}
////////////////////////////////////////////////////////////////
BOOL MorphClose(HWND hWnd,BOOL Hori)
{
	DWORD              BufSize;
    LPBITMAPINFOHEADER lpImgData;
	LPSTR              lpPtr;
	HLOCAL             hTempImgData;
	LPBITMAPINFOHEADER lpTempImgData;
	LPSTR              lpTempPtr;
	HLOCAL             hTempImgData1;
	LPBITMAPINFOHEADER lpTempImgData1;
	LPSTR              lpTempPtr1;
	HDC                hDc;
	HFILE              hf;
	LONG               x,y;
	unsigned char      num;
	int                i;

	if( NumColors!=256){
    	MessageBox(hWnd,"Must be a mono bitmap with grayscale palette!","Error Message",MB_OK|MB_ICONEXCLAMATION);
        return FALSE;
    }
	BufSize=bf.bfSize-sizeof(BITMAPFILEHEADER);
	
	if((hTempImgData=LocalAlloc(LHND,BufSize))==NULL)
    {
    	MessageBox(hWnd,"Error alloc memory!","Error Message",MB_OK|MB_ICONEXCLAMATION);
        return FALSE;
    }

	if((hTempImgData1=LocalAlloc(LHND,BufSize))==NULL)
    {
    	MessageBox(hWnd,"Error alloc memory!","Error Message",MB_OK|MB_ICONEXCLAMATION);
		LocalFree(hTempImgData);
        return FALSE;
    }
	//step 1: dilation,the result is stored in lpTempImgData
    lpImgData=(LPBITMAPINFOHEADER)GlobalLock(hImgData);    
	lpTempImgData=(LPBITMAPINFOHEADER)LocalLock(hTempImgData);
	//copy image data
	memcpy(lpTempImgData,lpImgData,BufSize);
	if(Hori)
	{
		for(y=0;y<bi.biHeight;y++){
			lpPtr=(char *)lpImgData+(BufSize-LineBytes-y*LineBytes)+1;
			lpTempPtr=(char *)lpTempImgData+(BufSize-LineBytes-y*LineBytes)+1;
			for(x=1;x<bi.biWidth-1;x++){
				num=(unsigned char)*lpPtr;
				if (num==255){
					*lpTempPtr=(unsigned char)255;
					for(i=0;i<3;i++){
						num=(unsigned char)*(lpPtr+i-1);
						if(num==0){
							*lpTempPtr=(unsigned char)0;
							break;
						}
					}
				}
				else *lpTempPtr=(unsigned char)0;
				lpPtr++;
				lpTempPtr++;
			}
		}
	}
	else{
		for(y=1;y<bi.biHeight-1;y++){
			lpPtr=(char *)lpImgData+(BufSize-LineBytes-y*LineBytes);
			lpTempPtr=(char *)lpTempImgData+(BufSize-LineBytes-y*LineBytes);
			for(x=0;x<bi.biWidth;x++){
				num=(unsigned char)*lpPtr;
				if (num==255){
					*lpTempPtr=(unsigned char)255;
					for(i=0;i<3;i++){
						num=(unsigned char)*(lpPtr+(i-1)*LineBytes);
						if(num==0){
							*lpTempPtr=(unsigned char)0;
							break;
						}
					}
				}
				else *lpTempPtr=(unsigned char)0;
				lpPtr++;
				lpTempPtr++;
			}
		}
	}
	//step 2: erosion,the result is stored in lpTempImgData1
	//copy image data
	lpTempImgData1=(LPBITMAPINFOHEADER)LocalLock(hTempImgData1);
	//copy image data
	memcpy(lpTempImgData1,lpTempImgData,BufSize);
	if(Hori)
	{
		for(y=0;y<bi.biHeight;y++){
			lpTempPtr=(char *)lpTempImgData+(BufSize-LineBytes-y*LineBytes)+1;
			lpTempPtr1=(char *)lpTempImgData1+(BufSize-LineBytes-y*LineBytes)+1;
			for(x=1;x<bi.biWidth-1;x++){
				num=(unsigned char)*lpTempPtr;
				if (num==0){
					*lpTempPtr1=(unsigned char)0;
					for(i=0;i<3;i++){
						num=(unsigned char)*(lpTempPtr+i-1);
						if(num==255){
							*lpTempPtr1=(unsigned char)255;
							break;
						}
					}
				}
				else *lpTempPtr1=(unsigned char)255;
				lpTempPtr++;
				lpTempPtr1++;
			}
		}
	}
	else{
		for(y=1;y<bi.biHeight-1;y++){
			lpTempPtr=(char *)lpTempImgData+(BufSize-LineBytes-y*LineBytes);
			lpTempPtr1=(char *)lpTempImgData1+(BufSize-LineBytes-y*LineBytes);
			for(x=0;x<bi.biWidth;x++){
				num=(unsigned char)*lpTempPtr;
				if (num==0){
					*lpTempPtr1=(unsigned char)0;
					for(i=0;i<3;i++){
						num=(unsigned char)*(lpTempPtr+(i-1)*LineBytes);
						if(num==255){
							*lpTempPtr1=(unsigned char)255;
							break;
						}
					}
				}
				else *lpTempPtr1=(unsigned char)255;
				lpTempPtr++;
				lpTempPtr1++;
			}
		}
	}

    if(hBitmap!=NULL)
	    DeleteObject(hBitmap);
	hDc=GetDC(hWnd);	
	hBitmap=CreateDIBitmap(hDc,	(LPBITMAPINFOHEADER)lpTempImgData1, (LONG)CBM_INIT,
				(LPSTR)lpTempImgData1+sizeof(BITMAPINFOHEADER) +NumColors*sizeof(RGBQUAD),
   				(LPBITMAPINFO)lpTempImgData1, DIB_RGB_COLORS);

	if(Hori)
		hf=_lcreat("c:\\hmclose.bmp",0);
	else
		hf=_lcreat("c:\\vmclose.bmp",0);

	_lwrite(hf,(LPSTR)&bf,sizeof(BITMAPFILEHEADER)); 
	_lwrite(hf,(LPSTR)lpTempImgData1,BufSize);
	_lclose(hf);

 	ReleaseDC(hWnd,hDc);
	LocalUnlock(hTempImgData);
	LocalFree(hTempImgData);
	LocalUnlock(hTempImgData1);
	LocalFree(hTempImgData1);
	GlobalUnlock(hImgData);
	return TRUE;
}
////////////////////////////////////////////////////////////////
BOOL Thinning(HWND hWnd)
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
	int			       num;
	BOOL               Finished;
	int                nw,n,ne,w,e,sw,s,se;
	static int erasetable[256]={
								0,0,1,1,0,0,1,1,
								1,1,0,1,1,1,0,1,
								1,1,0,0,1,1,1,1,
								0,0,0,0,0,0,0,1,
								
								0,0,1,1,0,0,1,1,
								1,1,0,1,1,1,0,1,
								1,1,0,0,1,1,1,1,
								0,0,0,0,0,0,0,1,
								
								1,1,0,0,1,1,0,0,
								0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,
								
								1,1,0,0,1,1,0,0,
								1,1,0,1,1,1,0,1,
								0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,

								0,0,1,1,0,0,1,1,
								1,1,0,1,1,1,0,1,
								1,1,0,0,1,1,1,1,
								0,0,0,0,0,0,0,1,
								
								0,0,1,1,0,0,1,1,
								1,1,0,1,1,1,0,1,
								1,1,0,0,1,1,1,1,
								0,0,0,0,0,0,0,0,
								
								1,1,0,0,1,1,0,0,
								0,0,0,0,0,0,0,0,
								1,1,0,0,1,1,1,1,
								0,0,0,0,0,0,0,0,

								1,1,0,0,1,1,0,0,
								1,1,0,1,1,1,0,0,
								1,1,0,0,1,1,1,0,
								1,1,0,0,1,0,0,0
						  };

	if( NumColors!=256){
    	MessageBox(hWnd,"Must be a mono bitmap with grayscale palette!","Error Message",MB_OK|MB_ICONEXCLAMATION);
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

	Finished=FALSE;
    while(!Finished){
    	Finished=TRUE;
		for (y=1;y<bi.biHeight-1;y++){ 
			lpPtr=(char *)lpImgData+(BufSize-LineBytes-y*LineBytes);
			lpTempPtr=(char *)lpTempImgData+(BufSize-LineBytes-y*LineBytes);
			x=1; 
			while(x<bi.biWidth-1){
				if(*(lpPtr+x)==0){
					w=(unsigned char)*(lpPtr+x-1);
					e=(unsigned char)*(lpPtr+x+1);
					if( (w==255)|| (e==255)){
						nw=(unsigned char)*(lpPtr+x+LineBytes-1);
						n=(unsigned char)*(lpPtr+x+LineBytes);
						ne=(unsigned char)*(lpPtr+x+LineBytes+1);
						sw=(unsigned char)*(lpPtr+x-LineBytes-1);
						s=(unsigned char)*(lpPtr+x-LineBytes);
						se=(unsigned char)*(lpPtr+x-LineBytes+1);
						num=nw/255+n/255*2+ne/255*4+w/255*8+e/255*16+sw/255*32+s/255*64+se/255*128;
						if(erasetable[num]==1){
							*(lpPtr+x)=(BYTE)255;
							*(lpTempPtr+x)=(BYTE)255;
							Finished=FALSE;
							x++;
						}
					}
				}
				x++;
			}
		}
	
		for (x=1;x<bi.biWidth-1;x++){ 
			y=1;
			while(y<bi.biHeight-1){
				lpPtr=(char *)lpImgData+(BufSize-LineBytes-y*LineBytes);
				lpTempPtr=(char *)lpTempImgData+(BufSize-LineBytes-y*LineBytes);
				if(*(lpPtr+x)==0){
					n=(unsigned char)*(lpPtr+x+LineBytes);
					s=(unsigned char)*(lpPtr+x-LineBytes);
					if( (n==255)|| (s==255)){
						nw=(unsigned char)*(lpPtr+x+LineBytes-1);
						ne=(unsigned char)*(lpPtr+x+LineBytes+1);
						w=(unsigned char)*(lpPtr+x-1);
						e=(unsigned char)*(lpPtr+x+1);
						sw=(unsigned char)*(lpPtr+x-LineBytes-1);
						se=(unsigned char)*(lpPtr+x-LineBytes+1);
						num=nw/255+n/255*2+ne/255*4+w/255*8+e/255*16+sw/255*32+s/255*64+se/255*128;
						if(erasetable[num]==1){
							*(lpPtr+x)=(BYTE)255;
							*(lpTempPtr+x)=(BYTE)255;
							Finished=FALSE;
							y++;
						}
					}
				}
				y++;
			}
		} 
	}

    if(hBitmap!=NULL)
	    DeleteObject(hBitmap);
	hDc=GetDC(hWnd);	
	hBitmap=CreateDIBitmap(hDc,	(LPBITMAPINFOHEADER)lpTempImgData, (LONG)CBM_INIT,
				(LPSTR)lpTempImgData+sizeof(BITMAPINFOHEADER) +NumColors*sizeof(RGBQUAD),
   				(LPBITMAPINFO)lpTempImgData, DIB_RGB_COLORS);

	hf=_lcreat("c:\\thinning.bmp",0);
	_lwrite(hf,(LPSTR)&bf,sizeof(BITMAPFILEHEADER)); 
	_lwrite(hf,(LPSTR)lpTempImgData,BufSize);
	_lclose(hf);

 	ReleaseDC(hWnd,hDc);
	LocalUnlock(hTempImgData);
	LocalFree(hTempImgData);
	GlobalUnlock(hImgData);
	return TRUE;
}
