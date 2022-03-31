#include "corepch.h"

#define GLM_FORCE_SWIZZLE

#include <stdio.h>
#include <iostream>
#include <vector>
#include <functional>
#include "glm/glm.hpp"
	
void ShapeFunctions(std::vector<float>& shapefuncs, float xsi)
{
	shapefuncs.push_back(0.5f * (1.0f - xsi) - 0.5f * (1.0f - xsi * xsi));
	shapefuncs.push_back(1.0f - xsi * xsi);
	shapefuncs.push_back(0.5f * (1.0f + xsi) - 0.5f * (1.0f - xsi * xsi));
}

void ShapeFunctionsDerivatives(std::vector<float>& shapederivs, float xsi)
{
	shapederivs.push_back(-0.5f - 0.5f * (-2.0f * xsi));
	shapederivs.push_back(-2.0f * xsi);
	shapederivs.push_back(0.5f - 0.5f * (-2.0f * xsi));
}

float Jacobian(glm::vec2& vector)
{
	return glm::length(vector);
}

glm::vec2 Normal(std::vector<float>& shapederivs, glm::vec2 node0, glm::vec2 node1, glm::vec2 node2)
{
	glm::vec2 v1 = shapederivs[0] * node0 + shapederivs[1] * node1 + shapederivs[2]* node2;

	return glm::cross(glm::vec3(v1, 0), { 0, 0, 1 }).xy;
}

class Side
{
public:
	Side(glm::vec2& v0, glm::vec2& v1, int id)
		: vertex0(v0), vertex1(v1), id(id)
	{
		glm::vec2 vector1 = v1 - v0;
		length = glm::length(vector1);
	}

	const float Length() const { return length; }
	const int GetId() const { return id; }
	const glm::vec2 GetVertice0() const { return vertex0; }
	const glm::vec2 GetVertice1() const { return vertex1; }

private:
	glm::vec2 vertex0 = {};
	glm::vec2 vertex1 = {};
	float length;
	int id;
};

std::vector<Side> CreateSides(std::vector<glm::vec2>& vertices)
{
	std::vector<Side> sides = {};
	for (size_t i = 1; i < vertices.size(); i++)
	{
		Side s(vertices[i - 1], vertices[i], (int)i);
		sides.push_back(s);
	}
	Side sfinal(vertices[vertices.size() - 1], vertices[0], (int)vertices.size());
	sides.push_back(sfinal);

	return sides;
}

class Elements
{
public:
	Elements(std::vector<glm::vec2>& nodes, int i)
	{
		id = i;
		node0 = nodes[0];
		node1 = nodes[1];
		node2 = nodes[2];
	}
	std::vector<float> CalculateShapes(float xsi)
	{ 
		ShapeFunctions(nodeshape, xsi);

		return nodeshape;
	}
	std::vector<float> CalculateDerivatives(float xsi) 
	{ 
		ShapeFunctionsDerivatives(nodederivs, xsi);

		return nodederivs;
	}
	const glm::vec2 GetNode0() const { return node0; }
	const glm::vec2 GetNode1() const { return node1; }
	const glm::vec2 GetNode2() const { return node2; }
	const int GetId() const { return id; }

private:
	int id;
	glm::vec2 node0;
	glm::vec2 node1;
	glm::vec2 node2;
	std::vector<float> nodeshape;
	std::vector<float> nodederivs;
};

std::vector<Elements> Discretize(int elementsperside, std::vector<Side>& sides)
{
	std::vector<glm::vec2> nodes = {};
	std::vector<Elements> elements = {};
	nodes.resize(3);
	float elementlength;

	for (size_t i = 0; i < sides.size(); i++)
	{
		nodes[0] = sides[i].GetVertice0();
		elementlength = sides[i].Length() / elementsperside;
		for(int e = 0; e < elementsperside; e++)
		{
			nodes[1] = nodes[0] + (sides[i].GetVertice1() - sides[i].GetVertice0()) / sides[i].Length() * elementlength / 2.0f;
			nodes[2] = nodes[0] + (sides[i].GetVertice1() - sides[i].GetVertice0()) / sides[i].Length() * elementlength;
			Elements element(nodes, (e + 1) + 10 * (int)i);
			elements.push_back(element);
			nodes.clear();
			nodes.resize(3);
			nodes[0] = element.GetNode2();
		}
	}

	return elements;
}

struct GaussIntegral
{
	std::vector<float> gausscoords;
	std::vector<float> gaussweights;
};

