//////////////////////////////////////////////////////////////
//Name:geotrans.c
//Purpose: To perform geometric transform
//Author: phoenix, CS, TshingHua, Beijing, P.R.C.
//Email: bjlufengjun@www.163.net or lufengjun@hotmail.com
//Date:April 3, 1998

//header file
#include "bmp.h"
#include "memory.h"
#include "math.h"

//macro definition
#define WIDTHBYTES(i)    ((i+31)/32*4)
#define PI 3.1415926535
#define RADIAN(angle) ((angle)*PI/180.0) //convert angle to radian

//function declaration
int PASCAL WinMain (HANDLE, HANDLE, LPSTR, int);
LRESULT CALLBACK MainWndProc(HWND , UINT,WPARAM, LPARAM);
BOOL LoadBmpFile (HWND hWnd,char *BmpFileName);
BOOL CALLBACK InputBox( HWND hDlg, UINT message,WPARAM wParam, LPARAM lParam );
BOOL Translation(HWND hWnd);
BOOL Rotation(HWND hWnd);
BOOL Mirror(HWND hWnd,BOOL XDirection);
BOOL Transpose(HWND hWnd);
BOOL Zoom(HWND hWnd);

//global variable declaration
BITMAPFILEHEADER   bf;
BITMAPINFOHEADER   bi;
HPALETTE           hPalette=NULL;
HBITMAP            hBitmap=NULL;
HGLOBAL            hImgData=NULL;
DWORD              NumColors;
DWORD              LineBytes;
HWND               hWnd;
HINSTANCE          ghInst;
int                xOffset=0,yOffset=0;
float			   RotateAngle=0.0f;
float              ZoomRatio=0.25f;
DWORD              ImgWidth=0 , ImgHeight=0;
///////////////////////////////////////////////////////////
int PASCAL WinMain (HANDLE hInstance, HANDLE hPrevInstance,
		    LPSTR lpszCmdLine, int nCmdShow)
{
	MSG       msg;
	WNDCLASS  wndclass;

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
 
	hWnd = CreateWindow ("phoenix ip system","geometric transform",
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
		case IDM_TRANSLATION: 
			if(hImgData!=NULL){
				if(Translation(hWnd))
					InvalidateRect(hWnd,NULL,TRUE);
			}
			else
				MessageBox(hWnd,"File not loaded yet!","Error Message",MB_OK|MB_ICONEXCLAMATION);
			break;
		case IDM_ROTATION: 
			if(hImgData!=NULL){
				if(Rotation(hWnd))
					InvalidateRect(hWnd,NULL,TRUE);
			}
			else
				MessageBox(hWnd,"File not loaded yet!","Error Message",MB_OK|MB_ICONEXCLAMATION);
			break;
		case IDM_MIRRORX: 
			if(hImgData!=NULL){
				if(Mirror(hWnd,TRUE))
					InvalidateRect(hWnd,NULL,TRUE);
			}
			else
				MessageBox(hWnd,"File not loaded yet!","Error Message",MB_OK|MB_ICONEXCLAMATION);
			break;
		case IDM_MIRRORY: 
			if(hImgData!=NULL){
				if(Mirror(hWnd,FALSE))
					InvalidateRect(hWnd,NULL,TRUE);
			}
			else
				MessageBox(hWnd,"File not loaded yet!","Error Message",MB_OK|MB_ICONEXCLAMATION);
			break;
		case IDM_TRANSPOSE: 
			if(hImgData!=NULL){
				if(Transpose(hWnd))
					InvalidateRect(hWnd,NULL,TRUE);
			}
			else
				MessageBox(hWnd,"File not loaded yet!","Error Message",MB_OK|MB_ICONEXCLAMATION);
			break;
		case IDM_ZOOM: 
			if(hImgData!=NULL){
				if(Zoom(hWnd))
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
    _llseek(hf,sizeof(BITMAPFILEHEADER),SEEK_SET);
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
     	SetDlgItemText(hDlg,ID_XOFFSET,"0");
     	SetDlgItemText(hDlg,ID_YOFFSET,"0");
     	SetDlgItemText(hDlg,ID_ANGLE,"0");
     	SetDlgItemText(hDlg,ID_ZOOMRATIO,"0.25");
    	return TRUE;
   	case WM_COMMAND:		   
    	if ( wParam == IDOK || wParam == IDCANCEL )
       	{
        	GetDlgItemText(hDlg,ID_XOFFSET,str,80);
			xOffset=atoi(str);
        	GetDlgItemText(hDlg,ID_YOFFSET,str,80);
			yOffset=atoi(str);
        	GetDlgItemText(hDlg,ID_ANGLE,str,80);
			RotateAngle=(float)atof(str);
        	GetDlgItemText(hDlg,ID_ZOOMRATIO,str,80);
			ZoomRatio=(float)atof(str);
            EndDialog ( hDlg, TRUE );
            return  TRUE;
       	}
        break;
   		}
	return FALSE;			     
}
////////////////////////////////////////////////////////////////
BOOL Translation(HWND hWnd)
{
	DLGPROC            dlgInputBox = NULL;
	DWORD              OffBits,BufSize;
    LPBITMAPINFOHEADER lpImgData;
	LPSTR              lpPtr;
	HLOCAL             hTempImgData;
	LPBITMAPINFOHEADER lpTempImgData;
	LPSTR              lpTempPtr;
	int				   SrcX0,SrcY0,SrcX1,SrcY1,DstX0,DstY0,DstX1,DstY1;
	int                RectWidth,RectHeight;
	BOOL               xVisible,yVisible;
	HDC                hDc;
	HFILE              hf;
	int                i;

	dlgInputBox = (DLGPROC) MakeProcInstance ( (FARPROC)InputBox, ghInst );
	DialogBox (ghInst, "INPUTBOX", hWnd, dlgInputBox);
	FreeProcInstance ( (FARPROC) dlgInputBox );

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

	memset(lpTempPtr,(BYTE)255,BufSize);
	memcpy(lpTempPtr,lpPtr,OffBits);

	xVisible=TRUE;
	if( xOffset<= -bi.biWidth )
		xVisible=FALSE;
	else if( xOffset<=0){
		DstX0=0;
		DstX1=bi.biWidth+xOffset;
	}
	else if ( xOffset<bi.biWidth){
		DstX0=xOffset;
		DstX1=bi.biWidth;
	}
	else
		xVisible=FALSE;
	SrcX0=DstX0-xOffset;
	SrcX1=DstX1-xOffset;
	RectWidth=DstX1-DstX0;

	yVisible=TRUE;
	if( yOffset<= -bi.biHeight )
		yVisible=FALSE;
	else if( yOffset<=0){
		DstY0=0;
		DstY1=bi.biHeight+yOffset;
	}
	else if ( yOffset<bi.biHeight){
		DstY0=yOffset;
		DstY1=bi.biHeight;
	}
	else
		yVisible=FALSE;
	SrcY0=DstY0-yOffset;
	SrcY1=DstY1-yOffset;
	RectHeight=DstY1-DstY0;

	if( xVisible && yVisible){
		for(i=0;i<RectHeight;i++){
			lpPtr=(char *)lpImgData+(BufSize-LineBytes-(i+SrcY0)*LineBytes)+SrcX0;
			lpTempPtr=(char *)lpTempImgData+(BufSize-LineBytes-(i+DstY0)*LineBytes)+DstX0;
			memcpy(lpTempPtr,lpPtr,RectWidth);
		}
	}

	hDc=GetDC(hWnd);
    if(hBitmap!=NULL)
	    DeleteObject(hBitmap);
	
	hBitmap=CreateDIBitmap(hDc,	(LPBITMAPINFOHEADER)lpTempImgData, (LONG)CBM_INIT,
				(LPSTR)lpTempImgData+sizeof(BITMAPINFOHEADER) +NumColors*sizeof(RGBQUAD),
   				(LPBITMAPINFO)lpTempImgData, DIB_RGB_COLORS);

    hf=_lcreat("c:\\translation.bmp",0);
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
BOOL Rotation(HWND hWnd)
{
	DLGPROC            dlgInputBox = NULL;
	DWORD              OffBits,SrcBufSize,DstBufSize,DstLineBytes;
    LPBITMAPINFOHEADER lpImgData;
	LPSTR              lpPtr;
	HLOCAL             hTempImgData;
	LPBITMAPINFOHEADER lpTempImgData;
	LPSTR              lpTempPtr;
	float			   SrcX1,SrcY1,SrcX2,SrcY2,SrcX3,SrcY3,SrcX4,SrcY4;
	float			   DstX1,DstY1,DstX2,DstY2,DstX3,DstY3,DstX4,DstY4;
	DWORD              Wold,Hold,Wnew,Hnew;
	HDC                hDc;
	HFILE              hf;
	DWORD              x0,y0,x1,y1;
	float              cosa,sina; //cos(a),sin(a)
	float			   num1,num2;
	BITMAPFILEHEADER   DstBf;
	BITMAPINFOHEADER   DstBi;

	dlgInputBox = (DLGPROC) MakeProcInstance ( (FARPROC)InputBox, ghInst );
	DialogBox (ghInst, "INPUTBOX", hWnd, dlgInputBox);
	FreeProcInstance ( (FARPROC) dlgInputBox );
	
	RotateAngle=(float)RADIAN(RotateAngle);
	cosa=(float)cos((double)RotateAngle);
	sina=(float)sin((double)RotateAngle);

	Wold=bi.biWidth;
	Hold=bi.biHeight;
	SrcX1=(float)(-0.5*Wold);
	SrcY1=(float)(0.5*Hold);
	SrcX2=(float)(0.5*Wold);
	SrcY2=(float)(0.5*Hold);
	SrcX3=(float)(-0.5*Wold);
	SrcY3=(float)(-0.5*Hold);
	SrcX4=(float)(0.5*Wold);
	SrcY4=(float)(-0.5*Hold);

	DstX1=cosa*SrcX1+sina*SrcY1;
	DstY1=-sina*SrcX1+cosa*SrcY1;
	DstX2=cosa*SrcX2+sina*SrcY2;
	DstY2=-sina*SrcX2+cosa*SrcY2;
	DstX3=cosa*SrcX3+sina*SrcY3;
	DstY3=-sina*SrcX3+cosa*SrcY3;
	DstX4=cosa*SrcX4+sina*SrcY4;
	DstY4=-sina*SrcX4+cosa*SrcY4;

	Wnew = (DWORD)(max(fabs(DstX4-DstX1), fabs(DstX3-DstX2))+0.5);
    Hnew = (DWORD)(max(fabs(DstY4-DstY1), fabs(DstY3-DstY2))+0.5);
	num1=(float)( -0.5*Wnew*cosa-0.5*Hnew*sina+0.5*Wold);
	num2=(float)(0.5*Wnew*sina-0.5*Hnew*cosa+0.5*Hold);

	OffBits=bf.bfOffBits-sizeof(BITMAPFILEHEADER);
	SrcBufSize=bf.bfSize-sizeof(BITMAPFILEHEADER);

	ImgWidth=Wnew;
	ImgHeight=Hnew;

	DstLineBytes=(DWORD)WIDTHBYTES(Wnew*bi.biBitCount);
	DstBufSize=(DWORD)(sizeof(BITMAPINFOHEADER)+NumColors*sizeof(RGBQUAD)+(DWORD)DstLineBytes*Hnew);

	if((hTempImgData=LocalAlloc(LHND,DstBufSize))==NULL)
    {
    	MessageBox(hWnd,"Error alloc memory!","Error Message",MB_OK|MB_ICONEXCLAMATION);
        return FALSE;
    }

    lpImgData=(LPBITMAPINFOHEADER)GlobalLock(hImgData);    
	lpTempImgData=(LPBITMAPINFOHEADER)LocalLock(hTempImgData);

	lpPtr=(char *)lpImgData;
	lpTempPtr=(char *)lpTempImgData;

	memset(lpTempPtr,(BYTE)255,DstBufSize);
	memcpy(lpTempPtr,lpPtr,OffBits);
	
	//get new bitmapfileheader and bitmapinfoheader
	memcpy((char *)&DstBf,(char *)&bf,sizeof(BITMAPFILEHEADER));
	memcpy((char *)&DstBi,(char *)&bi,sizeof(BITMAPINFOHEADER));
	DstBf.bfSize=DstBufSize+sizeof(BITMAPFILEHEADER);
	DstBi.biWidth=Wnew;
	DstBi.biHeight=Hnew;

	//overwrite bitmapinfoheader with the new one
	memcpy(lpTempPtr,(char *)&DstBi,sizeof(BITMAPINFOHEADER));

	for(y1=0;y1<Hnew;y1++)
		for(x1=0;x1<Wnew;x1++){
			x0= (DWORD)(x1*cosa+y1*sina+num1);
			y0= (DWORD)(-1.0f*x1*sina+y1*cosa+num2);
			if( (x0>=0) && (x0<Wold) && (y0>=0) && (y0<Hold))
			{
				lpPtr=(char *)lpImgData+(SrcBufSize-LineBytes-y0*LineBytes)+x0;
				lpTempPtr=(char *)lpTempImgData+(DstBufSize-DstLineBytes-y1*DstLineBytes)+x1;
				*lpTempPtr=*lpPtr;
			}
	}

	hDc=GetDC(hWnd);
    if(hBitmap!=NULL)
	    DeleteObject(hBitmap);
	
	hBitmap=CreateDIBitmap(hDc,	(LPBITMAPINFOHEADER)lpTempImgData, (LONG)CBM_INIT,
				(LPSTR)lpTempImgData+sizeof(BITMAPINFOHEADER) +NumColors*sizeof(RGBQUAD),
   				(LPBITMAPINFO)lpTempImgData, DIB_RGB_COLORS);

    hf=_lcreat("c:\\rotation.bmp",0);
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
BOOL Mirror(HWND hWnd,BOOL XDirection)
{
	DWORD              OffBits,BufSize;
    LPBITMAPINFOHEADER lpImgData;
	LPSTR              lpPtr;
	HLOCAL             hTempImgData;
	LPBITMAPINFOHEADER lpTempImgData;
	LPSTR              lpTempPtr;
	HDC                hDc;
	HFILE              hf;
	LONG               x0,y0,x1,y1;

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

	memset(lpTempPtr,(BYTE)255,BufSize);
	memcpy(lpTempPtr,lpPtr,OffBits);

	if( XDirection){
		for(y1=0;y1<bi.biHeight;y1++)
			for(x1=0;x1<bi.biWidth;x1++){
				x0=bi.biWidth-1-x1;
				y0=y1;
				lpPtr=(char *)lpImgData+(BufSize-LineBytes-y0*LineBytes)+x0;
				lpTempPtr=(char *)lpTempImgData+(BufSize-LineBytes-y1*LineBytes)+x1;
				*lpTempPtr=*lpPtr;
		}
	}
	else{
		for(y1=0;y1<bi.biHeight;y1++)
			for(x1=0;x1<bi.biWidth;x1++){
				x0=x1;
				y0=bi.biHeight-1-y1;
				lpPtr=(char *)lpImgData+(BufSize-LineBytes-y0*LineBytes)+x0;
				lpTempPtr=(char *)lpTempImgData+(BufSize-LineBytes-y1*LineBytes)+x1;
				*lpTempPtr=*lpPtr;
		}
	}

	hDc=GetDC(hWnd);
    if(hBitmap!=NULL)
	    DeleteObject(hBitmap);
	
	hBitmap=CreateDIBitmap(hDc,	(LPBITMAPINFOHEADER)lpTempImgData, (LONG)CBM_INIT,
				(LPSTR)lpTempImgData+sizeof(BITMAPINFOHEADER) +NumColors*sizeof(RGBQUAD),
   				(LPBITMAPINFO)lpTempImgData, DIB_RGB_COLORS);
	if( XDirection)
		hf=_lcreat("c:\\mirrorx.bmp",0);
	else
		hf=_lcreat("c:\\mirrory.bmp",0);

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
BOOL Transpose(HWND hWnd)
{
	DWORD              OffBits,SrcBufSize,DstBufSize,DstLineBytes;
    LPBITMAPINFOHEADER lpImgData;
	LPSTR              lpPtr;
	HLOCAL             hTempImgData;
	LPBITMAPINFOHEADER lpTempImgData;
	LPSTR              lpTempPtr;
	DWORD              Wnew,Hnew;
	HDC                hDc;
	HFILE              hf;
	DWORD              x0,y0,x1,y1;
	BITMAPFILEHEADER   DstBf;
	BITMAPINFOHEADER   DstBi;

	Wnew = (DWORD)bi.biHeight;
    Hnew = (DWORD)bi.biWidth;

	OffBits=bf.bfOffBits-sizeof(BITMAPFILEHEADER);
	SrcBufSize=bf.bfSize-sizeof(BITMAPFILEHEADER);

	ImgWidth=Wnew;
	ImgHeight=Hnew;

	DstLineBytes=(DWORD)WIDTHBYTES(Wnew*bi.biBitCount);
	DstBufSize=(DWORD)(sizeof(BITMAPINFOHEADER)+NumColors*sizeof(RGBQUAD)+(DWORD)DstLineBytes*Hnew);

	if((hTempImgData=LocalAlloc(LHND,DstBufSize))==NULL)
    {
    	MessageBox(hWnd,"Error alloc memory!","Error Message",MB_OK|MB_ICONEXCLAMATION);
        return FALSE;
    }

    lpImgData=(LPBITMAPINFOHEADER)GlobalLock(hImgData);    
	lpTempImgData=(LPBITMAPINFOHEADER)LocalLock(hTempImgData);

	lpPtr=(char *)lpImgData;
	lpTempPtr=(char *)lpTempImgData;

	memset(lpTempPtr,(BYTE)255,DstBufSize);
	memcpy(lpTempPtr,lpPtr,OffBits);
	
	//get new bitmapfileheader and bitmapinfoheader
	memcpy((char *)&DstBf,(char *)&bf,sizeof(BITMAPFILEHEADER));
	memcpy((char *)&DstBi,(char *)&bi,sizeof(BITMAPINFOHEADER));
	DstBf.bfSize=DstBufSize+sizeof(BITMAPFILEHEADER);
	DstBi.biWidth=Wnew;
	DstBi.biHeight=Hnew;

	//overwrite bitmapinfoheader with the new one
	memcpy(lpTempPtr,(char *)&DstBi,sizeof(BITMAPINFOHEADER));

	for(y1=0;y1<Hnew;y1++)
		for(x1=0;x1<Wnew;x1++){
			x0= y1;
			y0= x1;
			lpPtr=(char *)lpImgData+(SrcBufSize-LineBytes-y0*LineBytes)+x0;
			lpTempPtr=(char *)lpTempImgData+(DstBufSize-DstLineBytes-y1*DstLineBytes)+x1;
			*lpTempPtr=*lpPtr;
		}
	
	hDc=GetDC(hWnd);
    if(hBitmap!=NULL)
	    DeleteObject(hBitmap);
	
	hBitmap=CreateDIBitmap(hDc,	(LPBITMAPINFOHEADER)lpTempImgData, (LONG)CBM_INIT,
				(LPSTR)lpTempImgData+sizeof(BITMAPINFOHEADER) +NumColors*sizeof(RGBQUAD),
   				(LPBITMAPINFO)lpTempImgData, DIB_RGB_COLORS);

    hf=_lcreat("c:\\transpose.bmp",0);
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
BOOL Zoom(HWND hWnd)
{
	DLGPROC            dlgInputBox = NULL;
	DWORD              OffBits,SrcBufSize,DstBufSize,DstLineBytes;
    LPBITMAPINFOHEADER lpImgData;
	LPSTR              lpPtr;
	HLOCAL             hTempImgData;
	LPBITMAPINFOHEADER lpTempImgData;
	LPSTR              lpTempPtr;
	DWORD              Wold,Hold,Wnew,Hnew;
	HDC                hDc;
	HFILE              hf;
	DWORD              x0,y0,x1,y1;
	float			   num1;
	BITMAPFILEHEADER   DstBf;
	BITMAPINFOHEADER   DstBi;

	dlgInputBox = (DLGPROC) MakeProcInstance ( (FARPROC)InputBox, ghInst );
	DialogBox (ghInst, "INPUTBOX", hWnd, dlgInputBox);
	FreeProcInstance ( (FARPROC) dlgInputBox );
	
	num1=(float)(1.0/ZoomRatio);
	Wold=bi.biWidth;
	Hold=bi.biHeight;
	Wnew = (DWORD)(Wold*ZoomRatio+0.5);
    Hnew = (DWORD)(Hold*ZoomRatio+0.5);

	OffBits=bf.bfOffBits-sizeof(BITMAPFILEHEADER);
	SrcBufSize=bf.bfSize-sizeof(BITMAPFILEHEADER);

	ImgWidth=Wnew;
	ImgHeight=Hnew;

	DstLineBytes=(DWORD)WIDTHBYTES(Wnew*bi.biBitCount);
	DstBufSize=(DWORD)(sizeof(BITMAPINFOHEADER)+NumColors*sizeof(RGBQUAD)+(DWORD)DstLineBytes*Hnew);

	if((hTempImgData=LocalAlloc(LHND,DstBufSize))==NULL)
    {
    	MessageBox(hWnd,"Error alloc memory!","Error Message",MB_OK|MB_ICONEXCLAMATION);
        return FALSE;
    }

    lpImgData=(LPBITMAPINFOHEADER)GlobalLock(hImgData);    
	lpTempImgData=(LPBITMAPINFOHEADER)LocalLock(hTempImgData);

	lpPtr=(char *)lpImgData;
	lpTempPtr=(char *)lpTempImgData;

	memset(lpTempPtr,(BYTE)255,DstBufSize);
	memcpy(lpTempPtr,lpPtr,OffBits);
	
	//get new bitmapfileheader and bitmapinfoheader
	memcpy((char *)&DstBf,(char *)&bf,sizeof(BITMAPFILEHEADER));
	memcpy((char *)&DstBi,(char *)&bi,sizeof(BITMAPINFOHEADER));
	DstBf.bfSize=DstBufSize+sizeof(BITMAPFILEHEADER);
	DstBi.biWidth=Wnew;
	DstBi.biHeight=Hnew;

	//overwrite bitmapinfoheader with the new one
	memcpy(lpTempPtr,(char *)&DstBi,sizeof(BITMAPINFOHEADER));

	for(y1=0;y1<Hnew;y1++)
		for(x1=0;x1<Wnew;x1++){
			x0= (DWORD)(x1*num1);
			y0= (DWORD)(y1*num1);
			if( (x0>=0) && (x0<Wold) && (y0>=0) && (y0<Hold))
			{
				lpPtr=(char *)lpImgData+(SrcBufSize-LineBytes-y0*LineBytes)+x0;
				lpTempPtr=(char *)lpTempImgData+(DstBufSize-DstLineBytes-y1*DstLineBytes)+x1;
				*lpTempPtr=*lpPtr;
			}
	}

	hDc=GetDC(hWnd);
    if(hBitmap!=NULL)
	    DeleteObject(hBitmap);
	
	hBitmap=CreateDIBitmap(hDc,	(LPBITMAPINFOHEADER)lpTempImgData, (LONG)CBM_INIT,
				(LPSTR)lpTempImgData+sizeof(BITMAPINFOHEADER) +NumColors*sizeof(RGBQUAD),
   				(LPBITMAPINFO)lpTempImgData, DIB_RGB_COLORS);

    hf=_lcreat("c:\\zoom.bmp",0);
	_lwrite(hf,(LPSTR)&DstBf,sizeof(BITMAPFILEHEADER)); 
	_lwrite(hf,(LPSTR)lpTempImgData,DstBufSize);
	_lclose(hf);

 	ReleaseDC(hWnd,hDc);
	LocalUnlock(hTempImgData);
	LocalFree(hTempImgData);
	GlobalUnlock(hImgData);
	return TRUE;
}
