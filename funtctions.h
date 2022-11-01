#pragma once
#include <vector>

const double PI = 3.14159;



////////////////////////////////////////////////
double Michalewicz(std::vector<double> values)
{
	const int m = 10;
	double sum = 0;
	int size = values.size();
	for (int i = 0; i < size; i++)
	{
		sum += sin(values[i]) * pow(sin(((i + 1) * values[i] * values[i]) / PI), 2 * m);
	}
	return -sum;
}
////////////////////////////////////////////////
double DeJong(std::vector<double> values)
{
	double sum = 0;
	int size = values.size();
	for (int i = 0; i < size; i++)
	{
		sum += values[i] * values[i];
	}
	return sum;
}
////////////////////////////////////////////////
double Schwelf(std::vector<double> values)
{
	double sum = 0;
	int size = values.size();
	for (int i = 0; i < size; i++)
	{
		sum += (-values[i]) * sin(sqrt(abs(values[i])));
	}
	return sum;
}
////////////////////////////////////////////////
double Rastrigin(std::vector<double> values)
{
	double sum = 0;
	int n = values.size();
	for(int i=0; i<n; i++)
	{
		sum += (values[i] * values[i]) - 10 * cos(2 * PI * values[i]);
	}
	return 10 * n + sum;
}