#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <sstream>
#include <windows.h>
#include <chrono>

#include "../structures/array/array.h";

class file {
public:
	file() {}
	file(std::string path, std::string name);
	~file();

	void addItem(std::string item);

	void newLine();

	void saveFile();

	structures::Array<structures::Array<int>*>* loadFile(std::string path, std::string name, const int n);

private:
	std::string filename_;
	std::string path_;
	std::string text_;

private:
	void saveToFile(std::string text, std::string path, std::string fileName);

	void createPath(std::string path);
};