GaussIntegral GaussPointsAndWeights(int intorder)
{
	std::vector<float> gausscoords;
	std::vector<float> gaussweights;

	switch (intorder)
	{
	case 1:
		gausscoords.push_back(0.0f);
		gaussweights.push_back(2.0f);
		break;
	case 2:
		gausscoords.push_back(-0.577350269f);
		gausscoords.push_back(0.577350269f);
		gaussweights.push_back(1.0f);
		gaussweights.push_back(1.0f);
		break;
	case 3:
		gausscoords.push_back(-0.774596669f);
		gausscoords.push_back(0.0f);
		gausscoords.push_back(0.774596669f);
		gaussweights.push_back(0.555555555f);
		gaussweights.push_back(0.888888888f);
		gaussweights.push_back(0.555555555f);
		break;
	case 4:
		gausscoords.push_back(-0.861136311f);
		gausscoords.push_back(-0.339981043f);
		gausscoords.push_back(0.339981043f);
		gausscoords.push_back(0.861136311f);
		gaussweights.push_back(0.347854845f);
		gaussweights.push_back(0.652145154f);
		gaussweights.push_back(0.652145154f);
		gaussweights.push_back(0.347854845f);
		break;
	case 5:
		gausscoords.push_back(-0.906179845f);
		gausscoords.push_back(-0.538469310f);
		gausscoords.push_back(0.0f);
		gausscoords.push_back(0.538469310f);
		gausscoords.push_back(-0.906179845f);
		gaussweights.push_back(0.236926885f);
		gaussweights.push_back(0.478628670f);
		gaussweights.push_back(0.568888888f);
		gaussweights.push_back(0.478628670f);
		gaussweights.push_back(0.236926885f);
		break;
	case 6:
		gausscoords.push_back(-0.932469514f);
		gausscoords.push_back(-0.661209386f);
		gausscoords.push_back(-0.238619186f);
		gausscoords.push_back(0.238619186f);
		gausscoords.push_back(0.661209386f);
		gausscoords.push_back(0.932469514f);
		gaussweights.push_back(0.171324492f);
		gaussweights.push_back(0.360761573f);
		gaussweights.push_back(0.467913934f);
		gaussweights.push_back(0.467913934f);
		gaussweights.push_back(0.360761573f);
		gaussweights.push_back(0.171324492f);
		break;
	case 7:
		gausscoords.push_back(-0.949107912f);
		gausscoords.push_back(-0.741531185f);
		gausscoords.push_back(-0.405845151f);
		gausscoords.push_back(0.0f);
		gausscoords.push_back(0.405845151f);
		gausscoords.push_back(0.741531185f);
		gausscoords.push_back(0.949107912f);
		gaussweights.push_back(0.129484966f);
		gaussweights.push_back(0.279705391f);
		gaussweights.push_back(0.381830050f);
		gaussweights.push_back(0.417959183f);
		gaussweights.push_back(0.381830050f);
		gaussweights.push_back(0.279705391f);
		gaussweights.push_back(0.129484966f);
		break;
	case 8:
		gausscoords.push_back(-0.960289856f);
		gausscoords.push_back(-0.796666477f);
		gausscoords.push_back(-0.525532409f);
		gausscoords.push_back(-0.183434642f);
		gausscoords.push_back(0.183434642f);
		gausscoords.push_back(0.525532409f);
		gausscoords.push_back(0.796666477f);
		gausscoords.push_back(0.960289856f);
		gaussweights.push_back(0.101228536f);
		gaussweights.push_back(0.222381034f);
		gaussweights.push_back(0.313706645f);
		gaussweights.push_back(0.362683783f);
		gaussweights.push_back(0.362683783f);
		gaussweights.push_back(0.313706645f);
		gaussweights.push_back(0.222381034f);
		gaussweights.push_back(0.101228536f);
		break;
	}

	return {gausscoords, gaussweights};
}

float CalculateTotalLength(std::vector<Elements>& elements, int intorder)
{
	float result = 0, xsi = 0;

	for (Elements element : elements)
	{
		for (int i = 0; i < intorder; i++)
		{
			xsi = GaussPointsAndWeights(intorder).gausscoords[i];
			result += Jacobian(Normal(element.CalculateDerivatives(xsi), element.GetNode0(), element.GetNode1(), element.GetNode2())) * GaussPointsAndWeights(intorder).gaussweights[i];
		}
	}

	return result;
}

int main()
{
	// define vertices
	std::vector<glm::vec2> vertices = {
		{0,0}, {300,0}, {300, 10}, {10, 10}, {10,200}, {0,200}
	};

	// define sides
	std::vector<Side> sides = CreateSides(vertices);

	// discretization
	std::vector<Elements> elements = Discretize(10, sides);

	std::cout << "Total length of cross-section (1): " << CalculateTotalLength(elements, 1) << std::endl;
	std::cout << "Total length of cross-section (2): " << CalculateTotalLength(elements, 2) << std::endl;
	std::cout << "Total length of cross-section (3): " << CalculateTotalLength(elements, 3) << std::endl;
	std::cout << "Total length of cross-section (4): " << CalculateTotalLength(elements, 4) << std::endl;
	std::cout << "Total length of cross-section (5): " << CalculateTotalLength(elements, 5) << std::endl;
	std::cout << "Total length of cross-section (6): " << CalculateTotalLength(elements, 6) << std::endl;
	std::cout << "Total length of cross-section (7): " << CalculateTotalLength(elements, 7) << std::endl;
	std::cout << "Total length of cross-section (8): " << CalculateTotalLength(elements, 8) << std::endl;
	
	std::cin.get();

	return 0;
}