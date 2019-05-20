
// IppCreateView.cpp : CIppCreateView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "IppCreate.h"
#endif

#include "IppCreateDoc.h"
#include "IppCreateView.h"

#include "IppDib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CIppCreateView

IMPLEMENT_DYNCREATE(CIppCreateView, CView)

BEGIN_MESSAGE_MAP(CIppCreateView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CIppCreateView ����/�Ҹ�

CIppCreateView::CIppCreateView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CIppCreateView::~CIppCreateView()
{
}

BOOL CIppCreateView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CIppCreateView �׸���

void CIppCreateView::OnDraw(CDC* /*pDC*/)
{
	CIppCreateDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CIppCreateView �μ�

BOOL CIppCreateView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CIppCreateView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CIppCreateView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CIppCreateView ����

#ifdef _DEBUG
void CIppCreateView::AssertValid() const
{
	CView::AssertValid();
}

void CIppCreateView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CIppCreateDoc* CIppCreateView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CIppCreateDoc)));
	return (CIppCreateDoc*)m_pDocument;
}
#endif //_DEBUG


// CIppCreateView �޽��� ó����


void CIppCreateView::OnLButtonDown(UINT nFlags, CPoint point)
{
	IppDib dib;
	dib.Load("lenna.bmp");

	CClientDC dc(this);
	dib.Draw(dc.m_hDC, point.x, point.y);

	CView::OnLButtonDown(nFlags, point);
}
