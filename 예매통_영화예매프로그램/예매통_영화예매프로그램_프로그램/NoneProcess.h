#pragma once
#include "Process.h"
class App;

// �α��� ���� ������ ����ϴ� Ŭ���� 
class NoneProcess : public Process
{
public:
	NoneProcess();
	~NoneProcess();

public:
	virtual void destroy() {}
	virtual void doRun(App* app);

public:
	bool logic_JoinMember(App* app); // ȸ������ 
	bool logic_Login(App* app); // �α��� 
	bool logic_LeaveMember(App* app); // ȸ��Ż�� 
};

