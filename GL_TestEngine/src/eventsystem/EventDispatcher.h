#pragma once

#include <vector>

#include "IEvent.h"

namespace engine {
	class EventDispatcher {
	public:
		EventDispatcher(unsigned int eventType);
		~EventDispatcher();

		void dispatch();

	private:
		unsigned int m_eventsType = EventType::None;	// Defines what type of events the Dispatcher accepts

	};
}