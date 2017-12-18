#pragma once 
#include "stdafx.h"

// 전역으로 사용되는 구조체나, 상수 값들을 선언하는 헤더이다. 

// 사용자 타입 
enum TYPE_ACTOR {
	ACTOR_USER = 0, // 사용자 
	ACTOR_MANAGER = 1,  // 관리자 
};


// 시간을 표현하는 구조체 
struct Time {
	int year; // 년 
	int month; // 월 
	int day; // 일 

	int hour; // 시 
	int minute; // 분 
	int second;  // 초 

	Time() {
		year = 0;
		month = 0;
		day = 0;
		hour = 0;
		minute = 0;
		second = 0;
	}
	void WriteFile(ofstream & out) {
		out << year << endl;
		out << month << endl;
		out << day << endl;

		out << hour << endl;
		out << minute << endl;
		out << second << endl;
	}
	void ReadFile(ifstream & in) {
		in >> year;
		in >> month;
		in >> day;

		in >> hour;
		in >> minute;
		in >> second;
	}

	void setYMD(int _year, int _month, int _day) {
		year = _year;
		month = _month;
		day = _day;
		hour = 0;
		minute = 0;
		second = 0;
	}

	void setHMS(int _hour, int _minute, int _second) {
		year = 0;
		month = 0;
		day = 0;
		hour = _hour;
		minute = _minute;
		second = _second;
	}

	void setAll(int _year, int _month, int _day, int _hour, int _minute, int _second) {
		year = _year;
		month = _month;
		day = _day;
		hour = _hour;
		minute = _minute;
		second = _second;
	}

	// 년월일만 출력 
	void display_ymd() {
		cout << year << "년 " << month << "월 " << day << "일 ";
	}

	// 시분초만출력 
	void display_hms() {
		cout << hour << ":" << minute << ":" << second;
	}

	// 시간전체 출력 
	void display_all() {
		cout << year << "년 " << month << "월 " << day << "일 " << hour << ":" << minute << ":" << second;
	}

	// 시분초만 가져오기
	string get_hms() {
		return std::to_string(hour) + ":" + std::to_string(minute) + ":" + std::to_string(second);
	}

	// 년월일 가져오기 
	string get_ymd() {
		return std::to_string(year) + "년 " + std::to_string(month) + "월 " + std::to_string(day) + "일";
	}

	// 시간전체 가져오기 
	string get_all() {
		return std::to_string(year) + "년 " + std::to_string(month) + "월 " + std::to_string(day) + "일" + std::to_string(hour) + ":" + std::to_string(minute) + ":" + std::to_string(second);
	}
};

// 예매정보 
struct ReserveInfo {
	int code; // 코드 
	int movieIndex;// 영화번호 
	string movieName; // 영화이름 
	Time reserveTime; // 영화시간 
	string seat; // 좌석정보
	int rowindex; // 좌석 행 번호 
	int colindex; // 좌석 열 번호 

	ReserveInfo() {
		code = 0; 
		movieIndex = 0; 
		movieName = "";
		seat = "";
		rowindex = 0; 
		colindex = 0; 
	}

	void WriteFile(ofstream & out) {
		out << code << endl; 
		out << movieIndex << endl;
		out << movieName.c_str() << endl;
		reserveTime.WriteFile(out);
		out << seat.c_str() << endl;
		out << rowindex << endl; 
		out << colindex << endl; 
	}

	void ReadFile(ifstream & in) {
		in >> code;
		in >> movieIndex;
		in >> movieName;
		reserveTime.ReadFile(in);
		in >> seat;
		in >> rowindex; 
		in >> colindex; 
	}
};



// 회원정보 
struct MemberInfo {
	string id; // 아이디 
	string pwd;  // 비번 
	int actortype; // 사용자 타입 

	// 예약정보 
	vector<ReserveInfo> reserveList; 

	MemberInfo() {
		id = "";
		pwd = "";
		actortype = 0; 
	}

	MemberInfo(string _id, string _pwd, int _actortype) {
		id = _id; 
		pwd = _pwd; 
		actortype = _actortype;
	}

	void WriteFile(ofstream & out) {
		out << id.c_str() << endl;
		out << pwd.c_str() << endl;
		out << actortype << endl;

		int cnt = reserveList.size();
		out << cnt << endl; 
		for (auto r : reserveList) {
			r.WriteFile(out); 
		}
	}

