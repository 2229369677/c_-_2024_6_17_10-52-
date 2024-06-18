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
	//����������
	void run();

	int menu();

	//1.��ʾ����ѧ��
	void display();
	//2.���
	void add();
	//3.ɾ��
	void erase();
	//4.�޸�
	void modify();
	//5.����
	void search();

	void drawBackGroud();
	void enevtLoop();//�¼�ѭ��

	void readFile(const std::string & fileName);//���ļ�
	void saveFile(const std::string& fileName);//д�ļ�
private:
	IMAGE m_bk;
	ExMessage m_msg;
	std::vector<PushButton*> menu_btns;
private:
	std::string m_header;//����ѧ����Ϣ
	std::vector<Student> vec_stu;
};

