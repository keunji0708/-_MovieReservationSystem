#pragma once
#include "define.h"
#include <time.h>
class App;

// ���α׷��� ���� �帧�� ó���ϴ� Ŭ���� , ��忡 ���� NoneProcess or UserProcess or ManagerProcess Ŭ������ ȣ��ȴ�. 
class Process
{
protected:
	int logic; // Process ������ ���� ���� flag 
public:
	Process();
	~Process();

public :
	virtual void destroy() = 0; // �޸� ���Ž� 
	virtual void doRun(App* app) = 0;  // ��忡 ���� ȣ��Ǵ� �Լ� 

	void CLEAR_STD_BUFFER() {
		Sleep(1000);
		cin.clear(); cin.ignore(256, '\n');
	}
};



