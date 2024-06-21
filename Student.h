#pragma once
#include<string>
//学号，姓名，年龄，性别，出生年月，地址，电话，E - mail等
class Student
{
public:
	Student();
	Student(std::string id, const std::string& name, std::string age, const std::string& gender, std::string date_of_firth, const std::string& address, std::string phone, const std::string& email);
	std::string formatInfo();//格式化数据
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

