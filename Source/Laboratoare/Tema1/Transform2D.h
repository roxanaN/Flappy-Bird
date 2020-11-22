#pragma once

#include <include/glm.h>

namespace Transform2D {
	inline glm::mat3 Translate(float translateX, float translateY) {
		return glm::transpose(
			glm::mat3(1, 0, translateX,
				0, 1, translateY,
				0, 0, 1)
		);
	}

	inline glm::mat3 Rotate(float radians) {
		radians = radians * M_PI / 180.0;
		return glm::mat3(cos(radians), -sin(radians), 0,
			sin(radians), cos(radians), 0,
			0, 0, 1);
	}
}
