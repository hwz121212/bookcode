// vfwappDoc.h : CvfwappDoc ��Ľӿ�
//


#pragma once


class CvfwappDoc : public CDocument
{
protected: // �������л�����
	CvfwappDoc();
	DECLARE_DYNCREATE(CvfwappDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CvfwappDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


