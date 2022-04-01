#include "corepch.h"

#include <atstgw.h>

int main()
{
	ReadInputFile(section, timer);

	section.vertices = CreateVertices(section);
	section.sides = CreateSides(section.vertices);
	section.elements = Discretize(10, section.sides);

	section.perimeter = CalculateL(section.elements, 3);
	section.area = CalculateA(section.elements, 3);
	section.sx = CalculateSX(section.elements, 3);
	section.sy = CalculateSY(section.elements, 3);
	section.Ixx = CalculateIXX(section.elements, 3);
	section.Iyy = CalculateIYY(section.elements, 3);

	WriteOutputFile(section, timer);

	return 0;
}