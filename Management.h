#pragma once
#include"Window.h"
#include"PushButton.h"
#include<vector>
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
private:
	IMAGE m_bk;
	ExMessage m_msg;
	std::vector<PushButton*> menu_btns;
};

