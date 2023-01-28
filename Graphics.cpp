#include "Graphics.h"
#include "Exception.h"

Graphics* const Graphics::graphics{ new Graphics() };
bool Graphics::isInitialized{ false };

Graphics::~Graphics() noexcept
{
	pRenderTarget->Release();
	pFactory->Release();
	pTextFormat->Release();
	pWriteFactory->Release();
}

Graphics* Graphics::GetGraphicsPointer() noexcept
{
	return graphics;
}

void Graphics::InitializeCOM()
{
	HRESULT hr{};
	THROW_IF_FAILED_HR(CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE));
}

void Graphics::UnitializeCOM() noexcept
{
	CoUninitialize();
}

void Graphics::Initialize(HWND hWindow)
{
	if (isInitialized)
		return;

	HRESULT hr{};

	THROW_IF_FAILED_HR(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory));

	RECT rc{};
	THROW_IF_LAST_FAILED(GetClientRect(hWindow, &rc));
	D2D1_SIZE_U windowSize = D2D1::SizeU(rc.right, rc.bottom);
	THROW_IF_FAILED_HR(pFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(hWindow, windowSize),
		&pRenderTarget
	));

	THROW_IF_FAILED_HR(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(pWriteFactory), reinterpret_cast<IUnknown**>(&pWriteFactory)));

	THROW_IF_FAILED_HR(pWriteFactory->CreateTextFormat(
		fontName,
		NULL,
		DWRITE_FONT_WEIGHT_BOLD,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		fontSize,
		L"",
		&pTextFormat
	));

	isInitialized = true;
}

void Graphics::BeginDraw() const noexcept
{
	pRenderTarget->BeginDraw();
}

void Graphics::BeginDraw(float r, float g, float b, float a) const noexcept
{
	this->BeginDraw();
	this->Fill(r, g, b, a);
}

void Graphics::EndDraw() const
{
	HRESULT hr{};
	THROW_IF_FAILED_HR(pRenderTarget->EndDraw());
}

void Graphics::Fill(float r, float g, float b, float a) const noexcept
{
	pRenderTarget->Clear(D2D1::ColorF(r, g, b, a));
}

void Graphics::DrawLine(const D2D1_POINT_2F& pointA, const D2D1_POINT_2F& pointB, const D2D1_COLOR_F& color, float strokeWidth) const
{
	CComPtr<ID2D1SolidColorBrush> pBrush{};

	HRESULT hr{};
	THROW_IF_FAILED_HR(pRenderTarget->CreateSolidColorBrush(color, &pBrush));

	pRenderTarget->DrawLine(pointA, pointB, pBrush, strokeWidth);
}

void Graphics::FillRectangle(
	float x, float y, float x2, float y2,
	float r, float g, float b, float a
) const
{
	CComPtr<ID2D1SolidColorBrush> pBrush{};

	HRESULT hr{};
	THROW_IF_FAILED_HR(pRenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(r, g, b, a),
		&pBrush
	));

	pRenderTarget->FillRectangle(
		D2D1::RectF(x, y, x2, y2),
		pBrush
	);
}

void Graphics::DrawWString(const std::wstring& text, const D2D1_COLOR_F& textColor, const D2D1_RECT_F& layoutRect) const
{
	CComPtr<ID2D1SolidColorBrush> pBrush{};

	HRESULT hr{};
	THROW_IF_FAILED_HR(pRenderTarget->CreateSolidColorBrush(textColor, &pBrush));
	THROW_IF_FAILED_HR(pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER));

	pRenderTarget->DrawText(
		text.c_str(),
		static_cast<UINT32>(text.size()),
		pTextFormat,
		D2D1::RectF(
			layoutRect.left,
			layoutRect.top + (layoutRect.bottom - layoutRect.top - realFontSize) / 2 - (fontSize - realFontSize),
			layoutRect.right, layoutRect.bottom
		),
		pBrush,
		D2D1_DRAW_TEXT_OPTIONS_CLIP
	);
	THROW_IF_FAILED_HR(pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING));
}

void Graphics::DrawWString(const std::wstring& text, const D2D1_COLOR_F& textColor, int x, int y)
{
	CComPtr<ID2D1SolidColorBrush> pBrush{};

	HRESULT hr{};
	THROW_IF_FAILED_HR(pRenderTarget->CreateSolidColorBrush(textColor, &pBrush));

	pRenderTarget->DrawText(
		text.c_str(),
		static_cast<UINT32>(text.size()),
		pTextFormat,
		D2D1::RectF(
			static_cast<float>(x),
			static_cast<float>(y),
			static_cast<float>(GetSystemMetrics(SM_CXSCREEN)), 
			static_cast<float>(GetSystemMetrics(SM_CYSCREEN))
		),
		pBrush,
		D2D1_DRAW_TEXT_OPTIONS_NONE
	);
}

void Graphics::FillCircle(const D2D1_POINT_2F& centerPoint, const float radius, const D2D1_COLOR_F& bgColor) const
{
	CComPtr<ID2D1SolidColorBrush> pBrush{};

	HRESULT hr{};
	THROW_IF_FAILED_HR(pRenderTarget->CreateSolidColorBrush(bgColor, &pBrush));

	pRenderTarget->FillEllipse(D2D1::Ellipse(centerPoint, radius, radius), pBrush);
}