#include "Student.h"
#include<sstream>

Student::Student()
{
}

Student::Student(std::string id, const std::string& name, std::string age, const std::string& gender, std::string date_of_firth, const std::string& address, std::string phone, const std::string& email)
	:id(id),name(name),age(age),gender(gender),date_of_birth(date_of_birth),address(address),phone(phone),email(email)
{
}

std::string Student::formatInfo()
{
	std::stringstream ss;
	ss << id << "\t" << name << "\t" << age << "\t" << gender << "\t" << date_of_birth << "\t" << address << "\t" << phone << "\t" << email << std::endl;
	return ss.str();
}

Student Student::fromstring(const std::string& str)
{
	Student stu;
	std::stringstream ss(str);
	ss >> stu.id >>
		stu.name >>
		stu.age >>
		stu.gender >>
		stu.date_of_birth >>
		stu.address >>
		stu.phone >>
		stu.email;
	return stu;
}