#pragma once
#include"Window.h"
#include"PushButton.h"
#include<vector>
#include"Student.h"
#include<fstream>
#include<sstream>
class Management
{
	enum Operator
	{
		Display,
		Insert,
		Remove,
		Modify,
		Search,
		Menu = 66
	};
public:
	Management();
	//启动管理类
	void run();

	int menu();

	//1.显示所有学生
	void display();
	//2.添加
	void add();
	//3.删除
	void erase();
	//4.修改
	void modify();
	//5.查找
	void search();

	void drawBackGroud();
	void enevtLoop();//事件循环

	void readFile(const std::string & fileName);//读文件
	void saveFile(const std::string& fileName);//写文件
private:
	IMAGE m_bk;
	ExMessage m_msg;
	std::vector<PushButton*> menu_btns;
private:
	std::string m_header;//保存学生信息
	std::vector<Student> vec_stu;
};

