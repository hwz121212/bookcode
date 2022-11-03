// cadView.cpp : implementation of the CCadView class
//

#include "stdafx.h"
#include "cad.h"

#include "cadDoc.h"
#include "cadView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCadView

IMPLEMENT_DYNCREATE(CCadView, CView)

BEGIN_MESSAGE_MAP(CCadView, CView)
	//{{AFX_MSG_MAP(CCadView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(IDD_LINE, OnLine)
	ON_COMMAND(IDD_RECTANGLE, OnRectangle)
	ON_COMMAND(IDD_TRANGLE, OnTriangle)
	ON_COMMAND(IDD_ELLIPSE, OnEllipse)
	ON_COMMAND(IDD_SELECT, OnSelect)
	ON_COMMAND(IDD_REDO, OnRedo)
	ON_COMMAND(IDD_UNDO, OnUndo)
	ON_UPDATE_COMMAND_UI(IDD_UNDO, OnUpdateUndo)
	ON_UPDATE_COMMAND_UI(IDD_REDO, OnUpdateRedo)
	ON_UPDATE_COMMAND_UI(IDD_LINE, OnUpdateLine)
	ON_UPDATE_COMMAND_UI(IDD_TRANGLE, OnUpdateTrangle)
	ON_UPDATE_COMMAND_UI(IDD_RECTANGLE, OnUpdateRectangle)
	ON_UPDATE_COMMAND_UI(IDD_ELLIPSE, OnUpdateEllipse)
	ON_COMMAND(IDD_PENTAGON, OnPentagon)
	ON_UPDATE_COMMAND_UI(IDD_PENTAGON, OnUpdatePentagon)
	ON_COMMAND(IDD_PENTAGRAM, OnPentagram)
	ON_UPDATE_COMMAND_UI(IDD_PENTAGRAM, OnUpdatePentagram)
	ON_COMMAND(IDD_RIGHTTRIANGLE, OnRighttriangle)
	ON_UPDATE_COMMAND_UI(IDD_RIGHTTRIANGLE, OnUpdateRighttriangle)
	ON_COMMAND(IDD_CIRCLE, OnCircle)
	ON_UPDATE_COMMAND_UI(IDD_CIRCLE, OnUpdateCircle)
	ON_COMMAND(IDD_PARALLELOGRAM, OnParallelogram)
	ON_UPDATE_COMMAND_UI(IDD_PARALLELOGRAM, OnUpdateParallelogram)
	ON_COMMAND(IDD_DIAMOND, OnDiamond)
	ON_UPDATE_COMMAND_UI(IDD_DIAMOND, OnUpdateDiamond)
	ON_COMMAND(IDD_LADDER, OnLadder)
	ON_UPDATE_COMMAND_UI(IDD_LADDER, OnUpdateLadder)
	ON_COMMAND(IDD_HEXAGONAL, OnHexagonal)
	ON_UPDATE_COMMAND_UI(IDD_HEXAGONAL, OnUpdateHexagonal)
	ON_COMMAND(IDD_ARC, OnArc)
	ON_UPDATE_COMMAND_UI(IDD_ARC, OnUpdateArc)
	ON_COMMAND(ID_CUBE, OnCube)
	ON_UPDATE_COMMAND_UI(ID_CUBE, OnUpdateCube)
	ON_COMMAND(ID_TETRAHEDRON, OnTetrahedron)
	ON_UPDATE_COMMAND_UI(ID_TETRAHEDRON, OnUpdateTetrahedron)
	ON_COMMAND(ID_MITSUBISHI, OnMitsubishi)
	ON_UPDATE_COMMAND_UI(ID_MITSUBISHI, OnUpdateMitsubishi)
	ON_COMMAND(ID_CYLINDER, OnCylinder)
	ON_UPDATE_COMMAND_UI(ID_CYLINDER, OnUpdateCylinder)
	ON_COMMAND(ID_SPHERE, OnSphere)
	ON_UPDATE_COMMAND_UI(ID_SPHERE, OnUpdateSphere)
	ON_COMMAND(ID_OCTA, OnOcta)
	ON_UPDATE_COMMAND_UI(ID_OCTA, OnUpdateOcta)
	ON_COMMAND(ID_RYOTAI, OnRyotai)
	ON_UPDATE_COMMAND_UI(ID_RYOTAI, OnUpdateRyotai)
	ON_COMMAND(ID_CONE, OnCone)
	ON_UPDATE_COMMAND_UI(ID_CONE, OnUpdateCone)
	ON_UPDATE_COMMAND_UI(IDD_SELECT, OnUpdateSelect)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_COMMAND(ID_EDIT_UNDO, &CCadView::OnEditUndo)
	ON_COMMAND(ID_EDIT_REDO, &CCadView::OnEditRedo)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCadView construction/destruction

CCadView::CCadView()
{
	m_nShapeType = 0;
	m_pCommand = NULL;
}

