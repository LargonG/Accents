#pragma once
#include <string>
#include <vector>
#include <map>
#include <set>

class Editor
{
private:
	std::string m_database;
	std::map<std::string, std::set<std::string>> m_categories;
	std::set<std::string> m_allCommands;

public:
	Editor(std::string database);
	void Run();
};

