#pragma once

#include <MathUtils.h>
#include <Vertex.h>
#include <Side.h>
#include <Element.h>
#include <Functions.h>
#include <Data.h>

static void ReadInputFile(Data& data)
{
	std::ifstream input("io/input.in");

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

					data.vertex.push_back(glm::vec2(x, y));
				}
				break;
			}
		}

		input.close();
	}
	else
		__debugbreak;
}

static std::vector<Vertex> CreateVertices(Data& data)
{
	std::vector<Vertex> vert = {};
	for (size_t i = 0; i < data.vertex.size(); i++)
	{
		Vertex v(data.vertex[i], (int)i + 1);
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

static void WriteOutputFile(Data& data)
{
	auto now = std::chrono::system_clock::now();
	std::time_t time = std::chrono::system_clock::to_time_t(now);
	std::ofstream output("io/output.out");

	output << "Analysis realized on " << std::ctime(&time) << std::endl;
	output << "### INPUT PROPERTIES ###" << std::endl;
	output << std::endl;

	for (Vertex vertex : data.vertices)
	{
		output << "Vertex [" << vertex.GetId() << "] coordinates: (" << vertex.GetVertex().x << ", " << vertex.GetVertex().y << ")" << std::endl;
	}

	output << std::endl;

	for (Side side : data.sides)
	{
		output << "Side [" << side.GetId() << "] connectivities: (" << side.GetVertex0Id() << ", " << side.GetVertex1Id() << ")" << std::endl;
	}

	output << std::endl;
	output << "Total number of elements created: " << data.elements.size() << std::endl;
	output << std::endl;

	output << "### GEOMETRIC PROPERTIES ###" << std::endl;
	output << std::endl;

	output << "Perimeter: " << data.perimeter << std::endl;
	output << "Area: " << data.area << std::endl;

	output.close();
}