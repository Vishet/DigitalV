#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include <windows.h>
#include <string>
#include <functional>

class GenericWindow
{
private:
	HWND windowHandle{};
	static bool isClassCreated;
	std::string title;
	int width;
	int height;
	bool absoluteDimension;
	const DWORD style;
	Keyboard* keyboard;
	Mouse* mouse;

public:
	GenericWindow(const GenericWindow&) = delete;
	GenericWindow(const GenericWindow&&) = delete;
	GenericWindow operator=(const GenericWindow&) = delete;
	GenericWindow operator=(const GenericWindow&&) = delete;

	GenericWindow(
		const std::string& title,
		int width, int height, bool absoluteDimension,
		DWORD style,
		Keyboard* keyboard,
		Mouse* mouse
	) noexcept;
	~GenericWindow() noexcept;

	void Show() const noexcept;
	void Hide() const noexcept;
	bool isVisible() const noexcept;
	HWND GetWindowHandle() const noexcept { return windowHandle; }
	void Initialize();
	bool HandleInput(UINT message, WPARAM wParam, LPARAM lParam) noexcept;

	inline int GetWidth() const { return width; }
	inline int GetHeight() const { return height; }

private:
	virtual LRESULT WindowProcedure(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam) = 0;
	static LRESULT CALLBACK WindowProcedureCanalizer(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam) noexcept;
	void CreateClass() const;
};
