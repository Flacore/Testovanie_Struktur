#include "test.h"

#define PATH "scenario/"

Test::Test()
{
}

Test::~Test()
{
}

void Test::uloha1()
{
	int vloz, zrus, index, set;
	vloz = zrus = index = set = 25;

	file* file_ = new file();
	structures::Array<structures::Array<int>*>* scenario = (*file_).loadFile(PATH, "uloha1.txt", 4);
	delete file_;

	cout << "Choose testing scenario:" << endl;
	cout << "1: insert 20%, delete 20%, get/set 50%, get index 10%"<< endl;
	cout << "2: insert 35%, delete 35%, get/set 20%, get index 10%" << endl;
	cout << "3: insert 45%, delete 45%, get/set 5%, get index 5%" << endl;
	cout << "Own scenario:" << endl;
	for (int i = 0; i < scenario->size(); i++) {
		cout << i + 4 <<": insert "<<(*(*scenario)[i])[0]<<"%, delete "<< (*(*scenario)[i])[1] <<"%, get/set "<< (*(*scenario)[i])[2] <<"%, get index "<< (*(*scenario)[i])[3] <<"%" << endl;
	}
	cout << scenario->size() + 4 << ": create own scenario" << endl;

	int choose = key_.getChoice(1, 3 + scenario->size());
	
	std::string csvName="";

	switch (choose)
	{
	case 1:
		csvName = "ScenarioA.csv";
		vloz = 20;
		zrus = 20;
		index = 10;
		set = 50;
		break;
	case 2:
		csvName = "ScenarioB.csv";
		vloz = 35;
		zrus = 35;
		index = 10;
		set = 20;
		break;
	case 3:
		csvName = "ScenarioC.csv";
		vloz = 45;
		zrus = 45;
		index = 5;
		set = 5;
		break;
	default:
		if (scenario->size() > 0 && choose < scenario->size() + 4) {
			csvName = "Scenario";
			csvName.append(to_string(choose - 3));
			csvName.append(".csv");
			vloz = (*(*scenario)[choose - 4])[0];
			zrus = (*(*scenario)[choose - 4])[1];
			index = (*(*scenario)[choose - 4])[3];
			set = (*(*scenario)[choose - 4])[2];
		}
		else {
			createScenario(1);
		}
		break;
	}

	ADT_List* listTest = new ADT_List(vloz,zrus,index,set,csvName);
	(*listTest).start_testing();
	delete listTest;
}

void Test::uloha2()
{
	int vloz, vyber, ukaz;
	vloz = 50;
	vyber = ukaz = 25;

	file* file_ = new file();
	structures::Array<structures::Array<int>*>* scenario = (*file_).loadFile(PATH, "uloha2.txt", 3);
	delete file_;

	cout << "Choose testing scenario:" << endl;
	cout << "1: insert 35%, get 35%, show 30%" << endl;
	cout << "2: insert 50%, get 30%, show 20%" << endl;
	cout << "3: insert 70%, get 25%, show 5%" << endl;
	cout << "Own scenario:" << endl;
	for (int i = 0; i < scenario->size(); i++) {
		cout << i + 4 << ": insert " << (*(*scenario)[i])[0] << "%, get " << (*(*scenario)[i])[1] << "%, show " << (*(*scenario)[i])[2] << "%" << endl;
	}
	cout << scenario->size() + 4 << ": create own scenario" << endl;

	int choose = key_.getChoice(1, 3 + scenario->size());
	
	std::string csvName = "";

	switch (choose)
	{
	case 1:
		csvName = "ScenarioA.csv";
		vloz = 35;
		ukaz = 35;
		vyber = 30;
		break;
	case 2:
		csvName = "ScenarioB.csv";
		vloz = 50;
		ukaz = 30;
		vyber = 20;
		break;
	case 3:
		csvName = "ScenarioC.csv";
		vloz = 70;
		ukaz = 25;
		vyber = 5;
		break;
	default:
		if (scenario->size() > 0 && choose < scenario->size() + 4) {
			csvName = "Scenario";
			csvName.append(to_string(choose - 3));
			csvName.append(".csv");
			vloz = (*(*scenario)[choose - 4])[0];
			vyber = (*(*scenario)[choose - 4])[1];
			ukaz = (*(*scenario)[choose - 4])[2];
		}
		else {
			createScenario(2);
		}
		break;
	}

	ADT_PriorityFront* pFront = new ADT_PriorityFront(vloz, vyber, ukaz, csvName);
	(*pFront).do_testing();
	delete pFront;
}

