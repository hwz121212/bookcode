// Shape.h: interface for the CShape class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHAPE_H__44A48389_CF20_4302_A823_EFE4C85B2745__INCLUDED_)
#define AFX_SHAPE_H__44A48389_CF20_4302_A823_EFE4C85B2745__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum ENUM_SHAPE_TYPE
{
	type_select = 1,
	type_line,
	type_rectangle,
	type_ellipse,
	type_triangle,
	type_pentagon, 
	type_pentagram, 
	type_righttriangle,
	type_circle,
	type_parallelogram,
	type_diamond,
	type_ladder,
	type_hexagonal,
	type_arc, 
	type_cube,
	type_tetrahedron,
	type_mitsubishi,
	type_cylinder,
	type_sphere,
	type_octa,
	type_ryotai,
	type_cone

};
class CShape : public CObject  
{
protected:
	Point m_ptStart;
	Point m_ptEnd;
public:
	
	virtual void Draw(CDC* pDC) = 0;
	CShape();
	virtual ~CShape();
	virtual void OnLButtonDown(UINT nFlags, CPoint point) = 0;
	virtual void OnLButtonUp(UINT nFlags, CPoint point) = 0;
	virtual void OnMouseMove(UINT nFlags, CPoint point) = 0;
	virtual Rect GetRectBound() = 0;
	


};

#endif // !defined(AFX_SHAPE_H__44A48389_CF20_4302_A823_EFE4C85B2745__INCLUDED_)
