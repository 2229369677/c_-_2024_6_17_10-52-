#include "Management.h"
#include<conio.h>
#include<iostream>

#include<algorithm>

Management::Management()
{
	readFile("./images/student.txt");
	//主界面背景图初始化
	::loadimage(&m_bk, "./images/10002.jpg", Window::width(), Window::height());
	//主界面按钮初始化
	/*settextstyle(20, 0, "宋体");*/

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
	//初始化查看学生的表格
	m_showTable = new Table;
	m_showTable->setRowCount(16);
	m_showTable->setHeader(m_header);
	for (auto& val : vec_stu)
	{
		m_showTable->insertData(val.formatInfo());
	}
	//让表格居中
	m_showTable->move(50,80);

	//添加学生按钮
	m_addBtn.reset(new PushButton("添加",700,200));
	//添加学生窗口
	m_addEdit.reset(new lineEdit("点击填写学生信息"));
	m_addEdit->setTitle("请输入学生信息 以空格分开");

	//查找学生按钮
	m_searchBtn.reset(new PushButton("查找", 700, 200));

	//查找学生窗口
	m_searchEdit.reset(new lineEdit("点击填写学生学号或姓名"));
	m_searchEdit->setTitle("请输入学生学号或姓名");

	//删除学生按钮
	m_eraseBtn.reset(new PushButton("删除", 700, 200));

	//删除学生窗口
	m_eraseEdit.reset(new lineEdit(""));
	m_eraseEdit->setTitle("请输入学生学号");

	//修改学生按钮
	m_modifyBtn.reset(new PushButton("修改", 700, 200));

	//修改学生窗口
	m_modifyEdit.reset(new lineEdit(""));
	m_modifyEdit->setTitle("请输入学生学号或姓名");
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
				enevtLoop();
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
	settextstyle(40, 0, "宋体");
	outtextxy((Window::width()-textwidth("学生管理系统")) / 2, 50, "学生管理系统");
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
	const char str[] = {"学生信息"};
	settextstyle(30, 0, "宋体");
	outtextxy((Window::width() - textwidth(str)) / 2, 20, str);
	m_showTable->drawHeader();
	m_showTable->show();
}

void Management::add()
{
	const char str[] = { "<请输入: 学号 姓名 年龄 性别 出生年月 地址 电话 E - mail>" };
	settextstyle(25, 0, "宋体");
	outtextxy((Window::width() - textwidth(str)) / 2, 130, str);
	m_addEdit->show();
	m_addBtn->show();
	if (m_addBtn->isClicked()&&!m_addEdit->text().empty())
	{
		vec_stu.push_back(Student::fromstring(m_addEdit->text()));
		std::string tempstr;//加个’\t'
		{
			tempstr +=
				vec_stu.back().id += '\t';tempstr +=
				vec_stu.back().name ;tempstr +='\t';tempstr +=
				vec_stu.back().age ;tempstr +='\t';tempstr +=
				vec_stu.back().gender ;tempstr +='\t';tempstr +=
				vec_stu.back().date_of_birth ;tempstr +='\t';tempstr +=
				vec_stu.back().address ;tempstr +='\t';tempstr +=
				vec_stu.back().phone ;tempstr +='\t';tempstr +=
				vec_stu.back().email; tempstr += '\t';
		}
		m_showTable->insertData(tempstr);
		m_addEdit->clean();//重置
		m_addBtn->correction();
	}
}

void Management::erase()
{
	const std::string str[] = {"<请输入要删除的学生: 学号>"};
	settextstyle(25, 0, "宋体");
	outtextxy((Window::width() - textwidth(str->data())) / 2, 130, str->data());
	m_eraseEdit->show();
	m_eraseBtn->show();

	auto & tempstr = m_eraseEdit->text();

	if (!str->empty())
	{
		auto it = std::find_if(vec_stu.begin(), vec_stu.end(), [&](const Student& stu)
			{
				return stu.id == tempstr;
			});
		if (it == vec_stu.end())
		{
			settextstyle(16, 0, "宋体");
			outtextxy((Window::width() - textwidth(str->data())) / 2, 250, "没找到该学生");
		}
		else
		{
			settextstyle(16, 0, "宋体");
			outtextxy((Window::width() - textwidth(str->data())) / 2, 250, (it->formatInfo().data()));
			m_eraseEdit->correction();
			m_eraseBtn->eventLoop(m_msg);
			if (m_eraseBtn->isClicked())
			{
				decltype(it) temp = it;
				decltype(it) it_del = it;
				for (it_del = it + 1; it_del != vec_stu.end(); it_del++)
				{
					*temp = *it_del;
					temp = it_del;
				}
				
				if (it_del == vec_stu.end())
				{
					HWND hnd = GetHWnd();
					MessageBox(hnd, "删除成功", "提示", MB_OKCANCEL);
					vec_stu.pop_back();
					//重新初始化一下表格数据
					m_showTable->clean_data();
					for (auto& val : vec_stu)
					{
						m_showTable->insertData(val.formatInfo());
					}
				}
				else
				{
					HWND hnd = GetHWnd();
					MessageBox(hnd, "删除失败", "提示", MB_OKCANCEL);
				}
			}
		}
	}
}

