#include "stdafx.h"
#include "UserProcess.h"
#include "App.h"
#include "CodeGenerator.h"

UserProcess::UserProcess()
{
}


UserProcess::~UserProcess()
{
}

void UserProcess::doRun(App* app) {
	if (NULL == app) return;

	system("cls"); // ȭ���� ������ �����. 
	cout << endl;
	cout << "�����������������������" << endl;
	cout << "���� ����ڸ��" << endl;
	cout << "�����������������������" << endl;
	cout << endl; 
	cout << "\t1)������ȭ����" << endl;
	cout << "\t2)��¥����ȭ�ð�����" << endl;
	cout << "\t3)��ȭ�˻�" << endl;
	cout << "\t4)��ȭ����" << endl;
	cout << "\t5)�α׾ƿ�" << endl;

	logic = -1;
	while (true) {
		cout << endl;
		cout << "�� ��ȣ�� �Է��ϼ��� (1~5) :";
		cin >> logic;
		if (logic < 0 || logic > 5) {
			cout << "\t���߸��Է� �ϼ̽��ϴ�. �ٽ��Է����ּ���!" << endl;
			CLEAR_STD_BUFFER();
			continue;
		}
		break;
	}

	while (true) {
		if (1 == logic) { // ������ȭ���� 
			if (logic_OpenMovieInfo(app)) break;
		}
		else if (2 == logic) { // ��¥����ȭ�ð����� 
			if (logic_MovieTimeInfo(app)) break;
		}
		else if (3 == logic) { // ��ȭ�˻� 
			if (logic_SearchMovie(app)) break;
		}
		else if (4 == logic) { // ��ȭ����
			if (logic_ReserveMovieMenu(app)) break;
		}
		else if (5 == logic) {
			app->changeMode(TYPE_MODE::MODE_NONE);

			cout << endl;
			cout << "\t�α׾ƿ� �Ǿ����ϴ�!" << endl;
			CLEAR_STD_BUFFER();
			break;
		}
	}


}

