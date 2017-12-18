#include "stdafx.h"
#include "App.h"
#include "Process.h"
#include "ManagerProcess.h"
#include "NoneProcess.h"
#include "UserProcess.h"
#include "CodeGenerator.h"

App::App() :currentMode(TYPE_MODE::MODE_NONE), loginMemberID("")
{
	// ���� ó�� Ŭ���� ���� 
	proc[TYPE_MODE::MODE_NONE] = new NoneProcess();
	proc[TYPE_MODE::MODE_USER] = new UserProcess();
	proc[TYPE_MODE::MODE_MANAGER] = new ManagerProcess();

	// �󿵰� ���� ��� 
	/*gate[TYPE_GATE::GATE_A].gateNo = (int)TYPE_GATE::GATE_A;
	gate[TYPE_GATE::GATE_B].gateNo = (int)TYPE_GATE::GATE_B;
	gate[TYPE_GATE::GATE_C].gateNo = (int)TYPE_GATE::GATE_C;
	gate[TYPE_GATE::GATE_D].gateNo = (int)TYPE_GATE::GATE_D;*/

	// ���� �ε� 
	ReadFile(); 
}


App::~App()
{
	// �޸� ���� 
	for (int i = 0; i < TYPE_MODE::MODE_MAX; ++i) {
		proc[i]->destroy();
		delete proc[i];
		proc[i] = NULL;
	}
}


// ���α׷� ���� �Լ� 
void App::run(){


	// ���α׷��� ���� ���� , �ֱ������� ���鼭 ������� �Է��� �ް� ó���� �Ѵ�. 
	while (true) {

		if (NULL != proc[currentMode]) {

			fflush(stdin);
			// ���� ��忡 �´� �۾��� ���� �Ѵ�. 
			proc[currentMode]->doRun(this); 

			WriteFile(); 
		}
		
	}

	
}

// ������ �о�´�. 
void App::ReadFile() {
	ifstream in;
	in.open("data.txt");
	if (!in)
	{
		// ������ ���� ��� ���� 
		return;
	}

	// �ڵ� �߱� ��ȣ �ε� 
	{
		CodeGenerator::getInstance()->ReadFile(in); 
	}

	// ȸ�������� �ε� 
	{
		int memberCnt = 0;
		in >> memberCnt;

		for (int i = 0; i < memberCnt; ++i) {
			MemberInfo m;
			m.ReadFile(in);
			memberList.push_back(m);
		}
	}
	
	// ��ȭ ������ �ε� 
	{
		int movieCnt = 0;
		in >> movieCnt;

		for (int i = 0; i < movieCnt; ++i) {
			MovieInfo m;
			m.ReadFile(in);
			movieList.push_back(m); 
		}
	}

	// �󿵰� ������ �ε� 
	{
		for (int i = 0; i < TYPE_GATE::GATE_MAX; ++i) {
			gate[i].ReadFile(in);
		}
	}
}

// ������ �����Ѵ�. 
void App::WriteFile() {
	ofstream out;
	out.open("data.txt");

	// �ڵ� �߱� ��ȣ ���� 
	{
		CodeGenerator::getInstance()->WriteFile(out);
	}
	// ȸ������ ���� 
	{
		int memberCnt = memberList.size();
		out << memberCnt << endl;

		for (auto member : memberList) {
			member.WriteFile(out);
		}
	}

	// ��ȭ ������ ���� 
	{
		int movieCnt = movieList.size();
		out << movieCnt << endl; 

		for (auto movie : movieList) {
			movie.WriteFile(out); 
		}
	}
	
	// �󿵰� ������ ���� 
	{
		for (int i = 0; i < TYPE_GATE::GATE_MAX; ++i) {
			gate[i].WriteFile(out); 
		}
	}
}