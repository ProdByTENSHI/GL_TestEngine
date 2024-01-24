#pragma once

#include "eventsystem/IEvent.h"

namespace engine {
	class WindowEvent : public IEvent {
	public:
		const unsigned int getType() override { return m_eventType; }

	protected:
		unsigned int m_eventType = EventType::WindowEvent;
	};
}