#include "corepch.h"

#include <atstgw.h>

int main()
{
	std::vector<Vertex> vertices = CreateVertices();

	for (Vertex vertex : vertices)
	{
		std::cout << "Vertex id: " << vertex.GetId() << " - coordinates: (" << vertex.GetVertex().x << ", " << vertex.GetVertex().y << ")" << std::endl;
	}

	// define sides
	std::vector<Side> sides = CreateSides(vertices);

	for (Side side : sides)
	{
		std::cout << "Side id: " << side.GetId() << " - connectivities: (" << side.GetVertex0Id() << ", " << side.GetVertex1Id() << ")" << std::endl;
	}

	// discretization
	std::vector<Element> elements = Discretize(1, sides);

	std::cout << "Element perimeter: " << CalculateTotalLength(elements, 1) << std::endl;
	std::cout << "Element area: " << CalculateArea(elements, 1) << std::endl;
	
	std::cin.get();

	return 0;
}