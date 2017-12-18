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

	system("cls"); // ȭ���� ������ �����. 
	cout << endl;
	cout << "�����������������������" << endl;
	cout << "���� ȸ������" << endl;
	cout << "�����������������������" << endl;
	cout << endl; 
	cout << "\t1)ȸ������" << endl;
	cout << "\t2)�α���" << endl;
	cout << "\t3)ȸ��Ż��" << endl;

	logic = -1;
	while (true) {
		cout << endl;
		cout << "�� ��ȣ�� �Է��ϼ��� (1~3) :";
		cin >> logic;
		if (logic < 0 || logic > 3) {
			cout << "\t���߸��Է� �ϼ̽��ϴ�. �ٽ��Է����ּ���!" << endl;
			CLEAR_STD_BUFFER();
			continue;
		}

		break;
	}

	while (true) {
		if (1 == logic) { // ȸ������ 
			if (logic_JoinMember(app)) break;
		}
		else if (2 == logic) { // �α��� 
			if (logic_Login(app)) break;
		}
		else if (3 == logic) { // ȸ��Ż�� 
			if (logic_LeaveMember(app)) break;
		}
	}
}


// ȸ�� ���� ���μ��� 
bool NoneProcess::logic_JoinMember(App* app) {

	if (NULL == app) return false;
	system("cls"); // ȭ���� ������ �����. 

	MemberInfo member;
	cout << endl;
	cout << "�����������������������" << endl;
	cout << "���� ȸ������ >> ȸ������" << endl;
	cout << "�����������������������" << endl;

	cout << endl;
	cout << "\t1. ȸ�������ϱ�" << endl; 
	cout << "\t2. �ǵ��ư���" << endl;

	int menu = -1;
	while (true) {
		cout << "\t�� �޴��� �����ϼ���(1~2):";
		cin >> menu;

		if (1 != menu && 2 != menu) {
			cout << endl;
			cout << "\t���߸� �Է��ϼ̽��ϴ�!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}
		break; 
	}
	
	if (2 == menu) {
		cout << "\t�����޴��� �ǵ��� ���ϴ�!" << endl; 
		Sleep(1000);
		return true;
	}
		




	while (true) {
		cout << endl;
		cout << "\t�� ID �Է�(10):";
		cin >> member.id;

		if (0 == strlen(member.id.c_str())) {
			cout << endl;
			cout << "\t��ID�� �Է��ϼ���!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}

		// �̹� �����ϴ� ID���� üũ 
		if (true == app->checkExistID(member.id)) {
			cout << endl;
			cout << "\t���̹������ϴ� ID�Դϴ� �ٸ� ID�� �Է��ϼ���!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}

		if (10 < strlen(member.id.c_str())) {
			cout << endl;
			cout << "\t�ر��ڼ��� 10�� �̸����� �Է����ּ���!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}
		break;
	}



	while (true) {
		cout << endl;
		cout << "\t�� ��й�ȣ �Է�(10):";
		cin >> member.pwd;

		if (0 == strlen(member.id.c_str())) {
			cout << endl;
			cout << "\t�غ�й�ȣ�� �Է��ϼ���!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}

		if (10 < strlen(member.id.c_str())) {
			cout << endl;
			cout << "\t�ر��ڼ��� 10�� �̸����� �Է����ּ���!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}
		break;
	}

	while (true) {
		cout << endl;
		cout << "\t�� Type 1:User, 2:Manager ( 1~2 ) :";
		cin >> member.actortype;

		if (1 > member.actortype || 2 < member.actortype) {
			cout << endl;
			cout << "\t��1�Ǵ� 2�� �Է����ּ���!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}
		member.actortype--;
		break;
	}

	app->addMember(member);

	cout << "\t��ϵǾ����ϴ�!" << endl;
	CLEAR_STD_BUFFER();

	return true; // true�� ��ȯ�ϸ� ������ Ż���ؼ� ȸ������ ���� �޴��� �̵��ϰ� �ȴ�. 
}


// �α��� ���μ��� 
bool NoneProcess::logic_Login(App* app) {
	if (NULL == app) return false;
	system("cls"); // ȭ���� ������ �����.


	MemberInfo member;
	cout << endl;
	cout << "�����������������������" << endl;
	cout << "���� ȸ������ >> �α���" << endl;
	cout << "�����������������������" << endl;

	
	while (true) {
		cout << endl;
		cout << "\t�� ID �Է�(10):";
		cin >> member.id;

		if (0 == strlen(member.id.c_str())) {
			cout << endl;
			cout << "\t��ID�� �Է��ϼ���!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}

		// �����ϴ� ID���� üũ 
		if (false == app->checkExistID(member.id)) {
			cout << endl;
			cout << "\t�����������ʴ� ID�Դϴ� ID�� �ٽ� �Է��ϼ���!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}

		if (10 < strlen(member.id.c_str())) {
			cout << endl;
			cout << "\t�ر��ڼ��� 10�� �̸����� �Է����ּ���!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}
		break;
	}



	while (true) {
		cout << endl;
		cout << "\t�� ��й�ȣ �Է�(10):";
		cin >> member.pwd;

		if (0 == strlen(member.id.c_str())) {
			cout << endl;
			cout << "\t�غ�й�ȣ�� �Է��ϼ���!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}

		if (10 < strlen(member.id.c_str())) {
			cout << endl;
			cout << "\t�ر��ڼ��� 10�� �̸����� �Է����ּ���!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}
		break;
	}
	// ���� üũ 
	if (false == app->checkAuth(member.id.c_str(), member.pwd.c_str())) {
		cout << endl;
		cout << "\t��ȸ�� ������ ��ġ���� �ʽ��ϴ�!";
		cout << endl;
		CLEAR_STD_BUFFER();
		return false;
	}
	else {
		cout << endl;
		cout << "\t�طα��� �Ǿ����ϴ�!";
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


// ȸ�� Ż�� ���μ��� 
bool NoneProcess::logic_LeaveMember(App* app) {

	if (NULL == app) return false;
	system("cls"); // ȭ���� ������ �����. 

	MemberInfo member;

	cout << endl;
	cout << "�����������������������" << endl;
	cout << "���� ȸ������ >> ȸ��Ż��" << endl;
	cout << "�����������������������" << endl;

	cout << endl;
	cout << "\t1. ȸ��Ż���ϱ�" << endl;
	cout << "\t2. �ǵ��ư���" << endl;

	int menu = -1;
	while (true) {
		cout << "\t�� �޴��� �����ϼ���(1~2):";
		cin >> menu;

		if (1 != menu && 2 != menu) {
			cout << endl;
			cout << "\t���߸� �Է��ϼ̽��ϴ�!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}
		break;
	}

	if (2 == menu) {
		cout << "\t�����޴��� �ǵ��� ���ϴ�!" << endl;
		Sleep(1000);
		return true;
	}



	while (true) {
		cout << endl;
		cout << "\t�� ID �Է�(10):";
		cin >> member.id;

		if (0 == strlen(member.id.c_str())) {
			cout << endl;
			cout << "\t��ID�� �Է��ϼ���!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}

		// �����ϴ� ID���� üũ 
		if (false == app->checkExistID(member.id)) {
			cout << endl;
			cout << "\t�����������ʴ� ID�Դϴ� ID�� �ٽ� �Է��ϼ���!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}

		if (10 < strlen(member.id.c_str())) {
			cout << endl;
			cout << "\t�ر��ڼ��� 10�� �̸����� �Է����ּ���!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}
		break;
	}



	while (true) {
		cout << endl;
		cout << "\t�� ��й�ȣ �Է�(10):";
		cin >> member.pwd;

		if (0 == strlen(member.id.c_str())) {
			cout << endl;
			cout << "\t�غ�й�ȣ�� �Է��ϼ���!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}

		if (10 < strlen(member.id.c_str())) {
			cout << endl;
			cout << "\t�ر��ڼ��� 10�� �̸����� �Է����ּ���!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}
		break;
	}

	// id �� �н����尡 ��ġ�ϴ� �� Ȯ���ϰ� Ż��ó���Ѵ�. 
	if (false == app->checkAuth(member.id.c_str(), member.pwd.c_str())) {
		cout << endl;
		cout << "\t�غ�й�ȣ�� ��ġ���� �ʽ��ϴ�!";
		cout << endl;
		CLEAR_STD_BUFFER();
		return false;
	}

	// Ż���� �� �ѹ� �� Ȯ�� 
	cout << endl;
	cout << "\t�� Ż���Ͻðڽ��ϱ�? (Y/N) : ";
	string yn;
	cin >> yn;

	// �빮�ڷ� ��� �ٲ۴�. 
	transform(yn.begin(), yn.end(), yn.begin(), toupper);

	if (!strcmp(yn.c_str(), "Y")) {
		// Ż�� ó�� 
		app->leaveMember(member.id.c_str());
		cout << "\t��Ż���Ͽ����ϴ�" << endl;
		CLEAR_STD_BUFFER();

	}
	else {
		cout << "\t����ҵǾ����ϴ�" << endl;
		CLEAR_STD_BUFFER();

	}

	return true;
}