void Test::uloha3()
{
	int choice = 1;
	cout << "Choose testing scenario:" << endl;
	cout << "1: matrix sum." << endl;
	cout << "2: matrix multiplication." << endl;
	
	int choose = key_.getChoice(1, 2);
	
	std::string csvName = "";

	switch (choose)
	{
	case 1:
		csvName = "ScenarioA.csv";
		choice = 1;
		break;
	case 2:
		csvName = "ScenarioB.csv";
		choice = 2;
		break;
	default:
		csvName = "ScenarioA.csv";
		choice = 1;
		break;
	}

	ADT_Matrix* matrixTest = new ADT_Matrix(choice, csvName);
	(*matrixTest).do_testing();
	delete matrixTest;

}

void Test::uloha4()
{
	int vloz, zrus, index, set;
	vloz = zrus = index = set = 25;

	file* file_ = new file();
	structures::Array<structures::Array<int>*>* scenario = (*file_).loadFile(PATH, "uloha1.txt", 4);
	delete file_;

	cout << "Choose testing scenario:" << endl;
	cout << "1: insert 20%, delete 20%, get/set 50%, get index 10%" << endl;
	cout << "2: insert 35%, delete 35%, get/set 20%, get index 10%" << endl;
	cout << "3: insert 45%, delete 45%, get/set 5%, get index 5%" << endl;
	cout << "Own scenario:" << endl;
	for (int i = 0; i < scenario->size(); i++) {
		cout << i + 4 << ": insert " << (*(*scenario)[i])[0] << "%, delete " << (*(*scenario)[i])[1] << "%, get/set " << (*(*scenario)[i])[2] << "%, get index " << (*(*scenario)[i])[3] << "%" << endl;
	}
	cout << scenario->size() + 4 << ": create own scenario" << endl;

	int choose = key_.getChoice(1, 3 + scenario->size());
	
	std::string csvName = "";

	switch (choose)
	{
	case 1:
		csvName = "ScenarioA.csv";
		vloz = 20;
		zrus = 20;
		index = 10;
		set = 50;
		break;
	case 2:
		csvName = "ScenarioB.csv";
		vloz = 35;
		zrus = 35;
		index = 10;
		set = 20;
		break;
	case 3:
		csvName = "ScenarioC.csv";
		vloz = 45;
		zrus = 45;
		index = 5;
		set = 5;
		break;
	default:
		if (scenario->size() > 0 && choose < scenario->size() + 4) {
			csvName = "Scenario";
			csvName.append(to_string(choose - 3));
			csvName.append(".csv");
			vloz = (*(*scenario)[choose - 4])[0];
			zrus = (*(*scenario)[choose - 4])[1];
			index = (*(*scenario)[choose - 4])[3];
			set = (*(*scenario)[choose - 4])[2];
		}
		else {
			createScenario(1);
		}
		break;
	}

	ADT_CircularList* listTest = new ADT_CircularList(vloz, zrus, index, set, csvName);
	(*listTest).start_testing();
	delete listTest;
}

void Test::uloha5()
{
	int vloz, vyber, ukaz;
	vloz = 50;
	vyber = ukaz = 25;

	file* file_ = new file();
	structures::Array<structures::Array<int>*>* scenario = (*file_).loadFile(PATH, "uloha2.txt", 3);
	delete file_;

	cout << "Choose testing scenario:" << endl;
	cout << "1: insert 35%, get 35%, show 30%" << endl;
	cout << "2: insert 50%, get 30%, show 20%" << endl;
	cout << "3: insert 70%, get 25%, show 5%" << endl;
	cout << "Own scenario:" << endl;
	for (int i = 0; i < scenario->size(); i++) {
		cout << i + 4 << ": insert " << (*(*scenario)[i])[0] << "%, get " << (*(*scenario)[i])[1] << "%, show " << (*(*scenario)[i])[2] << "%" << endl;
	}
	cout << scenario->size() + 4 << ": create own scenario" << endl;

	int choose = key_.getChoice(1, 3 + scenario->size());

	std::string csvName = "";

	switch (choose)
	{
	case 1:
		csvName = "ScenarioA.csv";
		vloz = 35;
		ukaz = 35;
		vyber = 30;
		break;
	case 2:
		csvName = "ScenarioB.csv";
		vloz = 50;
		ukaz = 30;
		vyber = 20;
		break;
	case 3:
		csvName = "ScenarioC.csv";
		vloz = 70;
		ukaz = 25;
		vyber = 5;
		break;
	default:
		if (scenario->size() > 0 && choose < scenario->size() + 4) {
			csvName = "Scenario";
			csvName.append(to_string(choose - 3));
			csvName.append(".csv");
			vloz = (*(*scenario)[choose - 4])[0];
			vyber = (*(*scenario)[choose - 4])[1];
			ukaz = (*(*scenario)[choose - 4])[2];
		}
		else {
			createScenario(2);
		}
		break;
	}

	ADT_TwoList* twoListTest = new ADT_TwoList(vloz, vyber, ukaz, csvName);
	(*twoListTest).do_testing();
	delete twoListTest;
}

