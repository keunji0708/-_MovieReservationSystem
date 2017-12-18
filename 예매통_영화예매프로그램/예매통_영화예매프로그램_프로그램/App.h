#pragma once

#include "define.h"
#include <time.h>

// 모드 타입 
enum TYPE_MODE {
	MODE_NONE = 0,
	MODE_USER = 1, // 사용자 모드  
	MODE_MANAGER = 2 , // 관리자 모드
	MODE_MAX, 
};

// 상영관 타입
enum TYPE_GATE {
	GATE_A = 0, // A관 
	GATE_B = 1, // B관
	GATE_C = 2, // C관
	GATE_D = 3, // D관
	GATE_MAX = 4,
};


class Process; 

// 프로그램 전체 로직을 처리 담당하는 중앙 관리 클래스 
class App
{
private:
	vector<MemberInfo> memberList; // 사용자 목록 
	vector<MovieInfo> movieList; // 영화목록 

	
	
	// 프로그램의 현재 실행 모드 ( 0: 비로그인 상태, 1: 사용자모드, 2: 관리자 모드 ) 
	TYPE_MODE currentMode; 

	// 모드별로 처리해야할 로직 클래스 포인터 배열 
	Process * proc[TYPE_MODE::MODE_MAX]; 

	

public:
	MovieGateInfo gate[TYPE_GATE::GATE_MAX]; // 상영관 정보 
											 // 로그인 한 회원 포인터 
	string loginMemberID;
public:
	App();
	~App();

	// 프로그램을 시작 한다. 
	void run();

public:
	// 파일을 읽어온다. 
	void ReadFile();

	// 파일을 저장한다. 
	void WriteFile();


	// 모드 변경 시 
	void changeMode(TYPE_MODE mode) {
		if (0 > mode || TYPE_MODE::MODE_MAX <= mode) return;

		currentMode = mode; 
	}

	// 멤버를 추가한다. 
	void addMember(MemberInfo info) { memberList.push_back(info);  }

	// 멤버 정보를 가져온다. 
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


	// 멤버 id가 중복되는지 체크하는 함수 
	bool checkExistID(string id) {
		if (memberList.size() == 0) return false;
		for (auto m : memberList) {
			if (!strcmp(id.c_str(), m.id.c_str())) {
				return true; // 중복되는 아이디가 있음. 
			}
		}
		return false; // 중복되는 아이디가 없음. 
	}
		
	// id, pwd가 일치하는 지 인증체크 
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

	// 회원 탈퇴 처리 
	void leaveMember(string id) {
		for (auto it = memberList.begin(); it != memberList.end(); ++it) {
			MemberInfo & m = *it; 
			// 같은 id를 가진 member를 제거 
			if (!strcmp(id.c_str(), m.id.c_str())) {
				memberList.erase(it); 
				return; 
			}
		}
	}

	// 영화번호로 영화가 존재하는지 체크 
	bool checkExistMovie(int index) {

		if (movieList.size() == 0) return false; 

		for (auto m : movieList) {
			if (m.index == index) return true; 
		}
		return false; 
	}

	// 영화이름으로 영화가 존재하는지 체크 
	bool checkExistMovie(string name) {

		if (movieList.size() == 0) return false; 

		for (auto m : movieList) {
			if (!strcmp(m.name.c_str(), name.c_str())) return true;
		}
		return false;
	}

	// 영화등록 
	void addMovie(MovieInfo movie) {
		movieList.push_back(movie); 
	}

	// 영화정보가져오기 
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

	// 모든 영화정보 출력 
	void displMovieInfoAll() {
		for (auto m : movieList) {
			cout << "\t" << m.index << "." << m.name.c_str() << endl; 
		}
	}

	// 모든 영화의 사이즈를 구한다. 
	int getMaxMovieCount() {
		return movieList.size();
	}

	// 모든 영화정보 가져오기 
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

	// 영화이름으로 영화의 모든 정보를 제거 한다. 
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

	// 상영중인 영화 목록 가져오기 
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

	// 해당 영화가 상영관에 등록된 것인지 확인 
	bool checkExistMovieFromGate(int gateType, int index) {
		
		for (auto it = gate[gateType].playMovieMap.begin(); it != gate[gateType].playMovieMap.end(); ++it) {
			if (it->second.index == index) return true; // 상영중 
		}
		return false; // 미상영 
	}

	//  상영관 정보 출력 
	void displayMovieGateInfo(int gateType) {
		
		int count = 1; 
		for (auto it = gate[gateType].playMovieMap.begin(); it != gate[gateType].playMovieMap.end(); ++it) {
			cout << "\t" << count << ". 상영시간 (" << it->second.playtime.get_ymd().c_str() << it->second.playtime.get_hms().c_str() << ") 영화이름 (" << it->second.name.c_str() << ")" << endl;
			count++;
		}
	}

