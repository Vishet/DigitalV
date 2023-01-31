#include "Mouse.h"

#include <windows.h>

Mouse* const Mouse::mouse{ new Mouse() };
bool Mouse::isInitialized{ false };

Mouse::Event::Event(Type type, const Mouse& parent) noexcept :
	type{ type },
	x{ parent.x },
	y{ parent.y },
	isLMBPressed{ parent.isLMBPressed },
	isRMBPressed{ parent.isRMBPressed },
	isMMBPressed{ parent.isMMBPressed }
{
}

const Mouse::Event::Type& Mouse::Event::GetType() const noexcept
{
	return type;
}

const std::pair<int, int> Mouse::Event::GetPosition() const noexcept
{
	return std::pair<int, int>(x, y);
}

int Mouse::Event::GetX() const noexcept
{
	return x;
}

int Mouse::Event::GetY() const noexcept
{
	return y;
}

bool Mouse::Event::IsLMBPressed() const noexcept
{
	return isLMBPressed;
}

bool Mouse::Event::IsRMBPressed() const noexcept
{
	return isRMBPressed;
}

bool Mouse::Event::IsMMBPressed() const noexcept
{
	return isMMBPressed;
}

const std::optional<const Mouse::Event> Mouse::ReadEvent() noexcept
{
	if (eventQueue.empty())
		return {};
	else
	{
		Event popEvent{ eventQueue.front() };
		eventQueue.pop();
		return popEvent;
	}
}

void Mouse::Clear() noexcept
{
	isLMBPressed = false;
	isRMBPressed = false;
	isMMBPressed = false;
}

const std::pair<int, int> Mouse::GetPosition() const noexcept
{
	return std::pair<int, int>(x, y);
}

int Mouse::GetX() const noexcept
{
	return x;
}

int Mouse::GetY() const noexcept
{
	return y;
}

int Mouse::GetLimitedX() const noexcept
{
	if (isXLimited)
		return limitedX;
	else
		return x;
}

int Mouse::GetLimitedY() const noexcept
{
	if (isYLimited)
		return limitedY;
	else
		return y;
}

bool Mouse::IsLMBDown() const noexcept
{
	return isLMBPressed;
}

bool Mouse::IsRMBDown() const noexcept
{
	return isRMBPressed;
}

bool Mouse::IsMMBDown() const noexcept
{
	return isMMBPressed;
}

bool Mouse::IsInWindow() const noexcept
{
	return isInWindow;
}

void Mouse::OnLMBPressed() noexcept
{
	isLMBPressed = true;
	eventQueue.emplace(Event(Event::Type::LMBPressed, *this));
	TrimQueue(eventQueue);
}

void Mouse::OnRMBPressed() noexcept
{
	isRMBPressed = true;
	eventQueue.emplace(Event(Event::Type::RMBPressed, *this));
	TrimQueue(eventQueue);
}

void Mouse::OnMMBPressed() noexcept
{
	isMMBPressed = true;
	eventQueue.emplace(Event(Event::Type::MMBPressed, *this));
	TrimQueue(eventQueue);
}

void Mouse::OnLMBReleased() noexcept
{
	isLMBPressed = false;
	eventQueue.emplace(Event(Event::Type::LMBReleased, *this));
	TrimQueue(eventQueue);
}

void Mouse::OnRMBReleased() noexcept
{
	isRMBPressed = false;
	eventQueue.emplace(Event(Event::Type::RMBReleased, *this));
	TrimQueue(eventQueue);
}

void Mouse::OnMMBReleased() noexcept
{
	isMMBPressed = false;
	eventQueue.emplace(Event(Event::Type::MMBReleased, *this));
	TrimQueue(eventQueue);
}

void Mouse::OnWheelUp() noexcept
{
	eventQueue.emplace(Event(Event::Type::WheelUp, *this));
	TrimQueue(eventQueue);
}

void Mouse::OnWheelDown() noexcept
{
	eventQueue.emplace(Event(Event::Type::WheelDown, *this));
	TrimQueue(eventQueue);
}

void Mouse::OnWheelDelta(int delta) noexcept
{
	wheelDeltaCarry += delta;

	while (wheelDeltaCarry >= WHEEL_DELTA)
	{
		OnWheelUp();
		wheelDeltaCarry -= WHEEL_DELTA;
	}

	while (wheelDeltaCarry <= -WHEEL_DELTA)
	{
		OnWheelDown();
		wheelDeltaCarry += WHEEL_DELTA;
	}
}

void Mouse::OnMove(int x, int y) noexcept
{
	this->x = x;
	this->y = y;

	if (!isXLimited)
		limitedX = x;
	if (!isYLimited)
		limitedY = y;

	eventQueue.emplace(Event(Event::Type::Move, *this));
	TrimQueue(eventQueue);
}

void Mouse::OnEnter() noexcept
{
	isInWindow = true;
	eventQueue.emplace(Event(Event::Type::Enter, *this));
	TrimQueue(eventQueue);

	isXLimited = false;
	isYLimited = false;
}

void Mouse::OnLeave() noexcept
{
	isInWindow = false;
	eventQueue.emplace(Event(Event::Type::Leave, *this));
	TrimQueue(eventQueue);

	isXLimited = false;
	isYLimited = false;
}

void Mouse::OnLimitX(bool limit, float x) noexcept
{
	if (limit)
		limitedX = x;
	isXLimited = limit;
}

void Mouse::OnLimitY(bool limit, float y) noexcept
{
	if (limit)
		limitedY = y;
	isYLimited = limit;
}

void Mouse::TrimQueue(std::queue<Event>& queue) noexcept
{
	while (queue.size() > maxEvents)
	{
		queue.pop();
	}
}

Mouse* Mouse::GetMousePointer() noexcept
{
	return mouse;
}
