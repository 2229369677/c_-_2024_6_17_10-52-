#include "lineEdit.h"

lineEdit::lineEdit(const std::string &str,int x, int y, int w, int h)
	:PushButton(str,x,y,w,h)
{
}

void lineEdit::show()
{
    setfillcolor(cur_c);
    ::fillroundrect(m_x, m_y, m_x + m_w, m_y + m_h, 10, 10);

    settextcolor(RGB(238, 238, 242));
    settextstyle(16, 0, "����");
    int tx = m_x + (m_w - textwidth(m_text.c_str())) / 2;
    int ty = m_y + (m_h - textheight(m_text.c_str())) / 2;

    outtextxy(tx, ty, m_text.c_str());

    //��������Ի���
    if (isClicked())
    {
        char buf[200];
        InputBox(buf,200, m_title.data(),"�����");
        m_text = buf;
    }
}

bool lineEdit::Inputcheck(const std::string& str)
{
    int count_t = std::count(str.begin(), str.end(), ' ');
    if (count_t != 7)
    {
        HWND hnd = GetHWnd();
        MessageBox(hnd, "�����������������", "��ʾ", MB_OKCANCEL);
        return false;
    }
    return true;
}