	// 상영 날짜 정보 제거
	bool RemoveMovieGateInfo(int gateType, int delNo) {
		// delNo는 순서 정보임. 

		int count = 1;
		for (auto it = gate[gateType].playMovieMap.begin(); it != gate[gateType].playMovieMap.end(); ++it) {
			if (count == delNo) {
				// 삭제 
				gate[gateType].playMovieMap.erase(it);
				return true; 
			}

			count++;
		}
		return false; 
	}

	// 전체 상영관에서 해당 영화의 시간을 조회해서 가져온다. 
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
	// 특정 상영관에서 해당 영화의 시간을 조회해서 가져온다. 
	void GetMovieTimeByGateNo(int gateNo, int movieIndex, vector<MovieInfo> & outList) {
		for (auto it = gate[gateNo].playMovieMap.begin(); it != gate[gateNo].playMovieMap.end(); ++it) {
			MovieInfo &info = it->second;
			if (movieIndex == info.index) {
				outList.push_back(info);
			}
		}
	}


	// 전체 영화의  상영 정보를 출력 한다. 
	void displayMovieInfoByGateAll() {
		for (auto movie : movieList) {
			cout << endl; 
			cout << "\t영화 " << movie.name.c_str() << "(개봉일:" << movie.openDate.get_ymd().c_str() << "/ 폐관일:" << movie.endtime.get_ymd().c_str() << ")" << endl;

			for (int i = 0; i < TYPE_GATE::GATE_MAX; ++i) {
				for (auto it = gate[i].playMovieMap.begin(); it != gate[i].playMovieMap.end(); ++it) {
					MovieInfo &info = it->second;
					if (movie.index == info.index) {
						cout << "\t\t" << info.playtime.get_ymd().c_str() << " " << i + 1 << "관 " << info.playtime.get_all().c_str() << endl; 
					}
				}
			}

		}
		cout << endl; 
	}

	// 선택한 상영시간으로 좌석정보를 얻어낸다.
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

	// 좌석 예약 
	void ReserveSeat(int movieIndex, string hms, int rindex, int cindex) {
		for (int i = 0; i < TYPE_GATE::GATE_MAX; ++i) {
			for (auto it = gate[i].playMovieMap.begin(); it != gate[i].playMovieMap.end(); ++it) {
				MovieInfo &info = it->second;
				if (movieIndex == info.index) {
					auto it_seat = gate[i].seatMap.find(hms.c_str());
					if (it_seat != gate[i].seatMap.end()) {
						SeatInfo &info = it_seat->second;

						// 예매상태 설정 
						info.seat[rindex][cindex] = 1;

						// 예매한 사람 ID 저장 
						info.seatReserveMemberID[rindex][cindex] = loginMemberID.c_str();
						return;
					}
					
				}
			}
		}
	}

	// 좌석 예약 취소 
	void ReserveCancelSeat(int movieIndex, string hms, int rindex, int cindex) {
		for (int i = 0; i < TYPE_GATE::GATE_MAX; ++i) {
			for (auto it = gate[i].playMovieMap.begin(); it != gate[i].playMovieMap.end(); ++it) {
				MovieInfo &info = it->second;
				if (movieIndex == info.index) {
					auto it_seat = gate[i].seatMap.find(hms.c_str());
					if (it_seat != gate[i].seatMap.end()) {
						SeatInfo &info = it_seat->second;

						// 예매상태 설정 
						info.seat[rindex][cindex] = 0;

						// 예매한 사람 ID 저장 
						info.seatReserveMemberID[rindex][cindex] = "";
						return;
					}
				}
			}
		}
	}

	// 내 정보에 예약 정보 설정 
	void ReserveMyInfo(const ReserveInfo &reserveInfo ) {
		for (auto it = memberList.begin(); it != memberList.end(); ++it) {
			MemberInfo & memberInfo = *it; 
			if (!strcmp(loginMemberID.c_str(), memberInfo.id.c_str())) {
				memberInfo.reserveList.push_back(reserveInfo); 
			}
		}
	}

	// 내 정보에 파라메터로 넘어온 예약 정보와 동일한 예약이 있었는지 중복 검사한다. 
	bool alreadyReserveMyInfo(const ReserveInfo &reserveInfo) {
		for (auto it = memberList.begin(); it != memberList.end(); ++it) {
			MemberInfo & memberInfo = *it;
			if (!strcmp(loginMemberID.c_str(), memberInfo.id.c_str())) {
				for (auto reserve : memberInfo.reserveList)
				{
					// 영화번호와 좌석 번호 와 시간이 같다면 중복 
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

	// 예매 정보 가져오기 
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

	// 예매 취소 처리 
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

