#pragma once

// �¼� ���Ž� �߱޵Ǵ� �ڵ� ������  ( �̱��� ���·� Ŭ���� ���� ) 
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

	// �ڵ� ���� 
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

