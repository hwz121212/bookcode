#pragma once

#define RYG_SETSTATE WM_USER + 0
#define RYG_GETSTATE WM_USER + 1

LRESULT CALLBACK AFX_EXPORT
    RygWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

// CRygWnd

class CRygWnd : public CWnd
{
	DECLARE_DYNAMIC(CRygWnd)


private:
    int m_nState; // 0=off, 1=red, 2=yellow, 3=green

    static CRect  s_rect;
    static CPoint s_point;
    static CRect  s_rColor[3];
    static CBrush s_bColor[4];

public:
    static BOOL RegisterWndClass(HINSTANCE hInstance);


public:
	CRygWnd();
	virtual ~CRygWnd();

private:
    void SetMapping(CDC* pDC);
    void UpdateColor(CDC* pDC, int n);

protected:
	afx_msg LRESULT OnSetState(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnGetState(WPARAM wParam, LPARAM lParam);
    DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
protected:
	virtual void PostNcDestroy();
};


