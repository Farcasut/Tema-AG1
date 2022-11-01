#pragma once
#include <vector>

class function
{

	double start;
	double end;
	int dimension;
public:
	function(double a, double b, int c) :start(a), end(b), dimension(c){}
	virtual double evaluate(std::vector<double>) = 0;

};
