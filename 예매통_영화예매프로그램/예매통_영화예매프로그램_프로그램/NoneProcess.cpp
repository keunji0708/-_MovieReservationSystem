#include "stdafx.h"
#include "NoneProcess.h"
#include "App.h"


NoneProcess::NoneProcess()
{
}


NoneProcess::~NoneProcess()
{
}

void NoneProcess::doRun(App* app) {

	if (NULL == app) return;

	system("cls"); // 화면을 깨끗히 지운다. 
	cout << endl;
	cout << "〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓" << endl;
	cout << "▶▶ 회원정보" << endl;
	cout << "〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓" << endl;
	cout << endl; 
	cout << "\t1)회원가입" << endl;
	cout << "\t2)로그인" << endl;
	cout << "\t3)회원탈퇴" << endl;

	logic = -1;
	while (true) {
		cout << endl;
		cout << "☞ 번호를 입력하세요 (1~3) :";
		cin >> logic;
		if (logic < 0 || logic > 3) {
			cout << "\t※잘못입력 하셨습니다. 다시입력해주세요!" << endl;
			CLEAR_STD_BUFFER();
			continue;
		}

		break;
	}

	while (true) {
		if (1 == logic) { // 회원정보 
			if (logic_JoinMember(app)) break;
		}
		else if (2 == logic) { // 로그인 
			if (logic_Login(app)) break;
		}
		else if (3 == logic) { // 회원탈퇴 
			if (logic_LeaveMember(app)) break;
		}
	}
}


