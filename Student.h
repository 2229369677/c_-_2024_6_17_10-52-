#pragma once
#include<string>
//ѧ�ţ����������䣬�Ա𣬳������£���ַ���绰��E - mail��
class Student
{
public:
	Student();
	Student(std::string id, const std::string& name, std::string age, const std::string& gender, std::string date_of_firth, const std::string& address, std::string phone, const std::string& email);
	std::string formatInfo();//��ʽ������
	static Student fromstring(const std::string &str);
public:
	std::string id;
	std::string name;
	std::string age;
	std::string gender;
	std::string date_of_birth;
	std::string address;
	std::string phone;
	std::string email;
};

