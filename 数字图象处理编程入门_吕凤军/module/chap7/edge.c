//////////////////////////////////////////////////////////////
//Name:edge.c
//Purpose: edge detectiong and hough transform
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

//function declaration
int PASCAL WinMain (HANDLE, HANDLE, LPSTR, int);
LRESULT CALLBACK MainWndProc(HWND , UINT,WPARAM, LPARAM);
BOOL LoadBmpFile (HWND hWnd,char *BmpFileName);
BOOL TemplateOperation(HWND hWnd, int TemplateType);
BOOL Outline(HWND hWnd);
BOOL Hough(HWND hWnd);
BOOL LapOfGauss(HWND hWnd);
BOOL Contour(HWND hWnd);
BOOL IsContourP(LONG x,LONG y, char *lpPtr);
BOOL SeedFill(HWND hWnd);
BOOL InitStack(HWND hWnd,LONG StackLen);
void DeInitStack();
BOOL MyPush(POINT p);
POINT MyPop();
BOOL IsStackEmpty();
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
float Template_HSobel[9]={-1.0f,0.0f,1.0f,-2.0f,0.0f,2.0f,-1.0f,0.0f,1.0f};
float Template_VSobel[9]={-1.0f,-2.0f,-1.0f,0.0f,0.0f,0.0f,1.0f,2.0f,1.0f};
float Template_HIsoSobel[9]={-1.0f,0.0f,1.0f,-1.4142f,0.0f,1.4142f,-1.0f,0.0f,1.0f};
float Template_VIsoSobel[9]={-1.0f,-1.4142f,-1.0f,0.0f,0.0f,0.0f,1.0f,1.4142f,1.0f};
float Template_Log[25]={-2.0f,-4.0f,-4.0f,-4.0f,-2.0f,
				   	    -4.0f,0.0f,8.0f,0.0f,-4.0f,
						-4.0f,8.0f,24.0f,8.0f,-4.0f,
						-4.0f,0.0f,8.0f,0.0f,-4.0f,
						-2.0f,-4.0f,-4.0f,-4.0f,-2.0f};
