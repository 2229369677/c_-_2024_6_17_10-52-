#include "Management.h"
#include<conio.h>
#include<iostream>


Management::Management()
{
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
