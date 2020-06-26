#include <iostream>
#include <algorithm>
#include <Windows.h>

#include "Dictionary.h"
#include "Statistic.h"
#include "StringLibrary.h"
#include "Editor.h"
#include "ConsoleColor.h"

using namespace std;

inline void wait() {
	char ch;
	cin >> ch;
}

int main() {
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	system("color 0F");

	cout << blue;
	cout << "����� ���������� � ��������� �� ����������� ��������.\n";
	cout << "��� ����� �������� �����, � ������� �� ������ ��������� ��������� ��������.\n";
	cout << "����� ������� ���, ��� ����� �������� �������, �� ������� ������ �������� � ������� ��������.\n";
	cout << "��� ���� ����� ����� �� ���������, �������� ����� \'exit\'.\n";
	cout << "��� ����, ����� �������� �������, �������� ����� \'editor\'.\n";
	cout << "�����!" << endl;
	cout << white;

	Dictionary dictionary("database.txt");
	Editor editor("database.txt");

	int correctAnswers = 0;
	int allAnswers = 0;

	bool answered = true;
	string word;
	while (true) {
		if (answered) {
			word = dictionary.GetRandomWord();
			answered = false;
		}
		if (word == "") {
			cout << "������! ������� ����!";
		}
		else {
			cout << "�����: " << StringLibrary::toLowerCase(word) << "\n";
			cout << "�����: ";
		}
		string ans; cin >> ans;
		if (ans == "exit") {
			break;
		}
		else if (ans == "editor") {
			editor.Run();
			dictionary.LoadData();
		}
		else if (word != "" && StringLibrary::toLowerCase(word) == StringLibrary::toLowerCase(ans)) {
			if (ans == word) {
				cout << green << "����� ������!\n" << white;
				++correctAnswers;
			}
			else {
				cout << red << "����� ��������, ���������� �����: " << word << "\n" << white;
			}
			++allAnswers;
			answered = true;
		}
		else {
			cout << blue << "�������, �� ����������� ����� �����, ������� ��������� ��� ���\n" << white;
		}
	}
	
	Statistic stat("stats.txt");
	double percent = allAnswers == 0 ? 0.0 : correctAnswers * 1.0 / allAnswers * 100.0;
	double avaragePercent = stat.GetAvaragePercent();
	cout << white;
	cout << "����� �������: " << allAnswers << "\n";
	cout << "���������� �������: " << green << correctAnswers << white << "\n";
	cout << "������� �������� �������: " << (percent > 75 ? green : percent > 25 ? yellow : red) << percent << "%\n" << white;
	double delta = percent - avaragePercent;
	cout << "��� �� " << abs(delta) << "% " << (delta > 0 ? "������" : "������") << ", ��� ������� �������, ������ " << avaragePercent << "%\n";
	stat.AddStat(allAnswers, correctAnswers);
	wait();
	return 0;
}