// vfwappView.h : CvfwappView ��Ľӿ�
//


#pragma once
#include <vfw.h>

class CvfwappView : public CView
{
protected: // �������л�����
	CvfwappView();
	DECLARE_DYNCREATE(CvfwappView)

// ����
public:
	CvfwappDoc* GetDocument() const;

// ����
public:
	HDRAWDIB m_hdd;
// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ʵ��
public:
	virtual ~CvfwappView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // vfwappView.cpp �еĵ��԰汾
inline CvfwappDoc* CvfwappView::GetDocument() const
   { return reinterpret_cast<CvfwappDoc*>(m_pDocument); }
#endif

