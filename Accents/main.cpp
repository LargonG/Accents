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
	cout << "Добро пожаловать в программу по запоминанию ударений.\n";
	cout << "Вам будет даваться слово, в котором вы должны правильно поставить ударение.\n";
	cout << "Чтобы сделать это, вам нужно написать гласную, на которую падает ударение в верхнем регистре.\n";
	cout << "Для того чтобы выйти из программы, напишите слово \'exit\'.\n";
	cout << "Для того, чтобы изменить словарь, напишите слово \'editor\'.\n";
	cout << "Удачи!" << endl;
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
			cout << "Ошибка! Словарь пуст!";
		}
		else {
			cout << "Слово: " << StringLibrary::toLowerCase(word) << "\n";
			cout << "Ответ: ";
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
				cout << green << "Ответ верный!\n" << white;
				++correctAnswers;
			}
			else {
				cout << red << "Ответ неверный, правильный ответ: " << word << "\n" << white;
			}
			++allAnswers;
			answered = true;
		}
		else {
			cout << blue << "Кажется, вы неправильно ввели слово, давайте попробуем ещё раз\n" << white;
		}
	}
	
	Statistic stat("stats.txt");
	double percent = allAnswers == 0 ? 0.0 : correctAnswers * 1.0 / allAnswers * 100.0;
	double avaragePercent = stat.GetAvaragePercent();
	cout << white;
	cout << "Всего ответов: " << allAnswers << "\n";
	cout << "Правильных ответов: " << green << correctAnswers << white << "\n";
	cout << "Процент пральных ответов: " << (percent > 75 ? green : percent > 25 ? yellow : red) << percent << "%\n" << white;
	double delta = percent - avaragePercent;
	cout << "Это на " << abs(delta) << "% " << (delta > 0 ? "больше" : "меньше") << ", чем средний процент, равный " << avaragePercent << "%\n";
	stat.AddStat(allAnswers, correctAnswers);
	wait();
	return 0;
}
