#include "Management.h"
#include<conio.h>
#include<iostream>

Management::Management()
{
	readFile("./images/student.txt");
	//�����汳��ͼ��ʼ��
	::loadimage(&m_bk, "./images/10002.jpg", Window::width(), Window::height());
	//�����水ť��ʼ��
	menu_btns.push_back(new PushButton("�鿴ѧ����Ϣ"));
	menu_btns.push_back(new PushButton("���ѧ����Ϣ"));
	menu_btns.push_back(new PushButton("ɾ��ѧ����Ϣ"));
	menu_btns.push_back(new PushButton("�޸�ѧ����Ϣ"));
	menu_btns.push_back(new PushButton("����ѧ����Ϣ"));
	menu_btns.push_back(new PushButton("�˳�ϵͳ"));

	//�ð�ť����
	for (int i = 0; i < menu_btns.size(); i++) 
	{
		menu_btns[i]->setFixedSize(250, 50);
		int bx = (Window::width() - menu_btns[i]->width()) / 2;

		int vspace = ((Window::height() - menu_btns.size() * menu_btns[i]->height()) / 2) + 20;//��ֱ���
		int by =vspace+ i * menu_btns[i]->height();
		
		menu_btns[i]->move(bx, by);
	}
}

void Management::run()
{
	//��ȡ�˵��ķ���ֵ
	int op = Menu;
	Window::beginDraw();
	while (true)
	{
		Window::clear();
		drawBackGroud();
		//��Ϣ����
		if (Window::hasMsg()) 
		{
			m_msg = Window::getMsg();
			switch (m_msg.message)
			{
			case WM_KEYDOWN:    //���̲���
				if (m_msg.vkcode == VK_ESCAPE)//��ESC�󷵻�������
				{
					op = Menu;
				}
				break;
			default:			//������

				break;
			}
		}
		
		
		switch (op)
		{
		case Management::Menu:
			op = menu();
			break;
		case Management::Display: 
			display();
			break;
		case Management::Insert:
			add();
			break;
		case Management::Remove:
			erase();
			break;
		case Management::Modify:
			modify();
			break;
		case Management::Search:
			search();
			break;
		default:
			saveFile("./images/text.txt");//�˳������ļ�
			exit(666);
			break;
		}
		Window::flushDraw();
	}
	Window::endDraw();
}

int Management::menu()
{
	for (int i = 0; i < menu_btns.size(); i++)
	{
		menu_btns[i]->show();
		menu_btns[i]->eventLoop(m_msg);
		if (menu_btns[i]->isClicked())//������ˣ����������ť��ֵ
		{
			return i;//�±�պ�������ֵ
		}
	}
	return Menu;
}

void Management::display()
{
	outtextxy(0, 0, "display()");
	std::cout << "display()" << std::endl;
}

void Management::add()
{
	outtextxy(0, 0, "add()");
	std::cout << "add()" << std::endl;
}

void Management::erase()
{
	outtextxy(0, 0, "etase()");
	std::cout << "erase()" << std::endl;
}

void Management::modify()
{
	outtextxy(0, 0, "modify()");
	std::cout << "modify()" << std::endl;
}

void Management::search()
{
	outtextxy(0, 0, "search()");
	std::cout << "search()" << std::endl;
}

void Management::drawBackGroud()
{
	::putimage(0, 0, &m_bk);
}

void Management::enevtLoop()
{

}

void Management::readFile(const std::string& fileName)
{
	std::fstream read(fileName, std::ios::in);
	if (!read.is_open())
	{
		return;
	}
	else
	{
		{//��ȡ��ͷ
			char buf[1024] = { 0 };
			read.getline(buf, 1024);//��һ��
			m_header = buf;
			//std::cout << buf << std::endl;
		}
		{//��ȡ����
			while (!read.eof())
			{
				char buf[1024] = { 0 };
				read.getline(buf, 1024);

				Student stu;
				std::stringstream ss(buf);
				ss >> stu.id >> stu.name >> stu.age >> stu.gender >> stu.date_of_birth >> stu.address >> stu.phone >> stu.email;
				vec_stu.push_back(stu);
				//std::cout << stu.id << stu.name << stu.age << stu.gender << stu.date_of_birth << stu.address << stu.phone << stu.email << std::endl;
			}
		}
	}
	read.close();
}

void Management::saveFile(const std::string& fileName)
{
	std::fstream write(fileName, std::ios::out | std::ios::trunc);
	if (!write.is_open())
	{
		std::cerr << fileName << "�ļ���ʧ��" << std::endl;
		return;
	}
	else
	{
		//д��ͷ
		m_header;
		write.write(m_header.c_str(), m_header.size());
		//д����
		for (auto& val : vec_stu)
		{
			std::string temp = val.formatInfo();
			write.write(temp.c_str(), temp.size());
		}
	}
	write.close();
}
