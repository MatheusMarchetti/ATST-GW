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

	inline const glm::vec2 GetNode0() const { return node0; }
	inline const glm::vec2 GetNode1() const { return node1; }
	inline const glm::vec2 GetNode2() const { return node2; }
	inline const int GetId() const { return id; }

private:
	int id;
	glm::vec2 node0;
	glm::vec2 node1;
	glm::vec2 node2;
	std::vector<float> nodeshape;
	std::vector<float> nodederivs;
};
