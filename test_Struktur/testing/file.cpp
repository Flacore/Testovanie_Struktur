#include "file.h"

file::file(std::string path, std::string name) :
	filename_(name),
	path_(path),
	text_("")
{
}

file::~file()
{
	filename_ = "";
	path_ = "";
	text_ = "";
}

void file::addItem(std::string item)
{
	text_.append(item);
	text_.append(",");
}

void file::newLine()
{
	if (text_.size() > 0) {
		text_ = text_.substr(0, text_.size() - 1);
		text_.append("\n");
	}
}

void file::saveFile()
{
	createPath(path_);
	saveToFile(text_, path_, filename_);
}

structures::Array<structures::Array<int>*>* file::loadFile(std::string path, std::string name, const int n)
{
	char trashBin;

	ifstream iFile(path+""+name);

	int numOfLines = 0;
	while (!iFile.eof())
	{
		numOfLines++;
	}
	iFile.close();

	structures::Array<structures::Array<int>*>* parameters =
		new structures::Array<structures::Array<int>*>(numOfLines);

	int i = 0;
	while (!iFile.eof())
	{
		(*parameters)[i] = new structures::Array<int>(n);
		if (n == 4) {
			iFile >> (*(*parameters)[i])[0] >> trashBin >> (*(*parameters)[i])[1] >> trashBin >> (*(*parameters)[i])[2] >> trashBin >> (*(*parameters)[i])[3];
		}
		else {
			iFile >> (*(*parameters)[i])[0] >> trashBin >> (*(*parameters)[i])[1] >> trashBin >> (*(*parameters)[i])[2];
		}
		i++;
	}
	iFile.close();

	return parameters;
}

void file::saveToFile(std::string text, std::string path,std::string fileName)
{
	std::ofstream out(path+""+fileName);
	out << text;
	out.close();
}

void file::createPath(std::string path)
{
	string  myMessage = path;
	int len;
	int slength = (int)myMessage.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, myMessage.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, myMessage.c_str(), slength, buf, len);
	std::wstring r(buf);
	std::wstring stemp = r.c_str();
	LPCWSTR result = stemp.c_str();

	if (CreateDirectory(result, NULL) ||
		ERROR_ALREADY_EXISTS == GetLastError())
	{
		//uspech
	}
	else
	{
		//neuspech
	}
}
