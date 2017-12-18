#pragma once

#include "define.h"
#include <time.h>

// ��� Ÿ�� 
enum TYPE_MODE {
	MODE_NONE = 0,
	MODE_USER = 1, // ����� ���  
	MODE_MANAGER = 2 , // ������ ���
	MODE_MAX, 
};

// �󿵰� Ÿ��
enum TYPE_GATE {
	GATE_A = 0, // A�� 
	GATE_B = 1, // B��
	GATE_C = 2, // C��
	GATE_D = 3, // D��
	GATE_MAX = 4,
};


class Process; 

// ���α׷� ��ü ������ ó�� ����ϴ� �߾� ���� Ŭ���� 
class App
{
private:
	vector<MemberInfo> memberList; // ����� ��� 
	vector<MovieInfo> movieList; // ��ȭ��� 

	
	
	// ���α׷��� ���� ���� ��� ( 0: ��α��� ����, 1: ����ڸ��, 2: ������ ��� ) 
	TYPE_MODE currentMode; 

	// ��庰�� ó���ؾ��� ���� Ŭ���� ������ �迭 
	Process * proc[TYPE_MODE::MODE_MAX]; 

	

public:
	MovieGateInfo gate[TYPE_GATE::GATE_MAX]; // �󿵰� ���� 
											 // �α��� �� ȸ�� ������ 
	string loginMemberID;
public:
	App();
	~App();

	// ���α׷��� ���� �Ѵ�. 
	void run();

public:
	// ������ �о�´�. 
	void ReadFile();

	// ������ �����Ѵ�. 
	void WriteFile();


	// ��� ���� �� 
	void changeMode(TYPE_MODE mode) {
		if (0 > mode || TYPE_MODE::MODE_MAX <= mode) return;

		currentMode = mode; 
	}

	// ����� �߰��Ѵ�. 
	void addMember(MemberInfo info) { memberList.push_back(info);  }

	// ��� ������ �����´�. 
	void GetMember(string id, MemberInfo & outInfo) {
		if (memberList.size() == 0) return;
		for (auto m : memberList) {
			if (!strcmp(id.c_str(), m.id.c_str())) {
				outInfo.id = m.id.c_str();
				outInfo.pwd = m.pwd.c_str();
				outInfo.actortype = m.actortype; 
			}
		}
	}


	// ��� id�� �ߺ��Ǵ��� üũ�ϴ� �Լ� 
	bool checkExistID(string id) {
		if (memberList.size() == 0) return false;
		for (auto m : memberList) {
			if (!strcmp(id.c_str(), m.id.c_str())) {
				return true; // �ߺ��Ǵ� ���̵� ����. 
			}
		}
		return false; // �ߺ��Ǵ� ���̵� ����. 
	}
		
	// id, pwd�� ��ġ�ϴ� �� ����üũ 
	bool checkAuth(string id, string pwd){

		if (memberList.size() == 0) return false; 

		for (auto m : memberList) {
			if (!strcmp(id.c_str(), m.id.c_str())) {
				if (!strcmp(pwd.c_str(), m.pwd.c_str())) {
					return true; // ok 
				}
			}
		}
		return false; // failed 
	}

	// ȸ�� Ż�� ó�� 
	void leaveMember(string id) {
		for (auto it = memberList.begin(); it != memberList.end(); ++it) {
			MemberInfo & m = *it; 
			// ���� id�� ���� member�� ���� 
			if (!strcmp(id.c_str(), m.id.c_str())) {
				memberList.erase(it); 
				return; 
			}
		}
	}

	// ��ȭ��ȣ�� ��ȭ�� �����ϴ��� üũ 
	bool checkExistMovie(int index) {

		if (movieList.size() == 0) return false; 

		for (auto m : movieList) {
			if (m.index == index) return true; 
		}
		return false; 
	}

	// ��ȭ�̸����� ��ȭ�� �����ϴ��� üũ 
	bool checkExistMovie(string name) {

		if (movieList.size() == 0) return false; 

		for (auto m : movieList) {
			if (!strcmp(m.name.c_str(), name.c_str())) return true;
		}
		return false;
	}

