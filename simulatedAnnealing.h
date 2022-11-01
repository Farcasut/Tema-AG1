

#include "bitRepresentation.h"




class simulatedAnnealing
{
	double best;
	double (*pointerToEvaluate)(std::vector<double>);
	bool (*trueFalse)(const double& a, const double& b);
	std::string minMax;
	std::string fileName;
public:

	simulatedAnnealing(double (*ptr)(std::vector<double>), bool (*ptrtrueFalse)(const double& a, const double& b), std::string minMax, std::string file)
	{
		std::cout << file <<"\n";
		this->minMax = minMax;
		if (ptrtrueFalse != nullptr)
			trueFalse = ptrtrueFalse;
		else
			throw("Invalid pointer to true false function");
		if (ptr != nullptr)
			pointerToEvaluate = ptr;
		else
			throw("Invalid Pointer to evalutate function");
		if (minMax == "min")
			best = INFINITY;
		else
			best = -INFINITY;
		this->fileName = file;
	}


	void startSimulatedAnnealing(double start, double end, int precision, int dimension)
	{
		std::cout << fileName<<" "<<dimension<<"\n";
		std::fstream file;
		file.open(fileName, std::fstream::in | std::ios_base::out | std::fstream::app);

		double temperature=1000;
		
		//int t0 = 0;
		//int k = 0;
		double min=INFINITY;
		bitRepresentation initial(start, end, precision, dimension);
		initial.createRandomString();
		
		int t0 = 1000;
		double evalInitial = pointerToEvaluate(initial.decodeAllSlices());
		int k = 0;
		while(temperature>0.0000001)
		{
			
			int t = initial.getTLD();
			while( t--/*temporar*/)
			{
				bitRepresentation succesor = initial.randomNeighbour();
				double evalSucc = pointerToEvaluate(succesor.decodeAllSlices());
				if(trueFalse(evalSucc, evalInitial))
				{
					
					initial = succesor;
					evalInitial = evalSucc;
				}
				else if(bitRepresentation::randomBetween0_1()<exp(-abs(evalSucc-evalInitial)/temperature))
				{
					initial = succesor;
					evalInitial = evalSucc;
				}
			}
			if(trueFalse(evalInitial, min))
			{
				min = evalInitial;
			}
			//temperature = t0 / (1 + k *3.1);
			//k++;
			temperature*=0.99994;
			//temperature = t0 * pow(0.82, k);
			//k++;
		}
		file << std::fixed << std::setprecision(5) << min<<"\n";
	}
};