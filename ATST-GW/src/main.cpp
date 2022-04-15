#include "corepch.h"

#include <atstgw.h>

int main()
{
	ReadInputFile(section, timer);

	int numberofnodes = 2;
	int elementsperside = 1;
	int integrationorder = 3;

	section.vertices = CreateVertices(section);
	section.sides = CreateSides(section.vertices);
	section.elements = Discretize(numberofnodes, elementsperside, section.sides);

	section.perimeter = CalculateL(section.elements, integrationorder);
	section.area = CalculateA(section.elements, integrationorder);
	section.sx = CalculateSX(section.elements, integrationorder);
	section.sy = CalculateSY(section.elements, integrationorder);
	section.Ixx = CalculateIXX(section.elements, integrationorder);
	section.Iyy = CalculateIYY(section.elements, integrationorder);
	section.Ixy = CalculateIXY(section.elements, integrationorder);

	WriteOutputFile(section, timer);

	return 0;
}