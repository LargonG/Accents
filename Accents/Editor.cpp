#include "Editor.h"
#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include <set>

#include "StringLibrary.h"

Editor::Editor(std::string database) : m_database(database)
{
	m_categories = {
	{"exit", {"exit", "выход"}},
	{"help", {"help", "помощь"}},
	{"list", {"list", "словарь", "список"}},
	{"add", {"add", "добавить"}},
	{"remove", {"remove", "удалить"}},
	{"change", {"change", "update", "изменить", "обновить"}}
	};
	for (const auto& line : m_categories)
		for (const auto& x : line.second)
			m_allCommands.insert(x);
}

void Editor::Run()
{
	std::set<std::string> words;;
	std::map<std::string, std::string> lowerWords;

	std::ifstream inp;
	inp.open(m_database);
	std::string s;
	while (inp >> s) {
		words.insert(s);
		lowerWords[StringLibrary::toLowerCase(s)] = s;
	}
	inp.close();

	bool running = true;
	while (running) {
		std::cout << "-> ";
		std::string com;
		std::cin >> com;
		if (!m_allCommands.count(com)) {
			std::cout << "Данная команда на найдена!\nЧтобы получить список команд, введите \'помощь\' или \'help\'\n";
			continue;
		}

		if (m_categories["exit"].count(com)) {
			running = false;
		}
		else if (m_categories["help"].count(com)) {
			// Команды выхода
			for (const auto& com : m_categories["exit"])
				std::cout << "[" << com << "] ";
			std::cout << "- выйти из редактора\n";

			// Команды подсказки
			for (const auto& com : m_categories["help"])
				std::cout << "[" << com << "] ";
			std::cout << "- вывести данную подсказку\n";
			
			// Команды добавления
			for (const auto& com : m_categories["add"])
				std::cout << "[" << com << "] ";
			std::cout << "<слово (с ударением)> - добавить слово в словарь (можно также пользоваться как поиском).\n";
			
			// Команды удаления
			for (const auto& com : m_categories["remove"])
				std::cout << "[" << com << "] ";
			std::cout << "<слово (без ударения)> - удалить слово из словаря.\n";
			
			// Команды обновления
			for (const auto& com : m_categories["change"])
				std::cout << "[" << com << "] ";
			std::cout << "<слово (с ударением)> - обновляет ударение в слове.\n";
			
			// Команды вывода словаря (списка)
			for (const auto& com : m_categories["list"])
				std::cout << "[" << com << "] ";
			std::cout << "- Выводит список из всех слов в словаре.\n";
			
			std::cout.flush();
		}
		else if (m_categories["list"].count(com)) {
			std::cout << "Словарь: ";
			for (const auto& x : words)
				std::cout << x << "\n";
			std::cout << std::endl;
		}
		else {
			std::string word;
			std::cin >> word;
			std::string lowerWord = StringLibrary::toLowerCase(word);

			if (m_categories["add"].count(com)) {
				if (lowerWords.count(lowerWord)) {
					std::cout << "Данное слово уже в словаре! Вот оно: " << lowerWords[lowerWord] << "\n";
					std::cout << "Если вы хотите поменять ударение, то введите команду update" << std::endl;
				}
				else {
					words.insert(word);
					lowerWords[lowerWord] = word;
				}
			}
			else if (m_categories["remove"].count(com)) {
				if (!lowerWords.count(lowerWord)) {
					std::cout << "Данного слова нет в словаре!" << std::endl;
				}
				else {
					words.erase(lowerWords[lowerWord]);
					lowerWords.erase(lowerWord);
				}
			}
			else if (m_categories["change"].count(com)) {
				if (!lowerWords.count(lowerWord)) {
					std::cout << "Данного слова нет в словаре!" << std::endl;
				}
				else {
					words.erase(lowerWords[lowerWord]);
					words.insert(word);
					lowerWords[lowerWord] = word;
				}
			}
		}
	}

	std::ofstream db;
	db.open(m_database);
	db.clear();
	for (const auto& x : words)
		db << x << "\n";
	db.close();
}