MYSTACK SeedFillStack;
POINT SeedPoint;
BOOL IsSelecting;
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

	hWnd = CreateWindow ("phoenix ip system","Edge detectiong and hough transform",
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

	IsSelecting=FALSE;
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
	case WM_LBUTTONDOWN:
		if(IsSelecting){
			SeedPoint.x = LOWORD(lParam);
			SeedPoint.y = HIWORD(lParam);
			IsSelecting=FALSE;
			if(SeedFill(hWnd))
				InvalidateRect(hWnd,NULL,TRUE);
		}
 		break;
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
		case IDM_OUTLINE:
			if(hImgData!=NULL){
				if(Outline(hWnd))
					InvalidateRect(hWnd,NULL,TRUE);
			}
			else
				MessageBox(hWnd,"File not loaded yet!","Error Message",MB_OK|MB_ICONEXCLAMATION);
			break;
		case IDM_HSOBEL:
			if(hImgData!=NULL){
				if(TemplateOperation(hWnd,TEMPLATE_SOBEL_H))
					InvalidateRect(hWnd,NULL,TRUE);
			}
			else
				MessageBox(hWnd,"File not loaded yet!","Error Message",MB_OK|MB_ICONEXCLAMATION);
			break;
		case IDM_VSOBEL:
			if(hImgData!=NULL){
				if(TemplateOperation(hWnd,TEMPLATE_SOBEL_V))
					InvalidateRect(hWnd,NULL,TRUE);
			}
			else
				MessageBox(hWnd,"File not loaded yet!","Error Message",MB_OK|MB_ICONEXCLAMATION);
			break;
		case IDM_HISOSOBEL:
			if(hImgData!=NULL){
				if(TemplateOperation(hWnd,TEMPLATE_ISOSOBEL_H))
					InvalidateRect(hWnd,NULL,TRUE);
			}
			else
				MessageBox(hWnd,"File not loaded yet!","Error Message",MB_OK|MB_ICONEXCLAMATION);
			break;
		case IDM_VISOSOBEL:
			if(hImgData!=NULL){
				if(TemplateOperation(hWnd,TEMPLATE_ISOSOBEL_V))
					InvalidateRect(hWnd,NULL,TRUE);
			}
			else
				MessageBox(hWnd,"File not loaded yet!","Error Message",MB_OK|MB_ICONEXCLAMATION);
			break;
		case IDM_HOUGH:
			if(hImgData!=NULL) 
				Hough(hWnd);
			else
				MessageBox(hWnd,"File not loaded yet!","Error Message",MB_OK|MB_ICONEXCLAMATION);
			break;
		case IDM_LOG:
			if(hImgData!=NULL){
				if(LapOfGauss(hWnd))
					InvalidateRect(hWnd,NULL,TRUE);
			}
			else
				MessageBox(hWnd,"File not loaded yet!","Error Message",MB_OK|MB_ICONEXCLAMATION);
			break;
		case IDM_CONTOUR:
			if(hImgData!=NULL){
				if(Contour(hWnd))
					InvalidateRect(hWnd,NULL,TRUE);
			}
			else
				MessageBox(hWnd,"File not loaded yet!","Error Message",MB_OK|MB_ICONEXCLAMATION);
			break;
		case IDM_SEEDFILL:
			if(hImgData!=NULL){
				IsSelecting=TRUE;
				MessageBox(hWnd,"Please click the area to be filled!","Message",MB_OK|MB_ICONEXCLAMATION);
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
	case TEMPLATE_SOBEL_H:
		coef=(float)1.0;
		memcpy(CoefArray,Template_HSobel,9*sizeof(float));
		strcpy(filename,"c:\\hsobel.bmp");
		break;
	case TEMPLATE_SOBEL_V:
		coef=(float)1.0;
		memcpy(CoefArray,Template_VSobel,9*sizeof(float));
		strcpy(filename,"c:\\vsobel.bmp");
		break;
	case TEMPLATE_ISOSOBEL_H:
		coef=(float)1.0;
		memcpy(CoefArray,Template_HIsoSobel,9*sizeof(float));
		strcpy(filename,"c:\\hisobel.bmp");
		break;
	case TEMPLATE_ISOSOBEL_V:
		coef=(float)1.0;
		memcpy(CoefArray,Template_VIsoSobel,9*sizeof(float));
		strcpy(filename,"c:\\visobel.bmp");
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
BOOL Outline(HWND hWnd)
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
	int                nw,n,ne,w,e,sw,s,se;

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

	for (y=1;y<bi.biHeight-1;y++){
		lpPtr=(char *)lpImgData+(BufSize-LineBytes-y*LineBytes);
		lpTempPtr=(char *)lpTempImgData+(BufSize-LineBytes-y*LineBytes);
		for (x=1;x<bi.biWidth-1;x++){
			if(*(lpPtr+x)==0){
				nw=(unsigned char)*(lpPtr+x+LineBytes-1);
				n=(unsigned char)*(lpPtr+x+LineBytes);
				ne=(unsigned char)*(lpPtr+x+LineBytes+1);
				w=(unsigned char)*(lpPtr+x-1);
				e=(unsigned char)*(lpPtr+x+1);
				sw=(unsigned char)*(lpPtr+x-LineBytes-1);
				s=(unsigned char)*(lpPtr+x-LineBytes);
				se=(unsigned char)*(lpPtr+x-LineBytes+1);
				num=nw+n+ne+w+e+sw+s+se;
				if(num==0)
					*(lpTempPtr+x)=(unsigned char)255;
			}
		}
	}

    if(hBitmap!=NULL)
	    DeleteObject(hBitmap);
	hDc=GetDC(hWnd);	
	hBitmap=CreateDIBitmap(hDc,	(LPBITMAPINFOHEADER)lpTempImgData, (LONG)CBM_INIT,
				(LPSTR)lpTempImgData+sizeof(BITMAPINFOHEADER) +NumColors*sizeof(RGBQUAD),
   				(LPBITMAPINFO)lpTempImgData, DIB_RGB_COLORS);

	hf=_lcreat("c:\\outline.bmp",0);
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
BOOL Hough(HWND hWnd)
{
    typedef struct{
    			  int topx;
    			  int topy;
    			  int botx;
    			  int boty;
    			  }MYLINE;

	DWORD              BufSize;
    LPBITMAPINFOHEADER lpImgData;
	LPSTR              lpPtr;
	HDC                hDc;
	LONG               x,y;
	long               i,maxd;
	int                k;
	int                Dist,Alpha;
    HGLOBAL            hDistAlpha,hMyLine;
    int	 			   *lpDistAlpha;
	MYLINE             *lpMyLine,*TempLine,MaxdLine;
    static LOGPEN      rlp={PS_SOLID,1,1,RGB(255,0,0)};
    HPEN               rhp;

	if( NumColors!=256){
    	MessageBox(hWnd,"Must be a mono bitmap with grayscale palette!","Error Message",MB_OK|MB_ICONEXCLAMATION);
        return FALSE;
    }
	Dist=(int)(sqrt( (double)bi.biWidth*bi.biWidth+(double)bi.biHeight*bi.biHeight)+0.5);
	Alpha=180 /2 ; //0 degree to 178 degree , step is 2 degrees

    if((hDistAlpha=GlobalAlloc(GHND,(DWORD)Dist* Alpha * sizeof(int)))==NULL){
    	MessageBox(hWnd,"Error alloc memory!","Error Message",MB_OK|MB_ICONEXCLAMATION);
        return FALSE;
    }

    if((hMyLine=GlobalAlloc(GHND,(DWORD)Dist*Alpha*sizeof(MYLINE)))==NULL){
   		GlobalFree(hDistAlpha);
	    return  FALSE;
	}

	BufSize=bf.bfSize-sizeof(BITMAPFILEHEADER);
    lpImgData=(LPBITMAPINFOHEADER)GlobalLock(hImgData);
    lpDistAlpha=(int *)GlobalLock(hDistAlpha);
	lpMyLine=(MYLINE *)GlobalLock(hMyLine);

	for (i=0;i<(long)Dist*Alpha;i++){
		TempLine=(MYLINE*)(lpMyLine+i);
		(*TempLine).boty=32767;
	}

	for (y=0;y<bi.biHeight;y++){
		lpPtr=(char *)lpImgData+(BufSize-LineBytes-y*LineBytes);
		for (x=0;x<bi.biWidth;x++)
			if(*(lpPtr++)==0)
				for (k=0;k<180;k+=2){
	       			i=(long)fabs((x*cos(k*PI/180.0)+y*sin(k*PI/180.0)));
			       	*(lpDistAlpha+i*Alpha+k/2)=*(lpDistAlpha+i*Alpha+k/2)+1;
					TempLine=(MYLINE*)(lpMyLine+i*Alpha+k/2);
					if(y> (*TempLine).topy){
						(*TempLine).topx=x;
						(*TempLine).topy=y;
					}
					if(y< (*TempLine).boty){
						(*TempLine).botx=x;
						(*TempLine).boty=y;
					}
		}
	}

	maxd=0;
	for (i=0;i<(long)Dist*Alpha;i++){
		TempLine=(MYLINE*)(lpMyLine+i);
		k=*(lpDistAlpha+i);
		if(	k > maxd){
			maxd=k;
			MaxdLine.topx=(*TempLine).topx;
			MaxdLine.topy=(*TempLine).topy;
			MaxdLine.botx=(*TempLine).botx;
			MaxdLine.boty=(*TempLine).boty;
		}
	}

	hDc = GetDC(hWnd);
	rhp = CreatePenIndirect(&rlp);
	SelectObject(hDc,rhp);
	MoveToEx(hDc,MaxdLine.botx,MaxdLine.boty,NULL);
	LineTo(hDc,MaxdLine.topx,MaxdLine.topy);
 	DeleteObject(rhp);                       
 	ReleaseDC(hWnd,hDc);

	GlobalUnlock(hImgData);
    GlobalUnlock(hDistAlpha);
	GlobalFree(hDistAlpha);
    GlobalUnlock(hMyLine);
	GlobalFree(hMyLine);
	return TRUE;
}
////////////////////////////////////////////////////////////////
BOOL LapOfGauss(HWND hWnd)
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
	float              TempNum;

	coef=(float)(1.0);

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

	for(y=2;y<bi.biHeight-2;y++)
			for(x=2;x<bi.biWidth-2;x++){
				lpPtr=(char *)lpImgData+(BufSize-LineBytes-y*LineBytes)+x;
				lpTempPtr=(char *)lpTempImgData+(BufSize-LineBytes-y*LineBytes)+x;
				TempNum=(float)((unsigned char)*(lpPtr+2*LineBytes-2))*Template_Log[0];
				TempNum+=(float)((unsigned char)*(lpPtr+2*LineBytes-1))*Template_Log[1];
				TempNum+=(float)((unsigned char)*(lpPtr+2*LineBytes))*Template_Log[2];
				TempNum+=(float)((unsigned char)*(lpPtr+2*LineBytes+1))*Template_Log[3];
				TempNum+=(float)((unsigned char)*(lpPtr+2*LineBytes+2))*Template_Log[4];

				TempNum+=(float)((unsigned char)*(lpPtr+LineBytes-2))*Template_Log[5];
				TempNum+=(float)((unsigned char)*(lpPtr+LineBytes-1))*Template_Log[6];
				TempNum+=(float)((unsigned char)*(lpPtr+LineBytes))*Template_Log[7];
				TempNum+=(float)((unsigned char)*(lpPtr+LineBytes+1))*Template_Log[8];
				TempNum+=(float)((unsigned char)*(lpPtr+LineBytes+2))*Template_Log[9];

				TempNum+=(float)((unsigned char)*(lpPtr-2))*Template_Log[10];
				TempNum+=(float)((unsigned char)*(lpPtr-1))*Template_Log[11];
				TempNum+=(float)((unsigned char)*(lpPtr))*Template_Log[12];
				TempNum+=(float)((unsigned char)*(lpPtr+1))*Template_Log[13];
				TempNum+=(float)((unsigned char)*(lpPtr+2))*Template_Log[14];

				TempNum+=(float)((unsigned char)*(lpPtr-LineBytes-2))*Template_Log[15];
				TempNum+=(float)((unsigned char)*(lpPtr-LineBytes-1))*Template_Log[16];
				TempNum+=(float)((unsigned char)*(lpPtr-LineBytes))*Template_Log[17];
				TempNum+=(float)((unsigned char)*(lpPtr-LineBytes+1))*Template_Log[18];
				TempNum+=(float)((unsigned char)*(lpPtr-LineBytes+2))*Template_Log[19];
				
				TempNum+=(float)((unsigned char)*(lpPtr-2*LineBytes-2))*Template_Log[20];
				TempNum+=(float)((unsigned char)*(lpPtr-2*LineBytes-1))*Template_Log[21];
				TempNum+=(float)((unsigned char)*(lpPtr-2*LineBytes))*Template_Log[22];
				TempNum+=(float)((unsigned char)*(lpPtr-2*LineBytes+1))*Template_Log[23];
				TempNum+=(float)((unsigned char)*(lpPtr-2*LineBytes+2))*Template_Log[24];

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

	hf=_lcreat("c:\\log.bmp",0);
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
BOOL Contour(HWND hWnd)
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
	POINT              StartP,CurP;
	BOOL               found;
	int                i;
	int                direct[8][2]={{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1},{0,1},{1,1}};

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
	memset(lpTempImgData,(BYTE)255,BufSize);
	memcpy(lpTempImgData,lpImgData,OffBits);

	found=FALSE;
	for (y=0;y<bi.biHeight && !found; y++){
		lpPtr=(char *)lpImgData+(BufSize-LineBytes-y*LineBytes);
		for (x=0;x<bi.biWidth && !found; x++)
			if (*(lpPtr++) ==0) found=TRUE;
	}

	if(found){
		StartP.x=x-1;
		StartP.y=y-1;
		lpTempPtr=(char *)lpTempImgData+(BufSize-LineBytes-StartP.y*LineBytes)+StartP.x;
		*lpTempPtr=(unsigned char)0;
   		CurP.x=StartP.x+1;
		CurP.y=StartP.y;
		lpPtr=(char *)lpImgData+(BufSize-LineBytes-CurP.y*LineBytes)+CurP.x;
		if(*lpPtr!=0){
	   		CurP.x=StartP.x+1;
			CurP.y=StartP.y+1;
			lpPtr=(char *)lpImgData+(BufSize-LineBytes-CurP.y*LineBytes)+CurP.x;
			if(*lpPtr!=0){
	   			CurP.x=StartP.x;
				CurP.y=StartP.y+1;
			}
			else{
	   			CurP.x=StartP.x-1;
				CurP.y=StartP.y+1;
			}
		}
		while (! ( (CurP.x==StartP.x) &&(CurP.y==StartP.y))){
			lpTempPtr=(char *)lpTempImgData+(BufSize-LineBytes-CurP.y*LineBytes)+CurP.x;
			*lpTempPtr=(unsigned char)0;
			for(i=0;i<8;i++){
				x=CurP.x+direct[i][0];
				y=CurP.y+direct[i][1];
				lpTempPtr=(char *)lpTempImgData+(BufSize-LineBytes-y*LineBytes)+x;
				lpPtr=(char *)lpImgData+(BufSize-LineBytes-y*LineBytes)+x;
				if( ( (*lpPtr==0)&&(*lpTempPtr!=0) ) || ( (x==StartP.x) &&(y==StartP.y)))
					if(IsContourP(x,y,lpPtr)){
				   		CurP.x=x;
						CurP.y=y;
						break;
					}
			}
		}
	}

    if(hBitmap!=NULL)
	    DeleteObject(hBitmap);
	hDc=GetDC(hWnd);	
	hBitmap=CreateDIBitmap(hDc,	(LPBITMAPINFOHEADER)lpTempImgData, (LONG)CBM_INIT,
				(LPSTR)lpTempImgData+sizeof(BITMAPINFOHEADER) +NumColors*sizeof(RGBQUAD),
   				(LPBITMAPINFO)lpTempImgData, DIB_RGB_COLORS);

	hf=_lcreat("c:\\contour.bmp",0);
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
BOOL IsContourP(LONG x,LONG y, char *lpPtr)
{
	int     num,n,w,e,s;

	n=(unsigned char)*(lpPtr+LineBytes);
	w=(unsigned char)*(lpPtr-1);
	e=(unsigned char)*(lpPtr+1);
	s=(unsigned char)*(lpPtr-LineBytes);
	num=n+w+e+s;
	if(num==0)
		return FALSE;

	return TRUE;
}
////////////////////////////////////////////////////////////////
BOOL SeedFill(HWND hWnd)
{
	DWORD              BufSize;
    LPBITMAPINFOHEADER lpImgData;
	HLOCAL             hTempImgData;
	LPBITMAPINFOHEADER lpTempImgData;
	LPSTR              lpTempPtr,lpTempPtr1;
	HDC                hDc;
	HFILE              hf;
	POINT              CurP,NeighborP;

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

	if(!InitStack(hWnd,(LONG)bi.biHeight*bi.biWidth)){
		LocalUnlock(hTempImgData);
		LocalFree(hTempImgData);
		GlobalUnlock(hImgData);
		return FALSE;
	}

	lpTempPtr=(char *)lpTempImgData+(BufSize-LineBytes-SeedPoint.y*LineBytes)+SeedPoint.x;
	if(*lpTempPtr==0){
    	MessageBox(hWnd,"The point you select is a contour point!","Error Message",MB_OK|MB_ICONEXCLAMATION);
		LocalUnlock(hTempImgData);
		LocalFree(hTempImgData);
		GlobalUnlock(hImgData);
		DeInitStack();
        return FALSE;
	}

	MyPush(SeedPoint);
	while(!IsStackEmpty())
	{
		CurP=MyPop();
		lpTempPtr=(char *)lpTempImgData+(BufSize-LineBytes-CurP.y*LineBytes)+CurP.x;
		*lpTempPtr=(unsigned char)0;
		//left neighbour
		if(CurP.x>0)
		{
			NeighborP.x=CurP.x-1;
			NeighborP.y=CurP.y;
			lpTempPtr1=lpTempPtr-1;
			if(*lpTempPtr1!=0)
				MyPush(NeighborP);
		}
		//up neighbour
		if(CurP.y>0)
		{
			NeighborP.x=CurP.x;
			NeighborP.y=CurP.y-1;
			lpTempPtr1=lpTempPtr+LineBytes;
			if(*lpTempPtr1!=0)
				MyPush(NeighborP);
		}
		//right neighbour
		if(CurP.x<bi.biWidth-1)
		{
			NeighborP.x=CurP.x+1;
			NeighborP.y=CurP.y;
			lpTempPtr1=lpTempPtr+1;
			if(*lpTempPtr1!=0)
				MyPush(NeighborP);
		}
		//down neighbour
		if(CurP.y<bi.biHeight-1)
		{
			NeighborP.x=CurP.x;
			NeighborP.y=CurP.y+1;
			lpTempPtr1=lpTempPtr-LineBytes;
			if(*lpTempPtr1!=0)
				MyPush(NeighborP);
		}
	}
	DeInitStack();

    if(hBitmap!=NULL)
	    DeleteObject(hBitmap);
	hDc=GetDC(hWnd);	
	hBitmap=CreateDIBitmap(hDc,	(LPBITMAPINFOHEADER)lpTempImgData, (LONG)CBM_INIT,
				(LPSTR)lpTempImgData+sizeof(BITMAPINFOHEADER) +NumColors*sizeof(RGBQUAD),
   				(LPBITMAPINFO)lpTempImgData, DIB_RGB_COLORS);

	hf=_lcreat("c:\\seed.bmp",0);
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
BOOL InitStack(HWND hWnd,LONG StackLen)
{
	SeedFillStack.ElementsNum=StackLen;
	if((SeedFillStack.hMem=GlobalAlloc(GHND,SeedFillStack.ElementsNum*sizeof(POINT)))==NULL)
	{
    	MessageBox(hWnd,"Error alloc memory!","ErrorMessage",MB_OK|
                   MB_ICONEXCLAMATION);
		return FALSE;
	}
	SeedFillStack.lpMyStack=(POINT *)GlobalLock(SeedFillStack.hMem);
	memset(SeedFillStack.lpMyStack,0,SeedFillStack.ElementsNum*sizeof(POINT));
	SeedFillStack.ptr=0;
	return TRUE;
}
////////////////////////////////////////////////////////////////
void DeInitStack()
{
	GlobalUnlock(SeedFillStack.hMem);
	GlobalFree(SeedFillStack.hMem);
	SeedFillStack.ElementsNum=0;
	SeedFillStack.ptr=0;
}
////////////////////////////////////////////////////////////////
BOOL MyPush(POINT p)
{
	POINT *TempPtr;
	if(SeedFillStack.ptr>=SeedFillStack.ElementsNum)
		return FALSE;
	TempPtr=(POINT *)(SeedFillStack.lpMyStack+SeedFillStack.ptr++);
	(*TempPtr).x=p.x;
	(*TempPtr).y=p.y;
	return TRUE;
}
////////////////////////////////////////////////////////////////
POINT MyPop()
{
	POINT InvalidP;
	InvalidP.x=-1;
	InvalidP.y=-1;

	if(SeedFillStack.ptr<=0)
		return InvalidP;
	SeedFillStack.ptr--;
	return *(SeedFillStack.lpMyStack+SeedFillStack.ptr);
}
////////////////////////////////////////////////////////////////
BOOL IsStackEmpty()
{
	return (SeedFillStack.ptr==0)?TRUE:FALSE;
}
