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

	/*
	int long long getTime() {
		struct timeval time_now {};
		gettimeofday(&time_now, nullptr);
		time_t msecs_time = (time_now.tv_sec * 1000000) + (time_now.tv_usec / 1000000);
		return msecs_time;
	}
	*/

	double getDuration() {
		std::chrono::duration<double, std::milli> elapsed = time_end - time_start;
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

private:
	int gettimeofday(struct timeval* tp, struct timezone* tzp) {
		namespace sc = std::chrono;
		sc::system_clock::duration d = sc::system_clock::now().time_since_epoch();
		sc::seconds s = sc::duration_cast<sc::seconds>(d);
		tp->tv_sec = s.count();
		tp->tv_usec = sc::duration_cast<sc::microseconds>(d - s).count();

		return 0;
	}
};
