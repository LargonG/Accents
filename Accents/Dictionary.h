#pragma once
#include <vector>
#include <string>

class Dictionary
{
private:
	std::string m_filename;
	std::vector<std::string> m_words;
public:
	Dictionary(std::string filename);
	void LoadData();
	std::string GetRandomWord();

};

