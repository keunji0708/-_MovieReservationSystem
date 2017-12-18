#include "stdafx.h"
#include "App.h"
#include "Process.h"
#include "ManagerProcess.h"
#include "NoneProcess.h"
#include "UserProcess.h"
#include "CodeGenerator.h"

App::App() :currentMode(TYPE_MODE::MODE_NONE), loginMemberID("")
{
	// 로직 처리 클래스 생성 
	proc[TYPE_MODE::MODE_NONE] = new NoneProcess();
	proc[TYPE_MODE::MODE_USER] = new UserProcess();
	proc[TYPE_MODE::MODE_MANAGER] = new ManagerProcess();

	// 상영관 정보 등록 
	/*gate[TYPE_GATE::GATE_A].gateNo = (int)TYPE_GATE::GATE_A;
	gate[TYPE_GATE::GATE_B].gateNo = (int)TYPE_GATE::GATE_B;
	gate[TYPE_GATE::GATE_C].gateNo = (int)TYPE_GATE::GATE_C;
	gate[TYPE_GATE::GATE_D].gateNo = (int)TYPE_GATE::GATE_D;*/

	// 파일 로딩 
	ReadFile(); 
}


App::~App()
{
	// 메모리 수거 
	for (int i = 0; i < TYPE_MODE::MODE_MAX; ++i) {
		proc[i]->destroy();
		delete proc[i];
		proc[i] = NULL;
	}
}


// 프로그램 시작 함수 
void App::run(){


	// 프로그램의 메인 루프 , 주기적으로 돌면서 사용자의 입력을 받고 처리를 한다. 
	while (true) {

		if (NULL != proc[currentMode]) {

			fflush(stdin);
			// 현재 모드에 맞는 작업을 실행 한다. 
			proc[currentMode]->doRun(this); 

			WriteFile(); 
		}
		
	}

	
}

// 파일을 읽어온다. 
void App::ReadFile() {
	ifstream in;
	in.open("data.txt");
	if (!in)
	{
		// 파일이 없을 경우 리턴 
		return;
	}

	// 코드 발급 번호 로딩 
	{
		CodeGenerator::getInstance()->ReadFile(in); 
	}

	// 회원데이터 로딩 
	{
		int memberCnt = 0;
		in >> memberCnt;

		for (int i = 0; i < memberCnt; ++i) {
			MemberInfo m;
			m.ReadFile(in);
			memberList.push_back(m);
		}
	}
	
	// 영화 데이터 로딩 
	{
		int movieCnt = 0;
		in >> movieCnt;

		for (int i = 0; i < movieCnt; ++i) {
			MovieInfo m;
			m.ReadFile(in);
			movieList.push_back(m); 
		}
	}

	// 상영관 데이터 로딩 
	{
		for (int i = 0; i < TYPE_GATE::GATE_MAX; ++i) {
			gate[i].ReadFile(in);
		}
	}
}

// 파일을 저장한다. 
void App::WriteFile() {
	ofstream out;
	out.open("data.txt");

	// 코드 발급 번호 쓰기 
	{
		CodeGenerator::getInstance()->WriteFile(out);
	}
	// 회원정보 쓰기 
	{
		int memberCnt = memberList.size();
		out << memberCnt << endl;

		for (auto member : memberList) {
			member.WriteFile(out);
		}
	}

	// 영화 데이터 쓰기 
	{
		int movieCnt = movieList.size();
		out << movieCnt << endl; 

		for (auto movie : movieList) {
			movie.WriteFile(out); 
		}
	}
	
	// 상영관 데이터 쓰기 
	{
		for (int i = 0; i < TYPE_GATE::GATE_MAX; ++i) {
			gate[i].WriteFile(out); 
		}
	}
}