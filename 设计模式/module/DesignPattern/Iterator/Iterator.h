
/********************************************************************
	CREATED:	2012/01/31
	FILENAME:	Iterator.h
	AUTHOR:		By Robot
	
	PURPOSE:	������ģʽ
		������Ҫ����һ���ۼ����󣬶��Ҳ�����Щ������ʲô����Ҫ������ʱ��
		���Ӧ�ÿ���ʹ�õ�����ģʽ��Ϊ������ͬ�ľۼ��ṹ�ṩ�磺��ʼ����һ����
		�Ƿ��������ǰ��һ���ͳһ�Ľӿڡ�
*********************************************************************/


#ifndef __ITERATOR_H__
#define __ITERATOR_H__

#include <iostream>
using std::cout;
using std::endl;

typedef int DATA;

class Aggregate;

/**
	������������
*/
class Iterator
{
public:
	Iterator(){}
	virtual ~Iterator(){}
	// �����׼ͨ�ýӿ�
	virtual void MoveToFirst() = 0;		//!< ָ���һ��
	virtual void MoveToNext() = 0;		//!< ָ��ǰ����һ��
	virtual bool IsEnd() = 0;			//!< �жϵ�ǰ�Ƿ���������Endλ��
	virtual DATA CurrentItem() = 0;		//!< ��ȡ��ǰԪ��
};


/**
	�����������
*/
class ConcreateIterater : public Iterator
{
public:
	ConcreateIterater(Aggregate* pAggregate);
	~ConcreateIterater();
	void MoveToFirst();
	void MoveToNext();
	bool IsEnd();
	DATA CurrentItem();
private:
	Aggregate* m_pAggreatate;
	int m_iCurrPosition;
};


#endif
