
// DragAndDropView.cpp: CDragAndDropView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "DragAndDrop.h"
#endif

#include "DragAndDropDoc.h"
#include "DragAndDropView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDragAndDropView

IMPLEMENT_DYNCREATE(CDragAndDropView, CView)

BEGIN_MESSAGE_MAP(CDragAndDropView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CDragAndDropView 생성/소멸

CDragAndDropView::CDragAndDropView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_strOutput = _T("");
	m_ptLocation = (0, 0);
	m_bDrag = false;
}

CDragAndDropView::~CDragAndDropView()
{
}

BOOL CDragAndDropView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CDragAndDropView 그리기

void CDragAndDropView::OnDraw(CDC* pDC)
{
	CDragAndDropDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	pDC->TextOut(m_ptLocation.x, m_ptLocation.y, m_strOutput);
}


// CDragAndDropView 인쇄

BOOL CDragAndDropView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CDragAndDropView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CDragAndDropView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CDragAndDropView 진단

#ifdef _DEBUG
void CDragAndDropView::AssertValid() const
{
	CView::AssertValid();
}

void CDragAndDropView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDragAndDropDoc* CDragAndDropView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDragAndDropDoc)));
	return (CDragAndDropDoc*)m_pDocument;
}
#endif //_DEBUG


// CDragAndDropView 메시지 처리기


void CDragAndDropView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	int nCharIndex;
	nCharIndex = m_strOutput.GetLength();
	
	if (nChar == VK_BACK)
	{
		m_strOutput.Delete(nCharIndex - 1, 1);
	}
	else
	{
		m_strOutput += (WCHAR)nChar;
	}

	Invalidate();
	CView::OnChar(nChar, nRepCnt, nFlags);
}


void CDragAndDropView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	switch (nChar)
	{
	case VK_LEFT:
		m_ptLocation.x--;
		break;
	case VK_RIGHT:
		m_ptLocation.x++;
		break;
	case VK_UP:
		m_ptLocation.y--;
		break;
	case VK_DOWN:
		m_ptLocation.y++;
		break;
	case VK_PRIOR:
		m_ptLocation.y -= 50;
		break;
	case VK_NEXT:
		m_ptLocation.y += 50;
		break;
	case VK_HOME:
		m_ptLocation = CPoint(0, 0);
		break;
	}

	if (m_ptLocation.x < 0)
	{
		m_ptLocation.x = 0;
		AfxMessageBox(_T("왼쪽으로 더이상 이동할 수 없습니다."));
	}
	if (m_ptLocation.y < 0)
	{
		m_ptLocation.y = 0;
		AfxMessageBox(_T("위쪽으로 더이상 이동할 수 없습니다."));
	}
	if (m_ptLocation.x > m_ptClientSize.x)
	{
		m_ptLocation.x = m_ptClientSize.x;
		AfxMessageBox(_T("오른쪽으로 더이상 이동할 수 없습니다."));
	}
	if (m_ptLocation.y > m_ptClientSize.y)
	{
		m_ptLocation.y = m_ptClientSize.y;
		AfxMessageBox(_T("아래쪽으로 더이상 이동할 수 없습니다."));
	}
	Invalidate();
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CDragAndDropView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	m_ptClientSize.x = cx;
	m_ptClientSize.y = cy;
	
	Invalidate();
}


void CDragAndDropView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (point.x >= m_ptLocation.x - 30 && point.x <= m_ptLocation.x + 30 &&
		point.y >= m_ptLocation.y - 30 && point.y <= m_ptLocation.y + 30)
	{
		m_bDrag = true;
	}
	m_ptLocation = point;
	Invalidate();
	CView::OnLButtonDown(nFlags, point);
}


void CDragAndDropView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_bDrag)
	{
		m_ptLocation = point; 
	}
	Invalidate();
	CView::OnMouseMove(nFlags, point);
}


void CDragAndDropView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_bDrag)
	{
		m_bDrag = false;
		m_ptLocation = point;
	}
	Invalidate();
	CView::OnLButtonUp(nFlags, point);
}


void CDragAndDropView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_strOutput.IsEmpty() == false)
	{
		if (AfxMessageBox(_T("문자열을 모두 지우시겠습니까?"), MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			m_strOutput.Empty();
		}
	}
	else
	{
		AfxMessageBox(_T("문자열을 입력하시오."));
	}
	Invalidate();
	CView::OnRButtonDown(nFlags, point);
}
