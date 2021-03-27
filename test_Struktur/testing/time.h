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

	int long long getTime() {
		struct timeval currentTime;
		gettimeofday(&currentTime, NULL);
		return currentTime.tv_sec * (int)1e6 + currentTime.tv_usec;
	}

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
