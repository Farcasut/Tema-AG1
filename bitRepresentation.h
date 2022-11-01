#pragma once
#include <iostream>
#include <random>
#include <vector>
#include <iomanip>
/// https://simplecxx.github.io/2018/11/03/seed-mt19937.html
std::random_device rd;
//std::seed_seq sd{ rd(), rd(), rd(), rd() };
std::mt19937 gen(rd());
std::bernoulli_distribution boolean(0.5);


class bitRepresentation
{
	int ld;
	int diminesions;
	int TLD;
	int prc;
	double a;
	double b;
public:
	std::vector<bool> bitmap;

	int getTLD()
	{
		return TLD;
	}
	int getLD()
	{
		return ld;
	}
	int getDimension()
	{
		return diminesions;
	}

	bitRepresentation(double start, double end, int precision, int d)
	{
		this->prc = precision;
		this->a = start;
		this->b = end;
		this->diminesions = d;
		this->ld = ceil(log2((end - start) * pow(10, precision)));
		this->TLD = d * ld;

	}
	bitRepresentation(const bitRepresentation& original)
	{
		this->bitmap = original.bitmap;
		this->a = original.a;
		this->b = original.b;
		this->ld = original.ld;
		this->diminesions = original.diminesions;
		this->TLD = original.TLD;

	}
	void createRandomString()
	{

		for (int i = 0; i < TLD; i++)
		{

			bitmap.push_back(boolean(gen));
		}
	}

	double decodeSlice(std::vector<bool> slice)
	{
		int x = 0;
		for (int i = 0; i < ld; i++)
		{
			x *= 2;
			x += slice[i];
		}
		double y = x / (pow(2, ld) - 1);
		y *= (b - a);
		y += a;
		return y;
	}
	std::vector<double> decodeAllSlices()
	{
		std::vector<double> decoded;
		for(int j=0;j<diminesions;j++)
		{
			int x = 0;
			for (int i = j*ld; i <(j+1)*ld; i++)
			{
				x *= 2;
				x += bitmap[i];
			}
			double y = x / (pow(2, ld) - 1);
			y *= (b - a);
			y += a;
			decoded.push_back(y);
		}
		return decoded;
	}
	bitRepresentation randomNeighbour()
	{
		std::uniform_int_distribution<> distrib(0, TLD - 1);
		bitRepresentation n(*this);
		int change = distrib(gen);
		n.bitmap[change] = !n.bitmap[change];
		return n;
	}
	static double randomBetween0_1()
	{
		std::uniform_real_distribution<> dis(0, 1);
		return dis(gen);
	}
	bitRepresentation neighbour(int index)
	{
		//std::uniform_int_distribution<> distrib(0, ld-1);
		bitRepresentation n(*this);
		n.bitmap[index] = !n.bitmap[index];
		return n;
	}
};