//********************************************************************************
//* TransparentWindow.CPP
//*
//* A transparent window class.
//*
//* Based on the idea of Jason Wylie ,Franz Polzer,Luo yun bin
//* e9225140@student.tuwien.ac.at
//* (C) 2002 by 王鹏
//*
//* Write to me:	mailwp@21cn.com
//********************************************************************************


#include "stdafx.h"
#include "TransparentWnd.h"
#include "Dib.h"
#include "resource.h"

#include <assert.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define WM_LIBEN WM_USER+994

CString GetCurPath()
{
	TCHAR exeFullPath[MAX_PATH];
	CString strPath;
	GetModuleFileName(NULL,exeFullPath,MAX_PATH);
	strPath.Format("%s", exeFullPath);
	strPath = strPath.Left(strPath.ReverseFind('\\'));

	return strPath;
}


//********************************************************************************
// LoadBMPImage	- Loads a BMP file and creates a bitmap GDI object
//		  also creates logical palette for it.
// Returns	- TRUE for success
// sBMPFile	- Full path of the BMP file
// bitmap	- The bitmap object to initialize
// pPal		- Will hold the logical palette. Can be NULL
//********************************************************************************
BOOL LoadBMPImage( LPCTSTR sBMPFile, CBitmap& bitmap, CPalette *pPal )
{
	CFile file;
	if( !file.Open( sBMPFile, CFile::modeRead) )
		return FALSE;
	
	BITMAPFILEHEADER bmfHeader;
	
	// Read file header
	if (file.Read((LPSTR)&bmfHeader, sizeof(bmfHeader)) != sizeof(bmfHeader))
		return FALSE;
	
	// File type should be 'BM'
	if (bmfHeader.bfType != ((WORD) ('M' << 8) | 'B'))
		return FALSE;
	
	// Get length of the remainder of the file and allocate memory
	DWORD nPackedDIBLen = file.GetLength() - sizeof(BITMAPFILEHEADER);
	HGLOBAL hDIB = ::GlobalAlloc(GMEM_FIXED, nPackedDIBLen);
	if (hDIB == 0)
		return FALSE;
	
	// Read the remainder of the bitmap file.
	if (file.Read((LPSTR)hDIB, nPackedDIBLen) != nPackedDIBLen )
	{
		::GlobalFree(hDIB);
		return FALSE;
	}
	
	
	BITMAPINFOHEADER &bmiHeader = *(LPBITMAPINFOHEADER)hDIB ;
	BITMAPINFO &bmInfo = *(LPBITMAPINFO)hDIB ;
	
	// If bmiHeader.biClrUsed is zero we have to infer the number
	// of colors from the number of bits used to specify it.
	int nColors = bmiHeader.biClrUsed ? bmiHeader.biClrUsed : 
	1 << bmiHeader.biBitCount;
	
	LPVOID lpDIBBits;
	if( bmInfo.bmiHeader.biBitCount > 8 )
		lpDIBBits = (LPVOID)((LPDWORD)(bmInfo.bmiColors + bmInfo.bmiHeader.biClrUsed) + 
		((bmInfo.bmiHeader.biCompression == BI_BITFIELDS) ? 3 : 0));
	else
		lpDIBBits = (LPVOID)(bmInfo.bmiColors + nColors);
	
	// Create the logical palette
	if( pPal != NULL )
	{
		// Create the palette
		if( nColors <= 256 )
		{
			UINT nSize = sizeof(LOGPALETTE) + (sizeof(PALETTEENTRY) * nColors);
			LOGPALETTE *pLP = (LOGPALETTE *) new BYTE[nSize];
			
			pLP->palVersion = 0x300;
			pLP->palNumEntries = nColors;
			
			for( int i=0; i < nColors; i++)
			{
				pLP->palPalEntry[i].peRed = bmInfo.bmiColors[i].rgbRed;
				pLP->palPalEntry[i].peGreen = bmInfo.bmiColors[i].rgbGreen;
				pLP->palPalEntry[i].peBlue = bmInfo.bmiColors[i].rgbBlue;
				pLP->palPalEntry[i].peFlags = 0;
			}
			
			pPal->CreatePalette( pLP );
			
			delete[] pLP;
		}
	}
	
	CClientDC dc(NULL);
	CPalette* pOldPalette = NULL;
	if( pPal )
	{
		pOldPalette = dc.SelectPalette( pPal, FALSE );
		dc.RealizePalette();
	}
	
	HBITMAP hBmp = CreateDIBitmap( dc.m_hDC,		// handle to device context 
		&bmiHeader,	// pointer to bitmap size and format data 
		CBM_INIT,	// initialization flag 
		lpDIBBits,	// pointer to initialization data 
		&bmInfo,	// pointer to bitmap color-format data 
		DIB_RGB_COLORS);		// color-data usage 
	bitmap.Attach( hBmp );
	
	if( pOldPalette )
		dc.SelectPalette( pOldPalette, FALSE );
	
	::GlobalFree(hDIB);
	return TRUE;
}

