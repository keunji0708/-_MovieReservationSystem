#pragma once
#include "Process.h"

class App;

// 사용자 모드를 담당하는 클래스 
class UserProcess : public Process
{
public:
	UserProcess();
	~UserProcess();

	virtual void destroy() {}
	virtual void doRun(App* app);//사용자 모드 실행

public:
	bool logic_OpenMovieInfo(App* app); //개봉영화정보
	bool logic_MovieTimeInfo(App* app);//날짜별 영화시간 정보
	bool logic_SearchMovie(App* app);// 영화검색
	bool logic_ReserveMovieMenu(App* app);//영화예매

	void DisplayMovieInfo(MovieInfo *m);

	bool logic_ReserveMovie(App* app); 
	bool logic_MyReservInfo(App* app);//예매정보 확인
	bool logic_CancelReservInfo(App* app);

	int convertToRowIndex(string str);
};