void Test::uloha6()
{
	int vloz, zrus, LogOp, SetOp;
	vloz = zrus = LogOp = SetOp = 25;


	file* file_ = new file();
	structures::Array<structures::Array<int>*>* scenario = (*file_).loadFile(PATH, "uloha6.txt", 4);
	delete file_;

	cout << "Choose testing scenario:" << endl;
	cout << "1: insert 20%, delete 20%, logical operation 50%, set operation 10%" << endl;
	cout << "2: insert 35%, delete 35%, logical operation 20%, set operation 10%" << endl;
	cout << "Own scenario:" << endl;
	for (int i = 0; i < scenario->size(); i++) {
		cout << i + 3 << ": insert " << (*(*scenario)[i])[0] << "%, delete " << (*(*scenario)[i])[1] << "%, logical operation " << (*(*scenario)[i])[2] << "%, set operation " << (*(*scenario)[i])[3] << "%" << endl;
	}

	cout << scenario->size() + 3 << ": create own scenario" << endl;

	int choose = key_.getChoice(1, 2 + scenario->size());

	std::string csvName = "";

	switch (choose)
	{
	case 1:
		csvName = "ScenarioA.csv";
		vloz = 20;
		zrus = 20;
		LogOp = 50;
		SetOp = 10;
		break;
	case 2:
		csvName = "ScenarioB.csv";
		vloz = 35;
		zrus = 35;
		LogOp = 20;
		SetOp = 10;
		break;
	default:
		if (scenario->size() > 0 && choose < scenario->size() + 3) {
			csvName = "Scenario";
			csvName.append(to_string(choose - 2));
			csvName.append(".csv");
			vloz = (*(*scenario)[choose - 3])[0];
			zrus = (*(*scenario)[choose - 3])[1];
			LogOp = (*(*scenario)[choose - 3])[1];
			SetOp = (*(*scenario)[choose - 3])[3];
		}
		else {
			createScenario(3);
		}
		break;
	}

	ADT_BitMap* bitMapTest = new ADT_BitMap(vloz, zrus, LogOp, SetOp, csvName);
	(*bitMapTest).do_testing();
	delete bitMapTest;
}

