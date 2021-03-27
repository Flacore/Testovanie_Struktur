#pragma once

#include "test/ADT_List.h";
#include "test/ADT_CircularList.h";
#include "test/ADT_PriorityFront.h";
#include "test/ADT_TwoList.h";
#include "test/ADT_Matrix.h";
#include "test/ADT_BitMap.h";

#include "Key_Getter.h";

class Test {
public:
	Test();
	~Test();

	void uloha1();

	void uloha2();

	void uloha3();

	void uloha4();

	void uloha5();

	void uloha6();

private:
	KeyPressed key_;

private:
	void createScenario(int type);
};