#include <chrono>
#include "hillClimbing.h"
#include <iostream>
#include <fstream>
#include <map>
#include <thread>
#include "funtctions.h"
#include "improvmentFunctions.h"
#include "simulatedAnnealing.h"
#include <string>
void startCliming(double (*ptr)(std::vector<double>), bool (*ptrtrueFalse)(const double& a, const double& b), bitRepresentation(*improvmentPtr)(bitRepresentation& initial, double initialValue, std::string minMax, double (*pointerToEvaluate)(std::vector<double>), bool (*trueFalse)(const double& a, const double& b)), std::string minMax, int numberOfIterations, std::string file, double start, double end, int precision, int dimensions, char improvmentType, char dim)
{
	file += improvmentType;
	file += dim;
	std::string tm = file + "time";
	std::fstream time;
	time.open(tm, std::fstream::in | std::ios_base::out | std::fstream::app);
	std::vector<double> result;
	
	for (int i = 0; i < 30; i++)
	{

		hillCliming generic(ptr, ptrtrueFalse, improvmentPtr, minMax, numberOfIterations, file);
		auto st = std::chrono::steady_clock::now();
		double x = generic.hillClimingStart(start, end, precision, dimensions);
		auto ed = std::chrono::steady_clock::now();
		std::chrono::duration<double> elapsed_seconds = ed - st;
		time << std::fixed << std::setprecision(5) << elapsed_seconds.count() << "\n";
		result.push_back(x);
	}
	file += "R";
	std::fstream res;
	res.open(file, std::fstream::in | std::ios_base::out | std::fstream::app);
	for(auto x:result)
	{
		res << x << "\n";
	}
	
}


void startAnnealing(double(*ptr)(std::vector<double>), bool(*ptrTrueFasle)(const double&a, const double&b), std::string minMax, std::string fileName,double start, double end,double precision,int dimensions, char d)
{
	fileName += d;
	std::string tm = fileName + "time";
	std::fstream time;
	time.open(tm, std::fstream::in | std::ios_base::out | std::fstream::app);
	
	for (int i=0; i<30; i++)
	{
		simulatedAnnealing generic(ptr, ptrTrueFasle, minMax, fileName);
		auto st = std::chrono::steady_clock::now();
		generic.startSimulatedAnnealing(start, end, precision, dimensions);
		auto ed = std::chrono::steady_clock::now();
		std::chrono::duration<double> elapsed_seconds = ed - st;
		time << elapsed_seconds.count() << "\n";

	}


}


void ste2(){
	auto min = [](const double& a, const double& b)
	{
		return a < b;
	};
	auto max = [](const double& a, const double& b)
	{
		return a > b;
	};
	startAnnealing(Michalewicz, min, "min", "SimulatedAnnealing-M", 0, PI, 5, 30, '3');

}





int main()
{
	auto min = [](const double& a, const double& b)
	{
		return a < b;
	};
	auto max = [](const double& a, const double& b)
	{
		return a > b;
	};
	//startCliming(Rastrigin, min, bestImprovment, "min", 10000, "Rastrigin-", -5.12, 5.12, 5, 5, 'B', '5');
	startAnnealing(Rastrigin, min, "min", "Test", -5.12, 5.12, 5, 10, 'R');
	
	//for(int i=0;i<10;i++)
	//{
	//	
	//}
	//std::thread fc2(ste2);
	//for (int i = 0; i < 10; i++)
	//{

	//}
	//std::thread fc31(ste3);
	//fc2.join();
	//fc31.join();

	

	return 0;
}