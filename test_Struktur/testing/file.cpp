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
}

void file::addComma()
{
	text_.append(",");
}

void file::addSpacer()
{
		text_.append(" ");
}

void file::removeLastChar()
{
	if (text_.size() > 0) {
		text_ = text_.substr(0, text_.size() - 1);
	}
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
	std::string trash;

	ifstream iFile(path.append(name));

	structures::Array<structures::Array<int>*>* parameters =
		new structures::Array<structures::Array<int>*>(0);

	if (!iFile.fail()) {
		int numOfLines = 0;
		while (!iFile.eof())
		{
			if (n == 4) {
				iFile >> trash >> trash >> trash >> trash ;
			}
			else {
				iFile >> trash >> trash >> trash;
			}
			numOfLines++;
		}

		iFile.close();

		parameters = new structures::Array<structures::Array<int>*>(numOfLines);

		int i = 0;
		ifstream iFile2(path);
		while (!iFile2.eof())
		{
			if (i < numOfLines) {
				(*parameters)[i] = new structures::Array<int>(n);
				if (n == 4) {
					int o1, o2, o3, o4;
					iFile2 >> o1 >> o2 >> o3 >> o4;
					(*(*parameters)[i])[0] = o1;
					(*(*parameters)[i])[1] = o2;
					(*(*parameters)[i])[2] = o3;
					(*(*parameters)[i])[3] = o4;
				}
				else {
					iFile2 >> (*(*parameters)[i])[0] >> (*(*parameters)[i])[1] >> (*(*parameters)[i])[2];
				}
			}
			i++;
		}
		iFile2.close();
	}

	return parameters;
}

void file::saveToFile(std::string text, std::string path,std::string fileName)
{
	std::string file_;
	file_.append(path);
	file_.append(fileName);
	std::ofstream out(file_);
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
