#include "Dictionary.h"
#include <fstream>
#include <random>
#include <time.h>

Dictionary::Dictionary(std::string filename) : m_filename(filename)
{
	srand(time(0));
	LoadData();
}

void Dictionary::LoadData()
{	
	m_words.clear();

	std::ifstream db;
	db.open(m_filename);

	std::string word;
	while (db >> word)
		m_words.push_back(word);
	db.close();
}

std::string Dictionary::GetRandomWord()
{
	if (m_words.size() == 0)
		return "";
	int id = rand() % m_words.size();
	return m_words[id];
}
