#pragma once

struct GaussIntegral
{
	std::vector<float> gausscoords;
	std::vector<float> gaussweights;
};

static void ShapeFunctions(std::vector<float>& shapefuncs, float xsi)
{
	float N1, N2, N3;
	N1 = 0.5f * (1.0f - xsi);
	N2 = 0.5f * (1.0f + xsi);

	if ((int)shapefuncs.size() == 2)
	{
		shapefuncs[0] = N1;
		shapefuncs[1] = N2;
	}
	else
	{
		N3 = 1.0f - xsi * xsi;
		shapefuncs[0] = N1 - 0.5f * N3;
		shapefuncs[1] = N3;
		shapefuncs[2] = N2 - 0.5f * N3;
	}
}

static void ShapeFunctionsDerivatives(std::vector<float>& shapederivs, float xsi)
{
	float N1, N2, N3;
	N1 = -0.5f;
	N2 = 0.5f;

	if ((int)shapederivs.size() == 2)
	{
		shapederivs[0] = N1;
		shapederivs[1] = N2;
	}
	else
	{
		N3 = -2.0f * xsi;
		shapederivs[0] = N1 - 0.5f * N3;
		shapederivs[1] = N3;
		shapederivs[2] = N2 - 0.5f * N3;
	}
}

static float Jacobian(glm::vec2& vector)
{
	return glm::length(vector);
}

static glm::vec2 Normal(std::vector<float>& shapederivs, const std::vector<glm::vec2>& nodes)
{
	glm::vec2 v1 = {};

	for (size_t i = 0; i < nodes.size(); i++)
	{
		v1 += shapederivs[i] * nodes[i];
	}

	return glm::dvec2(glm::cross(glm::vec3(v1, 0), { 0, 0, 1 }));
}

static GaussIntegral GaussPointsAndWeights(int intorder)
{
	std::vector<float> gausscoords;
	std::vector<float> gaussweights;

	switch (intorder)
	{
	case 1:
		gausscoords.push_back(0.0f);
		gaussweights.push_back(2.0f);
		break;
	case 2:
		gausscoords.push_back(-0.577350269f);
		gausscoords.push_back(0.577350269f);
		gaussweights.push_back(1.0f);
		gaussweights.push_back(1.0f);
		break;
	case 3:
		gausscoords.push_back(-0.774596669f);
		gausscoords.push_back(0.0f);
		gausscoords.push_back(0.774596669f);
		gaussweights.push_back(0.555555555f);
		gaussweights.push_back(0.888888888f);
		gaussweights.push_back(0.555555555f);
		break;
	case 4:
		gausscoords.push_back(-0.861136311f);
		gausscoords.push_back(-0.339981043f);
		gausscoords.push_back(0.339981043f);
		gausscoords.push_back(0.861136311f);
		gaussweights.push_back(0.347854845f);
		gaussweights.push_back(0.652145154f);
		gaussweights.push_back(0.652145154f);
		gaussweights.push_back(0.347854845f);
		break;
	case 5:
		gausscoords.push_back(-0.906179845f);
		gausscoords.push_back(-0.538469310f);
		gausscoords.push_back(0.0f);
		gausscoords.push_back(0.538469310f);
		gausscoords.push_back(-0.906179845f);
		gaussweights.push_back(0.236926885f);
		gaussweights.push_back(0.478628670f);
		gaussweights.push_back(0.568888888f);
		gaussweights.push_back(0.478628670f);
		gaussweights.push_back(0.236926885f);
		break;
	case 6:
		gausscoords.push_back(-0.932469514f);
		gausscoords.push_back(-0.661209386f);
		gausscoords.push_back(-0.238619186f);
		gausscoords.push_back(0.238619186f);
		gausscoords.push_back(0.661209386f);
		gausscoords.push_back(0.932469514f);
		gaussweights.push_back(0.171324492f);
		gaussweights.push_back(0.360761573f);
		gaussweights.push_back(0.467913934f);
		gaussweights.push_back(0.467913934f);
		gaussweights.push_back(0.360761573f);
		gaussweights.push_back(0.171324492f);
		break;
	case 7:
		gausscoords.push_back(-0.949107912f);
		gausscoords.push_back(-0.741531185f);
		gausscoords.push_back(-0.405845151f);
		gausscoords.push_back(0.0f);
		gausscoords.push_back(0.405845151f);
		gausscoords.push_back(0.741531185f);
		gausscoords.push_back(0.949107912f);
		gaussweights.push_back(0.129484966f);
		gaussweights.push_back(0.279705391f);
		gaussweights.push_back(0.381830050f);
		gaussweights.push_back(0.417959183f);
		gaussweights.push_back(0.381830050f);
		gaussweights.push_back(0.279705391f);
		gaussweights.push_back(0.129484966f);
		break;
	case 8:
		gausscoords.push_back(-0.960289856f);
		gausscoords.push_back(-0.796666477f);
		gausscoords.push_back(-0.525532409f);
		gausscoords.push_back(-0.183434642f);
		gausscoords.push_back(0.183434642f);
		gausscoords.push_back(0.525532409f);
		gausscoords.push_back(0.796666477f);
		gausscoords.push_back(0.960289856f);
		gaussweights.push_back(0.101228536f);
		gaussweights.push_back(0.222381034f);
		gaussweights.push_back(0.313706645f);
		gaussweights.push_back(0.362683783f);
		gaussweights.push_back(0.362683783f);
		gaussweights.push_back(0.313706645f);
		gaussweights.push_back(0.222381034f);
		gaussweights.push_back(0.101228536f);
		break;
	}

	return { gausscoords, gaussweights };
}