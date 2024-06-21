#pragma once
#include"Window.h"
#include"PushButton.h"
#include<vector>
#include"Student.h"
#include<fstream>
#include<sstream>
#include"Table.h"
#include<memory>
#include<cstdio>
#include"lineEdit.h"
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

private:
	//查看学生表格
	Table* m_showTable;
	std::unique_ptr<PushButton> m_addBtn;//添加学生按钮
	std::unique_ptr<lineEdit> m_addEdit;//添加学生窗口

	std::unique_ptr<PushButton> m_searchBtn;//查找学生按钮
	std::unique_ptr<lineEdit> m_searchEdit;//查找学生窗口

	std::unique_ptr<PushButton> m_eraseBtn;//删除学生按钮
	std::unique_ptr<lineEdit> m_eraseEdit;//删除学生窗口

	std::unique_ptr<PushButton> m_modifyBtn;//修改学生按钮
	std::unique_ptr<lineEdit> m_modifyEdit;//修改学生窗口
};