//********************************************************************************
//       function:FindBmpFile()
//       strParent   search path
//       1.search bmp file
//       2.create random number
//********************************************************************************
void CTransparentWnd::FindBmpFile(CString strPath)
{
	int nFilecount1=0;  // 背景
	int nFilecount2=0;  // 数字
	int nFilter;
	nFilter=GetCurPath().GetLength()+10;
	CFileFind finder;
	
	// build a string with wildcards
	CString strWildcard(strPath);
	strWildcard += _T("\\*.bmp");
	try
	{
		//--------------------------------------------------------------
		// start working for filescount
		//--------------------------------------------------------------
		BOOL bWorking = finder.FindFile(strWildcard);
		
		while (bWorking)
		{
			bWorking = finder.FindNextFile();
			
			// skip . and .. files; otherwise, we'd
			// recur infinitely!
			
			if (finder.IsDots())
				continue;
			
			// if it's NOT a directory, recursively search it
			
			if (!finder.IsDirectory())
			{
				if (finder.GetFilePath().GetLength() > nFilter)
					nFilecount1++;   //background
				else
					nFilecount2++;   //number
			}
		}
		DWORD dwTick=GetTickCount();
		//random the image
		nFilecount1=(int)(dwTick%(nFilecount1-1));
		nFilecount2=(int)(dwTick%(nFilecount2-1));
		//--------------------------------------------------------------
		//  获得具体的图片
		//--------------------------------------------------------------
		bWorking = finder.FindFile(strWildcard);
		int m=0;
		int n=0;
		while (bWorking)  //2
		{
			bWorking = finder.FindNextFile();
			
			// skip . and .. files; otherwise, we'd
			// recur infinitely!
			
			if (finder.IsDots())
				continue;
			
			// if it's NOT a directory, recursively search it
			
			if (!finder.IsDirectory())
			{
				if (finder.GetFilePath().GetLength() > nFilter)
				{					
				    if (m==nFilecount1)
					m_szBmpFile=finder.GetFilePath();
					m++;
				}
				else
				{					
				    if (n==nFilecount2)
					m_szNumFile=finder.GetFilePath();
					n++;
				}
			}
		}//2
	}
	catch(...)
	{
		
	}
	
}
//********************************************************************************
//* Constructor
//********************************************************************************
CTransparentWnd::CTransparentWnd()
{
	
	m_nh1=0;
	m_nh2=0;
	m_nm1=0;
	m_nm2=0;
	m_ns1=0;
	m_ns2=0;
}


//********************************************************************************
//* Destructor
//********************************************************************************
CTransparentWnd::~CTransparentWnd()
{
	KillTimer(1);
	
	//AfxPostQuitMessage(0);
	
}


BEGIN_MESSAGE_MAP(CTransparentWnd, CWnd)
//{{AFX_MSG_MAP(CTransparentWnd)
ON_WM_PAINT()
ON_WM_ERASEBKGND()
ON_WM_LBUTTONDOWN()
ON_WM_TIMER()
ON_COMMAND(ID_MIN_ICON, OnMinIcon)
ON_WM_CONTEXTMENU()
ON_COMMAND(ID_CLOSE, OnClose)
//}}AFX_MSG_MAP
ON_MESSAGE(WM_LIBEN,OnLiben)
END_MESSAGE_MAP()


//********************************************************************************
//* CreateTransparent()
//*
//* Creates the main application window transparent
//********************************************************************************

