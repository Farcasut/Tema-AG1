#pragma once
#include "bitRepresentation.h"

//argumente-> original, evaluarea originalului,string pentru a seta min/max, pointer catre functia necesara pentru evaluarea vecinului, pointer pentru a
//evalua ifului;

bitRepresentation bestImprovment(bitRepresentation& initial, double initialValue, std::string minMax, double (*pointerToEvaluate)(std::vector<double>), bool (*trueFalse)(const double& a, const double& b))
{
	int bestBit = -1;
	double best = minMax == "min" ? INFINITY : -INFINITY;

	const int LOOP = initial.getTLD();
	for (int i = 0; i < LOOP; i++)
	{
		auto n = initial.neighbour(i);
		double current = pointerToEvaluate(n.decodeAllSlices());
		if (trueFalse(current, best))
		{
			bestBit = i;
			best = current;
		}
	}
	return initial.neighbour(bestBit);
}
bitRepresentation worstImprovment(bitRepresentation& initial, double initialValue, std::string minMax, double (*pointerToEvaluate)(std::vector<double>), bool (*trueFalse)(const double& a, const double& b))
{
	int bestBit = -1;
	double best = minMax == "min" ? -INFINITY : INFINITY;

	const int LOOP = initial.getTLD();
	for (int i = 0; i < LOOP; i++)
	{
		auto n = initial.neighbour(i);
		double current = pointerToEvaluate(n.decodeAllSlices());
		if (trueFalse(current, initialValue) && !trueFalse(current, best))
		{
			bestBit = i;
			best = current;
		}
	}
	return bestBit == -1 ? initial: initial.neighbour(bestBit);
}
bitRepresentation firstImprovment(bitRepresentation& initial, double initialValue, std::string minMax, double (*pointerToEvaluate)(std::vector<double>), bool (*trueFalse)(const double& a, const double& b))
{
	const int LOOP = initial.getTLD();
	for (int i = 0; i < LOOP; i++)
	{
		auto n = initial.neighbour(i);
		if (trueFalse(pointerToEvaluate(n.decodeAllSlices()), initialValue))
			return n;
	}
	return initial;
}
