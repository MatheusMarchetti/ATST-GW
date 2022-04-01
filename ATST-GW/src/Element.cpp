#include <corepch.h>
#include <Element.h>

Element::Element(std::vector<glm::vec2>& nodes, int i)
{
	id = i;
	node0 = nodes[0];
	node1 = nodes[1];
	node2 = nodes[2];
}

std::vector<float> Element::CalculateShapes(float xsi)
{
	ShapeFunctions(nodeshape, xsi);

	return nodeshape;
}

std::vector<float> Element::CalculateDerivatives(float xsi)
{
	ShapeFunctionsDerivatives(nodederivs, xsi);

	return nodederivs;
}

float Element::GetDirectorCosineX(std::vector<float>& shapederivs)
{
	glm::vec2 v1 = shapederivs[0] * node0 + shapederivs[1] * node1 + shapederivs[2] * node2;

	return glm::abs(glm::dot(v1, { 1,0 }) / glm::length(v1));
}

float Element::GetDirectorCosineY(std::vector<float>& shapederivs)
{
	glm::vec2 v1 = shapederivs[0] * node0 + shapederivs[1] * node1 + shapederivs[2] * node2;

	return glm::abs(glm::dot(v1, { 0,1 }) / glm::length(v1));
}

glm::vec2 Element::GetGlobalCoordinate(std::vector<float>& nodeshape)
{
	return nodeshape[0] * node0 + nodeshape[1] * node1 + nodeshape[2] * node2;
}