#pragma once

#include <MathUtils.h>

class Vertex
{
public:
	Vertex(glm::vec2& v, int id) : vertex(v), id(id) {}
	inline const int GetId() { return id; }
	inline const glm::vec2 GetVertex() { return vertex; }

private:
	int id;
	glm::vec2 vertex;
};