	// ��ȭ��� 
	void addMovie(MovieInfo movie) {
		movieList.push_back(movie); 
	}

	// ��ȭ������������ 
	MovieInfo* GetMovie(int index) {
		for (auto it = movieList.begin(); it != movieList.end(); ++it) {

			MovieInfo &info = *it;
			if (info.index == index) {
				return &info; 
			}	
		}
		return NULL;
	}
	MovieInfo* GetMovie(string name) {
		for (auto it = movieList.begin(); it != movieList.end(); ++it) {

			MovieInfo &info = *it;
			if (!strcmp(info.name.c_str(), name.c_str())) {
				return &info;
			}
		}
		return NULL;
	}

	// ��� ��ȭ���� ��� 
	void displMovieInfoAll() {
		for (auto m : movieList) {
			cout << "\t" << m.index << "." << m.name.c_str() << endl; 
		}
	}

	// ��� ��ȭ�� ����� ���Ѵ�. 
	int getMaxMovieCount() {
		return movieList.size();
	}

	// ��� ��ȭ���� �������� 
	void GetMovieList(vector<MovieInfo> &outMovieInfo) {
		for (auto m : movieList) {
			outMovieInfo.push_back(m); 
		}
	}

	

	time_t getTimeInt(int year, int month, int day) {
		struct tm t = { 0 };
		t.tm_year = year - 1900;
		t.tm_mon = month - 1;
		t.tm_mday = day;
		t.tm_hour = 0;
		t.tm_min = 0;
		t.tm_sec = 0;

		return mktime(&t);
	}

	time_t getTimeInt(int year, int month, int day, int hour, int minute, int second) {
		struct tm t = { 0 };
		t.tm_year = year - 1900;
		t.tm_mon = month - 1;
		t.tm_mday = day;
		t.tm_hour = hour;
		t.tm_min = minute;
		t.tm_sec = second;

		return mktime(&t);
	}

	// ��ȭ�̸����� ��ȭ�� ��� ������ ���� �Ѵ�. 
	void RemoveMovieAll(string name) {
		for (auto it = movieList.begin(); it != movieList.end(); ++it) {
			MovieInfo & info = *it; 
			if (!strcmp(info.name.c_str(), name.c_str())) {
				movieList.erase(it); 
				break; 

			}
		}

		for (int i = 0; i < TYPE_GATE::GATE_MAX; ++i) {
			for (auto it = gate[i].playMovieMap.begin(); it != gate[i].playMovieMap.end(); ) {
				MovieInfo &info = it->second;
				if (!strcmp(info.name.c_str(), name.c_str())) {
					it = gate[i].playMovieMap.erase(it);
				}
				else {
					it++;
				}
			}
		}
	}

	// ������ ��ȭ ��� �������� 
	void GetMovieByTime(int y, int m, int d, vector<MovieInfo> & outList) {

		for (int i = 0; i < TYPE_GATE::GATE_MAX; ++i) {
			for (auto it = gate[i].playMovieMap.begin(); it != gate[i].playMovieMap.end(); ++it) {
				MovieInfo info = it->second;
				
				time_t s = getTimeInt(info.playtime.year, info.playtime.month, info.playtime.day);
				time_t e = getTimeInt(info.endtime.year, info.endtime.month, info.endtime.day);
				time_t b = getTimeInt(y, m, d);
				
				if (s <= b && e >= b) {
					outList.push_back(info);
				}
			}
		}
		
		/*for (auto movie : movieList) {

			if (movie.openDate.year <= y) {
				outList.push_back(movie);
			}
			else {
				if (movie.openDate.month <= m) {
					outList.push_back(movie);
				}
				else {
					if (movie.openDate.day <= d) {
						outList.push_back(movie);
					}
				}
			}
		}*/
	}

	// �ش� ��ȭ�� �󿵰��� ��ϵ� ������ Ȯ�� 
	bool checkExistMovieFromGate(int gateType, int index) {
		
		for (auto it = gate[gateType].playMovieMap.begin(); it != gate[gateType].playMovieMap.end(); ++it) {
			if (it->second.index == index) return true; // ���� 
		}
		return false; // �̻� 
	}

