#pragma once

#include <MathUtils.h>
#include <Side.h>

class Element
{
public:
	Element(std::vector<glm::vec2>& nodes, int i);
	std::vector<float> CalculateShapes(float xsi);
	std::vector<float> CalculateDerivatives(float xsi);

	float GetDirectorCosineX(std::vector<float>& shapederivs);
	float GetDirectorCosineY(std::vector<float>& shapederivs);

	glm::vec2 GetGlobalCoordinate(std::vector<float>& nodeshape);

	inline const std::vector<glm::vec2> GetNode() const { return nodes; }
	inline const int GetId() const { return id; }
	inline const float GetLength() const{ return length; }

private:
	int id;
	float length;
	std::vector<glm::vec2> nodes;
	std::vector<float> nodeshape;
	std::vector<float> nodederivs;
};
