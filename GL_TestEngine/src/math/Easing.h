#pragma once

#include <glm/glm.hpp>

// Formulas stolen from https://easings.net/
namespace engine {
	constexpr float PI = 3.14159265359;

	// Keine Ahnung was die machen ich hatte 3 Punkte in Mathe, aber die werden für die Back-Easing Funktionen anscheinend gebraucht
	const float EASE_BACK_CONST1 = 1.70158f;
	const float EASE_BACK_CONST2 = EASE_BACK_CONST1 * 1.525f;
	const float EASE_BACK_CONST3 = EASE_BACK_CONST1 + 1;

	// Das gleiche wie oben aber für Bounce-Easing Funktionen
	const float EASE_BOUNCE_CONST1 = 7.5625f;
	const float EASE_BOUNCE_CONST2 = 2.75f;

	class Easing {
	public:
		static float easeInSine(float value) {
			return 1 - glm::cos((value * PI) * 0.5f);
		}

		static float easeOutSine(float value) {
			return glm::sin((value * PI) * 0.5f);
		}

		static float easeInOutSine(float value) {
			return -(glm::cos(PI * value) - 1) * 0.5f;
		}

		static float easeInCubic(float value) {
			return value * value * value;
		}

		static float easeOutCubic(float value) {
			return 1 - glm::pow(1 - value, 3);
		}

		static float easeInOutCubic(float value) {
			return value < 0.5 ? 4 * value * value * value : 1 - glm::pow(-2 * value + 2, 3) / 2;
		}

		static float easeInQuint(float value) {
			return value * value * value * value * value;
		}

		static float easeOutQuint(float value) {
			return 1 - glm::pow(1 - value, 5);
		}

		static float easeInOutQuint(float value) {
			return value < 0.5 ? 16 * value * value * value * value * value : 1 - glm::pow(-2 * value + 2, 5) * 0.5f;
		}

		static float easeInCirc(float value) {
			return 1 - glm::sqrt(1 - glm::pow(value, 2));
		}

		static float easeOutCirc(float value) {
			return glm::sqrt(1 - glm::pow(value - 1, 2));
		}

		static float easeInOutCirc(float value) {
			return value < 0.5 ? (1 - glm::sqrt(1 - glm::pow(2 * value, 2))) * 0.5f : (glm::sqrt(1 - glm::pow(-2 * value + 2, 2)) + 1) * 0.5f;
		}

		static float easeInQuad(float value) {
			return value * value;
		}

		static float easeOutQuad(float value) {
			return 1 - (1 - value) * (1 - value);
		}

		static float easeInOutQuad(float value) {
			return value < 0.5 ? 2 * value * value : 1 - glm::pow(-2 * value + 2, 2) * 0.5f;
		}

		static float easeInExpo(float value) {
			return value == 0 ? 0 : glm::pow(2, 10 * value - 10);
		}

		static float easeOutExpo(float value) {
			return value == 1 ? 1 : 1 - glm::pow(2, -10 * value);
		}

		static float easeInOutExpo(float value) {
			return value == 0
				? 0
				: value == 1
				? 1
				: value < 0.5 ? glm::pow(2, 20 * value - 10) * 0.5f
				: (2 - glm::pow(2, -20 * value + 10)) * 0.5f;
		}

		static float easeInBack(float value) {
			return EASE_BACK_CONST3 * value * value * value - EASE_BACK_CONST1 * value * value;
		}

		static float easeOutBack(float value) {
			return 1 + EASE_BACK_CONST3 * glm::pow(value - 1, 3) + EASE_BACK_CONST1 * glm::pow(value - 1, 2);
		}

		static float easeInOutBack(float value) {
			return value < 0.5
				? (glm::pow(2 * value, 2) * ((EASE_BACK_CONST2 + 1) * 2 * value - EASE_BACK_CONST2)) * 0.5f
				: (glm::pow(2 * value - 2, 2) * ((EASE_BACK_CONST2 + 1) * (value * 2 - 2) + EASE_BACK_CONST2) + 2) * 0.5f;
		}

		static float easeInBounce(float value) {
			return 1 - easeOutBounce(1 - value);
		}

		static float easeOutBounce(float value) {
			if (value < 1 / EASE_BOUNCE_CONST2) {
				return EASE_BOUNCE_CONST1 * value * value;
			}
			else if (value < 2 / EASE_BOUNCE_CONST2) {
				return EASE_BOUNCE_CONST1 * (value -= 1.5 / EASE_BOUNCE_CONST2) * value + 0.75;
			}
			else if (value < 2.5 / EASE_BOUNCE_CONST2) {
				return EASE_BOUNCE_CONST1 * (value -= 2.25 / EASE_BOUNCE_CONST2) * value + 0.9375;
			}
			else {
				return EASE_BOUNCE_CONST1 * (value -= 2.625 / EASE_BOUNCE_CONST2) * value + 0.984375;
			}
		}

		static float easeInOutBounce(float value) {
			return value < 0.5
				? (1 - easeOutBounce(1 - 2 * value)) * 0.5f
				: (1 + easeOutBounce(2 * value - 1)) * 0.5f;
		}
	};
}