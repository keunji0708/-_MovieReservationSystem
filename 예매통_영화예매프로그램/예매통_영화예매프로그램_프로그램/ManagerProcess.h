#pragma once

#include "Process.h"

class App;


// ������ ��� �� ����ϴ� Ŭ���� 
class ManagerProcess : public Process 
{
public:
	ManagerProcess() {}
	~ManagerProcess() {}
public:
	virtual void destroy() {}
	virtual void doRun(App* app);

	bool logic_AddMovieInfo(App* app); // ��ȭ�����Է�
	bool logic_AddMovieInfoByDateTime(App* app); // ��¥�� ������ �Է� 
	
	
public:
	void AddPlayMovieTimeInfo(App* app, int gateNo, MovieInfo *movie); // �󿵽ð� ��� 
};

