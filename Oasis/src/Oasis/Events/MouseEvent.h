#include"../../oepch.h"
#pragma once
#include"Event.h"
namespace Oasis {
	class OE_API MouseMovedEvent : public Event {
	public:
		MouseMovedEvent(float x, float y)
			: m_X(x),m_Y(y){}
		EVENT_CLASS_CATEGORY((int)EventCategory::EventCategoryInput | (int)EventCategory::EventCategoryMouse);
		EVENT_CLASS_TYPE(MouseMoved);
		inline float getX() const { return m_X; }
		inline float getY() const { return m_Y; }
		std::string toString() const override {
			std::stringstream ss;
			ss << "MouseMovedEvent" << m_X << ' , ' << m_Y;
			return ss.str();
		}
	protected:
		float m_X, m_Y;
	};
	class OE_API MouseScrolledEvent : public Event {
	public:
		MouseScrolledEvent(float xoffset, float yoffset)
			: m_XOffset(xoffset), m_YOffset(yoffset) {}
		EVENT_CLASS_CATEGORY((int)EventCategory::EventCategoryInput | (int)EventCategory::EventCategoryMouse);
		EVENT_CLASS_TYPE(MouseScrolled);
		inline float getX() const { return m_XOffset; }
		inline float getY() const { return m_YOffset; }
		std::string toString() const override {
			std::stringstream ss;
			ss << "MouseScrolledEvent" << m_XOffset << ' , ' << m_YOffset;
			return ss.str();
		}
	protected:
		float m_XOffset, m_YOffset;
	};
	class OE_API MouseButtonEvent : public Event {
	public:
		EVENT_CLASS_CATEGORY((int)EventCategory::EventCategoryInput | (int)EventCategory::EventCategoryMouse);
		inline int getMouseButton() { return m_button; }
	protected:
		MouseButtonEvent(int b)
			:m_button(b){ }
		int m_button;
	};
	class OE_API MouseButtonPressedEvent : public MouseButtonEvent {
	public:
		MouseButtonPressedEvent(int b)
			:MouseButtonEvent(b) { }
		EVENT_CLASS_TYPE(MouseButtonPressed);
		std::string toString() const override {
			std::stringstream ss;
			ss << "MouseButtonPressedEvent " << m_button;
			return ss.str();
		}
	};
	class OE_API MouseButtonReleasedEvent : public MouseButtonEvent {
	public:
		MouseButtonReleasedEvent(int b)
			:MouseButtonEvent(b) { }
		EVENT_CLASS_TYPE(MouseButtonReleased);
		std::string toString() const override {
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent " << m_button;
			return ss.str();
		}
	};
}