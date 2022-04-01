#pragma once

struct Data
{
	// Raw input data
	std::vector<glm::vec2> vertex = {};

	// Processed data
	std::vector<Vertex> vertices = {};
	std::vector<Side> sides = {};
	std::vector<Element> elements = {};

	// Geometric results
	float perimeter;
	float area;
} section;