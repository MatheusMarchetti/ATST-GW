#pragma once

#include <MathUtils.h>

float CalculateTotalLength(std::vector<Element>& elements, int intorder)
{
	float result = 0, xsi = 0, W = 0;

	for (Element element : elements)
	{
		for (int i = 0; i < intorder; i++)
		{
			xsi = GaussPointsAndWeights(intorder).gausscoords[i];
			W = GaussPointsAndWeights(intorder).gaussweights[i];

			std::vector<float> derivs = element.CalculateDerivatives(xsi);
			glm::vec2 normal = Normal(derivs, element.GetNode0(), element.GetNode1(), element.GetNode2());
			float jacobian = Jacobian(normal);

			result += jacobian * W;
		}
	}

	return result;
}

float CalculateArea(std::vector<Element>& elements, int intorder)
{
	float result = 0, xsi = 0, W = 0;

	for (Element element : elements)
	{
		for (int i = 0; i < intorder; i++)
		{
			xsi = GaussPointsAndWeights(intorder).gausscoords[i];
			W = GaussPointsAndWeights(intorder).gaussweights[i];

			std::vector<float> shapes = element.CalculateShapes(xsi);
			std::vector<float> derivs = element.CalculateDerivatives(xsi);
			glm::vec2 coords = element.GetGlobalCoordinate(shapes);
			float dircosx = element.GetDirectorCosineX(derivs);
			float dircosy = element.GetDirectorCosineY(derivs);

			result += (coords.x * dircosx + coords.y * dircosy) * W;
		}
	}

	return result;
}