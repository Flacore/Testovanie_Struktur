#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <sstream>
#include <windows.h>
#include <chrono>

#include "heap_monitor/heap_monitor.h";
#include "testing/Key_Getter.h";
#include "testing/test.h";

#include "structures/matrix/coherant_matrix.h";
#include "structures/matrix/incoherant_matrix.h";

#define EXIT_VALUE 0
#define FIRST_TASK_VALUE 1
#define NUM_OF_TASKS 4
#define NUM_OF_SUBTASKS 3

using namespace std;
class main_class {
public:
	main_class() {
	}

	~main_class() {
	}



	void main() {
		bool b_Exit = true;
		do {
			printfMenu();
			int i_Choice = key.getChoice(EXIT_VALUE, NUM_OF_TASKS);
			if (i_Choice != 0) {
				if (NUM_OF_TASKS >= i_Choice)
					doTesting(i_Choice);
				else
					cout << "Choice dosn´t exist!" << endl;
			}
			else {
				b_Exit = false;
			}
		} while (b_Exit);
	}

private:
	KeyPressed key;
	Test test;

private:
	void doTesting(int i_Choice) {
		int i_SUBCHOICE = 0;
		switch (i_Choice)
		{
		case 1:
			test.uloha1();
			break;
		case 2:
			test.uloha2();
			break;
		case 3:
			test.uloha3();
			break;
		case 4:
			printfSubMenu();
			i_SUBCHOICE = key.getChoice(FIRST_TASK_VALUE, NUM_OF_SUBTASKS);
			if (i_SUBCHOICE != 0)
				switch (i_SUBCHOICE) {
				case 1:
					test.uloha4();
					break;
				case 2:
					test.uloha5();
					break;
				case 3:
					test.uloha6();
					break;
				default:
					cout << "Ops, something went wrong!" << endl;
					break;
				}
			break;
		default:
			cout << "Ops, something went wrong!" << endl;
			break;
		}
	}

	void printfMenu() {
		cout << "Menu:" << endl;
		cout << "  1.ADT_list testing." << endl;
		cout << "  2.ADT_priorityQueue testing." << endl;
		cout << "  3.ADT_Matrix testing" << endl;
		cout << "  4.Others test" << endl;
		cout << "  0.Exit" << endl;
	}

	void printfSubMenu() {
		cout << "SubMenu:" << endl;
		cout << "  1.Doubly circular linked list." << endl;
		cout << "  2.Two list as implementation of priority queue." << endl;
		cout << "  3.Bit map collection." << endl;
		cout << "  0.Go back" << endl;
	};

};

int main() {
	initHeapMonitor();
	main_class* tests = new main_class();
	(*tests).main();
	delete tests;
	return 0;
}
