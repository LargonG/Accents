#pragma once
#include <string>
#include <vector>

class Statistic
{
private:
	const static int SIZE = 100;
	std::string m_filename;
	std::vector<std::pair<int, int>> m_vals;

public:
	Statistic(std::string filename);
	void LoadStats();
	void AddStat(int all, int correct);
	double GetAvaragePercent();
};