bool UserProcess::logic_OpenMovieInfo(App* app) {

	if (NULL == app) return false;
	system("cls"); // ȭ���� ������ �����. 
	cout << endl;
	cout << "�����������������������" << endl;
	cout << "���� ����ڸ�� >> ������ȭ����" << endl;
	cout << "�����������������������" << endl;

	cout << endl; 
	app->displMovieInfoAll();

	int n = -1;
	while (true) {
		cout << endl; 
		cout << "\t(1)��ȭ���ú���, (2)�޴�������";
		cin >> n;

		if (1 != n && 2 != n) {
			cout << endl;
			cout << "\t���߸� �Է��ϼ̽��ϴ�!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}
		break; 
	}

	if (1 == n) { // ��ȭ���ú���

		int movieIndex = -1;
		while (true) {
			cout << "\t��ȭ��ȣ����:";

			
			cin >> movieIndex;

			if (0 > movieIndex) {
				cout << endl;
				cout << "\t���߸� �Է��ϼ̽��ϴ�!";
				cout << endl;
				CLEAR_STD_BUFFER();
				continue; 
			}

			break; 
		}
		
		MovieInfo *m = app->GetMovie(movieIndex);
		if (NULL == m) {
			cout << endl;
			cout << "\t�ؽý��ۿ���!";
			cout << endl;
			Sleep(1000);
			return false; 
		}

		DisplayMovieInfo(m); 
		
		cout << endl; 
		cout << "\t�� �ƹ�Ű�������ø� �����޴��� �̵��մϴ�" << endl; 

		_getche(); 

	}
	else if (2 == n) { // �޴�������
		cout << "\t���� �޴��� �̵��մϴ�!" << endl; 
		Sleep(1000); 
		return true; 
	}
	


	return true;
}

void UserProcess::DisplayMovieInfo(MovieInfo *m) {
	cout << endl;
	cout << "\t������������" << endl;
	cout << "\t���� ��ȭ����" << endl;
	cout << "\t������������" << endl;
	cout << endl; 
	cout << "\t��ȭ��: " << m->name.c_str() << endl;
	cout << "\t��������: " << m->openDate.get_ymd().c_str() << endl;
	cout << "\t���ѽð�: " << m->playAllTime << "��" << endl;
	cout << "\t�帣: " << m->category.c_str() << endl;
	cout << "\t�ٰŸ�: " << m->story.c_str() << endl;
}
bool UserProcess::logic_MovieTimeInfo(App* app) {

	if (NULL == app) return false;
	system("cls"); // ȭ���� ������ �����. 

	cout << endl;
	cout << "�����������������������" << endl;
	cout << "���� ����ڸ�� >> ��¥����ȭ�ð�����" << endl;
	cout << "�����������������������" << endl;

	// �����ڰ� ����� ��ȭ�� �󿵽ð� ���� ��� 
	app->displayMovieInfoByGateAll();
	
	cout << endl; 
	cout << "\t�� �ƹ�Ű�������ø� �����޴��� �̵��մϴ�" << endl;
	_getche();

	/*
	string date;
	vector<int> tokenList;
	while (true) {
		cout << endl;
		cout << "\t���� ���� ��¥�� �Է��ϼ��� (ex> 2017/10/21 ) :";
		
		cin >> date;

		
		int tokenCnt = 0;
		char *ptr = strtok(const_cast<char*>(date.c_str()), "/");
		while (ptr != NULL) {
			tokenCnt++;
			tokenList.push_back(atoi(ptr));
			ptr = strtok(NULL, "/");
		}

		if (3 != tokenCnt) {
			cout << endl;
			cout << "\t���߸��Է��ϼ̽��ϴ�!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}

		// �� üũ ( 1980~2017 )
		if (1980 > tokenList[0] || 2017 < tokenList[0]) {
			cout << endl;
			cout << "\t��1980~2017����� �Է°����մϴ�!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}

		// �� üũ (1~12 ) 
		if (1 > tokenList[1] || 12 < tokenList[1]) {
			cout << endl;
			cout << "\t��1~12������ �Է°����մϴ�!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}

		// �� üũ (1~31)
		if (1 > tokenList[2] || 31 < tokenList[2]) {
			cout << endl;
			cout << "\t��1~31�ϱ��� �Է°����մϴ�!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}

		break; 
	}

	//// �������� ����� �����´�. 
	vector<MovieInfo> outList; 
	app->GetMovieByTime(tokenList[0], tokenList[1], tokenList[2], outList);

	if (outList.size() == 0) {
		cout << "\t��û ������ ������ȭ�� �����ϴ�!" << endl; 
		CLEAR_STD_BUFFER();
	}
	else {
		cout << endl; 
		cout << "\t**�Ʒ��� ���� ��û������ ��ȭ ����� �˻��Ǿ����ϴ�!" << endl; 
		for (auto m : outList) {
			DisplayMovieInfo(&m);
		}
		cout << endl;
		cout << "\t�� �ƹ�Ű�������ø� �����޴��� �̵��մϴ�" << endl;

		_getche();
	}	*/
	
	return true;
}

bool UserProcess::logic_SearchMovie(App* app) {
	if (NULL == app) return false;
	system("cls"); // ȭ���� ������ �����. 
	cout << endl;
	cout << "�����������������������" << endl;
	cout << "���� ����ڸ�� >> ��ȭ�˻�" << endl;
	cout << "�����������������������" << endl;

	cout << endl;
	cout << "\t�� �˻��� ��ȭ�� �Է�:";
	string name; 
	cin >> name; 

	MovieInfo *m = app->GetMovie(name.c_str());
	if (NULL == m) {
		cout << endl;
		cout << "\t��ȭ�� �������� �ʽ��ϴ�!" << endl; 
		cout << endl;
		CLEAR_STD_BUFFER();
	}
	else {
		DisplayMovieInfo(m);

		cout << endl;
		cout << "\t�� �ƹ�Ű�������ø� �����޴��� �̵��մϴ�" << endl;

		_getche();
	}



	return true;
}

bool UserProcess::logic_ReserveMovieMenu(App* app) {

	if (NULL == app) return false;
	system("cls"); // ȭ���� ������ �����. 

	cout << endl;
	cout << "�����������������������" << endl;
	cout << "���� ����ڸ�� >> ��ȭ����" << endl;
	cout << "�����������������������" << endl;
	cout << endl; 
	cout << "\t1)��ȭ����" << endl;
	cout << "\t2)����������ȸ" << endl;
	cout << "\t3)�������" << endl;
	cout << "\t0)�ǵ��ư���" << endl;

	logic = -1;
	while (true) {
		cout << endl;
		cout << "�� ��ȣ�� �Է��ϼ��� (0~3) :";
		cin >> logic;
		if (logic < 0 || logic > 3) {
			cout << "\t���߸��Է� �ϼ̽��ϴ�. �ٽ��Է����ּ���!" << endl;
			CLEAR_STD_BUFFER();
			continue;
		}

		break;
	}

	while (true) {
		if (1 == logic) { // ��ȭ���� 
			if (logic_ReserveMovie(app)) break;
		}
		else if (2 == logic) { // ����������ȸ 
			if (logic_MyReservInfo(app)) break;
		}
		else if (3 == logic) { // �������
			if (logic_CancelReservInfo(app)) break;
		}
		else if (0 == logic) { // �ǵ��ư���
			
			cout << endl;
			cout << "\t�����޴��� �̵��մϴ�" << endl;
			Sleep(1000); 
			return true; 
		}
	}


	return true; 
}

bool UserProcess::logic_ReserveMovie(App* app) {
	if (NULL == app) return false;
	system("cls"); // ȭ���� ������ �����. 

	cout << endl;
	cout << "�����������������������" << endl;
	cout << "���� ����ڸ�� >> ��ȭ���� >> �����ϱ�" << endl;
	cout << "�����������������������" << endl;

	cout << endl;
	cout << "\t** ������ ��ȭ�� �����ϼ���!" << endl;
	cout << endl;
	app->displMovieInfoAll();

	cout << "\t" << app->getMaxMovieCount() + 1 << ".�ǵ��ư���" << endl;

	int movieIndex = -1;
	while (true) {
		cout << "\t��ȭ��ȣ����:";


		cin >> movieIndex;

		if (0 > movieIndex) {
			cout << endl;
			cout << "\t���߸� �Է��ϼ̽��ϴ�!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}

		if ((app->getMaxMovieCount() + 1) == movieIndex) {
			cout << endl;
			cout << "\t�ػ����޴��� �̵��մϴ�";
			cout << endl;
			CLEAR_STD_BUFFER();
			return true; 
		}

		break;
	}

	MovieInfo *m = app->GetMovie(movieIndex);
	if (NULL == m) {
		cout << endl;
		cout << "\t�ؽý��ۿ���!";
		cout << endl;
		CLEAR_STD_BUFFER();
		return false;
	}

	// ������¥�� �Է� 
	Time reqTime; 
	
	while (true) {
		cout << endl;
		cout << "\t�� ������¥ �Է�(��/��/��) ex)1980/09/28 : ";
		string str;
		cin >> str;

		vector<int> tokenList;
		int tokenCnt = 0;
		char *ptr = strtok(const_cast<char*>(str.c_str()), "/");
		while (ptr != NULL) {
			tokenCnt++;
			tokenList.push_back(atoi(ptr));
			ptr = strtok(NULL, "/");
		}

		if (3 != tokenCnt) {
			cout << endl;
			cout << "\t���߸��Է��ϼ̽��ϴ�!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}


		// �� üũ ( 1980~2018 )
		if (1980 > tokenList[0] || 2018 < tokenList[0]) {
			cout << endl;
			cout << "\t��1980~2018����� �Է°����մϴ�!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}

		// �� üũ (1~12 ) 
		if (1 > tokenList[1] || 12 < tokenList[1]) {
			cout << endl;
			cout << "\t��1~12������ �Է°����մϴ�!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}

		// �� üũ (1~31)
		if (1 > tokenList[2] || 31 < tokenList[2]) {
			cout << endl;
			cout << "\t��1~31�ϱ��� �Է°����մϴ�!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}

		reqTime.year = tokenList[0];
		reqTime.month = tokenList[1];
		reqTime.day = tokenList[2];

		break;
	}


	// ��ü �󿵰����� �ش� ��ȭ�� �ð��� ��ȸ�ؼ� �����´�. 
	vector<MovieInfo> outList;
	app->GetMovieTimeByGateAll(movieIndex, outList);

	if (0 == outList.size()) {
		cout << endl;
		cout << "\t�ش� ��ȭ�� ������ �ʽ��ϴ�!" << endl;
		cout << endl;
		CLEAR_STD_BUFFER();
		return false;
	}

	bool isExist = false; 
	for (auto out : outList) {
		// ��ȭ �󿵳�¥ ���� ��¥�� ���� ������ ���� ��� 
		time_t displayTime = app->getTimeInt(out.playtime.year, out.playtime.month, out.playtime.day);
		time_t displayEndTime = app->getTimeInt(out.endtime.year, out.endtime.month, out.endtime.day);
		time_t viewTime = app->getTimeInt(reqTime.year, reqTime.month, reqTime.day);

		if (displayTime <= viewTime && displayEndTime >= viewTime ) {
			isExist = true; 
			break; 
		}
	}
	if (false == isExist) {
		cout << endl;
		cout << "\t�ش� ��¥�� ������ �ʴ� ��ȭ�Դϴ�!" << endl;
		cout << endl;
		CLEAR_STD_BUFFER();
		return false;
	}


	// �� �ð��� ��� �Ѵ�. 

	cout << endl;
	cout << "\t������������" << endl;
	cout << "\t���� ��ȭ�󿵽ð�" << endl;
	cout << "\t������������" << endl;

	map<int, Time> selMap;
	int count = 1;
	for (auto m : outList) {
		cout << "\t" << count << "." << m.playtime.get_all().c_str() << endl;
		selMap.insert(pair<int, Time>(count, m.playtime));
		count++;
	}

	int n = -1;
	while (true) {
		cout << endl;
		cout << "\t�� �����ϼ��� (1~" << count << ") :" << endl;

		// �󿵽ð� ����� ���� �����ְ� �߰��� ���� �� �� �ֵ��� �Ѵ�. 

		cin >> n;
		if (1 > n || count < n) {
			cout << endl;
			cout << "\t���߸��Է��ϼ̽��ϴ�!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}

		auto it = selMap.find(n);
		if (it == selMap.end()) {
			cout << endl;
			cout << "\t���߸��Է��ϼ̽��ϴ�!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}
		break;
	}

	auto it = selMap.find(n);


	// ������ �󿵽ð����� �¼������� ����. 
	

	// �¼� ������ �����ش�. 
	while (true) {
		system("cls");

		SeatInfo outSeatInfo;
		app->GetMovieFormGateByTime(m->index, it->second.get_hms().c_str(), outSeatInfo);

		cout << endl;
		cout << "\t������������" << endl;
		cout << "\t���� �¼�����" << endl;
		cout << "\t������������" << endl;

		cout << endl; 
		cout << "\t���డ�ɼ� : �� " << endl; 
		cout << "\t����Ұ�: ��" << endl; 

		cout << "\t������������������������������������������" << endl; 
		cout << "\t��      screen       ��" << endl; 
		cout << "\t������������������������������������������" << endl;

		cout << "\t  ";
		for (int i = 0; i < 10; ++i) {
			 cout << i << " ";
		}
		cout << endl;

		char rowKey[10] = { 'a', 'b', 'c', 'd', 'e', 'f','g', 'h', 'i','j' };
		for (int i = 0; i < 10; ++i) {
			cout << "\t" << rowKey[i];
			for (int j = 0; j < 10; ++j) {
				if (1 == outSeatInfo.seat[i][j]) {
					
					cout << "��";
				}
				else {
					cout << "��";
				}
			}
			cout << endl;
		}


		cout << endl; 
		cout << "\t�� ������ �¼� ���� �����ϼ��� ( a~j ): ";

		string row; 
		cin >> row; 
		int rindex = convertToRowIndex(row.c_str());
		if (-1 == rindex) {
			cout << endl;
			cout << "\t���߸��Է��ϼ̽��ϴ�!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}
		
		if (0 > rindex || 9 < rindex) {
			cout << endl;
			cout << "\t���߸��Է��ϼ̽��ϴ�!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}

		int cindex = -1; 
		cout << "\t�� ������ �¼� ���� �����ϼ��� ( 0~9 ): ";
		cin >> cindex; 
		if (0 > cindex || 9 < cindex) {
			cout << endl;
			cout << "\t���߸��Է��ϼ̽��ϴ�!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}
		
		// �̹� ����Ǿ����� Ȯ�� 
		if (outSeatInfo.seat[rindex][cindex]) {
			cout << endl;
			cout << "\t���̹� ����� �¼��Դϴ�!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}

		// ���� �������� ��Ͽ� ���� 
		ReserveInfo reserveInfo;
		reserveInfo.movieIndex = m->index;
		reserveInfo.movieName = m->name.c_str();
		reserveInfo.reserveTime = it->second;
		reserveInfo.seat = row.c_str();
		reserveInfo.seat += std::to_string(cindex);
		reserveInfo.rowindex = rindex;
		reserveInfo.colindex = cindex;



		// �̹� �ڽ��� �����ߴ��� Ȯ�� 
		if (app->alreadyReserveMyInfo(reserveInfo)) {
			cout << endl;
			cout << "\t���ߺ� ������ �� �����ϴ�!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}

		// �¼� ���� 
		app->ReserveSeat(m->index, it->second.get_hms().c_str(), rindex, cindex);

		
		// �ڵ� �߱� 
		reserveInfo.code = CodeGenerator::getInstance()->createCode();

		app->ReserveMyInfo(reserveInfo);

		cout << endl; 
		cout << "\t���� �Ǿ����ϴ�!" << endl; 
		cout << "\t**�����ڵ�� (" << reserveInfo.code << ") �Դϴ�." << endl; 

		cout << endl; 
		cout << "\t�� ��� �����Ͻðڽ��ϱ�? (y or n ):";

		string yn;
		cin >> yn;

		// �빮�ڷ� ��� �ٲ۴�. 
		transform(yn.begin(), yn.end(), yn.begin(), toupper);

		if (!strcmp(yn.c_str(), "Y")) {
			// ����
			cout << "\t�ذ�� �����մϴ�!" << endl;
			Sleep(1000);
		}
		else {
			Sleep(1000);
			break;
		}
	}
	return true;
}

int UserProcess::convertToRowIndex(string str)
{
	if (!strcmp(str.c_str(), "a")) return 0; 
	else if (!strcmp(str.c_str(), "b")) return 1;
	else if (!strcmp(str.c_str(), "c")) return 2;
	else if (!strcmp(str.c_str(), "d")) return 3;
	else if (!strcmp(str.c_str(), "e")) return 4;
	else if (!strcmp(str.c_str(), "f")) return 5;
	else if (!strcmp(str.c_str(), "g")) return 6;
	else if (!strcmp(str.c_str(), "h")) return 7;
	else if (!strcmp(str.c_str(), "i")) return 8;
	else if (!strcmp(str.c_str(), "j")) return 9;
	return -1; 
}

bool UserProcess::logic_MyReservInfo(App* app) {
	if (NULL == app) return false;
	system("cls"); // ȭ���� ������ �����. 

	cout << endl;
	cout << "�����������������������" << endl;
	cout << "���� ����ڸ�� >> ��ȭ���� >> ����������ȸ" << endl;
	cout << "�����������������������" << endl;

	int code = -1;
	while (true) {
		cout << endl;
		cout << "\t�� �����ڵ带 �Է�: ";
		
		cin >> code;

		if (-1 == code) {
			cout << endl;
			cout << "\t���߸��Է��ϼ̽��ϴ�!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}
		break; 
	}


	
	ReserveInfo* r = app->GetReserveInfo(code); 
	if (NULL == r) {
		//�ڵ������� ��ġ���� �ʽ��ϴ�
		cout << endl;
		cout << "\t���ڵ������� ��ġ���� �ʽ��ϴ�!";
		cout << endl;
		CLEAR_STD_BUFFER();
		return true; 
	}


	cout << endl;
	cout << "\t������������" << endl;
	cout << "\t���� ��������" << endl;
	cout << "\t������������" << endl;
	cout << endl; 
	cout << "\t��ȭ�� : " << r->movieName.c_str() << endl;
	cout << "\t��ȭ�ð� : " << r->reserveTime.get_hms().c_str() << endl; 
	cout << "\t�����¼� : " << r->seat.c_str() << endl; 

	cout << endl;
	cout << "\t�� �ƹ�Ű�������ø� �����޴��� �̵��մϴ�" << endl;

	_getche();

	return true; 

}

bool UserProcess::logic_CancelReservInfo(App* app) {
	if (NULL == app) return false;
	system("cls"); // ȭ���� ������ �����. 

	cout << endl;
	cout << "�����������������������" << endl;
	cout << "���� ����ڸ�� >> ��ȭ���� >> �������" << endl;
	cout << "�����������������������" << endl;

	int code = -1;
	while (true) {
		cout << endl;
		cout << "\t�� �����ڵ带 �Է�: ";

		cin >> code;

		if (-1 == code) {
			cout << endl;
			cout << "\t���߸��Է��ϼ̽��ϴ�!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}
		break;
	}



	ReserveInfo* r = app->GetReserveInfo(code);
	if (NULL == r) {
		//�ڵ������� ��ġ���� �ʽ��ϴ�
		cout << endl;
		cout << "\t���ڵ������� ��ġ���� �ʽ��ϴ�!";
		cout << endl;
		CLEAR_STD_BUFFER();
		return true;
	}


	// Ż���� �� �ѹ� �� ���� ����. 
	cout << endl;
	cout << "\t�� ���� ��� �Ͻðڽ��ϱ�? (Y/N) : ";
	string yn;
	cin >> yn;

	// �빮�ڷ� ��� �ٲ۴�. 
	transform(yn.begin(), yn.end(), yn.begin(), toupper);

	

	if (!strcmp(yn.c_str(), "Y")) {

		// ������� ó�� 
		app->RemoveReserveMyinfo(code); 

		// �ڸ������͵� ���� ��Ų��. 
		app->ReserveCancelSeat(r->movieIndex, r->reserveTime.get_all().c_str(), r->rowindex, r->colindex);
		
		cout << "\t�ؿ�����ҵǾ����ϴ�" << endl;
		CLEAR_STD_BUFFER();

	}
	else {
		cout << "\t�ؿ�����ҵ��� �ʾҽ��ϴ�" << endl;
		CLEAR_STD_BUFFER();
	}


	return true; 
}