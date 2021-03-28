#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <sstream>
#include <windows.h>
#include <chrono>

class  Time
{
public:
	Time() {}
	~Time() {}

	double getDuration() {
		std::chrono::duration<double, std::micro> elapsed = time_end - time_start;
		return elapsed.count();
	}

	void setStart() {
		time_start = std::chrono::high_resolution_clock::now();
	}

	void setEnd() {
		time_end = std::chrono::high_resolution_clock::now();
	}

private:
	chrono::high_resolution_clock::time_point time_start;

	chrono::high_resolution_clock::time_point time_end;

};