	//  �󿵰� ���� ��� 
	void displayMovieGateInfo(int gateType) {
		
		int count = 1; 
		for (auto it = gate[gateType].playMovieMap.begin(); it != gate[gateType].playMovieMap.end(); ++it) {
			cout << "\t" << count << ". �󿵽ð� (" << it->second.playtime.get_ymd().c_str() << it->second.playtime.get_hms().c_str() << ") ��ȭ�̸� (" << it->second.name.c_str() << ")" << endl;
			count++;
		}
	}

	// �� ��¥ ���� ����
	bool RemoveMovieGateInfo(int gateType, int delNo) {
		// delNo�� ���� ������. 

		int count = 1;
		for (auto it = gate[gateType].playMovieMap.begin(); it != gate[gateType].playMovieMap.end(); ++it) {
			if (count == delNo) {
				// ���� 
				gate[gateType].playMovieMap.erase(it);
				return true; 
			}

			count++;
		}
		return false; 
	}

	// ��ü �󿵰����� �ش� ��ȭ�� �ð��� ��ȸ�ؼ� �����´�. 
	void GetMovieTimeByGateAll(int movieIndex, vector<MovieInfo> & outList) {

		for (int i = 0; i < TYPE_GATE::GATE_MAX; ++i) {
			for (auto it = gate[i].playMovieMap.begin(); it != gate[i].playMovieMap.end(); ++it) {
				MovieInfo &info = it->second;
				if (movieIndex == info.index) {
					outList.push_back(info); 
				}
			}
		}
	}
	// Ư�� �󿵰����� �ش� ��ȭ�� �ð��� ��ȸ�ؼ� �����´�. 
	void GetMovieTimeByGateNo(int gateNo, int movieIndex, vector<MovieInfo> & outList) {
		for (auto it = gate[gateNo].playMovieMap.begin(); it != gate[gateNo].playMovieMap.end(); ++it) {
			MovieInfo &info = it->second;
			if (movieIndex == info.index) {
				outList.push_back(info);
			}
		}
	}


	// ��ü ��ȭ��  �� ������ ��� �Ѵ�. 
	void displayMovieInfoByGateAll() {
		for (auto movie : movieList) {
			cout << endl; 
			cout << "\t��ȭ " << movie.name.c_str() << "(������:" << movie.openDate.get_ymd().c_str() << "/ �����:" << movie.endtime.get_ymd().c_str() << ")" << endl;

			for (int i = 0; i < TYPE_GATE::GATE_MAX; ++i) {
				for (auto it = gate[i].playMovieMap.begin(); it != gate[i].playMovieMap.end(); ++it) {
					MovieInfo &info = it->second;
					if (movie.index == info.index) {
						cout << "\t\t" << info.playtime.get_ymd().c_str() << " " << i + 1 << "�� " << info.playtime.get_all().c_str() << endl; 
					}
				}
			}

		}
		cout << endl; 
	}

	// ������ �󿵽ð����� �¼������� ����.
	void GetMovieFormGateByTime(int movieIndex , string hms, SeatInfo & outSeatInfo) {
		for (int i = 0; i < TYPE_GATE::GATE_MAX; ++i) {
			for (auto it = gate[i].playMovieMap.begin(); it != gate[i].playMovieMap.end(); ++it) {
				MovieInfo &info = it->second;
				if (movieIndex == info.index) {
					auto it_seat = gate[i].seatMap.find(hms.c_str());
					if (it_seat != gate[i].seatMap.end()) {
						outSeatInfo = it_seat->second;
						return; 
					}
				}
			}
		}
	}

