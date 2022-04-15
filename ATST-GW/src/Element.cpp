#include <corepch.h>
#include <Element.h>

Element::Element(std::vector<glm::vec2>& nodes, int id)
	:nodes(nodes), id(id)
{
	nodeshape.resize(nodes.size());
	nodederivs.resize(nodes.size());
	length = sqrt((nodes[1].x - nodes[0].x) * (nodes[1].x - nodes[0].x) + (nodes[1].y - nodes[0].y) * (nodes[1].y - nodes[0].y));
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
	glm::vec2 v1 = {};

	for (size_t i = 0; i < shapederivs.size(); i++)
	{
		v1 += shapederivs[i] * nodes[i];
	}

	return glm::dot(v1, { 0,1 }) / glm::length(v1);	// Notação invertida
}

float Element::GetDirectorCosineY(std::vector<float>& shapederivs)
{
	glm::vec2 v1 = {};

	for (size_t i = 0; i < shapederivs.size(); i++)
	{
		v1 += shapederivs[i] * nodes[i];
	}

	return glm::dot(v1, { 1,0 }) / glm::length(v1); // Notação invertida
}

glm::vec2 Element::GetGlobalCoordinate(std::vector<float>& nodeshape)
{
	glm::vec2 v1 = {};

	for (size_t i = 0; i < nodeshape.size(); i++)
	{
		v1 += nodeshape[i] * nodes[i];
	}
	return v1;
}