#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <sstream>
#include <windows.h>
#include <chrono>

namespace std {
	class KeyPressed
	{
	public:
		KeyPressed() {}
		~KeyPressed() {}

		int getChoice(int i_min, int i_max) {
			int i_Tmp = 0;
			cout << "Pick your choice: " << endl;

			i_Tmp = input_Int();

			if (i_Tmp == -1) {
				cout << "Wrong choice, please pick again." << endl;
				return i_Tmp = getChoice(i_min, i_max);
			}
			else {
				return i_Tmp;
			}
		}

		int generate_Int(int i_Min, int i_Max) {
			int tmp;
			if (i_Max > 0) {
				tmp = (rand() % i_Max) + i_Min;
			}
			else {
				tmp = 0;
			}
			return tmp;
		}
	private:
		int input_Int(int b = -1, int a = 0) {
			int integerReturn;
			cin >> integerReturn;
			return integerReturn;
		}

		double input_Double() {
			double x;
			cin >> x;
			return x;
		}

	};
}