#pragma once
#include "Process.h"
class App;

// 로그인 전의 업무를 담당하는 클래스 
class NoneProcess : public Process
{
public:
	NoneProcess();
	~NoneProcess();

public:
	virtual void destroy() {}
	virtual void doRun(App* app);

public:
	bool logic_JoinMember(App* app); // 회원가입 
	bool logic_Login(App* app); // 로그인 
	bool logic_LeaveMember(App* app); // 회원탈퇴 
};

