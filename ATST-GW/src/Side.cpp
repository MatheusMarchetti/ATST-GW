#include <corepch.h>
#include <Side.h>

Side::Side(Vertex& v0, Vertex& v1, int id)
	: vertex0(v0), vertex1(v1), id(id)
{
	glm::vec2 vector1 = v1.GetVertex() - v0.GetVertex();
	length = glm::length(vector1);
}