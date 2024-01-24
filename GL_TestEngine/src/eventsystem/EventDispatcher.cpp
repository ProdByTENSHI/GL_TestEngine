#include "EventDispatcher.h"

namespace engine {
	EventDispatcher::EventDispatcher(unsigned int eventType) {
		m_eventsType = eventType;
	}

	EventDispatcher::~EventDispatcher() {
		
	}
}