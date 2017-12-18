#pragma once

// 좌석 예매시 발급되는 코드 생성기  ( 싱글턴 형태로 클래스 만듬 ) 
class CodeGenerator
{
private:
	static CodeGenerator *instance; 
	
	int code; 

public:
	CodeGenerator();
	~CodeGenerator();

public:
	static CodeGenerator * getInstance() {
		if (NULL == instance) {
			instance = new CodeGenerator();
			
		}
		return instance;
	}

	// 코드 생성 
	int createCode() {

		if (0 == code) {
			code = 1000000;
		}

		code++; 
		return code; 
	}

	void WriteFile(ofstream & out) {
		out << code << endl; 
	}

	void ReadFile(ifstream & in) {
		in >> code; 
	}
};