	void ReadFile(ifstream & in) {
		in >> id;
		in >> pwd;
		in >> actortype;

		int cnt = 0;
		in >> cnt; 

		for (int i = 0; i < cnt; ++i) {
			ReserveInfo r; 
			r.ReadFile(in); 

			reserveList.push_back(r); 
		}
	}
};


// 영화정보 
struct MovieInfo {
	int index; // 영화번호 
	string name; // 영화이름 
	Time openDate; // 개봉일자
	Time playtime; // 상영시간 ( 상영관에 등록될때만 저장 ) 
	Time endtime; // 폐관날짜 
	int playAllTime; // 상영 플레이 시간 (분)
	string category; // 장르 
	string story; // 줄거리 

	vector<Time> startTimeList; // 상영시간 시작시간 

	MovieInfo() {
		
		index = 0;
		name = "";
		playAllTime = 0;
		category = "";
		story = ""; 
		
	}

	void WriteFile(ofstream & out) {
		out << index << endl; 
		out << name.c_str() << endl; 
		openDate.WriteFile(out); 
		playtime.WriteFile(out); 
		endtime.WriteFile(out); 
		out << playAllTime << endl; 
		out << category.c_str() << endl; 
		out << story.c_str() << endl; 

		int count = startTimeList.size();
		out << count << endl; 
		for (auto t : startTimeList) {
			t.WriteFile(out); 
		}
	}
	void ReadFile(ifstream & in) {
		in >> index;
		in >> name;
		openDate.ReadFile(in); 
		playtime.ReadFile(in);
		endtime.ReadFile(in); 
		in >> playAllTime;
		in >> category;

		// getline라이브러리 버그로 첫 입력 받을시 넘어가버린다, 그래서 두번 호출하면 정상동작함.
		getline(in, story);
		getline(in, story);
		//in >> story;

		int count;
		in >> count; 
		for (int i = 0; i < count; ++i) {
			Time t;
			t.ReadFile(in);
			startTimeList.push_back(t); 
		}
	}


};

// 좌석정보 
struct SeatInfo {
	int seat[10][10];
	string seatReserveMemberID[10][10];

	SeatInfo() {
		for (int i = 0; i < 10; ++i) {
			for (int j = 0; j < 10; ++j) {
				seat[i][j] = 0;
				seatReserveMemberID[i][j] = "";
			}
		}
	}

	void WriteFile(ofstream & out) {
		for (int i = 0; i < 10; ++i) {
			for (int j = 0; j < 10; ++j) {
				out << seat[i][j] << endl; 
				if (seat[i][j]) {
					out << seatReserveMemberID[i][j] << endl;
				}
			}
		}
	}

	void ReadFile(ifstream & in) {
		for (int i = 0; i < 10; ++i) {
			for (int j = 0; j < 10; ++j) {
				in >> seat[i][j];

				if (seat[i][j]) {
					in >> seatReserveMemberID[i][j];
				}
			}
		}
	}
};

// 상영관정보 
struct MovieGateInfo {

	//int gateNo; // 상영관 번호 
	map<string, MovieInfo> playMovieMap;// 시간별 상영영화목록 ( key: 상영시간, value: 상영할 영화 정보 ) 
	map<string, SeatInfo> seatMap; // 시간별 좌석 예매정보  ( key: 상영시간, value : 좌석정보 ) 
	
	MovieGateInfo() {
		//gateNo = 0;
		playMovieMap.clear();
		seatMap.clear(); 
	}

	void WriteFile(ofstream & out) {
		//out << gateNo << endl; 
		int size = playMovieMap.size(); 
		out << size << endl; 

		for (auto playMovie : playMovieMap) {

			out << playMovie.first.c_str() << endl; 
			playMovie.second.WriteFile(out); 
		}

		size = seatMap.size();
		out << size << endl; 

		for (auto seat : seatMap) {
			out << seat.first.c_str() << endl;
			seat.second.WriteFile(out);
		}
	}

	void ReadFile(ifstream & in) {
		//in >> gateNo;

		int size = 0; 
		in >> size; 
		for (int i = 0; i < size; ++i) {
			string key;
			in >> key; 

			MovieInfo movie; 
			movie.ReadFile(in); 
			playMovieMap.insert(pair<string, MovieInfo>(key.c_str(), movie));
		}

		in >> size; 
		for (int i = 0; i < size; ++i) {
			string key; 
			in >> key; 

			SeatInfo seat;
			seat.ReadFile(in); 
			seatMap.insert(pair<string, SeatInfo>(key.c_str(), seat));

		}
	}
};