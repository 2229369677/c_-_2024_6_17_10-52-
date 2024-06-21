#include "Table.h"
#include"Window.h"

Table::Table(int row, int col)
	:BasicWidget(0,0,0,0)
	,m_rows(row)
	,m_cols(col)
	,m_curPage(0)
	,m_maxPage(0)
	,m_extraData(0)
{
	m_prevBtn = new PushButton("��һҳ");
	m_nextBtn = new PushButton("��һҳ");
	m_firstBtn = new PushButton("��ҳ");
	m_lastBtn = new PushButton("βҳ");
}

Table::~Table()
{
	delete m_prevBtn;
	delete m_nextBtn;
	delete m_firstBtn;
	delete m_lastBtn;
}

void Table::setRowCount(int row)
{
	m_rows = row;
	
}

void Table::setColCount(int col)
{
	m_cols = col;
}

void Table::insertData(const std::string& data)
{
	m_datas.push_back(data);
	updatePage();
}

void Table::setHeader(const std::string& header)
{
	
	m_header = header;
	m_cols = std::count(header.begin(), header.end(), '\t')+1;
	settextstyle(20, 0,"����");
	//set���Ŀ�Ⱥ͸߶�
	m_gridW = ::textwidth("һ��������");//10*16 = 160;
	m_gridH = ::textheight(m_header.c_str())+8;//16
}

void Table::show()
{
	settextstyle(16, 0, "����");
	drawTableGrid();
	settextstyle(16, 0, "����");
	drawTableData();
}

void Table::drawTableGrid()
{
	
	//ȷ������ж����У�������
	setlinecolor(RGB(238, 238, 242));
	//������
	for (size_t i = 0; i < m_rows +1; i++)
	{
		int tem_w = textwidth(" 2229369677@qq.com ");//���һ��
		line(m_x, m_y + i * m_gridH, m_x + (m_cols-1)*m_gridW+tem_w, m_y + i * m_gridH);
	}
	//������
	for (size_t i = 0; i < m_cols + 1; i++)
	{
		
		if (i == m_cols)
		{
			int tem_w = textwidth(" 2229369677@qq.com ");//���һ��
			line(m_x + (i-1) * m_gridW+tem_w, m_y, m_x + (i - 1) * m_gridW + tem_w, m_y + m_rows * m_gridH);
		}
		else
		{
			line(m_x+i*m_gridW, m_y, m_x+ i * m_gridW , m_y + m_rows * m_gridH);
		}
	}
	drawButton();
}

void Table::drawTableData()
{
	//ÿ�����ֻ�����ǰҳ
	int begPos = m_curPage*m_rows;//���ݿ�ʼλ��
    int endPos = begPos+m_rows;//���ݵĽ���λ��
	if (begPos == m_maxPage*m_rows)
	{
		endPos = begPos + m_extraData;
	}


	for (size_t i = begPos; i < endPos; i++)//��
	{
		const auto& tempstr = split(m_datas[i]);//�ԡ�/t'�ָ�

		for (int j = 0; j < tempstr.size(); j++)//��
		{
			//���
			int tx = m_x + j * m_gridW;
			int ty = m_y + i%m_rows * m_gridH+5;
			outtextxy(tx, ty, tempstr[j].c_str());
		}
	}
}

void Table::drawButton()
{
	int dis = 10;//��������ľ���
	m_prevBtn ->move(50,80 +m_gridH*m_rows+dis);
	m_nextBtn->move(50+m_gridW,80 +m_gridH*m_rows+dis);
	m_firstBtn->move(50+m_gridW*2,80 +m_gridH*m_rows+dis);
	m_lastBtn->move(50+m_gridW*3, 80 +m_gridH*m_rows+dis);

	m_prevBtn->show();
	m_nextBtn->show();
	m_firstBtn->show();
	m_lastBtn->show();
	char str[20]{ 0 };
	sprintf_s(str, "��%dҳ/��%dҳ", m_curPage+1, m_maxPage+1);
	outtextxy(50 + m_gridW * (m_cols-1), 80 + m_gridH * m_rows+dis,str);
}

void Table::drawHeader()
{
	settextstyle(16, 0, "����");
	int tem_w = textwidth(" 2229369677@qq.com ");//���һ��
	//����
	line(m_x, m_y- m_gridH, m_x + (m_cols - 1) * m_gridW + tem_w, m_y - m_gridH);

	//����
	for (size_t i = 0; i < m_cols + 1; i++)
	{

		if (i == m_cols)
		{
			int tem_w = textwidth(" 2229369677@qq.com ");//���һ��
			line(m_x + (i - 1) * m_gridW + tem_w, m_y- m_gridH, m_x + (i - 1) * m_gridW + tem_w, m_y );
		}
		else
		{
			line(m_x + i * m_gridW, m_y-m_gridH, m_x + i * m_gridW, m_y);
		}
	}
	settextstyle(20,0,"����");
	//д���ͷ
	const auto& tempstr = split(m_header);
	for (int j = 0; j < tempstr.size(); j++)//��
	{
		//���
		int tx = m_x + j * m_gridW;
		int ty = m_y + 5-m_gridH;
		outtextxy(tx, ty, tempstr[j].c_str());
	}
}

void Table::clean_data()
{
	m_datas.clear();
}

void Table::eventLoop(const ExMessage& msg)
{
	m_prevBtn->eventLoop(msg);
	m_nextBtn->eventLoop(msg);
	m_firstBtn->eventLoop(msg);
	m_lastBtn->eventLoop(msg);

	if (m_prevBtn->isClicked())
	{
		if (m_curPage != 0)
		{
			m_curPage--;
		}
	}
	if (m_nextBtn->isClicked())
	{
		if (m_curPage != m_maxPage)
		{
			m_curPage++;
		}
	}
	if (m_firstBtn->isClicked())
	{
		m_curPage = 0;
	}
	if (m_lastBtn->isClicked())
	{
		m_curPage = m_maxPage;
	}
}

std::vector<std::string> Table::split(std::string str, char separator)
{
	std::vector<std::string> res;
	int index = 0;
	int i = 0;
	while ((index = str.find(separator,i)) != -1)
	{
		res.push_back(str.substr(i, index - i));
		i = index + 1;
	}
	res.push_back(str.substr(i, str.size() - i-1));
	return res;
}

void Table::updatePage()
{
	//����ҳ��
	m_maxPage = ceil(m_datas.size() / m_rows);
	m_extraData = m_datas.size() % m_rows;
	if (m_extraData == 0)
	{
		m_extraData = m_rows;
	}
}

