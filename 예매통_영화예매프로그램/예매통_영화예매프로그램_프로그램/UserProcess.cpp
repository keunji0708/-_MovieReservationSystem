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

	system("cls"); // 화면을 깨끗히 지운다. 
	cout << endl;
	cout << "〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓" << endl;
	cout << "▶▶ 사용자모드" << endl;
	cout << "〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓" << endl;
	cout << endl; 
	cout << "\t1)개봉영화정보" << endl;
	cout << "\t2)날짜별영화시간정보" << endl;
	cout << "\t3)영화검색" << endl;
	cout << "\t4)영화예매" << endl;
	cout << "\t5)로그아웃" << endl;

	logic = -1;
	while (true) {
		cout << endl;
		cout << "☞ 번호를 입력하세요 (1~5) :";
		cin >> logic;
		if (logic < 0 || logic > 5) {
			cout << "\t※잘못입력 하셨습니다. 다시입력해주세요!" << endl;
			CLEAR_STD_BUFFER();
			continue;
		}
		break;
	}

	while (true) {
		if (1 == logic) { // 개봉영화정보 
			if (logic_OpenMovieInfo(app)) break;
		}
		else if (2 == logic) { // 날짜별영화시간정보 
			if (logic_MovieTimeInfo(app)) break;
		}
		else if (3 == logic) { // 영화검색 
			if (logic_SearchMovie(app)) break;
		}
		else if (4 == logic) { // 영화예매
			if (logic_ReserveMovieMenu(app)) break;
		}
		else if (5 == logic) {
			app->changeMode(TYPE_MODE::MODE_NONE);

			cout << endl;
			cout << "\t로그아웃 되었습니다!" << endl;
			CLEAR_STD_BUFFER();
			break;
		}
	}


}