void CTransparentWnd::CreateTransparent(LPCTSTR pTitle)
{
	FindBmpFile(GetCurPath());
    CDib dib(m_szBmpFile);
	
	CRect rect(0,0,dib.m_nWidth,dib.m_nHeight);
	
	
	CreateEx(	WS_EX_TOOLWINDOW,
		AfxRegisterWndClass(0),
		pTitle,
		WS_POPUP | WS_SYSMENU|WS_EX_TOOLWINDOW,
		rect,
		NULL,
		NULL,
		NULL );
	SetupRegion(GetWindowDC());
	//m_BitmapID = BitmapID;
	SetTimer(1,100,NULL);
	
    NOTIFYICONDATA tnd;	
	
	tnd.cbSize=sizeof(NOTIFYICONDATA);
	
	tnd.hWnd=this->m_hWnd;
	
	tnd.uID=IDR_MAINFRAME;
	
	tnd.uFlags=NIF_MESSAGE|NIF_ICON|NIF_TIP;
	
	tnd.uCallbackMessage=WM_LIBEN;
	
	tnd.hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));
	
	strcpy(tnd.szTip,"提示信息");
	
	Shell_NotifyIcon(NIM_ADD,&tnd);
	
	SetWindowPos(
		(GetExStyle() & WS_EX_TOPMOST) ? &CWnd::wndNoTopMost : &CWnd::wndTopMost,
		0,0,0,0,
		SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE);
	
	HCURSOR hCursor;
	
	// Load a cursor resource that was originally created using
	hCursor = AfxGetApp()->LoadCursor(IDC_CURSOR1);
	SetCursor(hCursor);	

	//加入WS_EX_LAYERED扩展属性
	SetWindowLong(this->GetSafeHwnd(),GWL_EXSTYLE,
		GetWindowLong(this->GetSafeHwnd(),GWL_EXSTYLE)^0x80000);
	HINSTANCE hInst = LoadLibrary("User32.DLL"); 
	if(hInst) 
	{ 
		typedef BOOL (WINAPI *MYFUNC)(HWND,COLORREF,BYTE,DWORD); 
		MYFUNC fun = NULL;
		//取得SetLayeredWindowAttributes函数指针 
		fun=(MYFUNC)GetProcAddress(hInst, "SetLayeredWindowAttributes");
		if(fun)fun(this->GetSafeHwnd(),0,200,2); 
		FreeLibrary(hInst); 
	}
}


//********************************************************************************
//* SetupRegion()
//*
//* Set the Window Region for transparancy outside the mask region
//********************************************************************************
void CTransparentWnd::SetupRegion(CDC *pDC)
{
	CDC					memDC;
	CBitmap			cBitmap;
	CBitmap*		pOldMemBmp = NULL;
	COLORREF		col,maskcol;
	CRect				cRect;
	int					x, y;
	CRgn				wndRgn, rgnTemp;
    int sum;
	GetWindowRect(&cRect);
	
	//cBitmap.LoadBitmap(MaskID);
	LoadBMPImage(m_szBmpFile,cBitmap,NULL);
	memDC.CreateCompatibleDC(pDC);
	pOldMemBmp = memDC.SelectObject(&cBitmap);
	
	wndRgn.CreateRectRgn(0, 0, cRect.Width(), cRect.Height());
	
	maskcol=memDC.GetPixel(0, 0);
	for(x=0; x<=cRect.Width(); x++)
	{
		for(y=0; y<=cRect.Height(); y++)
		{
			col = memDC.GetPixel(x, y);
			if(col ==maskcol)
			{
				rgnTemp.CreateRectRgn(x, y, x+1, y+1);
				wndRgn.CombineRgn(&wndRgn, &rgnTemp, RGN_XOR);
				rgnTemp.DeleteObject();	
			}
			else if (col==0)
			{
				//判断数字的起始黑点
				
				sum=0;
				for(int k=0;k<25;k++) 
				{
					sum=sum+memDC.GetPixel(x, y+k)+memDC.GetPixel(x+109, y+k);
					if (sum!=0)
						break;
				}
				if (sum==0)     //得到起始点x,y
				{
					m_nNumX=x;
					m_nNumY=y;
				}
			}
			
		}
	}
	if (pOldMemBmp) memDC.SelectObject(pOldMemBmp);
	LoadBMPImage(m_szNumFile,m_mapB,NULL);
	SetWindowRgn((HRGN)wndRgn, TRUE);
}

//********************************************************************************
//* CTransparentWnd message handlers
//********************************************************************************

void CTransparentWnd::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CWnd::OnLButtonDown(nFlags, point);
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x,point.y));
}

BOOL CTransparentWnd::OnEraseBkgnd(CDC* pDC) 
{
	CRect	rect;
	GetWindowRect(&rect);
	
	CDC memDC;
	CBitmap			cBitmap;
	CBitmap*		pOldMemBmp = NULL;
	
	LoadBMPImage(m_szBmpFile,cBitmap,NULL);
	memDC.CreateCompatibleDC(pDC);
	pOldMemBmp = memDC.SelectObject(&cBitmap);
	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);
	
	if (pOldMemBmp) memDC.SelectObject( pOldMemBmp );	
	
	return TRUE;
}

