#pragma once

#include "EventType.h"

namespace engine {
	class IEvent {
	public:
		virtual const unsigned int getType() { return m_eventType; }

	protected:
		unsigned int m_eventType = EventType::None;
	};
}