#pragma once

#include <MathUtils.h>

float CalculateL(std::vector<Element>& elements, int intorder)
{
	float result = 0;

	for (Element element : elements)
	{
		for (int i = 0; i < intorder; i++)
		{
			float xsi = GaussPointsAndWeights(intorder).gausscoords[i];
			float W = GaussPointsAndWeights(intorder).gaussweights[i];

			std::vector<float> derivs = element.CalculateDerivatives(xsi);
			glm::vec2 normal = Normal(derivs, element.GetNode0(), element.GetNode1(), element.GetNode2());
			float j = Jacobian(normal);

			result += j * W;
		}
	}

	return result;
}

float CalculateA(std::vector<Element>& elements, int intorder)
{
	float result = 0;

	for (Element element : elements)
	{
		for (int i = 0; i < intorder; i++)
		{
			float xsi = GaussPointsAndWeights(intorder).gausscoords[i];
			float W = GaussPointsAndWeights(intorder).gaussweights[i];

			std::vector<float> derivs = element.CalculateDerivatives(xsi);
			glm::vec2 normal = Normal(derivs, element.GetNode0(), element.GetNode1(), element.GetNode2());
			float j = Jacobian(normal);

			std::vector<float> shapes = element.CalculateShapes(xsi);
			glm::vec2 coords = element.GetGlobalCoordinate(shapes);
			float dircosx = element.GetDirectorCosineX(derivs);
			float dircosy = element.GetDirectorCosineY(derivs);

			result += 0.5f * (coords.x * dircosx + coords.y * dircosy) * j * W;
		}
	}

	return result;
}

float CalculateSX(std::vector<Element>& elements, int intorder)
{
	float result = 0;

	for (Element element : elements)
	{
		for (int i = 0; i < intorder; i++)
		{
			float xsi = GaussPointsAndWeights(intorder).gausscoords[i];
			float W = GaussPointsAndWeights(intorder).gaussweights[i];

			std::vector<float> derivs = element.CalculateDerivatives(xsi);
			glm::vec2 normal = Normal(derivs, element.GetNode0(), element.GetNode1(), element.GetNode2());
			float j = Jacobian(normal);

			std::vector<float> shapes = element.CalculateShapes(xsi);
			glm::vec2 coords = element.GetGlobalCoordinate(shapes);
			float dircosy = element.GetDirectorCosineY(derivs);

			result += 0.5f * (coords.y * coords.y * dircosy) * j * W;
		}
	}

	return result;
}

float CalculateSY(std::vector<Element>& elements, int intorder)
{
	float result = 0;

	for (Element element : elements)
	{
		for (int i = 0; i < intorder; i++)
		{
			float xsi = GaussPointsAndWeights(intorder).gausscoords[i];
			float W = GaussPointsAndWeights(intorder).gaussweights[i];

			std::vector<float> derivs = element.CalculateDerivatives(xsi);
			glm::vec2 normal = Normal(derivs, element.GetNode0(), element.GetNode1(), element.GetNode2());
			float j = Jacobian(normal);

			std::vector<float> shapes = element.CalculateShapes(xsi);
			glm::vec2 coords = element.GetGlobalCoordinate(shapes);
			float dircosx = element.GetDirectorCosineX(derivs);

			result += 0.5f * (coords.x * coords.x * dircosx) * j * W;
		}
	}

	return result;
}

float CalculateIXX(std::vector<Element>& elements, int intorder)
{
	float result = 0;

	for (Element element : elements)
	{
		for (int i = 0; i < intorder; i++)
		{
			float xsi = GaussPointsAndWeights(intorder).gausscoords[i];
			float W = GaussPointsAndWeights(intorder).gaussweights[i];

			std::vector<float> derivs = element.CalculateDerivatives(xsi);
			glm::vec2 normal = Normal(derivs, element.GetNode0(), element.GetNode1(), element.GetNode2());
			float j = Jacobian(normal);

			std::vector<float> shapes = element.CalculateShapes(xsi);
			glm::vec2 coords = element.GetGlobalCoordinate(shapes);
			float dircosx = element.GetDirectorCosineX(derivs);

			result += (coords.y * coords.y * coords.x * dircosx) * j * W;
		}
	}

	return result;
}

float CalculateIYY(std::vector<Element>& elements, int intorder)
{
	float result = 0;

	for (Element element : elements)
	{
		for (int i = 0; i < intorder; i++)
		{
			float xsi = GaussPointsAndWeights(intorder).gausscoords[i];
			float W = GaussPointsAndWeights(intorder).gaussweights[i];

			std::vector<float> derivs = element.CalculateDerivatives(xsi);
			glm::vec2 normal = Normal(derivs, element.GetNode0(), element.GetNode1(), element.GetNode2());
			float j = Jacobian(normal);

			std::vector<float> shapes = element.CalculateShapes(xsi);
			glm::vec2 coords = element.GetGlobalCoordinate(shapes);
			float dircosy = element.GetDirectorCosineY(derivs);

			result += (coords.x * coords.x * coords.y * dircosy) * j * W;
		}
	}

	return result;
}