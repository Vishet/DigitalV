#pragma once

#include <Windows.h>
#include <vector>
#include <atlbase.h>
#include <string>

#include <dwrite.h>
#pragma comment(lib, "dwrite")

#include <d2d1.h>
#pragma comment(lib, "d2d1")

class Graphics
{
private:
	static Graphics* const graphics;
	static bool isInitialized;

	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;

	ID2D1Factory* pFactory{};
	ID2D1HwndRenderTarget* pRenderTarget{};
	IDWriteFactory* pWriteFactory{};

	static constexpr auto fontName{ L"Verdana" };
	static constexpr float fontSize{ 30.0f };
	static constexpr float realFontSize{ 22.0f };
	IDWriteTextFormat* pTextFormat{};

	Graphics() = default;

public:
	~Graphics() noexcept;

	static Graphics* GetGraphicsPointer() noexcept;

	static void InitializeCOM();
	static void UnitializeCOM() noexcept;

	void Initialize(HWND hWindow);

	void BeginDraw() const noexcept;
	void BeginDraw(float r, float g, float b, float a = 1.0f) const noexcept;
	void EndDraw() const;

	void Fill(float r, float g, float b, float a) const noexcept;

	void DrawLine(const D2D1_POINT_2F& pointA, const D2D1_POINT_2F& pointB, const D2D1_COLOR_F& color, float strokeWidth) const;
	void FillRectangle(
		float x, float y, float x2, float y2,
		float r, float g, float b, float a = 1.0f
	) const;
	void DrawCenteredText(
		const std::wstring& text, 
		float x, float y, float x1, float x2,
		float r, float g, float b, float a = 1.0f
	) const;
	void DrawWString(const std::wstring& text, const D2D1_COLOR_F& textColor, int x, int y);
	void FillCircle(
		float x, float y, 
		const float radius, 
		float r, float g, float b, float a = 1.0f
	) const;
	void DrawCircle(
		float x, float y,
		float radius, float strokeWidth,
		float r, float g, float b, float a = 1.0f
	) const;
};
