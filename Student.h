#pragma once
#include<string>
//ѧ�ţ����������䣬�Ա𣬳������£���ַ���绰��E - mail��
using uint32 = unsigned int;
class Student
{
public:
	Student();
	Student(uint32 id, const std::string& name, uint32 age, const std::string& gender, uint32 date_of_firth, const std::string& address, uint32 phone, const std::string& email);
	std::string formatInfo();//��ʽ������
public:
	uint32 id;
	std::string name;
	uint32 age;
	std::string gender;
	uint32 date_of_birth;
	std::string address;
	uint32 phone;
	std::string email;
};

