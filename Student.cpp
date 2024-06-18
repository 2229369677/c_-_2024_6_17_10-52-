#include "Student.h"
#include<sstream>

Student::Student()
{
}

Student::Student(uint32 id, const std::string& name, uint32 age, const std::string& gender, uint32 date_of_firth, const std::string& address, uint32 phone, const std::string& email)
	:id(id),name(name),age(age),gender(gender),date_of_birth(date_of_birth),address(address),phone(phone),email(email)
{
}

std::string Student::formatInfo()
{
	std::stringstream ss;
	ss << id << "\t" << name << "\t" << age << "\t" << gender << "\t" << date_of_birth << "\t" << address << "\t" << phone << "\t" << email << std::endl;
	return ss.str();
}
