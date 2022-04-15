#pragma once

#include <MathUtils.h>

float CalculateL(std::vector<Element>& elements, int intorder)
{
	float result = 0;
	GaussIntegral coeffs = GaussPointsAndWeights(intorder);

	for (Element element : elements)
	{
		for (int i = 0; i < intorder; i++)
		{
			float xsi = coeffs.gausscoords[i];
			float W = coeffs.gaussweights[i];

			glm::vec2 normal = Normal(element.CalculateDerivatives(xsi), element.GetNode());
			float j = Jacobian(normal);

			result += 0.5f * element.GetLength() * W;
		}
	}

	return result;
}

float CalculateA(std::vector<Element>& elements, int intorder)
{
	float result = 0;
	GaussIntegral coeffs = GaussPointsAndWeights(intorder);

	for (Element element : elements)
	{
		for (int i = 0; i < intorder; i++)
		{
			float xsi = coeffs.gausscoords[i];
			float W = coeffs.gaussweights[i];

			glm::vec2 normal = Normal(element.CalculateDerivatives(xsi), element.GetNode());
			float j = Jacobian(normal);

			glm::vec2 coords = element.GetGlobalCoordinate(element.CalculateShapes(xsi));
			float dircosx = element.GetDirectorCosineX(element.CalculateDerivatives(xsi));
			float dircosy = element.GetDirectorCosineY(element.CalculateDerivatives(xsi));

			result += 0.5f * abs((coords.x * dircosx + coords.y * dircosy)) * j * W;
		}
	}

	return result;
}

//float CalculateA(std::vector<Element>& elements, int intorder)
//{
//	float result = 0.0f;
//	GaussIntegral coeffs = GaussPointsAndWeights(intorder);
//
//	for (auto element : elements)
//	{
//		for (int i = 0; i < intorder; ++i)
//		{
//			float xsi = coeffs.gausscoords[i];
//			float w = coeffs.gaussweights[i];
//
//			float dircosx = element.GetDirectorCosineX(element.CalculateDerivatives(xsi));
//			float dircosy = element.GetDirectorCosineY(element.CalculateDerivatives(xsi));
//
//			glm::vec2 coords = element.GetGlobalCoordinate(element.CalculateShapes(xsi));
//
//			result += 0.5f * abs((coords.x * dircosy + coords.y * dircosx)) * w * 0.5f * element.GetLength();
//		}
//	}
//
//	return result;
//}

float CalculateSX(std::vector<Element>& elements, int intorder)
{
	float result = 0;
	GaussIntegral coeffs = GaussPointsAndWeights(intorder);

	for (Element element : elements)
	{
		for (int i = 0; i < intorder; i++)
		{
			float xsi = coeffs.gausscoords[i];
			float W = coeffs.gaussweights[i];

			glm::vec2 normal = Normal(element.CalculateDerivatives(xsi), element.GetNode());
			float j = Jacobian(normal);

			glm::vec2 coords = element.GetGlobalCoordinate(element.CalculateShapes(xsi));
			float dircosy = element.GetDirectorCosineY(element.CalculateDerivatives(xsi));

			result += 0.5f * abs((coords.y * coords.y * dircosy)) * j * W;
		}
	}

	return result;
}

float CalculateSY(std::vector<Element>& elements, int intorder)
{
	float result = 0;
	GaussIntegral coeffs = GaussPointsAndWeights(intorder);

	for (Element element : elements)
	{
		for (int i = 0; i < intorder; i++)
		{
			float xsi = coeffs.gausscoords[i];
			float W = coeffs.gaussweights[i];

			glm::vec2 normal = Normal(element.CalculateDerivatives(xsi), element.GetNode());
			float j = Jacobian(normal);

			glm::vec2 coords = element.GetGlobalCoordinate(element.CalculateShapes(xsi));
			float dircosx = element.GetDirectorCosineX(element.CalculateDerivatives(xsi));

			result += 0.5f * abs((coords.x * coords.x * dircosx)) * j * W;
		}
	}

	return result;
}

float CalculateIXX(std::vector<Element>& elements, int intorder)
{
	float result = 0;
	GaussIntegral coeffs = GaussPointsAndWeights(intorder);

	for (Element element : elements)
	{
		for (int i = 0; i < intorder; i++)
		{
			float xsi = coeffs.gausscoords[i];
			float W = coeffs.gaussweights[i];

			glm::vec2 normal = Normal(element.CalculateDerivatives(xsi), element.GetNode());
			float j = Jacobian(normal);

			glm::vec2 coords = element.GetGlobalCoordinate(element.CalculateShapes(xsi));
			float dircosx = element.GetDirectorCosineX(element.CalculateDerivatives(xsi));

			result += abs((coords.y * coords.y * coords.x * dircosx)) * j * W;
		}
	}

	return result;
}

float CalculateIYY(std::vector<Element>& elements, int intorder)
{
	float result = 0;
	GaussIntegral coeffs = GaussPointsAndWeights(intorder);

	for (Element element : elements)
	{
		for (int i = 0; i < intorder; i++)
		{
			float xsi = coeffs.gausscoords[i];
			float W = coeffs.gaussweights[i];

			glm::vec2 normal = Normal(element.CalculateDerivatives(xsi), element.GetNode());
			float j = Jacobian(normal);

			glm::vec2 coords = element.GetGlobalCoordinate(element.CalculateShapes(xsi));
			float dircosy = element.GetDirectorCosineY(element.CalculateDerivatives(xsi));

			result += abs((coords.x * coords.x * coords.y * dircosy)) * j * W;
		}
	}

	return result;
}

float CalculateIXY(std::vector<Element>& elements, int intorder)
{
	float result = 0;
	GaussIntegral coeffs = GaussPointsAndWeights(intorder);

	for (Element element : elements)
	{
		for (int i = 0; i < intorder; i++)
		{
			float xsi = coeffs.gausscoords[i];
			float W = coeffs.gaussweights[i];

			glm::vec2 normal = Normal(element.CalculateDerivatives(xsi), element.GetNode());
			float j = Jacobian(normal);

			glm::vec2 coords = element.GetGlobalCoordinate(element.CalculateShapes(xsi));
			float dircosx = element.GetDirectorCosineX(element.CalculateDerivatives(xsi));
			float dircosy = element.GetDirectorCosineY(element.CalculateDerivatives(xsi));

			result += 0.25f * (coords.x * coords.x * coords.y * dircosx + coords.y * coords.y * coords.x * dircosy) * j * W;
		}
	}

	return result;
}