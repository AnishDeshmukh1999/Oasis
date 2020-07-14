#pragma once

#include"Event.h"
#include<sstream>
namespace Oasis {
	class OE_API KeyEvent : public Event {
	public:
		inline int getKeyCode() const { return m_keycode; }
		EVENT_CLASS_CATEGORY(EventCategory::EventCategoryKeyboard | EventCategory::EventCategoryInput)
	protected:
		KeyEvent(int keycode): m_keycode(keycode) {}
		int m_keycode;
	};
	class OE_API KeyPressedEvent : public KeyEvent {
	public:
		KeyPressedEvent(int keycode, int repeatcount)
			: KeyEvent(keycode), m_repeatcount(repeatcount) {}
		inline int getRepeatCount() const { return m_repeatcount; }
		std::string toString() const override {
			std::stringstream ss;
			ss << "KeyPressedEvent" << m_keycode << "(" << m_repeatcount << " repeats )";
			return ss.str();
		}
EVENT_CLASS_TYPE(KeyPressed);
	private:
		int m_repeatcount;

	};
	class OE_API KeyReleasedEvent : public KeyEvent {
	public:
		KeyReleasedEvent(int keycode)
			: KeyEvent(keycode) {}
		std::string toString() const override {
			std::stringstream ss;
			ss << "KeyReleasedEvent" << m_keycode;
			return ss.str();
		}
		EVENT_CLASS_TYPE(KeyReleased);

	};
}