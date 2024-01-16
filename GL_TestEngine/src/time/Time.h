#pragma once

namespace engine {
	class Time {
	public:
		static float getDeltaTime() { return deltaTime; }
		static float getFPS();

		static void onUpdateStart();
		static void onUpdateEnd();
		
	private:
		static float deltaTime;
		static float updateStartTime;

	};
}