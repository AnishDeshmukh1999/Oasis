#include"../../oepch.h"
#pragma once

#include"Event.h"
namespace Oasis {

	class OE_API WindowCloseEvent : public Event {
	public:
		WindowCloseEvent() {}
		EVENT_CLASS_TYPE(WindowClose);
		EVENT_CLASS_CATEGORY((int) EventCategory::EventCategoryApplication);
		std::string toString() const override {
			std::stringstream ss;
			ss << " WindowCloseEvent ";
			return ss.str();
		}
	};

	class OE_API WindowResizeEvent : public Event {
	public:
		WindowResizeEvent(int width, int height)
			:m_width(width),m_height(height){ }
		inline unsigned int getWidth() { return m_width; }
		inline unsigned int getHeight() { return m_height; }
		EVENT_CLASS_TYPE(WindowResize);
		EVENT_CLASS_CATEGORY((int) EventCategory::EventCategoryApplication);

		std::string toString() const override {
			std::stringstream ss;
			ss << " WindowResizeEvent " << m_width << " , " << m_height;
			return ss.str();
		}
	private:
		unsigned int m_width, m_height;
	};

}