CCadView::~CCadView()
{
}

BOOL CCadView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCadView drawing

void CCadView::OnDraw(CDC* pDC)
{
	CMemDC memDC(pDC);
	CCadDoc* pDoc = GetDocument();
	CShape* pShape = NULL;
	ASSERT_VALID(pDoc);
	POSITION ps = pDoc->m_ShapeCollection.m_list.GetHeadPosition();
	while(ps)
	{
		pShape = (CShape *)pDoc->m_ShapeCollection.m_list.GetNext(ps);
		if (pShape)
		{
			pShape->Draw(&memDC);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CCadView printing

BOOL CCadView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCadView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCadView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CCadView diagnostics

#ifdef _DEBUG
void CCadView::AssertValid() const
{
	CView::AssertValid();
}

void CCadView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCadDoc* CCadView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCadDoc)));
	return (CCadDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCadView message handlers

void CCadView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	SetCapture();
	m_pCommand = CreateCommand();
	
	if (m_pCommand)
	{
		m_CommandManager.DoCommand(m_pCommand);
		m_pCommand->OnLButtonDown(nFlags, point);
	}
	CView::OnLButtonDown(nFlags, point);
}

void CCadView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (m_pCommand)
	{
		m_pCommand->OnLButtonUp(nFlags, point);
	}
	ReleaseCapture();
	CView::OnLButtonUp(nFlags, point);
}

void CCadView::OnMouseMove(UINT nFlags, CPoint point) 
{
	if ((MK_LBUTTON & nFlags) == 0)
	{
		return;
	}
	if (m_pCommand)
	{
		m_pCommand->OnMouseMove(nFlags, point);
	}

	Invalidate(FALSE);
	CView::OnMouseMove(nFlags, point);
}

void CCadView::OnLine() 
{
	m_nShapeType = type_line;
}

void CCadView::OnRectangle() 
{
	m_nShapeType = type_rectangle;
}

void CCadView::OnTriangle() 
{
	m_nShapeType = type_triangle;
}

void CCadView::OnEllipse() 
{
	m_nShapeType = type_ellipse;
}

void CCadView::OnSelect() 
{
	m_nShapeType = type_select;
	
}

CICommand* CCadView::CreateCommand()
{
	CCadDoc* pDoc = GetDocument();
	ASSERT(pDoc);
	CICommand* pCommand = NULL;
	switch (m_nShapeType)
	{
	case type_select:
		break;
	case type_line:
		pCommand = new CLineCommand(pDoc);
		break;
	case type_rectangle:
		pCommand = new CRectangleCommand(pDoc);
		break;
	case type_triangle:
		pCommand = new CTriangleCommand(pDoc);
		break;
	case type_ellipse:
		pCommand = new CEllipseCommand(pDoc);
		break;
	case type_pentagon:
		pCommand = new CPentagonCommand(pDoc);
		break;
	case type_pentagram:
		pCommand = new CPentagramCommand(pDoc);
		break;
	case type_righttriangle:
		pCommand = new CRightTriangleCommand(pDoc);
		break;
	case type_circle:
		pCommand = new CCircleCommand(pDoc);
		break;
	case type_parallelogram:
		pCommand = new CParallelogramCommand(pDoc);
		break;
	case type_diamond:
		pCommand = new CDiamondCommand(pDoc);
		break;
	case type_ladder:
		pCommand = new CLadderCommand(pDoc);
		break;
	case type_hexagonal:
		pCommand = new CHexagonalCommand(pDoc);
		break;
	case type_arc:
		pCommand = new CArcCommand(pDoc);
		break;
	case type_cube:
		pCommand = new CCubeCommand(pDoc);
		break;
	case type_tetrahedron:
		pCommand = new CTetrahedronCommand(pDoc);
		break;
	case type_mitsubishi:
		pCommand = new CMitsubishiCommand(pDoc);
		break;
	case type_cylinder:
		pCommand = new CCylinderCommand(pDoc);
		break;
	case type_sphere:
		pCommand = new CSphereCommand(pDoc);
		break;
	case type_octa:
		pCommand = new COctaCommand(pDoc);
		break;
	case type_ryotai:
		pCommand = new CRyotaiCommand(pDoc);
		break;
	case type_cone:
		pCommand = new CConeCommand(pDoc);
		break;
	default:
		pCommand = NULL;
		break;
	}
	return pCommand;
}

void CCadView::OnRedo() 
{
	if (m_CommandManager.CanRedo())
	{
		m_CommandManager.Redo();
		Invalidate(FALSE);
	}
}

void CCadView::OnUndo() 
{
	if (m_CommandManager.CanUndo())
	{
		m_CommandManager.Undo();
		Invalidate(FALSE);
	}
}

void CCadView::OnUpdateUndo(CCmdUI* pCmdUI) 
{
	BOOL bRet = m_CommandManager.CanUndo();
	pCmdUI->Enable(bRet);
}

