#pragma once
#include<string>
#include"PushButton.h"
#include"Configure.h"
#include<sstream>
#include"Student.h"
class lineEdit:public PushButton
{
public:
	lineEdit(const std::string& str = "添加学生", int x = 120, int y = 200, int w = 570, int h = 30);
	void show();
	inline void setTitle(const std::string& title) { m_title = title; };
	inline const std::string& text() { return m_text; }
	inline void clean() { m_text = "点击填写学生信息"; }

	bool Inputcheck(const std::string &str);//输入正确检查
private:
	std::string m_title;
};