bool UserProcess::logic_OpenMovieInfo(App* app) {

	if (NULL == app) return false;
	system("cls"); // 화면을 깨끗히 지운다. 
	cout << endl;
	cout << "〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓" << endl;
	cout << "▶▶ 사용자모드 >> 개봉영화정보" << endl;
	cout << "〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓" << endl;

	cout << endl; 
	app->displMovieInfoAll();

	int n = -1;
	while (true) {
		cout << endl; 
		cout << "\t(1)영화선택보기, (2)메뉴나가기";
		cin >> n;

		if (1 != n && 2 != n) {
			cout << endl;
			cout << "\t※잘못 입력하셨습니다!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}
		break; 
	}

	if (1 == n) { // 영화선택보기

		int movieIndex = -1;
		while (true) {
			cout << "\t영화번호선택:";

			
			cin >> movieIndex;

			if (0 > movieIndex) {
				cout << endl;
				cout << "\t※잘못 입력하셨습니다!";
				cout << endl;
				CLEAR_STD_BUFFER();
				continue; 
			}

			break; 
		}
		
		MovieInfo *m = app->GetMovie(movieIndex);
		if (NULL == m) {
			cout << endl;
			cout << "\t※시스템오류!";
			cout << endl;
			Sleep(1000);
			return false; 
		}

		DisplayMovieInfo(m); 
		
		cout << endl; 
		cout << "\t☞ 아무키나누르시면 상위메뉴로 이동합니다" << endl; 

		_getche(); 

	}
	else if (2 == n) { // 메뉴나가기
		cout << "\t상위 메뉴로 이동합니다!" << endl; 
		Sleep(1000); 
		return true; 
	}
	


	return true;
}

void UserProcess::DisplayMovieInfo(MovieInfo *m) {
	cout << endl;
	cout << "\t〓〓〓〓〓〓〓〓〓〓〓" << endl;
	cout << "\t▶▶ 영화정보" << endl;
	cout << "\t〓〓〓〓〓〓〓〓〓〓〓" << endl;
	cout << endl; 
	cout << "\t영화명: " << m->name.c_str() << endl;
	cout << "\t개봉일자: " << m->openDate.get_ymd().c_str() << endl;
	cout << "\t상영총시간: " << m->playAllTime << "분" << endl;
	cout << "\t장르: " << m->category.c_str() << endl;
	cout << "\t줄거리: " << m->story.c_str() << endl;
}
bool UserProcess::logic_MovieTimeInfo(App* app) {

	if (NULL == app) return false;
	system("cls"); // 화면을 깨끗히 지운다. 

	cout << endl;
	cout << "〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓" << endl;
	cout << "▶▶ 사용자모드 >> 날짜별영화시간정보" << endl;
	cout << "〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓" << endl;

	// 관리자가 등록한 영화별 상영시간 정보 출력 
	app->displayMovieInfoByGateAll();
	
	cout << endl; 
	cout << "\t☞ 아무키나누르시면 상위메뉴로 이동합니다" << endl;
	_getche();

	/*
	string date;
	vector<int> tokenList;
	while (true) {
		cout << endl;
		cout << "\t관람 예정 날짜를 입력하세요 (ex> 2017/10/21 ) :";
		
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
			cout << "\t※잘못입력하셨습니다!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}

		// 년 체크 ( 1980~2017 )
		if (1980 > tokenList[0] || 2017 < tokenList[0]) {
			cout << endl;
			cout << "\t※1980~2017년까지 입력가능합니다!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}

		// 월 체크 (1~12 ) 
		if (1 > tokenList[1] || 12 < tokenList[1]) {
			cout << endl;
			cout << "\t※1~12월까지 입력가능합니다!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}

		// 일 체크 (1~31)
		if (1 > tokenList[2] || 31 < tokenList[2]) {
			cout << endl;
			cout << "\t※1~31일까지 입력가능합니다!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}

		break; 
	}

	//// 열람가능 목록을 가져온다. 
	vector<MovieInfo> outList; 
	app->GetMovieByTime(tokenList[0], tokenList[1], tokenList[2], outList);

	if (outList.size() == 0) {
		cout << "\t시청 가능한 개봉영화가 없습니다!" << endl; 
		CLEAR_STD_BUFFER();
	}
	else {
		cout << endl; 
		cout << "\t**아래와 같이 시청가능한 영화 목록이 검색되었습니다!" << endl; 
		for (auto m : outList) {
			DisplayMovieInfo(&m);
		}
		cout << endl;
		cout << "\t☞ 아무키나누르시면 상위메뉴로 이동합니다" << endl;

		_getche();
	}	*/
	
	return true;
}

bool UserProcess::logic_SearchMovie(App* app) {
	if (NULL == app) return false;
	system("cls"); // 화면을 깨끗히 지운다. 
	cout << endl;
	cout << "〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓" << endl;
	cout << "▶▶ 사용자모드 >> 영화검색" << endl;
	cout << "〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓" << endl;

	cout << endl;
	cout << "\t☞ 검색할 영화명 입력:";
	string name; 
	cin >> name; 

	MovieInfo *m = app->GetMovie(name.c_str());
	if (NULL == m) {
		cout << endl;
		cout << "\t영화가 존재하지 않습니다!" << endl; 
		cout << endl;
		CLEAR_STD_BUFFER();
	}
	else {
		DisplayMovieInfo(m);

		cout << endl;
		cout << "\t☞ 아무키나누르시면 상위메뉴로 이동합니다" << endl;

		_getche();
	}



	return true;
}

bool UserProcess::logic_ReserveMovieMenu(App* app) {

	if (NULL == app) return false;
	system("cls"); // 화면을 깨끗히 지운다. 

	cout << endl;
	cout << "〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓" << endl;
	cout << "▶▶ 사용자모드 >> 영화예매" << endl;
	cout << "〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓" << endl;
	cout << endl; 
	cout << "\t1)영화예매" << endl;
	cout << "\t2)예매정보조회" << endl;
	cout << "\t3)예매취소" << endl;
	cout << "\t0)되돌아가기" << endl;

	logic = -1;
	while (true) {
		cout << endl;
		cout << "☞ 번호를 입력하세요 (0~3) :";
		cin >> logic;
		if (logic < 0 || logic > 3) {
			cout << "\t※잘못입력 하셨습니다. 다시입력해주세요!" << endl;
			CLEAR_STD_BUFFER();
			continue;
		}

		break;
	}

	while (true) {
		if (1 == logic) { // 영화예매 
			if (logic_ReserveMovie(app)) break;
		}
		else if (2 == logic) { // 예매정보조회 
			if (logic_MyReservInfo(app)) break;
		}
		else if (3 == logic) { // 예매취소
			if (logic_CancelReservInfo(app)) break;
		}
		else if (0 == logic) { // 되돌아가기
			
			cout << endl;
			cout << "\t상위메뉴로 이동합니다" << endl;
			Sleep(1000); 
			return true; 
		}
	}


	return true; 
}

bool UserProcess::logic_ReserveMovie(App* app) {
	if (NULL == app) return false;
	system("cls"); // 화면을 깨끗히 지운다. 

	cout << endl;
	cout << "〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓" << endl;
	cout << "▶▶ 사용자모드 >> 영화예매 >> 예매하기" << endl;
	cout << "〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓" << endl;

	cout << endl;
	cout << "\t** 예매할 영화를 선택하세요!" << endl;
	cout << endl;
	app->displMovieInfoAll();

	cout << "\t" << app->getMaxMovieCount() + 1 << ".되돌아가기" << endl;

	int movieIndex = -1;
	while (true) {
		cout << "\t영화번호선택:";


		cin >> movieIndex;

		if (0 > movieIndex) {
			cout << endl;
			cout << "\t※잘못 입력하셨습니다!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}

		if ((app->getMaxMovieCount() + 1) == movieIndex) {
			cout << endl;
			cout << "\t※상위메뉴로 이동합니다";
			cout << endl;
			CLEAR_STD_BUFFER();
			return true; 
		}

		break;
	}

	MovieInfo *m = app->GetMovie(movieIndex);
	if (NULL == m) {
		cout << endl;
		cout << "\t※시스템오류!";
		cout << endl;
		CLEAR_STD_BUFFER();
		return false;
	}

	// 관람날짜를 입력 
	Time reqTime; 
	
	while (true) {
		cout << endl;
		cout << "\t☞ 관람날짜 입력(년/월/일) ex)1980/09/28 : ";
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
			cout << "\t※잘못입력하셨습니다!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}


		// 년 체크 ( 1980~2018 )
		if (1980 > tokenList[0] || 2018 < tokenList[0]) {
			cout << endl;
			cout << "\t※1980~2018년까지 입력가능합니다!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}

		// 월 체크 (1~12 ) 
		if (1 > tokenList[1] || 12 < tokenList[1]) {
			cout << endl;
			cout << "\t※1~12월까지 입력가능합니다!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}

		// 일 체크 (1~31)
		if (1 > tokenList[2] || 31 < tokenList[2]) {
			cout << endl;
			cout << "\t※1~31일까지 입력가능합니다!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}

		reqTime.year = tokenList[0];
		reqTime.month = tokenList[1];
		reqTime.day = tokenList[2];

		break;
	}


	// 전체 상영관에서 해당 영화의 시간을 조회해서 가져온다. 
	vector<MovieInfo> outList;
	app->GetMovieTimeByGateAll(movieIndex, outList);

	if (0 == outList.size()) {
		cout << endl;
		cout << "\t해당 영화는 상영하지 않습니다!" << endl;
		cout << endl;
		CLEAR_STD_BUFFER();
		return false;
	}

	bool isExist = false; 
	for (auto out : outList) {
		// 영화 상영날짜 관람 날짜가 맞지 않으면 오류 출력 
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
		cout << "\t해당 날짜에 상영하지 않는 영화입니다!" << endl;
		cout << endl;
		CLEAR_STD_BUFFER();
		return false;
	}


	// 상영 시간을 출력 한다. 

	cout << endl;
	cout << "\t〓〓〓〓〓〓〓〓〓〓〓" << endl;
	cout << "\t▶▶ 영화상영시간" << endl;
	cout << "\t〓〓〓〓〓〓〓〓〓〓〓" << endl;

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
		cout << "\t☞ 선택하세요 (1~" << count << ") :" << endl;

		// 상영시간 목록을 먼저 보여주고 추가및 삭제 할 수 있도록 한다. 

		cin >> n;
		if (1 > n || count < n) {
			cout << endl;
			cout << "\t※잘못입력하셨습니다!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}

		auto it = selMap.find(n);
		if (it == selMap.end()) {
			cout << endl;
			cout << "\t※잘못입력하셨습니다!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}
		break;
	}

	auto it = selMap.find(n);


	// 선택한 상영시간으로 좌석정보를 얻어낸다. 
	

	// 좌석 정보를 보여준다. 
	while (true) {
		system("cls");

		SeatInfo outSeatInfo;
		app->GetMovieFormGateByTime(m->index, it->second.get_hms().c_str(), outSeatInfo);

		cout << endl;
		cout << "\t〓〓〓〓〓〓〓〓〓〓〓" << endl;
		cout << "\t▶▶ 좌석선택" << endl;
		cout << "\t〓〓〓〓〓〓〓〓〓〓〓" << endl;

		cout << endl; 
		cout << "\t예약가능석 : □ " << endl; 
		cout << "\t예약불가: ■" << endl; 

		cout << "\t┌───────────────────┐" << endl; 
		cout << "\t│      screen       │" << endl; 
		cout << "\t└───────────────────┘" << endl;

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
					
					cout << "■";
				}
				else {
					cout << "□";
				}
			}
			cout << endl;
		}


		cout << endl; 
		cout << "\t☞ 예약할 좌석 행을 선택하세요 ( a~j ): ";

		string row; 
		cin >> row; 
		int rindex = convertToRowIndex(row.c_str());
		if (-1 == rindex) {
			cout << endl;
			cout << "\t※잘못입력하셨습니다!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}
		
		if (0 > rindex || 9 < rindex) {
			cout << endl;
			cout << "\t※잘못입력하셨습니다!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}

		int cindex = -1; 
		cout << "\t☞ 예약할 좌석 열을 선택하세요 ( 0~9 ): ";
		cin >> cindex; 
		if (0 > cindex || 9 < cindex) {
			cout << endl;
			cout << "\t※잘못입력하셨습니다!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}
		
		// 이미 예약되었는지 확인 
		if (outSeatInfo.seat[rindex][cindex]) {
			cout << endl;
			cout << "\t※이미 예약된 좌석입니다!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}

		// 나의 예약정보 목록에 저장 
		ReserveInfo reserveInfo;
		reserveInfo.movieIndex = m->index;
		reserveInfo.movieName = m->name.c_str();
		reserveInfo.reserveTime = it->second;
		reserveInfo.seat = row.c_str();
		reserveInfo.seat += std::to_string(cindex);
		reserveInfo.rowindex = rindex;
		reserveInfo.colindex = cindex;



		// 이미 자신이 예약했는지 확인 
		if (app->alreadyReserveMyInfo(reserveInfo)) {
			cout << endl;
			cout << "\t※중복 예약할 수 없습니다!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}

		// 좌석 예약 
		app->ReserveSeat(m->index, it->second.get_hms().c_str(), rindex, cindex);

		
		// 코드 발급 
		reserveInfo.code = CodeGenerator::getInstance()->createCode();

		app->ReserveMyInfo(reserveInfo);

		cout << endl; 
		cout << "\t예약 되었습니다!" << endl; 
		cout << "\t**예매코드는 (" << reserveInfo.code << ") 입니다." << endl; 

		cout << endl; 
		cout << "\t☞ 계속 예매하시겠습니까? (y or n ):";

		string yn;
		cin >> yn;

		// 대문자로 모두 바꾼다. 
		transform(yn.begin(), yn.end(), yn.begin(), toupper);

		if (!strcmp(yn.c_str(), "Y")) {
			// 예매
			cout << "\t※계속 예매합니다!" << endl;
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
	system("cls"); // 화면을 깨끗히 지운다. 

	cout << endl;
	cout << "〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓" << endl;
	cout << "▶▶ 사용자모드 >> 영화예매 >> 예매정보조회" << endl;
	cout << "〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓" << endl;

	int code = -1;
	while (true) {
		cout << endl;
		cout << "\t☞ 예매코드를 입력: ";
		
		cin >> code;

		if (-1 == code) {
			cout << endl;
			cout << "\t※잘못입력하셨습니다!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}
		break; 
	}


	
	ReserveInfo* r = app->GetReserveInfo(code); 
	if (NULL == r) {
		//코드정보가 일치하지 않습니다
		cout << endl;
		cout << "\t※코드정보가 일치하지 않습니다!";
		cout << endl;
		CLEAR_STD_BUFFER();
		return true; 
	}


	cout << endl;
	cout << "\t〓〓〓〓〓〓〓〓〓〓〓" << endl;
	cout << "\t▶▶ 예약정보" << endl;
	cout << "\t〓〓〓〓〓〓〓〓〓〓〓" << endl;
	cout << endl; 
	cout << "\t영화명 : " << r->movieName.c_str() << endl;
	cout << "\t영화시간 : " << r->reserveTime.get_hms().c_str() << endl; 
	cout << "\t선택좌석 : " << r->seat.c_str() << endl; 

	cout << endl;
	cout << "\t☞ 아무키나누르시면 상위메뉴로 이동합니다" << endl;

	_getche();

	return true; 

}

bool UserProcess::logic_CancelReservInfo(App* app) {
	if (NULL == app) return false;
	system("cls"); // 화면을 깨끗히 지운다. 

	cout << endl;
	cout << "〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓" << endl;
	cout << "▶▶ 사용자모드 >> 영화예매 >> 예매취소" << endl;
	cout << "〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓" << endl;

	int code = -1;
	while (true) {
		cout << endl;
		cout << "\t☞ 예매코드를 입력: ";

		cin >> code;

		if (-1 == code) {
			cout << endl;
			cout << "\t※잘못입력하셨습니다!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}
		break;
	}



	ReserveInfo* r = app->GetReserveInfo(code);
	if (NULL == r) {
		//코드정보가 일치하지 않습니다
		cout << endl;
		cout << "\t※코드정보가 일치하지 않습니다!";
		cout << endl;
		CLEAR_STD_BUFFER();
		return true;
	}


	// 탈퇴할 지 한번 더 물어 본다. 
	cout << endl;
	cout << "\t☞ 예매 취소 하시겠습니까? (Y/N) : ";
	string yn;
	cin >> yn;

	// 대문자로 모두 바꾼다. 
	transform(yn.begin(), yn.end(), yn.begin(), toupper);

	

	if (!strcmp(yn.c_str(), "Y")) {

		// 예매취소 처리 
		app->RemoveReserveMyinfo(code); 

		// 자리데이터도 해제 시킨다. 
		app->ReserveCancelSeat(r->movieIndex, r->reserveTime.get_all().c_str(), r->rowindex, r->colindex);
		
		cout << "\t※예매취소되었습니다" << endl;
		CLEAR_STD_BUFFER();

	}
	else {
		cout << "\t※예매취소되지 않았습니다" << endl;
		CLEAR_STD_BUFFER();
	}


	return true; 
}