void CCadView::OnUpdateRedo(CCmdUI* pCmdUI) 
{
	BOOL bRet = m_CommandManager.CanRedo();
	pCmdUI->Enable(bRet);
}

void CCadView::OnUpdateLine(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck((m_nShapeType == type_line) ? TRUE : FALSE);
	
}

void CCadView::OnUpdateTrangle(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck((m_nShapeType == type_triangle) ? TRUE : FALSE);
}

void CCadView::OnUpdateRectangle(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck((m_nShapeType == type_rectangle) ? TRUE : FALSE);
}

void CCadView::OnUpdateEllipse(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck((m_nShapeType == type_ellipse) ? TRUE : FALSE);
	
}

void CCadView::OnPentagon() 
{
	m_nShapeType = type_pentagon;	
}

void CCadView::OnUpdatePentagon(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck((m_nShapeType == type_pentagon) ? TRUE : FALSE);
	
}

void CCadView::OnPentagram() 
{
	m_nShapeType = type_pentagram;	
}

void CCadView::OnUpdatePentagram(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck((m_nShapeType == type_pentagram) ? TRUE : FALSE);
	
}

void CCadView::OnRighttriangle() 
{
	m_nShapeType = type_righttriangle;
}

void CCadView::OnUpdateRighttriangle(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck((m_nShapeType == type_righttriangle) ? TRUE : FALSE);
	
}

void CCadView::OnCircle() 
{
	m_nShapeType = type_circle;
	
}

void CCadView::OnUpdateCircle(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck((type_circle == m_nShapeType) ? TRUE : FALSE);
	
}

void CCadView::OnParallelogram() 
{
	m_nShapeType = type_parallelogram;
	
}

void CCadView::OnUpdateParallelogram(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck((m_nShapeType == type_parallelogram) ? TRUE : FALSE);
	
}

void CCadView::OnDiamond() 
{
	m_nShapeType = type_diamond;
	
}

void CCadView::OnUpdateDiamond(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck((m_nShapeType == type_diamond) ? TRUE : FALSE);
}

void CCadView::OnLadder() 
{
	m_nShapeType = type_ladder;
}

void CCadView::OnUpdateLadder(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck((m_nShapeType == type_ladder) ? TRUE : FALSE);
	
}

void CCadView::OnHexagonal() 
{
	m_nShapeType = type_hexagonal;
	
}

void CCadView::OnUpdateHexagonal(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck((m_nShapeType == type_hexagonal) ? TRUE : FALSE);
	
}

void CCadView::OnArc() 
{
	m_nShapeType = type_arc;
}

void CCadView::OnUpdateArc(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck((m_nShapeType == type_arc) ? TRUE : FALSE);
	
}

void CCadView::OnCube() 
{
	m_nShapeType = type_cube;
	
}

void CCadView::OnUpdateCube(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck((m_nShapeType == type_cube) ? TRUE : FALSE);
}

void CCadView::OnTetrahedron() 
{
	m_nShapeType = type_tetrahedron;
	
}

void CCadView::OnUpdateTetrahedron(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck((m_nShapeType == type_tetrahedron) ? TRUE : FALSE);
	
}

void CCadView::OnMitsubishi() 
{
	m_nShapeType = type_mitsubishi;
	
}

void CCadView::OnUpdateMitsubishi(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck((m_nShapeType == type_mitsubishi) ? TRUE : FALSE);
	
}

void CCadView::OnCylinder() 
{
	m_nShapeType = type_cylinder;
	
}

void CCadView::OnUpdateCylinder(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck((m_nShapeType == type_cylinder) ? TRUE : FALSE);
	
}

void CCadView::OnSphere() 
{
	m_nShapeType = type_sphere;
	
}

void CCadView::OnUpdateSphere(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck((m_nShapeType == type_sphere) ? TRUE : FALSE);
	
}

void CCadView::OnOcta() 
{
	m_nShapeType = type_octa;
	
}

void CCadView::OnUpdateOcta(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck((m_nShapeType == type_octa) ? TRUE : FALSE);
	
}

void CCadView::OnRyotai() 
{
	m_nShapeType = type_ryotai;
	
}

void CCadView::OnUpdateRyotai(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck((m_nShapeType == type_ryotai) ? TRUE : FALSE);	
}

void CCadView::OnCone() 
{
	m_nShapeType = type_cone;
	
}

void CCadView::OnUpdateCone(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck((m_nShapeType == type_cone) ? TRUE : FALSE);	
}

void CCadView::OnUpdateSelect(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck((m_nShapeType == type_select) ? TRUE : FALSE);
}


void CCadView::OnEditUndo()
{
	m_CommandManager.Undo();
	Invalidate(FALSE);
}


void CCadView::OnEditRedo()
{
	m_CommandManager.Redo();
	Invalidate(FALSE);
}
