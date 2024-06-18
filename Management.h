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
private:
	IMAGE m_bk;
	ExMessage m_msg;
	std::vector<PushButton*> menu_btns;
};

