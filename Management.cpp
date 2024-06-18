#include "Management.h"
#include<conio.h>
#include<iostream>

Management::Management()
{
	readFile("./images/student.txt");
	//主界面背景图初始化
	::loadimage(&m_bk, "./images/10002.jpg", Window::width(), Window::height());
	//主界面按钮初始化
	menu_btns.push_back(new PushButton("查看学生信息"));
	menu_btns.push_back(new PushButton("添加学生信息"));
	menu_btns.push_back(new PushButton("删除学生信息"));
	menu_btns.push_back(new PushButton("修改学生信息"));
	menu_btns.push_back(new PushButton("查找学生信息"));
	menu_btns.push_back(new PushButton("退出系统"));

	//让按钮居中
	for (int i = 0; i < menu_btns.size(); i++) 
	{
		menu_btns[i]->setFixedSize(250, 50);
		int bx = (Window::width() - menu_btns[i]->width()) / 2;

		int vspace = ((Window::height() - menu_btns.size() * menu_btns[i]->height()) / 2) + 20;//垂直间隔
		int by =vspace+ i * menu_btns[i]->height();
		
		menu_btns[i]->move(bx, by);
	}
}

void Management::run()
{
	//获取菜单的返回值
	int op = Menu;
	Window::beginDraw();
	while (true)
	{
		Window::clear();
		drawBackGroud();
		//消息处理
		if (Window::hasMsg()) 
		{
			m_msg = Window::getMsg();
			switch (m_msg.message)
			{
			case WM_KEYDOWN:    //键盘操作
				if (m_msg.vkcode == VK_ESCAPE)//按ESC后返回主界面
				{
					op = Menu;
				}
				break;
			default:			//鼠标操作

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
			saveFile("./images/text.txt");//退出保存文件
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
		if (menu_btns[i]->isClicked())//被点击了，返回这个按钮的值
		{
			return i;//下标刚好是他的值
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
		{//读取表头
			char buf[1024] = { 0 };
			read.getline(buf, 1024);//读一行
			m_header = buf;
			//std::cout << buf << std::endl;
		}
		{//读取数据
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
		std::cerr << fileName << "文件打开失败" << std::endl;
		return;
	}
	else
	{
		//写表头
		m_header;
		write.write(m_header.c_str(), m_header.size());
		//写数据
		for (auto& val : vec_stu)
		{
			std::string temp = val.formatInfo();
			write.write(temp.c_str(), temp.size());
		}
	}
	write.close();
}
