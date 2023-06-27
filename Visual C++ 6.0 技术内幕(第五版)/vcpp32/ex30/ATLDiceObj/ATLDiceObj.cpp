// ATLDiceObj.cpp : Implementation of CATLDiceObj

#include "stdafx.h"
#include "Atldicesrvr.h"
#include "ATLDiceObj.h"

/////////////////////////////////////////////////////////////////////////////
// CATLDiceObj


BOOL CATLDiceObj::LoadBitmaps() {
   int i;
   BOOL bSuccess = TRUE;
   int nID = IDB_DICE1;

   switch(m_nDiceColor) {
      case 0:
         nID = IDB_DICE1;
         break;
         
      case 1:
         nID = IDB_BLUEDICE1;
         break;

      case 2:
         nID = IDB_REDDICE1;
         break;

   }
     
   for(i=0; i<MAX_DIEFACES; i++) {
      DeleteObject(m_dieBitmaps[i]);
      m_dieBitmaps[i] = LoadBitmap(_Module.m_hInst, 
                                   MAKEINTRESOURCE(nID+i));
      if(!m_dieBitmaps[i]) {
          ::MessageBox(NULL, 
			           "Failed to load bitmaps",
			           NULL, 
					   MB_OK);
          bSuccess = FALSE;
      } 
   }
   OutputDebugString("Got to the LoadBitmaps functions\n");
   return bSuccess;
}

void CATLDiceObj::ShowFirstDieFace(ATL_DRAWINFO& di) {

   BITMAP bmInfo;
   GetObject(m_dieBitmaps[m_nFirstDieValue-1],
	         sizeof(bmInfo), &bmInfo);

   SIZE size;
   
   size.cx = bmInfo.bmWidth;
   size.cy = bmInfo.bmHeight;

   HDC hMemDC;
   hMemDC = CreateCompatibleDC(di.hdcDraw);

   HBITMAP hOldBitmap;
   HBITMAP hbm = m_dieBitmaps[m_nFirstDieValue-1];
   hOldBitmap = (HBITMAP)SelectObject(hMemDC, hbm); 

   if (hOldBitmap == NULL)
      return;     // destructors will clean up

   BitBlt(di.hdcDraw,
          di.prcBounds->left+1,
          di.prcBounds->top+1,
          size.cx,
          size.cy,
          hMemDC, 0,
          0,
          SRCCOPY);

   SelectObject(di.hdcDraw, hOldBitmap);

   DeleteDC(hMemDC);
               
}

void CATLDiceObj::ShowSecondDieFace(ATL_DRAWINFO& di) {

   BITMAP bmInfo;
   GetObject(m_dieBitmaps[m_nFirstDieValue-1],
	         sizeof(bmInfo), &bmInfo);

   SIZE size;
   
   size.cx = bmInfo.bmWidth;
   size.cy = bmInfo.bmHeight;

   HDC hMemDC;
   hMemDC = CreateCompatibleDC(di.hdcDraw);

   HBITMAP hOldBitmap;
   HBITMAP hbm = m_dieBitmaps[m_nSecondDieValue-1];
   hOldBitmap = (HBITMAP)SelectObject(hMemDC, hbm); 

   if (hOldBitmap == NULL)
      return;     // destructors will clean up
   
   BitBlt(di.hdcDraw,
          di.prcBounds->left+size.cx + 2,
          di.prcBounds->top+1,
          size.cx,
          size.cy,
          hMemDC, 0,
          0,
          SRCCOPY);

   SelectObject(di.hdcDraw, hOldBitmap);

   DeleteDC(hMemDC);

}

STDMETHODIMP CATLDiceObj::RollDice()
{
	if(::IsWindow(m_hWnd)) {
	    SetTimer(1, 250);
	}
	return S_OK;
}


STDMETHODIMP CATLDiceObj::get_TimesToRoll(short *pVal)
{
	*pVal = m_nTimesToRoll;
	return S_OK;
}

STDMETHODIMP CATLDiceObj::put_TimesToRoll(short newVal)
{
	m_nTimesToRoll = newVal;
	return S_OK;
}

STDMETHODIMP CATLDiceObj::get_DiceColor(short *pVal)
{
	*pVal = m_nDiceColor;
	return S_OK;
}

STDMETHODIMP CATLDiceObj::put_DiceColor(short newVal)
{
	m_nDiceColor = newVal;
	LoadBitmaps();
	FireViewChange();
	return S_OK;
}

LRESULT CATLDiceObj::OnTimer(UINT msg, WPARAM wParam, 
				            LPARAM lParam, BOOL& bHandled) {

	if(m_nTimesRolled > m_nTimesToRoll) {
		m_nTimesRolled = 0;
		KillTimer(1);

		Fire_DiceRolled(m_nFirstDieValue, m_nSecondDieValue);

		if(m_nFirstDieValue == m_nSecondDieValue) {
			Fire_Doubles(m_nFirstDieValue);
		}

		if(m_nFirstDieValue == 1 &&
		   m_nSecondDieValue == 1) {
			Fire_SnakeEyes();
		}

	} else {
	    m_nFirstDieValue = (rand() % (MAX_DIEFACES)) + 1;
		m_nSecondDieValue = (rand() % (MAX_DIEFACES)) + 1;            
		FireViewChange();
		m_nTimesRolled++;
	}

	
	bHandled = TRUE;
	return 0;
}
