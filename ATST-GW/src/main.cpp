#include "corepch.h"

#include <atstgw.h>

int main()
{
	ReadInputFile(section);

	section.vertices = CreateVertices(section);
	section.sides = CreateSides(section.vertices);
	section.elements = Discretize(1, section.sides);

	section.perimeter = CalculateTotalLength(section.elements, 1);
	section.area = CalculateArea(section.elements, 1);
	
//	std::cin.get();

	WriteOutputFile(section);

	return 0;
}