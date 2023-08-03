
// Practice2bView.cpp: CPractice2bView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Practice2b.h"
#endif

#include "Practice2bDoc.h"
#include "Practice2bView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPractice2bView

IMPLEMENT_DYNCREATE(CPractice2bView, CView)

BEGIN_MESSAGE_MAP(CPractice2bView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CPractice2bView 생성/소멸

CPractice2bView::CPractice2bView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CPractice2bView::~CPractice2bView()
{
}

BOOL CPractice2bView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CPractice2bView 그리기

void CPractice2bView::OnDraw(CDC* pDC)
{
	CPractice2bDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	pDC->TextOut(10, 10, m_strWindowSize);
	CRect rect;
	GetClientRect(&rect);
	pDC->DrawText(m_strOutput, rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	pDC->TextOut(m_ptMouseMove.x, m_ptMouseMove.y, m_strMouseMove);
}


// CPractice2bView 인쇄

BOOL CPractice2bView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CPractice2bView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CPractice2bView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CPractice2bView 진단

#ifdef _DEBUG
void CPractice2bView::AssertValid() const
{
	CView::AssertValid();
}

void CPractice2bView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPractice2bDoc* CPractice2bView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPractice2bDoc)));
	return (CPractice2bDoc*)m_pDocument;
}
#endif //_DEBUG


// CPractice2bView 메시지 처리기


void CPractice2bView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	
	m_strWindowSize.Format(_T("윈도우 크기는 넓이 %d, 높이 %d입니다."), cx, cy);
	Invalidate();
}


void CPractice2bView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_bDrag = TRUE;
	m_strOutput = _T("왼쪽 마우스 버튼을 눌렀습니다.");
	Invalidate();
	
	CView::OnLButtonDown(nFlags, point);
	
}


void CPractice2bView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_strOutput = _T("오른쪽 마우스 버튼을 눌렀습니다");
	Invalidate();

	CView::OnRButtonDown(nFlags, point);
}


void CPractice2bView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_strOutput = _T("키보드를 눌렀습니다");
	Invalidate();
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CPractice2bView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_ptMouseMove = point;
	m_strMouseMove.Format(_T("X: %d, Y: %d"), point.x, point.y);

	if (m_bDrag == TRUE)
	{
		m_strOutput = _T("마우스를 드래그하고 있습니다.");
	}
	else
	{
		m_strOutput = _T("마우스를 이동 중 입니다.");
	}
	Invalidate();
	CView::OnMouseMove(nFlags, point);
}


void CPractice2bView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_bDrag = FALSE;
	CView::OnLButtonUp(nFlags, point);
}
