#pragma once
#include <fstream>
#include "bitRepresentation.h"






class hillCliming
{
	
	int numberOfIterations;
	double best;
	double (*pointerToEvaluate)(std::vector<double>);
	bitRepresentation (*improvment)(bitRepresentation& initial, double initialValue, std::string minMax, double (*pointerToEvaluate)(std::vector<double>), bool (*trueFalse)(const double& a, const double& b));
	bool (*trueFalse)(const double& a, const double& b);
	std::string minMax;
	std::string fileName;
public:

	

	hillCliming(double (*ptr)(std::vector<double>), bool (*ptrtrueFalse)(const double& a, const double& b),bitRepresentation(*improvmentPtr)(bitRepresentation& initial, double initialValue, std::string minMax, double (*pointerToEvaluate)(std::vector<double>), bool (*trueFalse)(const double& a, const double& b)), std::string minMax, int numberOfIterations, std::string file)
	{
		std::cout << file << " " << numberOfIterations <<"\n";
		this->minMax = minMax;
		if (ptrtrueFalse != nullptr)
			trueFalse = ptrtrueFalse;
		else
			throw("Invalid pointer to true false function");
		if (improvmentPtr != nullptr)
			improvment = improvmentPtr;
		else
			throw("Invalid pointer to improvment function");
		if (ptr != nullptr)
			pointerToEvaluate = ptr;
		else
			throw("Invalid Pointer to evalutate function");
		if (minMax == "min")
			best = INFINITY;
		else
			best = -INFINITY;
		this->numberOfIterations = numberOfIterations;
		this->fileName = file;
	}

	double hillClimingStart(double start, double end, int precision, int dimensions)
	{
		//std::cout << dimensions;
		std::fstream file;
		file.open(fileName, std::fstream::in |std::ios_base::out| std::fstream::app);


		std::vector<double> bestPoints;
		while (numberOfIterations-- >0)
		{
			if(numberOfIterations%1000==0)
			{
				printf("%d\n", numberOfIterations);
			}
			bool local = false;
			bitRepresentation initial(start, end, precision, dimensions);
			initial.createRandomString();
			double evalInitial = pointerToEvaluate(initial.decodeAllSlices());
			while(!local)
			{	
				bitRepresentation successor = improvment(initial, evalInitial, minMax, pointerToEvaluate, trueFalse);
				double evalSuccessor = pointerToEvaluate(successor.decodeAllSlices());
				if (trueFalse(evalSuccessor, evalInitial))
				{
					evalInitial = evalSuccessor;
					initial = successor;
				}
				else
				{

					local = true;
				
				}
			}
			if (trueFalse(evalInitial, best))
			{
				best = evalInitial;
				bestPoints = initial.decodeAllSlices();
			}
			

		}
		const int sizeBestPoints =bestPoints.size();
		for (int i=0; i < sizeBestPoints; i++)
		{
			file << std::fixed << std::setprecision(5)<< bestPoints[i]<< " ";
		}
		file << std::fixed<<std::setprecision(5) << best;
		file << "\n";

		std::cout << fileName <<" "<< std::fixed << std::setprecision(5) << best <<"\n";
		return best;
	}
	std::string getMinMax() { return minMax; }
};