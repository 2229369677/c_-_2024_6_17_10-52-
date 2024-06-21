#include "Management.h"
#include<conio.h>
#include<iostream>

#include<algorithm>

Management::Management()
{
	readFile("./images/student.txt");
	//�����汳��ͼ��ʼ��
	::loadimage(&m_bk, "./images/10002.jpg", Window::width(), Window::height());
	//�����水ť��ʼ��
	/*settextstyle(20, 0, "����");*/

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
	//��ʼ���鿴ѧ���ı��
	m_showTable = new Table;
	m_showTable->setRowCount(16);
	m_showTable->setHeader(m_header);
	for (auto& val : vec_stu)
	{
		m_showTable->insertData(val.formatInfo());
	}
	//�ñ�����
	m_showTable->move(50,80);

	//���ѧ����ť
	m_addBtn.reset(new PushButton("���",700,200));
	//���ѧ������
	m_addEdit.reset(new lineEdit("�����дѧ����Ϣ"));
	m_addEdit->setTitle("������ѧ����Ϣ �Կո�ֿ�");

	//����ѧ����ť
	m_searchBtn.reset(new PushButton("����", 700, 200));

	//����ѧ������
	m_searchEdit.reset(new lineEdit("�����дѧ��ѧ�Ż�����"));
	m_searchEdit->setTitle("������ѧ��ѧ�Ż�����");

	//ɾ��ѧ����ť
	m_eraseBtn.reset(new PushButton("ɾ��", 700, 200));

	//ɾ��ѧ������
	m_eraseEdit.reset(new lineEdit(""));
	m_eraseEdit->setTitle("������ѧ��ѧ��");

	//�޸�ѧ����ť
	m_modifyBtn.reset(new PushButton("�޸�", 700, 200));

	//�޸�ѧ������
	m_modifyEdit.reset(new lineEdit(""));
	m_modifyEdit->setTitle("������ѧ��ѧ�Ż�����");

	//����
	m_sortBtn_id.reset(new PushButton("��ѧ������", 850,0 ,100,20));
	m_sortBtn_name.reset(new PushButton("����������", 850, 20,100,20));
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
	settextstyle(40, 0, "����");
	outtextxy((Window::width()-textwidth("ѧ������ϵͳ")) / 2, 50, "ѧ������ϵͳ");
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
	const char str[] = {"ѧ����Ϣ"};
	settextstyle(30, 0, "����");
	outtextxy((Window::width() - textwidth(str)) / 2, 20, str);
	m_sortBtn_id->show();//��ť��ʾ
	m_sortBtn_name->show();
	if (m_sortBtn_id->isClicked())//��ѧ������ť��Ӧ
	{
		std::sort(vec_stu.begin(), vec_stu.end(), [](const Student& stu1, const Student& sut2)
			{
				return stu1.id < sut2.id;
			});
		m_showTable->clean_data();
		for (auto& val : vec_stu)
		{
			m_showTable->insertData(val.formatInfo());
		}
	}
	if (m_sortBtn_name->isClicked())//����������ť��Ӧ
	{
		std::sort(vec_stu.begin(), vec_stu.end(), [](const Student& stu1, const Student& sut2)
			{
				return stu1.name < sut2.name;
			});
		m_showTable->clean_data();
		for (auto& val : vec_stu)
		{
			m_showTable->insertData(val.formatInfo());
		}
	}
	m_showTable->drawHeader();//ͷ����ʾ
	m_showTable->show();//����������ʾ���ڻ��з�ҳ��ťʵ��
}

void Management::add()
{
	const char str[] = { "<������: ѧ�� ���� ���� �Ա� �������� ��ַ �绰 E - mail>" };
	settextstyle(25, 0, "����");
	outtextxy((Window::width() - textwidth(str)) / 2, 130, str);
	m_addEdit->show();//�������ʾ
	m_addBtn->show();//��ť��ʾ
	if (m_addBtn->isClicked()&&!m_addEdit->text().empty())//��ť��Ϣ��Ӧ��Ϊ��ֹ�հ����룬���������ַ������ƣ�
	{
		vec_stu.push_back(Student::fromstring(m_addEdit->text()));//���봢���������
		std::string tempstr;//�Ӹ���\t'//���ַ�������
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
		m_showTable->insertData(tempstr);//���չʾ���Ĵ�����Ϣ��
		m_addEdit->clean();//����������ı�������ӳɹ�����ʾ���úͣ����������ʾ����
		m_addBtn->correction();//��ֹ�������룬����ť��Ϣ����Ϊ0;
	}
}