	// �¼� ���� 
	void ReserveSeat(int movieIndex, string hms, int rindex, int cindex) {
		for (int i = 0; i < TYPE_GATE::GATE_MAX; ++i) {
			for (auto it = gate[i].playMovieMap.begin(); it != gate[i].playMovieMap.end(); ++it) {
				MovieInfo &info = it->second;
				if (movieIndex == info.index) {
					auto it_seat = gate[i].seatMap.find(hms.c_str());
					if (it_seat != gate[i].seatMap.end()) {
						SeatInfo &info = it_seat->second;

						// ���Ż��� ���� 
						info.seat[rindex][cindex] = 1;

						// ������ ��� ID ���� 
						info.seatReserveMemberID[rindex][cindex] = loginMemberID.c_str();
						return;
					}
					
				}
			}
		}
	}

	// �¼� ���� ��� 
	void ReserveCancelSeat(int movieIndex, string hms, int rindex, int cindex) {
		for (int i = 0; i < TYPE_GATE::GATE_MAX; ++i) {
			for (auto it = gate[i].playMovieMap.begin(); it != gate[i].playMovieMap.end(); ++it) {
				MovieInfo &info = it->second;
				if (movieIndex == info.index) {
					auto it_seat = gate[i].seatMap.find(hms.c_str());
					if (it_seat != gate[i].seatMap.end()) {
						SeatInfo &info = it_seat->second;

						// ���Ż��� ���� 
						info.seat[rindex][cindex] = 0;

						// ������ ��� ID ���� 
						info.seatReserveMemberID[rindex][cindex] = "";
						return;
					}
				}
			}
		}
	}

	// �� ������ ���� ���� ���� 
	void ReserveMyInfo(const ReserveInfo &reserveInfo ) {
		for (auto it = memberList.begin(); it != memberList.end(); ++it) {
			MemberInfo & memberInfo = *it; 
			if (!strcmp(loginMemberID.c_str(), memberInfo.id.c_str())) {
				memberInfo.reserveList.push_back(reserveInfo); 
			}
		}
	}

	// �� ������ �Ķ���ͷ� �Ѿ�� ���� ������ ������ ������ �־����� �ߺ� �˻��Ѵ�. 
	bool alreadyReserveMyInfo(const ReserveInfo &reserveInfo) {
		for (auto it = memberList.begin(); it != memberList.end(); ++it) {
			MemberInfo & memberInfo = *it;
			if (!strcmp(loginMemberID.c_str(), memberInfo.id.c_str())) {
				for (auto reserve : memberInfo.reserveList)
				{
					// ��ȭ��ȣ�� �¼� ��ȣ �� �ð��� ���ٸ� �ߺ� 
					if (reserve.movieIndex == reserveInfo.movieIndex
						&& reserve.rowindex == reserveInfo.rowindex 
						&& reserve.colindex == reserveInfo.colindex
						&& reserve.reserveTime.hour == reserveInfo.reserveTime.hour 
						&& reserve.reserveTime.minute == reserveInfo.reserveTime.minute) {
						return true; 
					}
				}
			}
		}
		return false; 
	}

	// ���� ���� �������� 
	ReserveInfo* GetReserveInfo(int code) {
		for (auto it = memberList.begin(); it != memberList.end(); ++it) {
			MemberInfo & memberInfo = *it;
			if (!strcmp(loginMemberID.c_str(), memberInfo.id.c_str())) {

				for (auto it2 = memberInfo.reserveList.begin(); it2 != memberInfo.reserveList.end(); ++it2) {

					ReserveInfo &reserveInfo = *it2; 
					if (reserveInfo.code == code) {
						return &reserveInfo;
					}
				}
				
			}
		}
		return NULL;
	}

	// ���� ��� ó�� 
	void RemoveReserveMyinfo(int code) {
		for (auto it = memberList.begin(); it != memberList.end(); ++it) {
			MemberInfo & memberInfo = *it;
			if (!strcmp(loginMemberID.c_str(), memberInfo.id.c_str())) {

				for (auto it2 = memberInfo.reserveList.begin(); it2 != memberInfo.reserveList.end(); ++it2) {
					ReserveInfo &reserveInfo = *it2;
					if (reserveInfo.code == code) {
						memberInfo.reserveList.erase(it2); 
						return; 
					}
				}
				
			}
		}
	}
};

