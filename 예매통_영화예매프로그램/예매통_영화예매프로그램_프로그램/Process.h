#pragma once
#include "define.h"
#include <time.h>
class App;

// 프로그램의 로직 흐름을 처리하는 클래스 , 모드에 따라서 NoneProcess or UserProcess or ManagerProcess 클래스가 호출된다. 
class Process
{
protected:
	int logic; // Process 내에서 로직 구분 flag 
public:
	Process();
	~Process();

public :
	virtual void destroy() = 0; // 메모리 수거시 
	virtual void doRun(App* app) = 0;  // 모드에 따라서 호출되는 함수 

	void CLEAR_STD_BUFFER() {
		Sleep(1000);
		cin.clear(); cin.ignore(256, '\n');
	}
};



