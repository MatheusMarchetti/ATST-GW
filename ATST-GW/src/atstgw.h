#pragma once

#include <MathUtils.h>
#include <Vertex.h>
#include <Side.h>
#include <Element.h>
#include <Functions.h>

template <typename T>
static std::vector<T> ReadInputFile()
{
	// Everything to be read from file
	std::vector<glm::vec2> vertices = {};

	std::ifstream input("resources/input.in");

	char checkChar;

	if (input)
	{
		while (input)
		{
			checkChar = input.get();

			switch (checkChar)
			{
			case '#':
				checkChar = input.get();
				while (checkChar != '\n')
					checkChar = input.get();
				break;

			case 'v':
				checkChar = input.get();
				if (checkChar == ' ')
				{
					float x, y;
					input >> x >> y;

					vertices.push_back(glm::vec2(x, y));
				}
				break;
			}
		}
	}
	else
		__debugbreak;

	if (typeid(T) == typeid(glm::vec2)) return vertices;
}

static std::vector<Vertex> CreateVertices()
{
	std::vector<glm::vec2> vertices = ReadInputFile<glm::vec2>();

	std::vector<Vertex> vert = {};
	for (size_t i = 0; i < vertices.size(); i++)
	{
		Vertex v(vertices[i], (int)i + 1);
		vert.push_back(v);
	}

	return vert;
}

static std::vector<Side> CreateSides(std::vector<Vertex>& vertices)
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

static std::vector<Element> Discretize(int elementsperside, std::vector<Side>& sides)
{
	std::vector<glm::vec2> nodes = {};
	std::vector<Element> elements = {};
	nodes.resize(3);
	float elementlength;

	for (size_t i = 0; i < sides.size(); i++)
	{
		nodes[0] = sides[i].GetVertex0();
		elementlength = sides[i].Length() / elementsperside;
		for (int e = 0; e < elementsperside; e++)
		{
			nodes[1] = nodes[0] + (sides[i].GetVertex1() - sides[i].GetVertex0()) / sides[i].Length() * elementlength / 2.0f;
			nodes[2] = nodes[0] + (sides[i].GetVertex1() - sides[i].GetVertex0()) / sides[i].Length() * elementlength;
			Element element(nodes, (e + 1) + elementsperside * (int)i);
			elements.push_back(element);
			nodes.clear();
			nodes.resize(3);
			nodes[0] = element.GetNode2();
		}
	}

	return elements;
}