//********************************************************************************
//   draw the current time
//********************************************************************************
void CTransparentWnd::OnPaint()
{
	CPaintDC dc(this);
	
	CDC mapDC;
	mapDC.CreateCompatibleDC( &dc );
	CBitmap* pOB = mapDC.SelectObject( &m_mapB );
	
	dc.BitBlt( m_nNumX, m_nNumY, 2, 25, &mapDC, 160, 0, SRCCOPY );
    
	dc.BitBlt( m_nNumX+70, m_nNumY, 8, 25, &mapDC, 150, 0, SRCCOPY );
    //秒
	dc.BitBlt( m_nNumX+78, m_nNumY, 15, 25, &mapDC, m_ns1*15, 0, SRCCOPY );
	dc.BitBlt( m_nNumX+93, m_nNumY, 15, 25, &mapDC, m_ns2*15, 0, SRCCOPY );
    //时
	dc.BitBlt( m_nNumX+2, m_nNumY, 15, 25, &mapDC, m_nh1*15, 0, SRCCOPY );
	dc.BitBlt( m_nNumX+17, m_nNumY, 15, 25, &mapDC, m_nh2*15, 0, SRCCOPY );
	//:
	dc.BitBlt( m_nNumX+32, m_nNumY, 8, 25, &mapDC, 150, 0, SRCCOPY );
    //分
	dc.BitBlt( m_nNumX+40, m_nNumY, 15, 25, &mapDC, m_nm1*15, 0, SRCCOPY );
	dc.BitBlt( m_nNumX+55, m_nNumY, 15, 25, &mapDC, m_nm2*15, 0, SRCCOPY );
	//:	
	dc.BitBlt( m_nNumX+108, m_nNumY, 2, 25, &mapDC, 150, 0, SRCCOPY );
	
	mapDC.SelectObject( pOB );	
}

//********************************************************************************
//   Get the Current time then set value the mambervar
//   If the time changed ,repaint it,otherwise return
//********************************************************************************
void CTransparentWnd::OnTimer(UINT_PTR nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CTime ctCurrentTime;
	ctCurrentTime = CTime::GetCurrentTime();
	int h=ctCurrentTime.GetHour();
	//int y=ctCurrentTime.GetYear();
	//int m=ctCurrentTime.GetMonth();
	//int d=ctCurrentTime.GetDay();
	int f=ctCurrentTime.GetMinute();
	int s=ctCurrentTime.GetSecond();
	if (m_nSecond==s)
		return;
	else
		m_nSecond=s;
	
	m_ns1=m_nSecond/10;
	m_ns2=m_nSecond%10;
	
	m_nh1=h/10;
	m_nh2=h%10;
	
	
	m_nm1=f/10;
	m_nm2=f%10;
	
	
	//只重绘时钟区域
	Invalidate(FALSE);
	
	CWnd::OnTimer(nIDEvent);
}

//********************************************************************************
//   the tray icon message loop
//********************************************************************************
LRESULT CTransparentWnd::OnLiben(WPARAM wParam,LPARAM lParam)
{	
	if(wParam!=IDR_MAINFRAME)
		return 0;
    switch(lParam)
    {
	case WM_RBUTTONUP://右键起来时弹出快捷菜单，这里只有一个“关闭”
		{
			
			LPPOINT lpoint=new tagPOINT;
			::GetCursorPos(lpoint);//得到鼠标位置
			CMenu *menu;
			CMenu PopMenu;
			PopMenu.LoadMenu(IDR_MENU_POPUP);
			menu = PopMenu.GetSubMenu (0);
			//确定弹出式菜单的位置
			menu->TrackPopupMenu(TPM_LEFTALIGN,lpoint->x,lpoint->y,this);
			//资源回收
			HMENU hmenu=menu->Detach();
			menu->DestroyMenu();
			delete lpoint;
		}
		break;
    case WM_LBUTTONDBLCLK://双击左键的处理
		{
			this->ShowWindow(SW_SHOW);//简单的显示主窗口完事儿
		}
		break;
    }
	return 0;
}

void CTransparentWnd::OnMinIcon() 
{
	ShowWindow(SW_HIDE);
}
//********************************************************************************
// Get the mouse pos and draw the pop menu
//********************************************************************************
void CTransparentWnd::OnContextMenu(CWnd* pWnd, CPoint point) 
{
    CMenu PopMenu;
	CMenu *pMenu;
	
	LPPOINT lpoint=new tagPOINT;
	::GetCursorPos(lpoint);//得到鼠标位置
	
	CPoint pt;
	pt= point ;
	
	PopMenu.LoadMenu(IDR_MENU_POPUP);
	ClientToScreen (&pt);
	// show the menu (returns, when menu is closed again!)
	pMenu = PopMenu.GetSubMenu (0);
	pMenu->TrackPopupMenu (TPM_LEFTALIGN,lpoint->x,lpoint->y,this);
}
//********************************************************************************
// When the App exit,delete the tray icon
//********************************************************************************
void CTransparentWnd::OnClose() 
{
	NOTIFYICONDATA tnid;
	
	tnid.cbSize=sizeof(NOTIFYICONDATA);
	
	tnid.hWnd=this->m_hWnd;
	
	tnid.uID=IDR_MAINFRAME;//保证删除的是我们的图标
	
	Shell_NotifyIcon(NIM_DELETE,&tnid);
	
	SendMessage(WM_CLOSE,0,0);
}


BOOL CTransparentWnd::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}
