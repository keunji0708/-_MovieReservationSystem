#pragma once

#include "Process.h"

class App;


// 관리자 모드 를 담당하는 클래스 
class ManagerProcess : public Process 
{
public:
	ManagerProcess() {}
	~ManagerProcess() {}
public:
	virtual void destroy() {}
	virtual void doRun(App* app);

	bool logic_AddMovieInfo(App* app); // 영화정보입력
	bool logic_AddMovieInfoByDateTime(App* app); // 날짜별 상영정보 입력 
	
	
public:
	void AddPlayMovieTimeInfo(App* app, int gateNo, MovieInfo *movie); // 상영시간 등록 
};

