
// CExercise3aView.h: CCExercise3aView 클래스의 인터페이스
//

#pragma once


class CCExercise3aView : public CView
{
protected: // serialization에서만 만들어집니다.
	CCExercise3aView() noexcept;
	DECLARE_DYNCREATE(CCExercise3aView)

// 특성입니다.
public:
	CCExercise3aDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CCExercise3aView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	CString m_strStopWatch; // 출력되는 스톱워치 문자열을 저장할 변수
	CString m_strRecord[30]; // 기록된 내용을 저장하는 문자열 배열
	int m_nCount; // 기록된 내용의 변수
	int m_nMinute; // 분을 나타내는 변수
	int m_nSecond; // 초를 나타내는 변수
	int m_nMSecond; // 1/100초를 나타내는 변수
	bool m_bStopWatchRun; // 스톱워치가 작동되는지를 저장하는 변수
	

	void UpdateComboBox();
};

#ifndef _DEBUG  // CExercise3aView.cpp의 디버그 버전
inline CCExercise3aDoc* CCExercise3aView::GetDocument() const
   { return reinterpret_cast<CCExercise3aDoc*>(m_pDocument); }
#endif

