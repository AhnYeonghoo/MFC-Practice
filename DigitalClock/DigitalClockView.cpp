
// DigitalClockView.cpp: CDigitalClockView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "DigitalClock.h"
#endif

#include "DigitalClockDoc.h"
#include "DigitalClockView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDigitalClockView

IMPLEMENT_DYNCREATE(CDigitalClockView, CView)

BEGIN_MESSAGE_MAP(CDigitalClockView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CDigitalClockView 생성/소멸

CDigitalClockView::CDigitalClockView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_bTimerRun = false;
	m_bTimerType = true;

}

CDigitalClockView::~CDigitalClockView()
{
}

BOOL CDigitalClockView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CDigitalClockView 그리기

void CDigitalClockView::OnDraw(CDC* pDC)
{
	CDigitalClockDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	CRect rect;
	GetClientRect(&rect);
	
	pDC->DrawText(m_strTimer, rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);


	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CDigitalClockView 인쇄

BOOL CDigitalClockView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CDigitalClockView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CDigitalClockView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CDigitalClockView 진단

#ifdef _DEBUG
void CDigitalClockView::AssertValid() const
{
	CView::AssertValid();
}

void CDigitalClockView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDigitalClockDoc* CDigitalClockView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDigitalClockDoc)));
	return (CDigitalClockDoc*)m_pDocument;
}
#endif //_DEBUG


// CDigitalClockView 메시지 처리기


int CDigitalClockView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	SetTimer(0, 1000, NULL);
	m_bTimerRun = TRUE;
	return 0;
}


void CDigitalClockView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	int hour;
	CString str;
	CTime timer;
	timer = CTime::GetCurrentTime();
	
	if (m_bTimerType)
	{
		m_strTimer.Format(_T("현재는 %d년 %d월 %d일 %d시 %d분 %d초"),
			timer.GetYear(), timer.GetMonth(), timer.GetDay(), timer.GetHour(), timer.GetMinute(), timer.GetSecond());
	} 
	else
	{
		hour = timer.GetHour();
		if (hour >= 12)
		{
			str = _T("PM");
			if (hour >= 13)
			{
				hour = hour - 12;
			}
		}
		else
		{
			str = _T("AM");
		}
		m_strTimer.Format(_T("지금은 %s %d시 %d분 %d초"), str, hour, timer.GetMinute(), timer.GetSecond());
		Invalidate();
	}
	CView::OnTimer(nIDEvent);
}


void CDigitalClockView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_bTimerType)
	{
		if (AfxMessageBox(_T("시, 분, 초 형태로 표시하시겠습니까?"), MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			m_bTimerType = false;
		}
	}
	else
	{
		if (AfxMessageBox(_T("년, 월, 일, 시, 분, 초 형태로 표시하시겠습니까?"), MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			m_bTimerType = true;
		}
	}
	CView::OnLButtonDown(nFlags, point);
}


void CDigitalClockView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_bTimerRun == false)
	{
		if (AfxMessageBox(_T("디지털시계를 동작시키겠습니까?"), MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			SetTimer(0, 1000, NULL);
			m_bTimerRun = true;
		}
	}
	else
	{
		if (AfxMessageBox(_T("정말로 디지털시계 동작을 멈추겠습니까?"), MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			KillTimer(0);
			m_bTimerRun = false;
		}
	}
	CView::OnRButtonDown(nFlags, point);
}


void CDigitalClockView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (m_bTimerRun)
		KillTimer(0);
}
