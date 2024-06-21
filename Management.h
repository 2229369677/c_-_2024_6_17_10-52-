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

private:
	//�鿴ѧ�����
	Table* m_showTable;
	std::unique_ptr<PushButton> m_addBtn;//���ѧ����ť
	std::unique_ptr<lineEdit> m_addEdit;//���ѧ������

	std::unique_ptr<PushButton> m_searchBtn;//����ѧ����ť
	std::unique_ptr<lineEdit> m_searchEdit;//����ѧ������

	std::unique_ptr<PushButton> m_eraseBtn;//ɾ��ѧ����ť
	std::unique_ptr<lineEdit> m_eraseEdit;//ɾ��ѧ������

	std::unique_ptr<PushButton> m_modifyBtn;//�޸�ѧ����ť
	std::unique_ptr<lineEdit> m_modifyEdit;//�޸�ѧ������
};