void Management::erase()
{
	const std::string str[] = {"<������Ҫɾ����ѧ��: ѧ��>"};//ѧ��Ψһ����ֹ��ɾ
	settextstyle(25, 0, "����");
	outtextxy((Window::width() - textwidth(str->data())) / 2, 130, str->data());
	m_eraseEdit->show();//�������ʾ
	m_eraseBtn->show();//��ť��ʾ

	auto & tempstr = m_eraseEdit->text();//����������Ϣ���ô����в���

	if (!str->empty())//��Ϊ������в��ң���ֹ�հײ���
	{
		//ʹ��������find_if��������ѧ�Ų���
		auto it = std::find_if(vec_stu.begin(), vec_stu.end(), [&](const Student& stu)
			{
				return stu.id == tempstr;
			});
		if (it == vec_stu.end())//�ж��Ƿ��ҵ����Բ��Ҳ�����ʾ
		{
			settextstyle(16, 0, "����");
			outtextxy((Window::width() - textwidth(str->data())) / 2, 250, "û�ҵ���ѧ��");
		}
		else
		{
			settextstyle(16, 0, "����");
			outtextxy((Window::width() - textwidth(str->data())) / 2, 250, (it->formatInfo().data()));
			m_eraseEdit->correction();//������Ϣ��������ֹ��Ϣ���е���Ϣ����ɴ���
			m_eraseBtn->eventLoop(m_msg);//������Ϣ
			if (m_eraseBtn->isClicked())//ɾ��������Ӧ
			{
				//���������������ҵ�Ҫɾ����ѧ�������ѧ����Ϣ����ǰ�ƶ�һλ�������һ��ѧ����Ϣɾ����
				//�������ɾ������
				decltype(it) temp = it;
				decltype(it) it_del = it;
				for (it_del = it + 1; it_del != vec_stu.end(); it_del++)
				{
					*temp = *it_del;
					temp = it_del;
				}
				
				if (it_del == vec_stu.end())//��ɾ��������ʾ
				{
					HWND hnd = GetHWnd();
					MessageBox(hnd, "ɾ���ɹ�", "��ʾ", MB_OKCANCEL);
					vec_stu.pop_back();
					//���³�ʼ��һ�±�����ݣ���ʵʱ����
					{
						m_showTable->clean_data();
						for (auto& val : vec_stu)
						{
							m_showTable->insertData(val.formatInfo());
						}
					}
				}
				else
				{
					HWND hnd = GetHWnd();
					MessageBox(hnd, "ɾ��ʧ��", "��ʾ", MB_OKCANCEL);
				}
			}
		}
	}
}

void Management::modify()
{
	const std::string str[] = { "<������Ҫ�޸ĵ�ѧ��: ѧ��>" };
	settextstyle(25, 0, "����");
	outtextxy((Window::width() - textwidth(str->data())) / 2, 130, str->data());
	m_modifyEdit->show();
	m_modifyBtn->show();

	auto& tempstr = m_modifyEdit->text();//���������ѧ�ţ������в��Ҳ���

	if (!str->empty())//�жϲ�Ϊ��
	{
		//���ò���
		auto it = std::find_if(vec_stu.begin(), vec_stu.end(), [&](const Student& stu)
			{
				return stu.id == tempstr;
			});
		if (it == vec_stu.end())//���Ҳ�������ʾ��Ϣ
		{
			settextstyle(16, 0, "����");
			outtextxy((Window::width() - textwidth(str->data())) / 2, 250, "û�ҵ���ѧ��");
		}
		else
		{
			settextstyle(16, 0, "����");
			outtextxy((Window::width() - textwidth(str->data())) / 2, 250, (it->formatInfo().data()));
			m_modifyEdit->correction();//ˢ����Ϣ
			m_modifyBtn->eventLoop(m_msg);
			if (m_modifyBtn->isClicked())//�޸Ĳ���
			{
				//��������Ի���
				std::string temp_text;//�����޸�����
				if (m_modifyBtn->isClicked())
				{
					char buf[200];
					InputBox(buf, 200, "��Ҫ�޸ĵ�����: ѧ�� ���� ���� �Ա� �������� ��ַ �绰 E - mail", "�����");
					temp_text = buf;
				}
				*it = Student::fromstring(temp_text);//��ֵ��ֵ
				HWND hnd = GetHWnd();
				MessageBox(hnd, "�޸ĳɹ�", "��ʾ", MB_OKCANCEL);//�޸���ʾ��Ϣ

				//���³�ʼ��һ�±�����ݣ���ʵʱ���ݸ���
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
	const char str[] = { "<������: ѧ�Ż�����>" };
	settextstyle(25, 0, "����");
	outtextxy((Window::width() - textwidth(str)) / 2, 130, str);
	m_searchEdit->show();
	m_searchBtn->show();
	bool is = false;//�Ƿ�鵽
	if (m_searchBtn->isClicked() && !m_searchEdit->text().empty())
	{
		std::string tempstr;
		//����
		for (auto i : vec_stu)
		{
			if (i.id == m_searchEdit->text() || i.name == m_searchEdit->text())
			{
				//��ѧ������д����ת�ַ�����������������ֱ�Ӹ���ճ����add()����Ĵ���
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
		if (is)//������ʾ��Ϣ
		{
			MessageBox(hnd,tempstr.data(), "ѧ����Ϣ", MB_OKCANCEL);
		}
		else
		{
			MessageBox(hnd, "û�в鵽", "ѧ����Ϣ", MB_OKCANCEL);
		}
		m_searchEdit->clean();//����
		m_searchBtn->correction();
	}
}//����

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
	m_sortBtn_id->eventLoop(m_msg);
	m_sortBtn_name->eventLoop(m_msg);
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
		std::cerr << fileName << "�ļ���ʧ��" << std::endl;
		return;
	}
	else
	{
		//д��ͷ
		m_header+='\n';
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
