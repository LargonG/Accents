#include "Statistic.h"
#include <fstream>
#include <algorithm>

Statistic::Statistic(std::string filename) : m_filename(filename)
{
	LoadStats();
}

void Statistic::LoadStats()
{
	m_vals.clear();

	std::ifstream file;
	file.open(m_filename);

	int all, correct;
	while (file >> all >> correct)
		m_vals.push_back({ all, correct });
	file.close();
}

void Statistic::AddStat(int all, int correct)
{
	m_vals.push_back({ all, correct });
	std::ofstream file;
	file.open(m_filename);
	file.clear();
	for (int i = std::max(0, (int)m_vals.size() - SIZE); i < m_vals.size(); ++i)
		file << m_vals[i].first << " " << m_vals[i].second << "\n";
	file.close();
}

double Statistic::GetAvaragePercent()
{
	if (m_vals.size() == 0)
		return 0.0;
	double ans = 0;
	for (const auto& x : m_vals) {
		if (x.first == 0)
			continue;
		ans += x.second * 1.0 / x.first;
	}
	return ans / m_vals.size() * 100.0;
}
