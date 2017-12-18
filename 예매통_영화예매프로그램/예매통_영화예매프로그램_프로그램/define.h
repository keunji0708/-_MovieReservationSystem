#pragma once 
#include "stdafx.h"

// �������� ���Ǵ� ����ü��, ��� ������ �����ϴ� ����̴�. 

// ����� Ÿ�� 
enum TYPE_ACTOR {
	ACTOR_USER = 0, // ����� 
	ACTOR_MANAGER = 1,  // ������ 
};


// �ð��� ǥ���ϴ� ����ü 
struct Time {
	int year; // �� 
	int month; // �� 
	int day; // �� 

	int hour; // �� 
	int minute; // �� 
	int second;  // �� 

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

	// ����ϸ� ��� 
	void display_ymd() {
		cout << year << "�� " << month << "�� " << day << "�� ";
	}

	// �ú��ʸ���� 
	void display_hms() {
		cout << hour << ":" << minute << ":" << second;
	}

	// �ð���ü ��� 
	void display_all() {
		cout << year << "�� " << month << "�� " << day << "�� " << hour << ":" << minute << ":" << second;
	}

	// �ú��ʸ� ��������
	string get_hms() {
		return std::to_string(hour) + ":" + std::to_string(minute) + ":" + std::to_string(second);
	}

	// ����� �������� 
	string get_ymd() {
		return std::to_string(year) + "�� " + std::to_string(month) + "�� " + std::to_string(day) + "��";
	}

	// �ð���ü �������� 
	string get_all() {
		return std::to_string(year) + "�� " + std::to_string(month) + "�� " + std::to_string(day) + "��" + std::to_string(hour) + ":" + std::to_string(minute) + ":" + std::to_string(second);
	}
};

// �������� 
struct ReserveInfo {
	int code; // �ڵ� 
	int movieIndex;// ��ȭ��ȣ 
	string movieName; // ��ȭ�̸� 
	Time reserveTime; // ��ȭ�ð� 
	string seat; // �¼�����
	int rowindex; // �¼� �� ��ȣ 
	int colindex; // �¼� �� ��ȣ 

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



// ȸ������ 
struct MemberInfo {
	string id; // ���̵� 
	string pwd;  // ��� 
	int actortype; // ����� Ÿ�� 

	// �������� 
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


// ��ȭ���� 
struct MovieInfo {
	int index; // ��ȭ��ȣ 
	string name; // ��ȭ�̸� 
	Time openDate; // ��������
	Time playtime; // �󿵽ð� ( �󿵰��� ��ϵɶ��� ���� ) 
	Time endtime; // �����¥ 
	int playAllTime; // �� �÷��� �ð� (��)
	string category; // �帣 
	string story; // �ٰŸ� 

	vector<Time> startTimeList; // �󿵽ð� ���۽ð� 

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

		// getline���̺귯�� ���׷� ù �Է� ������ �Ѿ������, �׷��� �ι� ȣ���ϸ� ��������.
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

// �¼����� 
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

// �󿵰����� 
struct MovieGateInfo {

	//int gateNo; // �󿵰� ��ȣ 
	map<string, MovieInfo> playMovieMap;// �ð��� �󿵿�ȭ��� ( key: �󿵽ð�, value: ���� ��ȭ ���� ) 
	map<string, SeatInfo> seatMap; // �ð��� �¼� ��������  ( key: �󿵽ð�, value : �¼����� ) 
	
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