void Test::autoTesting()
{
	
	//List
	cout << "Start testing structure List." << endl;
	for (int i = 1; i <= 3; i++) {

		std::string csvName;
		int vloz, zrus, index, set;

		switch (i)
		{
		case 1:
			csvName = "ScenarioA.csv";
			vloz = 20;
			zrus = 20;
			index = 10;
			set = 50;
			break;
		case 2:
			csvName = "ScenarioB.csv";
			vloz = 35;
			zrus = 35;
			index = 10;
			set = 20;
			break;
		case 3:
			csvName = "ScenarioC.csv";
			vloz = 45;
			zrus = 45;
			index = 5;
			set = 5;
			break;
		}

		ADT_List* listTest = new ADT_List(vloz, zrus, index, set, csvName);
		(*listTest).start_testing();
		delete listTest;
		cout << "Done doing 'Linked/Array list'-" << csvName << endl;


		ADT_CircularList* twolistTest = new ADT_CircularList(vloz, zrus, index, set, csvName);
		(*twolistTest).start_testing();
		delete twolistTest;
		cout << "Done doing 'CircularList'-" << csvName << endl;

		cout << "Done doing -" << csvName << endl;
	}
	cout << "List done!" << endl;

	//PriorityQueue
	cout << "Start testing structure PriorityQueue." << endl;
	for (int i = 1; i <= 3; i++) {


		std::string csvName;
		int vloz, ukaz, vyber;

		switch (i)
		{
		case 1:
			csvName = "ScenarioA.csv";
			vloz = 35;
			ukaz = 35;
			vyber = 30;
			break;
		case 2:
			csvName = "ScenarioB.csv";
			vloz = 50;
			ukaz = 30;
			vyber = 20;
			break;
		case 3:
			csvName = "ScenarioC.csv";
			vloz = 70;
			ukaz = 25;
			vyber = 5;
			break;
		}

		ADT_PriorityFront* pFront = new ADT_PriorityFront(vloz, vyber, ukaz, csvName);
		(*pFront).do_testing();
		delete pFront;
		cout << "Done doing 'PriorityFront'-" << csvName << endl;

		ADT_TwoList* twoListTest = new ADT_TwoList(vloz, vyber, ukaz, csvName);
		(*twoListTest).do_testing();
		delete twoListTest;
		cout << "Done doing 'TwoList'-" << csvName << endl;
	}
	cout << "PriorityQueue done!" << endl;


	//Matrix
	cout << "Start testing structure Matrix." << endl;
	for (int i = 2; i <= 2; i++) {
		std::string csvName;
		int choice;

		switch (2)
		{
		case 1:
			csvName = "ScenarioA.csv";
			choice = 1;
			break;
		case 2:
			csvName = "ScenarioB.csv";
			choice = 2;
			break;
		default:
			csvName = "ScenarioA.csv";
			choice = 1;
			break;
		}

		ADT_Matrix* matrixTest = new ADT_Matrix(choice, csvName);
		(*matrixTest).do_testing();
		delete matrixTest;
		cout << "Done doing -" << csvName << endl;
	}
	cout << "Matrix done!" << endl;

	
	//ByteMap
	cout << "Start testing structure ByteMap." << endl;
	for (int i = 1; i <= 2; i++) {
		std::string csvName;
		int vloz, zrus, LogOp, SetOp;

		switch (i)
		{
		case 1:
			csvName = "ScenarioA.csv";
			vloz = 20;
			zrus = 20;
			LogOp = 50;
			SetOp = 10;
			break;
		case 2:
			csvName = "ScenarioB.csv";
			vloz = 35;
			zrus = 35;
			LogOp = 20;
			SetOp = 10;
			break;
		}

		ADT_BitMap* bitMapTest = new ADT_BitMap(vloz, zrus, LogOp, SetOp, csvName);
		(*bitMapTest).do_testing();
		delete bitMapTest;
		cout << "Done doing -" << csvName << endl;
	}
	cout << "ByteMap done!" << endl;
	
}

void Test::createScenario(int type)
{
	int size_ = 0;
	if (type == 2) {
		size_ = 3;
	}
	else {
		size_ = 4;
	}

	structures::Array<int>* tmp = new structures::Array<int>(size_);
	std::string path = "scenario/";
	std::string name = "default.txt";
	switch (type) {
	case 1:
		cout << "Insert" << endl;
		(*tmp)[0] = key_.getChoice(0,100);
		cout << "Remove" << endl;
		(*tmp)[1] = key_.getChoice(0, 100);
		cout << "Get/Set" << endl;
		(*tmp)[2] = key_.getChoice(0, 100);
		cout << "Get index" << endl;
		(*tmp)[3] = key_.getChoice(0, 100);
		name = "uloha1.txt";
		break;
	case 2:
		cout << "Insert" << endl;
		(*tmp)[0] = key_.getChoice(0, 100);
		cout << "Get" << endl;
		(*tmp)[1] = key_.getChoice(0, 100);
		cout << "Show" << endl;
		(*tmp)[2] = key_.getChoice(0, 100);
		name = "uloha2.txt";
		break;
	case 3:
		cout << "Insert" << endl;
		(*tmp)[0] = key_.getChoice(0, 100);
		cout << "Remove" << endl;
		(*tmp)[1] = key_.getChoice(0, 100);
		cout << "Logical operation" << endl;
		(*tmp)[2] = key_.getChoice(0, 100);
		cout << "Set operation" << endl;
		(*tmp)[3] = key_.getChoice(0, 100);
		name = "uloha6.txt";
		break;
	}

	file* file_ = new file();
	structures::Array<structures::Array<int>*>* scenario = (*file_).loadFile(PATH, name, 4);
	delete file_;
	
	file* savefile_ = new file(path, name);
	for (int i = 0; i < scenario->size(); i++) {
		for (int j = 0; j < tmp->size(); j++) {
			savefile_->addItem(to_string((*(*scenario)[i])[j]));
			savefile_->addSpacer();
		}
		savefile_->newLine();
	}

	int sum = 0;
	for (int i = 0; i < tmp->size(); i++) {
		sum += (*tmp)[i];
		savefile_->addItem(to_string((*tmp)[i]));
		savefile_->addSpacer();
	}
	savefile_->removeLastChar();

	if (sum == 100) {
		savefile_->saveFile();
	}
	else {
		cout << "Cannot create scenario." << endl;
	}

	delete savefile_;

	delete tmp;
}
