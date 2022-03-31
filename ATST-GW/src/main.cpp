#include "corepch.h"

#define GLM_FORCE_SWIZZLE

#include <stdio.h>
#include <iostream>
#include <vector>
#include "glm/glm.hpp"
	
void ShapeFunctions(std::vector<glm::vec2>& nodes, glm::vec2& coords)
{
	glm::vec2 node0, node1;
	node0 = { 0.5 * (1 - coords.x), 0.5 * (1 - coords.y) };
	node1 = { 0.5 * (1 + coords.x), 0.5 * (1 + coords.y) };

	nodes.push_back(node0);
	nodes.push_back(node1);
}

void ShapeFunctionsDerivatives(std::vector<glm::vec2>& nodes, glm::vec2& coords)
{
	glm::vec2 node0, node1;
	node0 = { 0.5, 0.5 };
	node1 = { 0.5, 0.5 };

	nodes.push_back(node0);
	nodes.push_back(node1);
}

glm::vec2 PositionInGlobalCoordinates(std::vector<glm::vec2>& shapes, glm::vec2& globalcoords, std::vector<glm::vec2>& nodecoords)
{
	ShapeFunctions(shapes, globalcoords);
	glm::vec2 position = {};

	for (size_t i = 0; i < nodecoords.size(); i++)
	{
		position += shapes[i] * nodecoords[i];
	}

	return position;
}

glm::vec2 VectorInElementDirection(std::vector<glm::vec2>& nodederivs, glm::vec2& globalcoords, std::vector<glm::vec2>& nodecoords)
{
	//nodederivs -> to store node derivatives;
	//globalcoords -> global coordinates of a point in the element;
	//nodecoords -> global coordinates of the nodes;
	ShapeFunctionsDerivatives(nodederivs, globalcoords);
	glm::vec2 v = {};

	for (size_t i = 0; i < nodecoords.size(); i++)
	{
		v += nodederivs[i] * nodecoords[i];
	}

	return v;
}

glm::vec2 Normal(glm::vec2& vector)
{
	return glm::normalize(glm::cross(glm::vec3(vector, 0), {0,0,1})).xy;
}

float Jacobian(glm::vec2& vector)
{
	glm::vec2 v = Normal(vector);
	return glm::length(v);
}

class Sides
{
public:
	Sides(float l, int i) : length(l), id(i) {}
	Sides(std::vector<glm::vec2>& vertices)
	{
		glm::vec2 v1 = {};

		for (size_t i = 1; i < vertices.size(); i++)
		{
			v1 = vertices[i] - vertices[i - 1];
			length = Length(v1);
			id = (int)i;
			vertex0 = vertices[i - 1];
			vertex1 = vertices[i];
			sides.push_back({ length, id });
		}

		v1 = vertices[0] - vertices[vertices.size() - 1];
		length = Length(v1);
		id = (int)vertices.size();
		sides.push_back({ length, id });
	}
	float Length(glm::vec2 vector) { return glm::length(vector); }
	float Length() { return length; }
	int Id() { return id; }
	std::vector<Sides> List() { return sides; }
	glm::vec2 GetVertice0() { return vertex0; }
	glm::vec2 GetVertice1() { return vertex1; }

private:
	std::vector<Sides> sides = {};
	glm::vec2 vertex0 = {};
	glm::vec2 vertex1 = {};
	float length;
	int id;
};

class Elements
{
public:
	Elements(std::vector<glm::vec2>& nodes, int i)
	{
		id = i;
		node0 = nodes[0];
		node1 = nodes[1];
		parallelvector = node1 - node0;
		normalvector = Normal(parallelvector);
	}
	std::vector<glm::vec2> GetShapes() { return nodeshape; }
	std::vector<glm::vec2> GetDerivatives() { return nodederivs; }
	glm::vec2 GetNode0() { return node0; }
	glm::vec2 GetNode1() { return node1; }
	glm::vec2 GetVector() { return parallelvector; }
	glm::vec2 GetNormal() { return normalvector; }
	int GetId() { return id; }

private:
	int id;
	glm::vec2 node0;
	glm::vec2 node1;
	glm::vec2 parallelvector;
	glm::vec2 normalvector;
	std::vector<glm::vec2> nodeshape;
	std::vector<glm::vec2> nodederivs;
};

void Discretize(std::vector<Elements>& elements, int elementsperside, std::vector<Sides>& sides)
{
	std::vector<glm::vec2> nodes = {};
	nodes.resize(2);
	float elementlength;

	for (size_t i = 0; i < sides.size(); i++)
	{
		int e = 0;
		nodes.push_back(sides[i].GetVertice0());
		elementlength = sides[i].Length() / elementsperside;
		while (e < elementsperside)
		{
			nodes.push_back(nodes[0] + (sides[i].GetVertice1() - sides[i].GetVertice0()) / sides[i].Length() * elementlength);
			Elements element(nodes, (e + 1) + 10 * (int)i);
			elements.push_back(element);
			nodes.clear();
			nodes.push_back(element.GetNode0());

			e++;
		}
	}
}

int main()
{
	// define vertices
	std::vector<glm::vec2> vertices = {
		{0,0}, {300,0}, {300, 10}, {10, 10}, {10,200}, {0,200}
	};

	// define sides
	Sides s(vertices);
	std::vector<Sides> sides = s.List();

	// discretization
	std::vector<Elements> elements;
	Discretize(elements, 10, sides);

	for (size_t i = 0; i < elements.size(); i++)
	{
		std::cout << "Element id: " << elements[i].GetId() << std::endl;
	}
	
	std::cin.get();

	return 0;
}