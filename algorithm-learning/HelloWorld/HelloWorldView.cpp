
// HelloWorldView.cpp : implementation of the CHelloWorldView class
//

#include "stdafx.h"
#include "HelloWorld.h"
#include <d2d1_1.h>
#include "HelloWorldDoc.h"
#include "HelloWorldView.h"
#include <d2d1effects.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

template<class Interface>
inline void
SafeRelease(Interface **ppInterfaceToRelease)
{
    if (*ppInterfaceToRelease != NULL)
    {
        (*ppInterfaceToRelease)->Release();

        (*ppInterfaceToRelease) = NULL;
    }
}

// CHelloWorldView

IMPLEMENT_DYNCREATE(CHelloWorldView, CView)

BEGIN_MESSAGE_MAP(CHelloWorldView, CView)
	ON_REGISTERED_MESSAGE(AFX_WM_DRAW2D, &CHelloWorldView::OnDraw2d)
END_MESSAGE_MAP()

// CHelloWorldView construction/destruction

using namespace D2D1;

CHelloWorldView::CHelloWorldView()
{
	// Initialize Direct2D
	EnableD2DSupport();
	m_pBlueBrush = new CD2DSolidColorBrush(GetRenderTarget(), ColorF(ColorF::RoyalBlue));
	m_pTextFormat = new CD2DTextFormat(GetRenderTarget(), _T("Gabriola"), 50);
	m_pTextFormat->Get()->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	m_pTextFormat->Get()->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
    m_pBitmap = new CD2DBitmap(GetRenderTarget(), L"c:\\temp\\avatar.jpg");
    m_pathGeometry = new CD2DPathGeometry(GetRenderTarget());
}

CHelloWorldView::~CHelloWorldView()
{
}

BOOL CHelloWorldView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CHelloWorldView drawing

void CHelloWorldView::OnDraw(CDC* /*pDC*/)
{
	CHelloWorldDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}

// CHelloWorldView diagnostics

#ifdef _DEBUG
void CHelloWorldView::AssertValid() const
{
	CView::AssertValid();
}

void CHelloWorldView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CHelloWorldDoc* CHelloWorldView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHelloWorldDoc)));
	return (CHelloWorldDoc*)m_pDocument;
}
#endif //_DEBUG


// CHelloWorldView message handlers

CD2DPathGeometry* CHelloWorldView::drawAvatar(float x, float y, float width, float height)
{
    CD2DPathGeometry* pPathGeometry = new CD2DPathGeometry(GetRenderTarget());
    pPathGeometry->Create(GetRenderTarget());
    ID2D1GeometrySink* pSink = pPathGeometry->Open();
    if (pSink)
    {
        pSink->SetFillMode(D2D1_FILL_MODE_WINDING);
        pSink->BeginFigure(
            D2D1::Point2F(x, y + width/2), // Start point of the top half circle
            D2D1_FIGURE_BEGIN_FILLED
            );

        // Add the top half circle
        pSink->AddArc(
            D2D1::ArcSegment(
            D2D1::Point2F(x + width, y), // end point of the top half circle, also the start point of the bottom half circle
            D2D1::SizeF(width / 2, width / 2), // radius
            0.0f, // rotation angle
            D2D1_SWEEP_DIRECTION_CLOCKWISE,
            D2D1_ARC_SIZE_SMALL
            ));

        // Add the bottom half circle
        pSink->AddArc(
            D2D1::ArcSegment(
            D2D1::Point2F(x, y + width / 2), // end point of the bottom half circle
            D2D1::SizeF(width / 2, width / 2),   // radius of the bottom half circle, same as previous one.
            0.0f, // rotation angle
            D2D1_SWEEP_DIRECTION_CLOCKWISE,
            D2D1_ARC_SIZE_SMALL
            ));
        pSink->EndFigure(D2D1_FIGURE_END_CLOSED);
        pSink->Close();
    }

    return pPathGeometry;
}
// AFX_WM_DRAW2D event handler
afx_msg LRESULT CHelloWorldView::OnDraw2d(WPARAM wParam, LPARAM lParam)
{
	CHwndRenderTarget* pRenderTarget = (CHwndRenderTarget*)lParam;
	ASSERT_VALID(pRenderTarget);

	// Clear window background
	pRenderTarget->Clear(ColorF(ColorF::Beige));

	// Draw text
	CRect rect;
	GetClientRect(rect);
	pRenderTarget->DrawText(_T("Hello, World!"), rect, m_pBlueBrush, m_pTextFormat);
    CD2DPointF point(120.0f, 120.0f);
    CD2DSizeF size(80.0f, 80.0f);
    CD2DEllipse ellipse1(point, size);
    CD2DEllipse ellipse2(CD2DPointF(320, 120), size);
    CD2DEllipse ellipse3(CD2DPointF(520, 120), size);
    CD2DEllipse ellipse4(CD2DPointF(720, 120), size);
    CComQIPtr< ID2D1RenderTarget> pRT = pRenderTarget->GetRenderTarget();

    ID2D1GeometrySink* pSink = m_pathGeometry->Open();
    if (pSink)
    {
        pSink->SetFillMode(D2D1_FILL_MODE_WINDING);
        pSink->BeginFigure(
            D2D1::Point2F(0, 150), // Start point of the top half circle
            D2D1_FIGURE_BEGIN_FILLED
            );

        // Add the top half circle
        pSink->AddArc(
            D2D1::ArcSegment(
            D2D1::Point2F(300, 150), // end point of the top half circle, also the start point of the bottom half circle
            D2D1::SizeF(150, 150), // radius
            0.0f, // rotation angle
            D2D1_SWEEP_DIRECTION_CLOCKWISE,
            D2D1_ARC_SIZE_SMALL
            ));

        // Add the bottom half circle
        pSink->AddArc(
            D2D1::ArcSegment(
            D2D1::Point2F(0, 150), // end point of the bottom half circle
            D2D1::SizeF(150, 150),   // radius of the bottom half circle, same as previous one.
            0.0f, // rotation angle
            D2D1_SWEEP_DIRECTION_CLOCKWISE,
            D2D1_ARC_SIZE_SMALL
            ));

        pSink->EndFigure(D2D1_FIGURE_END_CLOSED);
        pSink->Close();
    }

    ID2D1Layer *pLayer = NULL;
    HRESULT hr = pRT->CreateLayer(NULL, &pLayer);
    if (SUCCEEDED(hr))
    {
        //pRT->SetTransform(D2D1::Matrix3x2F::Translation(0, 300));
        pRT->SetTransform(D2D1::Matrix3x2F::Translation(100, 300));
        pRT->PushLayer(D2D1::LayerParameters(D2D1::InfiniteRect(), m_pathGeometry->Get()), pLayer);
        pRT->DrawBitmap(m_pBitmap->Get(), D2D1::RectF(0,0, 300, 300));
        pRT->SetTransform(D2D1::Matrix3x2F::Identity());
        pRT->PopLayer();
    }
    SafeRelease(&pLayer);
	return TRUE;
}
