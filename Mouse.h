#pragma once

#include <utility> // std::pair
#include <queue>
#include <optional>

class Mouse
{
public:
	class Event
	{
	public:
		enum class Type
		{
			LMBPressed,
			LMBReleased,
			RMBPressed,
			RMBReleased,
			MMBPressed,
			MMBReleased,
			Move,
			WheelUp,
			WheelDown,
			Enter,
			Leave
		};

	private:
		const Type type;
		const int x;
		const int y;
		const bool isLMBPressed;
		const bool isRMBPressed;
		const bool isMMBPressed;

	public:
		Event(Type type, const Mouse& parent) noexcept;
		Event(const Event&) = default;
		Event operator=(const Event&) = delete;

		const Type& GetType() const noexcept;
		const std::pair<int, int> GetPosition() const noexcept;
		int GetX() const noexcept;
		int GetY() const noexcept;
		bool IsLMBPressed() const noexcept;
		bool IsRMBPressed() const noexcept;
		bool IsMMBPressed() const noexcept;
	};

private:
	static Mouse* const mouse;
	static bool isInitialized;

	std::queue<Event> eventQueue{};
	int x{ 0 };
	int y{ 0 };
	bool isLMBPressed{ false };
	bool isRMBPressed{ false };
	bool isMMBPressed{ false };
	bool isInWindow{ false };
	int wheelDeltaCarry{ 0 };
	static constexpr size_t maxEvents{ 16u };

public:
	Mouse() noexcept = default;
	Mouse(const Mouse&) = delete;
	Mouse operator=(const Mouse&) = delete;

	const std::optional<const Event> ReadEvent() noexcept;
	void Clear() noexcept;

	const std::pair<int, int> GetPosition() const noexcept;
	int GetX() const noexcept;
	int GetY() const noexcept;
	bool IsLMBDown() const noexcept;
	bool IsRMBDown() const noexcept;
	bool IsMMBDown() const noexcept;
	bool IsInWindow() const noexcept;

public:
	void OnLMBPressed() noexcept;
	void OnRMBPressed() noexcept;
	void OnMMBPressed() noexcept;
	void OnLMBReleased() noexcept;
	void OnRMBReleased() noexcept;
	void OnMMBReleased() noexcept;
	void OnWheelUp() noexcept;
	void OnWheelDown() noexcept;
	void OnWheelDelta(int delta) noexcept;
	void OnMove(int x, int y) noexcept;
	void OnEnter() noexcept;
	void OnLeave() noexcept;

	static void TrimQueue(std::queue<Event>& queue) noexcept;

	static Mouse* GetMousePointer() noexcept;
};
