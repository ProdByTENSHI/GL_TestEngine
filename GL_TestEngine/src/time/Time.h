#pragma once

namespace engine {
	class Time {
	public:
		static float getTime();
		static float getDeltaTime() { return deltaTime; }
		static float getFPS();
		static float getLastFrameTime() { return lastFrameTime; }
		static int getRenderedFrames();

		static void onUpdateStart();
		static void onUpdateEnd();

		static void onRenderStart();
		static void onRenderEnd();
		
	private:
		static float deltaTime;
		static float updateStartTime;
		static float lastFrameTime;
		static int renderedFrames;

	};
}