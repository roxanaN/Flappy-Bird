#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace Object2D {
	Mesh* CreateRectangle(std::string name, glm::vec3 leftBottomCorner, float length, float width, glm::vec3 color, bool fill = false);
	Mesh* CreateTriangle(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
	Mesh* CreateCircle(std::string name, glm::vec3 center, float radius, int verticesNo, glm::vec3 color, bool fill);
}