// 회원 가입 프로세스 
bool NoneProcess::logic_JoinMember(App* app) {

	if (NULL == app) return false;
	system("cls"); // 화면을 깨끗히 지운다. 

	MemberInfo member;
	cout << endl;
	cout << "〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓" << endl;
	cout << "▶▶ 회원정보 >> 회원가입" << endl;
	cout << "〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓" << endl;

	cout << endl;
	cout << "\t1. 회원가입하기" << endl; 
	cout << "\t2. 되돌아가기" << endl;

	int menu = -1;
	while (true) {
		cout << "\t☞ 메뉴를 선택하세요(1~2):";
		cin >> menu;

		if (1 != menu && 2 != menu) {
			cout << endl;
			cout << "\t※잘못 입력하셨습니다!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}
		break; 
	}
	
	if (2 == menu) {
		cout << "\t상위메뉴로 되돌아 갑니다!" << endl; 
		Sleep(1000);
		return true;
	}
		




	while (true) {
		cout << endl;
		cout << "\t☞ ID 입력(10):";
		cin >> member.id;

		if (0 == strlen(member.id.c_str())) {
			cout << endl;
			cout << "\t※ID를 입력하세요!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}

		// 이미 존재하는 ID인지 체크 
		if (true == app->checkExistID(member.id)) {
			cout << endl;
			cout << "\t※이미존재하는 ID입니다 다른 ID를 입력하세요!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}

		if (10 < strlen(member.id.c_str())) {
			cout << endl;
			cout << "\t※글자수가 10자 미만으로 입력해주세요!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}
		break;
	}



	while (true) {
		cout << endl;
		cout << "\t☞ 비밀번호 입력(10):";
		cin >> member.pwd;

		if (0 == strlen(member.id.c_str())) {
			cout << endl;
			cout << "\t※비밀번호를 입력하세요!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}

		if (10 < strlen(member.id.c_str())) {
			cout << endl;
			cout << "\t※글자수가 10자 미만으로 입력해주세요!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}
		break;
	}

	while (true) {
		cout << endl;
		cout << "\t☞ Type 1:User, 2:Manager ( 1~2 ) :";
		cin >> member.actortype;

		if (1 > member.actortype || 2 < member.actortype) {
			cout << endl;
			cout << "\t※1또는 2를 입력해주세요!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}
		member.actortype--;
		break;
	}

	app->addMember(member);

	cout << "\t등록되었습니다!" << endl;
	CLEAR_STD_BUFFER();

	return true; // true를 반환하면 루프를 탈출해서 회원정보 메인 메뉴로 이동하게 된다. 
}


// 로그인 프로세스 
bool NoneProcess::logic_Login(App* app) {
	if (NULL == app) return false;
	system("cls"); // 화면을 깨끗히 지운다.


	MemberInfo member;
	cout << endl;
	cout << "〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓" << endl;
	cout << "▶▶ 회원정보 >> 로그인" << endl;
	cout << "〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓" << endl;

	
	while (true) {
		cout << endl;
		cout << "\t☞ ID 입력(10):";
		cin >> member.id;

		if (0 == strlen(member.id.c_str())) {
			cout << endl;
			cout << "\t※ID를 입력하세요!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}

		// 존재하는 ID인지 체크 
		if (false == app->checkExistID(member.id)) {
			cout << endl;
			cout << "\t※존재하지않는 ID입니다 ID를 다시 입력하세요!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}

		if (10 < strlen(member.id.c_str())) {
			cout << endl;
			cout << "\t※글자수가 10자 미만으로 입력해주세요!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}
		break;
	}



	while (true) {
		cout << endl;
		cout << "\t☞ 비밀번호 입력(10):";
		cin >> member.pwd;

		if (0 == strlen(member.id.c_str())) {
			cout << endl;
			cout << "\t※비밀번호를 입력하세요!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}

		if (10 < strlen(member.id.c_str())) {
			cout << endl;
			cout << "\t※글자수가 10자 미만으로 입력해주세요!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}
		break;
	}
	// 인증 체크 
	if (false == app->checkAuth(member.id.c_str(), member.pwd.c_str())) {
		cout << endl;
		cout << "\t※회원 정보가 일치하지 않습니다!";
		cout << endl;
		CLEAR_STD_BUFFER();
		return false;
	}
	else {
		cout << endl;
		cout << "\t※로그인 되었습니다!";
		cout << endl;
		CLEAR_STD_BUFFER();

		app->loginMemberID = member.id;

		MemberInfo outMember;
		app->GetMember(member.id.c_str(), outMember);
		if (TYPE_ACTOR::ACTOR_USER == outMember.actortype) {
			app->changeMode(TYPE_MODE::MODE_USER);
		}
		else {
			app->changeMode(TYPE_MODE::MODE_MANAGER);
		}

		return true;
	}
}


// 회원 탈퇴 프로세스 
bool NoneProcess::logic_LeaveMember(App* app) {

	if (NULL == app) return false;
	system("cls"); // 화면을 깨끗히 지운다. 

	MemberInfo member;

	cout << endl;
	cout << "〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓" << endl;
	cout << "▶▶ 회원정보 >> 회원탈퇴" << endl;
	cout << "〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓" << endl;

	cout << endl;
	cout << "\t1. 회원탈퇴하기" << endl;
	cout << "\t2. 되돌아가기" << endl;

	int menu = -1;
	while (true) {
		cout << "\t☞ 메뉴를 선택하세요(1~2):";
		cin >> menu;

		if (1 != menu && 2 != menu) {
			cout << endl;
			cout << "\t※잘못 입력하셨습니다!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}
		break;
	}

	if (2 == menu) {
		cout << "\t상위메뉴로 되돌아 갑니다!" << endl;
		Sleep(1000);
		return true;
	}



	while (true) {
		cout << endl;
		cout << "\t☞ ID 입력(10):";
		cin >> member.id;

		if (0 == strlen(member.id.c_str())) {
			cout << endl;
			cout << "\t※ID를 입력하세요!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}

		// 존재하는 ID인지 체크 
		if (false == app->checkExistID(member.id)) {
			cout << endl;
			cout << "\t※존재하지않는 ID입니다 ID를 다시 입력하세요!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}

		if (10 < strlen(member.id.c_str())) {
			cout << endl;
			cout << "\t※글자수가 10자 미만으로 입력해주세요!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}
		break;
	}



	while (true) {
		cout << endl;
		cout << "\t☞ 비밀번호 입력(10):";
		cin >> member.pwd;

		if (0 == strlen(member.id.c_str())) {
			cout << endl;
			cout << "\t※비밀번호를 입력하세요!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}

		if (10 < strlen(member.id.c_str())) {
			cout << endl;
			cout << "\t※글자수가 10자 미만으로 입력해주세요!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}
		break;
	}

	// id 의 패스워드가 일치하는 지 확인하고 탈퇴처리한다. 
	if (false == app->checkAuth(member.id.c_str(), member.pwd.c_str())) {
		cout << endl;
		cout << "\t※비밀번호가 일치하지 않습니다!";
		cout << endl;
		CLEAR_STD_BUFFER();
		return false;
	}

	// 탈퇴할 지 한번 더 확인 
	cout << endl;
	cout << "\t☞ 탈퇴하시겠습니까? (Y/N) : ";
	string yn;
	cin >> yn;

	// 대문자로 모두 바꾼다. 
	transform(yn.begin(), yn.end(), yn.begin(), toupper);

	if (!strcmp(yn.c_str(), "Y")) {
		// 탈퇴 처리 
		app->leaveMember(member.id.c_str());
		cout << "\t※탈퇴하였습니다" << endl;
		CLEAR_STD_BUFFER();

	}
	else {
		cout << "\t※취소되었습니다" << endl;
		CLEAR_STD_BUFFER();

	}

	return true;
}
