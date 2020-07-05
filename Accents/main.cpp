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
	cout << "Äîáðî ïîæàëîâàòü â ïðîãðàììó ïî çàïîìèíàíèþ óäàðåíèé.\n";
	cout << "Âàì áóäåò äàâàòüñÿ ñëîâî, â êîòîðîì âû äîëæíû ïðàâèëüíî ïîñòàâèòü óäàðåíèå.\n";
	cout << "×òîáû ñäåëàòü ýòî, âàì íóæíî íàïèñàòü ãëàñíóþ, íà êîòîðóþ ïàäàåò óäàðåíèå â âåðõíåì ðåãèñòðå.\n";
	cout << "Äëÿ òîãî ÷òîáû âûéòè èç ïðîãðàììû, íàïèøèòå ñëîâî \'exit\'.\n";
	cout << "Äëÿ òîãî, ÷òîáû èçìåíèòü ñëîâàðü, íàïèøèòå ñëîâî \'editor\'.\n";
	cout << "Óäà÷è!" << endl;
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
			cout << "Îøèáêà! Ñëîâàðü ïóñò!";
		}
		else {
			cout << "Ñëîâî: " << StringLibrary::toLowerCase(word) << "\n";
			cout << "Îòâåò: ";
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
				cout << green << "Îòâåò âåðíûé!\n" << white;
				++correctAnswers;
			}
			else {
				cout << red << "Îòâåò íåâåðíûé, ïðàâèëüíûé îòâåò: " << word << "\n" << white;
			}
			++allAnswers;
			answered = true;
		}
		else {
			cout << blue << "Êàæåòñÿ, âû íåïðàâèëüíî ââåëè ñëîâî, äàâàéòå ïîïðîáóåì åù¸ ðàç\n" << white;
		}
	}
	
	Statistic stat("stats.txt");
	double percent = allAnswers == 0 ? 0.0 : correctAnswers * 1.0 / allAnswers * 100.0;
	double avaragePercent = stat.GetAvaragePercent();
	cout << white;
	cout << "Âñåãî îòâåòîâ: " << allAnswers << "\n";
	cout << "Ïðàâèëüíûõ îòâåòîâ: " << green << correctAnswers << white << "\n";
	cout << "Ïðîöåíò ïðàëüíûõ îòâåòîâ: " << (percent > 75 ? green : percent > 25 ? yellow : red) << percent << "%\n" << white;
	double delta = percent - avaragePercent;
	cout << "Ýòî íà " << abs(delta) << "% " << (delta > 0 ? "áîëüøå" : "ìåíüøå") << ", ÷åì ñðåäíèé ïðîöåíò, ðàâíûé " << avaragePercent << "%\n";
	stat.AddStat(allAnswers, correctAnswers);
	wait();
	return 0;
}
