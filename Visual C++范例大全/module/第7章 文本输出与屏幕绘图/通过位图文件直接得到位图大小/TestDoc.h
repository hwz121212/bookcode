// TestDoc.h :  CTestDoc ��Ľӿ�
//


#pragma once

class CTestDoc : public CDocument
{
protected: // �������л�����
	CTestDoc();
	DECLARE_DYNCREATE(CTestDoc)

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
	virtual ~CTestDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


