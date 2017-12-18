#pragma once
#include "Process.h"

class App;

// ����� ��带 ����ϴ� Ŭ���� 
class UserProcess : public Process
{
public:
	UserProcess();
	~UserProcess();

	virtual void destroy() {}
	virtual void doRun(App* app);//����� ��� ����

public:
	bool logic_OpenMovieInfo(App* app); //������ȭ����
	bool logic_MovieTimeInfo(App* app);//��¥�� ��ȭ�ð� ����
	bool logic_SearchMovie(App* app);// ��ȭ�˻�
	bool logic_ReserveMovieMenu(App* app);//��ȭ����

	void DisplayMovieInfo(MovieInfo *m);

	bool logic_ReserveMovie(App* app); 
	bool logic_MyReservInfo(App* app);//�������� Ȯ��
	bool logic_CancelReservInfo(App* app);

	int convertToRowIndex(string str);
};

