#pragma once

#include <Vertex.h>

class Side
{
public:
	Side(Vertex& v0, Vertex& v1, int id);

	inline const float Length() const { return length; }
	inline const int GetId() const { return id; }
	inline const glm::vec2 GetVertex0() { return vertex0.GetVertex(); }
	inline const int GetVertex0Id() { return vertex0.GetId(); }
	inline const glm::vec2 GetVertex1() { return vertex1.GetVertex(); }
	inline const int GetVertex1Id() { return vertex1.GetId(); }

private:
	Vertex vertex0;
	Vertex vertex1;
	float length;
	int id;
};