void Management::modify()
{
	const std::string str[] = { "<请输入要修改的学生: 学号>" };
	settextstyle(25, 0, "宋体");
	outtextxy((Window::width() - textwidth(str->data())) / 2, 130, str->data());
	m_modifyEdit->show();
	m_modifyBtn->show();

	auto& tempstr = m_modifyEdit->text();

	if (!str->empty())
	{
		auto it = std::find_if(vec_stu.begin(), vec_stu.end(), [&](const Student& stu)
			{
				return stu.id == tempstr;
			});
		if (it == vec_stu.end())
		{
			settextstyle(16, 0, "宋体");
			outtextxy((Window::width() - textwidth(str->data())) / 2, 250, "没找到该学生");
		}
		else
		{
			settextstyle(16, 0, "宋体");
			outtextxy((Window::width() - textwidth(str->data())) / 2, 250, (it->formatInfo().data()));
			m_modifyEdit->correction();
			m_modifyBtn->eventLoop(m_msg);
			if (m_modifyBtn->isClicked())
			{
				//点击弹出对话框
				std::string temp_text;
				if (m_modifyBtn->isClicked())
				{
					char buf[200];
					InputBox(buf, 200, "请要修改的内容: 学号 姓名 年龄 性别 出生年月 地址 电话 E - mail", "输入框");
					temp_text = buf;
				}
				*it = Student::fromstring(temp_text);
				HWND hnd = GetHWnd();
				MessageBox(hnd, "修改成功", "提示", MB_OKCANCEL);

				//重新初始化一下表格数据
				m_showTable->clean_data();
				for (auto& val : vec_stu)
				{
					m_showTable->insertData(val.formatInfo());
				}
			}
		}
	}
}

void Management::search()
{
	const char str[] = { "<请输入: 学号或姓名>" };
	settextstyle(25, 0, "宋体");
	outtextxy((Window::width() - textwidth(str)) / 2, 130, str);
	m_searchEdit->show();
	m_searchBtn->show();
	bool is = false;//是否查到
	if (m_searchBtn->isClicked() && !m_searchEdit->text().empty())
	{
		std::string tempstr;
		//查找
		for (auto i : vec_stu)
		{
			if (i.id == m_searchEdit->text() || i.name == m_searchEdit->text())
			{
				{
					tempstr +=
						i.id += ' '; tempstr +=
						i.name; tempstr += ' '; tempstr +=
						i.age; tempstr += ' '; tempstr +=
						i.gender; tempstr += ' '; tempstr +=
						i.date_of_birth; tempstr += ' '; tempstr +=
						i.address; tempstr += ' '; tempstr +=
						i.phone; tempstr += ' '; tempstr +=
						i.email; tempstr += ' ';
				}
				is = true;
			}
		}
		HWND hnd = GetHWnd();
		if (is)
		{
			MessageBox(hnd,tempstr.data(), "学生信息", MB_OKCANCEL);
		}
		else
		{
			MessageBox(hnd, "没有查到", "学生信息", MB_OKCANCEL);
		}
		m_searchEdit->clean();//重置
		m_searchBtn->correction();
	}
}//查找

void Management::drawBackGroud()
{
	::putimage(0, 0, &m_bk);
}

void Management::enevtLoop()
{
	m_showTable->eventLoop(m_msg);
	m_addBtn->eventLoop(m_msg);
	m_addEdit->eventLoop(m_msg);
	m_searchBtn->eventLoop(m_msg);
	m_searchEdit->eventLoop(m_msg);
	m_eraseBtn->eventLoop(m_msg);
	m_eraseEdit->eventLoop(m_msg);
	m_modifyBtn->eventLoop(m_msg);
	m_modifyEdit->eventLoop(m_msg);
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
				char buf[2048] = { 0 };
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
		m_header+='\n';
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
