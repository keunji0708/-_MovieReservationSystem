#include "stdafx.h"
#include "ManagerProcess.h"
#include "App.h"

void ManagerProcess::doRun(App* app) {
	if (NULL == app) return;

	system("cls"); // ȭ���� ������ �����. 
	cout << endl;
	cout << "�����������������������" << endl;
	cout << "���� �����ڸ��" << endl;
	cout << "�����������������������" << endl;
	cout << endl;
	cout << "\t1)��ȭ�����Է�" << endl;
	cout << "\t2)��¥�� �������Է�" << endl;
	cout << "\t3)�α׾ƿ�" << endl;



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
		if (1 == logic) { // ��ȭ�����Է� 
			if (logic_AddMovieInfo(app)) break;
		}
		else if (2 == logic) { // ��¥�� �������Է�  
			if (logic_AddMovieInfoByDateTime(app)) break;
		}
		else if (3 == logic) { // �α׾ƿ� 
			app->changeMode(TYPE_MODE::MODE_NONE);

			cout << endl;
			cout << "\t�α׾ƿ� �Ǿ����ϴ�!" << endl;
			break;
		}

	}
}

// ��ȭ ���� �Է� 
bool ManagerProcess::logic_AddMovieInfo(App* app) {
	if (NULL == app) return false;
	system("cls"); // ȭ���� ������ �����. 

	MovieInfo movie;

	cout << endl;
	cout << "�����������������������" << endl;
	cout << "���� �����ڸ�� >> ��ȭ�����Է�" << endl;
	cout << "�����������������������" << endl;

	cout << endl;
	cout << "\t1. ��ȭ�����Է��ϱ�" << endl;
	cout << "\t2. ��ȭ��������/����" << endl;
	cout << "\t3. �ǵ��ư���" << endl;

	int menu = -1;
	while (true) {
		cout << "\t�� �޴��� �����ϼ���(1~3):";
		cin >> menu;

		if (1 != menu && 2 != menu && 3 != menu ) {
			cout << endl;
			cout << "\t���߸� �Է��ϼ̽��ϴ�!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}
		break;
	}



	if (3 == menu) { // �ǵ��ư��� 
		cout << "\t�����޴��� �ǵ��� ���ϴ�!" << endl;
		Sleep(1000);
		return true;
	}

	if (1 == menu) { // ��ȭ���� �Է� 
		movie.index = -1;
		while (true) {

			cout << endl;
			cout << "\t�� ��ȭ��ȣ�Է�:";

			cin >> movie.index;

			if (0 == movie.index) {
				cout << endl;
				cout << "\t�ؿ�ȭ��ȣ�� �Է��ϼ���!";
				cout << endl;
				CLEAR_STD_BUFFER();
				continue;
			}
			else if (0 > movie.index) {
				cout << endl;
				cout << "\t���߸� �Է��ϼ̽��ϴ�!";
				cout << endl;
				CLEAR_STD_BUFFER();
				continue;
			}

			// �̹������ϴ� ��ȭ��ȣ���� üũ 
			if (true == app->checkExistMovie(movie.index)) {
				cout << endl;
				cout << "\t���̹� �����ϴ� ��ȭ��ȣ�Դϴ�!";
				cout << endl;
				CLEAR_STD_BUFFER();
				continue;
			}

			break;
		}


		while (true) {
			cout << endl;
			cout << "\t�� ��ȭ�� �Է�:";
			cin >> movie.name;

			if (0 == strlen(movie.name.c_str())) {
				cout << endl;
				cout << "\t�ؿ�ȭ���� �Է��ϼ���!";
				cout << endl;
				CLEAR_STD_BUFFER();
				continue;
			}

			// �����ϴ� ID���� üũ 
			if (true == app->checkExistMovie(movie.name.c_str())) {
				cout << endl;
				cout << "\t���̹� ��ϵ� ��ȭ�̸��Դϴ�!";
				cout << endl;
				CLEAR_STD_BUFFER();
				continue;
			}
			break;
		}


		while (true) {
			cout << endl;
			cout << "\t�� ������ �Է�(��/��/��) ex)1980/09/28 : ";
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

			movie.openDate.year = tokenList[0];
			movie.openDate.month = tokenList[1];
			movie.openDate.day = tokenList[2];

			break;
		}
		while (true) {
			cout << endl;
			cout << "\t�� ����� �Է�(��/��/��) ex)1980/09/28 : ";
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

			movie.endtime.year = tokenList[0];
			movie.endtime.month = tokenList[1];
			movie.endtime.day = tokenList[2];

			break;
		}

		while (true) {
			cout << endl;
			cout << "\t�� ���ѽð��Է�(�д���) :";
			cin >> movie.playAllTime;

			if (0 >= movie.playAllTime) {
				cout << endl;
				cout << "\t���߸��Է��ϼ̽��ϴ�!";
				cout << endl;
				CLEAR_STD_BUFFER();
				continue;
			}
			break;
		}

		while (true) {
			cout << endl;
			cout << "\t�� �帣 �Է�:";
			cin >> movie.category;

			if (0 == strlen(movie.category.c_str())) {
				cout << endl;
				cout << "\t���帣�� �Է��ϼ���!";
				cout << endl;
				CLEAR_STD_BUFFER();
				continue;
			}
			break;
		}

		while (true) {
			cout << endl;
			fflush(stdin);
			cout << "\t�� �ٰŸ��� �Է�:";
			string s;
			getline(cin, s);
			getline(cin, s);
			//cin >> movie.category;

			movie.story = s;
			if (0 == strlen(movie.story.c_str())) {
				cout << endl;
				cout << "\t���ٰŸ��� �Է��ϼ���!";
				cout << endl;
				CLEAR_STD_BUFFER();
				continue;
			}
			break;
		}


		app->addMovie(movie);

		cout << "\t����Ͽ����ϴ�!" << endl;
		Sleep(1000);
	}
	else if (2 == menu) { // ��ȭ�������� / ����
		
		system("cls"); // ȭ���� ������ �����. 

		cout << endl;
		cout << "�����������������������" << endl;
		cout << "���� �����ڸ�� >> ��ȭ�����Է� >> ��ȭ��������/ ����" << endl;
		cout << "�����������������������" << endl;

		cout << endl;
		cout << "\t1. �����ϱ�" << endl;
		cout << "\t2. �����ϱ�" << endl;
		cout << "\t3. �ǵ��ư���" << endl;

		int menu = -1;
		while (true) {
			cout << "\t�� �޴��� �����ϼ���(1~3):";
			cin >> menu;

			if (1 != menu && 2 != menu && 3 != menu) {
				cout << endl;
				cout << "\t���߸� �Է��ϼ̽��ϴ�!";
				cout << endl;
				CLEAR_STD_BUFFER();
				continue;
			}
			break;
		}



		if (3 == menu) { // �ǵ��ư��� 
			cout << "\t�����޴��� �ǵ��� ���ϴ�!" << endl;
			Sleep(1000);
			return false;
		}
		else if (1 == menu) { // �����ϱ� 

			string removeName;
			cout << endl; 
			cout << "\t�� ������ ��ȭ���� �Է��ϼ���:";
			cin >> removeName;

			// ���� ��ȭ�� �����ϴ��� üũ �Ѵ�. 
			MovieInfo * movie = app->GetMovie(removeName.c_str());
			if (NULL == movie) {
				cout << endl;
				cout << "\t���������� �ʴ� ��ȭ�Դϴ�!";
				cout << endl;
				CLEAR_STD_BUFFER();
				return false;
			}


			int sel = -1;
			while (1) {
				
				cout << endl;
				cout << "\t1. ��ȭ�̸�" << endl;
				cout << "\t2. ��������" << endl;
				cout << "\t3. �������" << endl;
				cout << "\t4. �󿵽ð�" << endl;
				cout << "\t5. �帣" << endl;
				cout << "\t6. �ٰŸ�" << endl;
				cout << "\t7. �ǵ��ư���" << endl;
				cout << "\t�� ������ �޴��� �����ϼ���(1~6):";
				cin >> sel;

				if (sel < 1 || sel > 7) {
					cout << endl;
					cout << "\t���߸� �Է��ϼ̽��ϴ�!";
					cout << endl;
					CLEAR_STD_BUFFER();
					continue;
				}
				break; 
			}
			
			if (1 == sel) { // ��ȭ�̸�
				string movieName; 
				while (true) {
					cout << endl;
					cout << "\t�� ��ȭ�� �Է�:";
					cin >> movieName;

					if (0 == strlen(movieName.c_str())) {
						cout << endl;
						cout << "\t�ؿ�ȭ���� �Է��ϼ���!";
						cout << endl;
						CLEAR_STD_BUFFER();
						continue;
					}

					// �����ϴ� ID���� üũ 
					if (true == app->checkExistMovie(movieName.c_str())) {
						cout << endl;
						cout << "\t���̹� ��ϵ� ��ȭ�̸��Դϴ�!";
						cout << endl;
						CLEAR_STD_BUFFER();
						continue;
					}
					break;
				}

				// ���� 
				movie->name = movieName.c_str(); 
			} 
			else if (2 == sel) { // �������� 
				while (true) {
					cout << endl;
					cout << "\t�� ������ �Է�(��/��/��) ex)1980/09/28 : ";
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

					movie->openDate.year = tokenList[0];
					movie->openDate.month = tokenList[1];
					movie->openDate.day = tokenList[2];

					break;
				}
			}
			else if (3 == sel) { // ������� 
				while (true) {
					cout << endl;
					cout << "\t�� ����� �Է�(��/��/��) ex)1980/09/28 : ";
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

					movie->endtime.year = tokenList[0];
					movie->endtime.month = tokenList[1];
					movie->endtime.day = tokenList[2];

					break;
				}
			}
			else if (4 == sel) { // �󿵽ð� 
				while (true) {
					cout << endl;
					cout << "\t�� ���ѽð��Է�(�д���) :";
					cin >> movie->playAllTime;

					if (0 >= movie->playAllTime) {
						cout << endl;
						cout << "\t���߸��Է��ϼ̽��ϴ�!";
						cout << endl;
						CLEAR_STD_BUFFER();
						continue;
					}
					break;
				}
			}
			else if (5 == sel) { // �帣 
				string cat;
				while (true) {
					cout << endl;
					cout << "\t�� �帣 �Է�:";
					cin >> cat;

					if (0 == strlen(cat.c_str())) {
						cout << endl;
						cout << "\t���帣�� �Է��ϼ���!";
						cout << endl;
						CLEAR_STD_BUFFER();
						continue;
					}
					break;
				}

				movie->category = cat.c_str();
			}
			else if (6 == sel) { // �ٰŸ�
				string story;

				while (true) {
					cout << endl;
					fflush(stdin);
					cout << "\t�� �ٰŸ��� �Է�:";
					string s;
					getline(cin, s);
					getline(cin, s);
					//cin >> movie.category;

					story = s;
					if (0 == strlen(story.c_str())) {
						cout << endl;
						cout << "\t���ٰŸ��� �Է��ϼ���!";
						cout << endl;
						CLEAR_STD_BUFFER();
						continue;
					}
					break;
				}
				movie->story = story; 
			}
			else if (7 == sel) { // �ǵ��ư��� 
				cout << "\t�����޴��� �ǵ��� ���ϴ�!" << endl;
				Sleep(1000);
				return false;
			}

			cout << "\t�����Ǿ����ϴ�!" << endl;
			Sleep(1000);
			return false;

		}
		else if (2 == menu) { // �����ϱ� 
			string removeName; 
			cout << "\t�� ������ ��ȭ���� �Է��ϼ���:";
			cin >> removeName; 

			// ���� ��ȭ�� �����ϴ��� üũ �Ѵ�. 
			MovieInfo * movie = app->GetMovie(removeName.c_str());
			if (NULL == movie) {
				cout << endl;
				cout << "\t���������� �ʴ� ��ȭ�Դϴ�!";
				cout << endl;
				CLEAR_STD_BUFFER();
				return false; 
			}

			cout << endl;
			cout << "\t�� ���� �����Ͻðڽ��ϱ�? (Y/N) : ";
			string yn;
			cin >> yn;

			// �빮�ڷ� ��� �ٲ۴�. 
			transform(yn.begin(), yn.end(), yn.begin(), toupper);

			if (!strcmp(yn.c_str(), "Y")) {
				// ���� ó�� 
				app->RemoveMovieAll(movie->name.c_str());
				
				cout << "\t�ػ����Ǿ����ϴ�" << endl;
				CLEAR_STD_BUFFER();

			}
			else {
				cout << "\t����ҵǾ����ϴ�" << endl;
				CLEAR_STD_BUFFER();

			}
		}
	}

	

	return true;
}

// ��¥�� ������ �Է� 
bool ManagerProcess::logic_AddMovieInfoByDateTime(App* app) {
	if (NULL == app) return false;
	system("cls"); // ȭ���� ������ �����. 

	cout << endl;
	cout << "�����������������������" << endl;
	cout << "���� �����ڸ�� >> ��¥���������Է�" << endl;
	cout << "�����������������������" << endl;

	// ��ϵ� ��ȭ����� �켱 �������� ��¥�� �������� �Է��� �����ڰ� ������ �� �ֵ��� ..
	vector<MovieInfo> outMovieList;
	app->GetMovieList(outMovieList);

	if (0 == outMovieList.size()) {
		cout << "\t�ص�ϵ� ��ȭ�� �����ϴ�!" << endl;
		return true; // true�� ��ȯ�ؼ� ���� �޴��� �̵� �ϵ��� �Ѵ�. 
	}

	for (auto m : outMovieList) {
		cout << "\t" << m.index << "." << m.name << endl;
	}
	cout << "\t" << outMovieList.size() + 1 << ".�ǵ��ư���" << endl;

	int movieIndex = -1;

	while (true) {
		cout << endl;
		cout << "\t�� ��ȭ��ȣ�Է�: ";
		cin >> movieIndex;

		if (0 == movieIndex) {
			cout << endl;
			cout << "\t�ؿ�ȭ��ȣ�� �Է��ϼ���!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}
		else if (0 > movieIndex) {
			cout << endl;
			cout << "\t���߸� �Է��ϼ̽��ϴ�!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}

		if ((outMovieList.size() + 1) == movieIndex) {
			cout << endl;
			cout << "\t�ػ����޴��� �ǵ��ư��ϴ�!";
			cout << endl;
			Sleep(1000); 
			return true; 
		}

		// �̹������ϴ� ��ȭ��ȣ���� üũ 
		if (false == app->checkExistMovie(movieIndex)) {
			cout << endl;
			cout << "\t�����������ʴ� ��ȭ��ȣ�Դϴ�!";
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
		cout << "\t�� ��ȭ (" << movie->name << ")�� ���� �󿵰��� �����ϼ���:" << endl;


		for (int i = 0; i < TYPE_GATE::GATE_MAX; ++i) {
			cout << "\t" << i + 1 << "." <<i + 1 << "��" << endl;
		}


		cin >> gateNo;

		if (0 > gateNo-1 || TYPE_GATE::GATE_MAX <= gateNo-1) {

			cout << endl;
			cout << "\t���߸��Է��ϼ̽��ϴ�!";
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}

		break;
	}

	// ���Ϸ��� ��ȭ�� �ش� �󿵰��� �̹� ��ϵ� ���� �ƴ��� Ȯ�� 
	if (app->checkExistMovieFromGate(gateNo - 1, movie->index)) {

		// �� ������ ���� ��� ���� 
		cout << endl;
		cout << "\t����������������������" << endl;
		cout << gateNo << "\t���� �󿵰� �󿵽ð� ���" << endl;
		cout << "\t����������������������" << endl;


		app->displayMovieGateInfo(gateNo - 1);
		cout << "\t����������������������" << endl;

		// �̹� �ִٸ� �󿵽ð��� �߰�/ ���� �� �� �־�� ��. 
		int n = -1;
		while (true) {

			cout << endl;
			cout << "\t1. �߰�" << endl;
			cout << "\t2. ����" << endl;
			cout << "\t3. �ǵ��ư���" << endl; 
			cout << "\t�� �����ϼ��� (1~3) :" << endl;

			// �󿵽ð� ����� ���� �����ְ� �߰��� ���� �� �� �ֵ��� �Ѵ�. 
			cin >> n;
			if (n != 1 && n != 2 && n != 3) {
				cout << endl;
				cout << "\t���߸��Է��ϼ̽��ϴ�!";
				cout << endl;
				CLEAR_STD_BUFFER();
				continue;
			}

			break;
		}
		if (1 == n) { // �߰� 
			cout << endl;
			AddPlayMovieTimeInfo(app, gateNo - 1, movie);
			cout << "\t��ϵǾ����ϴ�!" << endl;
			Sleep(1000);
		}
		else if (2 == n) { // ���� 

			while (true) {
				cout << endl;
				cout << "\t�� ������ ��ȣ�� �Է�:";
				int delNo = -1;
				cin >> delNo;

				if (app->RemoveMovieGateInfo(gateNo - 1, delNo)) {
					cout << "\t�����Ǿ����ϴ�!" << endl;
					cout << endl;
					CLEAR_STD_BUFFER();
					cout << endl;
				}
				else {
					cout << endl;
					cout << "\t���߸��Է��ϼ̽��ϴ�!";
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
		// �ű� ������ ��ϸ� ���� 
		AddPlayMovieTimeInfo(app, gateNo - 1, movie);
		cout << "\t��ϵǾ����ϴ�!" << endl;
		Sleep(1000);
	}


	return true;
}

void ManagerProcess::AddPlayMovieTimeInfo(App* app, int gateNo, MovieInfo *movie) {

	// ȸ���� �󿵳�¥ �Է� 
	{
		while (true) {
			cout << endl;
			cout << "\t�� �󿵽��۳�¥ �Է�(��/��/��) ex)1980/09/28 : ";
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

			movie->playtime.year = tokenList[0];
			movie->playtime.month = tokenList[1];
			movie->playtime.day = tokenList[2];

			break;
		}

	}
	


	cout << endl;
	cout << "\t�� ��� Ƚ�� �Է�: (1~5)";
	int playCnt = -1;

	while (true) {
		cin >> playCnt;
		if (0 > playCnt || 5 < playCnt) {
			cout << endl;
			cout << "\t��1~5ȸ ���� �Է� �����մϴ�!" << endl;
			cout << endl;
			CLEAR_STD_BUFFER();
			continue;
		}
		break;
	}

	for (int i = 0; i < playCnt; ++i) {

		
		// ȸ���� �󿵽ð� �Է� 
		{
			while (true) {
				cout << endl;
				cout << "\t�� " << i + 1 << "��° ����� �� �ð��� �Է��ϼ���! ex)10��30�л� ==> 10:30  : ";

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
					cout << "\t���߸��Է��ϼ̽��ϴ�!";
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

				// ���� �󿵽ð��� �����ϴ��� üũ 
				bool isExist = false;
				{
					vector<MovieInfo> outList;
					app->GetMovieTimeByGateNo(gateNo, movie->index, outList);
					
					for (auto out : outList) {
						// ��ȭ �󿵳�¥ ���� ��¥�� ���� ������ ���� ��� 
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
					cout << "\t���Է��� �ð��� �̹� �ٸ� ��ȭ�� ����Ǿ� �ֽ��ϴ�!";
					cout << endl;
					CLEAR_STD_BUFFER();
					continue;
				}

				

				auto it = app->gate[gateNo].playMovieMap.find(playTime.get_all());
				if (it == app->gate[gateNo].playMovieMap.end()) {
					// �ߺ��Ǵ� �ð��� ���ٸ� ��� 

					// �󿵽ð� 
					movie->playtime.hour = playTime.hour;
					movie->playtime.minute = playTime.minute;
					movie->playtime.second = playTime.second;

					// �󿵿�ȭ���� ��� 
					app->gate[gateNo].playMovieMap.insert(pair<string, MovieInfo>(playTime.get_all(), *movie));

					// �¼����� ��� 
					app->gate[gateNo].seatMap.insert(pair<string, SeatInfo>(playTime.get_all(), SeatInfo()));
				}
				else {
					cout << endl;
					cout << "\t���Է��� �ð��� �̹� �ٸ� ��ȭ�� ����Ǿ� �ֽ��ϴ�!";
					cout << endl;
					CLEAR_STD_BUFFER();
					continue;
				}

				break;
			}
		}
		

	}
}