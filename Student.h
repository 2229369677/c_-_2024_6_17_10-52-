#pragma once
#include<string>
//学号，姓名，年龄，性别，出生年月，地址，电话，E - mail等
using uint32 = unsigned int;
class Student
{
public:
	Student();
	Student(uint32 id, const std::string& name, uint32 age, const std::string& gender, uint32 date_of_firth, const std::string& address, uint32 phone, const std::string& email);
	std::string formatInfo();//格式化数据
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

