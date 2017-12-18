#include "stdafx.h"
#include "ManagerProcess.h"
#include "App.h"

void ManagerProcess::doRun(App* app) {
	if (NULL == app) return;

	system("cls"); // 화면을 깨끗히 지운다. 
	cout << endl;
	cout << "〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓" << endl;
	cout << "▶▶ 관리자모드" << endl;
	cout << "〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓" << endl;
	cout << endl;
	cout << "\t1)영화정보입력" << endl;
	cout << "\t2)날짜별 상영정보입력" << endl;
	cout << "\t3)로그아웃" << endl;



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
		if (1 == logic) { // 영화정보입력 
			if (logic_AddMovieInfo(app)) break;
		}
		else if (2 == logic) { // 날짜별 상영정보입력  
			if (logic_AddMovieInfoByDateTime(app)) break;
		}
		else if (3 == logic) { // 로그아웃 
			app->changeMode(TYPE_MODE::MODE_NONE);

			cout << endl;
			cout << "\t로그아웃 되었습니다!" << endl;
			break;
		}

	}
}

// 영화 정보 입력 
bool ManagerProcess::logic_AddMovieInfo(App* app) {
	if (NULL == app) return false;
	system("cls"); // 화면을 깨끗히 지운다. 

	MovieInfo movie;

	cout << endl;
	cout << "〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓" << endl;
	cout << "▶▶ 관리자모드 >> 영화정보입력" << endl;
	cout << "〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓" << endl;

	cout << endl;
	cout << "\t1. 영화정보입력하기" << endl;
	cout << "\t2. 영화정보수정/삭제" << endl;
	cout << "\t3. 되돌아가기" << endl;

	int menu = -1;
	while (true) {
		cout << "\t☞ 메뉴를 선택하세요(1~3):";
		cin >> menu;

		if (1 != menu && 2 != menu && 3 != menu ) {
			cout << endl;
			cout << "\t※잘못 입력하셨습니다!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}
		break;
	}



	if (3 == menu) { // 되돌아가기 
		cout << "\t상위메뉴로 되돌아 갑니다!" << endl;
		Sleep(1000);
		return true;
	}

	if (1 == menu) { // 영화정보 입력 
		movie.index = -1;
		while (true) {

			cout << endl;
			cout << "\t☞ 영화번호입력:";

			cin >> movie.index;

			if (0 == movie.index) {
				cout << endl;
				cout << "\t※영화번호를 입력하세요!";
				cout << endl;
				CLEAR_STD_BUFFER();
				continue;
			}
			else if (0 > movie.index) {
				cout << endl;
				cout << "\t※잘못 입력하셨습니다!";
				cout << endl;
				CLEAR_STD_BUFFER();
				continue;
			}

			// 이미존재하는 영화번호인지 체크 
			if (true == app->checkExistMovie(movie.index)) {
				cout << endl;
				cout << "\t※이미 존재하는 영화번호입니다!";
				cout << endl;
				CLEAR_STD_BUFFER();
				continue;
			}

			break;
		}


		while (true) {
			cout << endl;
			cout << "\t☞ 영화명 입력:";
			cin >> movie.name;

			if (0 == strlen(movie.name.c_str())) {
				cout << endl;
				cout << "\t※영화명을 입력하세요!";
				cout << endl;
				CLEAR_STD_BUFFER();
				continue;
			}

			// 존재하는 ID인지 체크 
			if (true == app->checkExistMovie(movie.name.c_str())) {
				cout << endl;
				cout << "\t※이미 등록된 영화이름입니다!";
				cout << endl;
				CLEAR_STD_BUFFER();
				continue;
			}
			break;
		}


		while (true) {
			cout << endl;
			cout << "\t☞ 개봉일 입력(년/월/일) ex)1980/09/28 : ";
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

			movie.openDate.year = tokenList[0];
			movie.openDate.month = tokenList[1];
			movie.openDate.day = tokenList[2];

			break;
		}
		while (true) {
			cout << endl;
			cout << "\t☞ 폐관일 입력(년/월/일) ex)1980/09/28 : ";
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

			movie.endtime.year = tokenList[0];
			movie.endtime.month = tokenList[1];
			movie.endtime.day = tokenList[2];

			break;
		}

		while (true) {
			cout << endl;
			cout << "\t☞ 상영총시간입력(분단위) :";
			cin >> movie.playAllTime;

			if (0 >= movie.playAllTime) {
				cout << endl;
				cout << "\t※잘못입력하셨습니다!";
				cout << endl;
				CLEAR_STD_BUFFER();
				continue;
			}
			break;
		}

		while (true) {
			cout << endl;
			cout << "\t☞ 장르 입력:";
			cin >> movie.category;

			if (0 == strlen(movie.category.c_str())) {
				cout << endl;
				cout << "\t※장르를 입력하세요!";
				cout << endl;
				CLEAR_STD_BUFFER();
				continue;
			}
			break;
		}

		while (true) {
			cout << endl;
			fflush(stdin);
			cout << "\t☞ 줄거리를 입력:";
			string s;
			getline(cin, s);
			getline(cin, s);
			//cin >> movie.category;

			movie.story = s;
			if (0 == strlen(movie.story.c_str())) {
				cout << endl;
				cout << "\t※줄거리를 입력하세요!";
				cout << endl;
				CLEAR_STD_BUFFER();
				continue;
			}
			break;
		}


		app->addMovie(movie);

		cout << "\t등록하였습니다!" << endl;
		Sleep(1000);
	}
	else if (2 == menu) { // 영화정보수정 / 삭제
		
		system("cls"); // 화면을 깨끗히 지운다. 

		cout << endl;
		cout << "〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓" << endl;
		cout << "▶▶ 관리자모드 >> 영화정보입력 >> 영화정보수정/ 삭제" << endl;
		cout << "〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓" << endl;

		cout << endl;
		cout << "\t1. 수정하기" << endl;
		cout << "\t2. 삭제하기" << endl;
		cout << "\t3. 되돌아가기" << endl;

		int menu = -1;
		while (true) {
			cout << "\t☞ 메뉴를 선택하세요(1~3):";
			cin >> menu;

			if (1 != menu && 2 != menu && 3 != menu) {
				cout << endl;
				cout << "\t※잘못 입력하셨습니다!";
				cout << endl;
				CLEAR_STD_BUFFER();
				continue;
			}
			break;
		}



		if (3 == menu) { // 되돌아가기 
			cout << "\t상위메뉴로 되돌아 갑니다!" << endl;
			Sleep(1000);
			return false;
		}
		else if (1 == menu) { // 수정하기 

			string removeName;
			cout << endl; 
			cout << "\t☞ 수정할 영화명을 입력하세요:";
			cin >> removeName;

			// 실제 영화가 존재하는지 체크 한다. 
			MovieInfo * movie = app->GetMovie(removeName.c_str());
			if (NULL == movie) {
				cout << endl;
				cout << "\t※존재하지 않는 영화입니다!";
				cout << endl;
				CLEAR_STD_BUFFER();
				return false;
			}


			int sel = -1;
			while (1) {
				
				cout << endl;
				cout << "\t1. 영화이름" << endl;
				cout << "\t2. 개봉일자" << endl;
				cout << "\t3. 폐관일자" << endl;
				cout << "\t4. 상영시간" << endl;
				cout << "\t5. 장르" << endl;
				cout << "\t6. 줄거리" << endl;
				cout << "\t7. 되돌아가기" << endl;
				cout << "\t☞ 수정할 메뉴를 선택하세요(1~6):";
				cin >> sel;

				if (sel < 1 || sel > 7) {
					cout << endl;
					cout << "\t※잘못 입력하셨습니다!";
					cout << endl;
					CLEAR_STD_BUFFER();
					continue;
				}
				break; 
			}
			
			if (1 == sel) { // 영화이름
				string movieName; 
				while (true) {
					cout << endl;
					cout << "\t☞ 영화명 입력:";
					cin >> movieName;

					if (0 == strlen(movieName.c_str())) {
						cout << endl;
						cout << "\t※영화명을 입력하세요!";
						cout << endl;
						CLEAR_STD_BUFFER();
						continue;
					}

					// 존재하는 ID인지 체크 
					if (true == app->checkExistMovie(movieName.c_str())) {
						cout << endl;
						cout << "\t※이미 등록된 영화이름입니다!";
						cout << endl;
						CLEAR_STD_BUFFER();
						continue;
					}
					break;
				}

				// 수정 
				movie->name = movieName.c_str(); 
			} 
			else if (2 == sel) { // 개봉일자 
				while (true) {
					cout << endl;
					cout << "\t☞ 개봉일 입력(년/월/일) ex)1980/09/28 : ";
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

					movie->openDate.year = tokenList[0];
					movie->openDate.month = tokenList[1];
					movie->openDate.day = tokenList[2];

					break;
				}
			}
			else if (3 == sel) { // 폐관일자 
				while (true) {
					cout << endl;
					cout << "\t☞ 폐관일 입력(년/월/일) ex)1980/09/28 : ";
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

					movie->endtime.year = tokenList[0];
					movie->endtime.month = tokenList[1];
					movie->endtime.day = tokenList[2];

					break;
				}
			}
			else if (4 == sel) { // 상영시간 
				while (true) {
					cout << endl;
					cout << "\t☞ 상영총시간입력(분단위) :";
					cin >> movie->playAllTime;

					if (0 >= movie->playAllTime) {
						cout << endl;
						cout << "\t※잘못입력하셨습니다!";
						cout << endl;
						CLEAR_STD_BUFFER();
						continue;
					}
					break;
				}
			}
			else if (5 == sel) { // 장르 
				string cat;
				while (true) {
					cout << endl;
					cout << "\t☞ 장르 입력:";
					cin >> cat;

					if (0 == strlen(cat.c_str())) {
						cout << endl;
						cout << "\t※장르를 입력하세요!";
						cout << endl;
						CLEAR_STD_BUFFER();
						continue;
					}
					break;
				}

				movie->category = cat.c_str();
			}
			else if (6 == sel) { // 줄거리
				string story;

				while (true) {
					cout << endl;
					fflush(stdin);
					cout << "\t☞ 줄거리를 입력:";
					string s;
					getline(cin, s);
					getline(cin, s);
					//cin >> movie.category;

					story = s;
					if (0 == strlen(story.c_str())) {
						cout << endl;
						cout << "\t※줄거리를 입력하세요!";
						cout << endl;
						CLEAR_STD_BUFFER();
						continue;
					}
					break;
				}
				movie->story = story; 
			}
			else if (7 == sel) { // 되돌아가기 
				cout << "\t상위메뉴로 되돌아 갑니다!" << endl;
				Sleep(1000);
				return false;
			}

			cout << "\t수정되었습니다!" << endl;
			Sleep(1000);
			return false;

		}
		else if (2 == menu) { // 삭제하기 
			string removeName; 
			cout << "\t☞ 삭제할 영화명을 입력하세요:";
			cin >> removeName; 

			// 실제 영화가 존재하는지 체크 한다. 
			MovieInfo * movie = app->GetMovie(removeName.c_str());
			if (NULL == movie) {
				cout << endl;
				cout << "\t※존재하지 않는 영화입니다!";
				cout << endl;
				CLEAR_STD_BUFFER();
				return false; 
			}

			cout << endl;
			cout << "\t☞ 정말 삭제하시겠습니까? (Y/N) : ";
			string yn;
			cin >> yn;

			// 대문자로 모두 바꾼다. 
			transform(yn.begin(), yn.end(), yn.begin(), toupper);

			if (!strcmp(yn.c_str(), "Y")) {
				// 삭제 처리 
				app->RemoveMovieAll(movie->name.c_str());
				
				cout << "\t※삭제되었습니다" << endl;
				CLEAR_STD_BUFFER();

			}
			else {
				cout << "\t※취소되었습니다" << endl;
				CLEAR_STD_BUFFER();

			}
		}
	}

	

	return true;
}

// 날짜별 상영정보 입력 
bool ManagerProcess::logic_AddMovieInfoByDateTime(App* app) {
	if (NULL == app) return false;
	system("cls"); // 화면을 깨끗히 지운다. 

	cout << endl;
	cout << "〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓" << endl;
	cout << "▶▶ 관리자모드 >> 날짜별상영정보입력" << endl;
	cout << "〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓" << endl;

	// 등록된 영화목록을 우선 보여주자 날짜별 상영정보를 입력할 관리자가 선택할 수 있도록 ..
	vector<MovieInfo> outMovieList;
	app->GetMovieList(outMovieList);

	if (0 == outMovieList.size()) {
		cout << "\t※등록된 영화가 없습니다!" << endl;
		return true; // true를 반환해서 메인 메뉴로 이동 하도록 한다. 
	}

	for (auto m : outMovieList) {
		cout << "\t" << m.index << "." << m.name << endl;
	}
	cout << "\t" << outMovieList.size() + 1 << ".되돌아가기" << endl;

	int movieIndex = -1;

	while (true) {
		cout << endl;
		cout << "\t☞ 영화번호입력: ";
		cin >> movieIndex;

		if (0 == movieIndex) {
			cout << endl;
			cout << "\t※영화번호를 입력하세요!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}
		else if (0 > movieIndex) {
			cout << endl;
			cout << "\t※잘못 입력하셨습니다!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}

		if ((outMovieList.size() + 1) == movieIndex) {
			cout << endl;
			cout << "\t※상위메뉴로 되돌아갑니다!";
			cout << endl;
			Sleep(1000); 
			return true; 
		}

		// 이미존재하는 영화번호인지 체크 
		if (false == app->checkExistMovie(movieIndex)) {
			cout << endl;
			cout << "\t※존재하지않는 영화번호입니다!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}

		break;
	}

	

	MovieInfo* movie;
	movie = app->GetMovie(movieIndex);
	if (NULL == movie) return false;


	

	cout << endl;

	int gateNo = -1;
	while (true) {
		cout << endl;
		cout << "\t☞ 영화 (" << movie->name << ")를 상영할 상영관을 선택하세요:" << endl;


		for (int i = 0; i < TYPE_GATE::GATE_MAX; ++i) {
			cout << "\t" << i + 1 << "." <<i + 1 << "관" << endl;
		}


		cin >> gateNo;

		if (0 > gateNo-1 || TYPE_GATE::GATE_MAX <= gateNo-1) {

			cout << endl;
			cout << "\t※잘못입력하셨습니다!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}

		break;
	}

	// 상영하려는 영화가 해당 상영관에 이미 등록된 것이 아닌지 확인 
	if (app->checkExistMovieFromGate(gateNo - 1, movie->index)) {

		// 상영 정보를 먼저 출력 하자 
		cout << endl;
		cout << "\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓" << endl;
		cout << gateNo << "\t▶▶ 상영관 상영시간 목록" << endl;
		cout << "\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓" << endl;


		app->displayMovieGateInfo(gateNo - 1);
		cout << "\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓" << endl;

		// 이미 있다면 상영시간을 추가/ 삭제 할 수 있어야 함. 
		int n = -1;
		while (true) {

			cout << endl;
			cout << "\t1. 추가" << endl;
			cout << "\t2. 삭제" << endl;
			cout << "\t3. 되돌아가기" << endl; 
			cout << "\t☞ 선택하세요 (1~3) :" << endl;

			// 상영시간 목록을 먼저 보여주고 추가및 삭제 할 수 있도록 한다. 
			cin >> n;
			if (n != 1 && n != 2 && n != 3) {
				cout << endl;
				cout << "\t※잘못입력하셨습니다!";
				cout << endl;
				CLEAR_STD_BUFFER();
				continue;
			}

			break;
		}
		if (1 == n) { // 추가 
			cout << endl;
			AddPlayMovieTimeInfo(app, gateNo - 1, movie);
			cout << "\t등록되었습니다!" << endl;
			Sleep(1000);
		}
		else if (2 == n) { // 삭제 

			while (true) {
				cout << endl;
				cout << "\t☞ 삭제할 번호를 입력:";
				int delNo = -1;
				cin >> delNo;

				if (app->RemoveMovieGateInfo(gateNo - 1, delNo)) {
					cout << "\t삭제되었습니다!" << endl;
					cout << endl;
					CLEAR_STD_BUFFER();
					cout << endl;
				}
				else {
					cout << endl;
					cout << "\t※잘못입력하셨습니다!";
					cout << endl;
					CLEAR_STD_BUFFER();
					continue;
				}

				break;
			}



		}
		else if (3 == n) {

			return true; 
		}



	}
	else {
		cout << endl;
		// 신규 임으로 등록만 지원 
		AddPlayMovieTimeInfo(app, gateNo - 1, movie);
		cout << "\t등록되었습니다!" << endl;
		Sleep(1000);
	}


	return true;
}

void ManagerProcess::AddPlayMovieTimeInfo(App* app, int gateNo, MovieInfo *movie) {

	// 회차별 상영날짜 입력 
	{
		while (true) {
			cout << endl;
			cout << "\t☞ 상영시작날짜 입력(년/월/일) ex)1980/09/28 : ";
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

			movie->playtime.year = tokenList[0];
			movie->playtime.month = tokenList[1];
			movie->playtime.day = tokenList[2];

			break;
		}

	}
	


	cout << endl;
	cout << "\t☞ 등록 횟수 입력: (1~5)";
	int playCnt = -1;

	while (true) {
		cin >> playCnt;
		if (0 > playCnt || 5 < playCnt) {
			cout << endl;
			cout << "\t※1~5회 까지 입력 가능합니다!" << endl;
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}
		break;
	}

	for (int i = 0; i < playCnt; ++i) {

		
		// 회차별 상영시간 입력 
		{
			while (true) {
				cout << endl;
				cout << "\t☞ " << i + 1 << "번째 등록할 상영 시간을 입력하세요! ex)10시30분상영 ==> 10:30  : ";

				string timeStr;
				cin >> timeStr;

				vector<int> tokenList;
				int tokenCnt = 0;
				char *ptr = strtok(const_cast<char*>(timeStr.c_str()), ":");
				while (ptr != NULL) {
					tokenCnt++;
					tokenList.push_back(atoi(ptr));
					ptr = strtok(NULL, ":");
				}

				if (2 != tokenCnt) {
					cout << endl;
					cout << "\t※잘못입력하셨습니다!";
					cout << endl;
					CLEAR_STD_BUFFER();
					continue;
				}

				Time playTime;
				playTime.year = movie->playtime.year;
				playTime.month = movie->playtime.month;
				playTime.day = movie->playtime.day;

				playTime.hour = tokenList[0];
				playTime.minute = tokenList[1];
				playTime.second = 0;

				// 같은 상영시간이 존재하는지 체크 
				bool isExist = false;
				{
					vector<MovieInfo> outList;
					app->GetMovieTimeByGateNo(gateNo, movie->index, outList);
					
					for (auto out : outList) {
						// 영화 상영날짜 관람 날짜가 맞지 않으면 오류 출력 
						time_t displayTime = app->getTimeInt(out.playtime.year, out.playtime.month, out.playtime.day, out.playtime.hour, out.playtime.minute, out.playtime.second);
						time_t displayEndTime = displayTime + (movie->playAllTime * 60);
						time_t viewTime = app->getTimeInt(movie->playtime.year, movie->playtime.month, movie->playtime.day, playTime.hour, playTime.minute, playTime.second);
						time_t viewTimeEndTime = viewTime + (movie->playAllTime * 60);

						if (displayTime < viewTime && displayEndTime > viewTime) {
							isExist = true;
							break;
						}

						if (viewTime < displayTime && viewTimeEndTime > displayTime) {
							isExist = true;
							break;
						}
					}
				}

				if (true == isExist) {
					cout << endl;
					cout << "\t※입력한 시간에 이미 다른 영화가 예약되어 있습니다!";
					cout << endl;
					CLEAR_STD_BUFFER();
					continue;
				}

				

				auto it = app->gate[gateNo].playMovieMap.find(playTime.get_all());
				if (it == app->gate[gateNo].playMovieMap.end()) {
					// 중복되는 시간이 없다면 등록 

					// 상영시간 
					movie->playtime.hour = playTime.hour;
					movie->playtime.minute = playTime.minute;
					movie->playtime.second = playTime.second;

					// 상영영화정보 등록 
					app->gate[gateNo].playMovieMap.insert(pair<string, MovieInfo>(playTime.get_all(), *movie));

					// 좌석정보 등록 
					app->gate[gateNo].seatMap.insert(pair<string, SeatInfo>(playTime.get_all(), SeatInfo()));
				}
				else {
					cout << endl;
					cout << "\t※입력한 시간에 이미 다른 영화가 예약되어 있습니다!";
					cout << endl;
					CLEAR_STD_BUFFER();
					continue;
				}

				break;
			}
		}
		

	}
}