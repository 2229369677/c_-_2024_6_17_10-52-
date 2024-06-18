#include "PushButton.h"

PushButton::PushButton(const std::string& text, int x, int y, int w, int h)
	: BasicWidget(x,y,w,h),m_text(text)
{

}

void PushButton::show()
{
    setfillcolor(cur_c);
    ::fillroundrect(m_x, m_y, m_x + m_w, m_y + m_h, 10, 10);

    settextcolor(RGB(238, 238, 242));
    int tx =m_x+ (m_w-textwidth(m_text.c_str()))/2;
    int ty = m_y+(m_h-textheight(m_text.c_str()))/2;

    outtextxy(tx, ty, m_text.c_str());

}

bool PushButton::isin()
{
    //鼠标点是否在矩形内
    if (m_msg.x >= m_x && m_msg.x < m_x + m_w && m_msg.y >= m_y && m_msg.y < m_y + m_h)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool PushButton::isClicked()
{
    if (isin())//在按钮上
    {
        if (m_msg.message == WM_LBUTTONDOWN)//判断左键是否点击
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

void PushButton::eventLoop(const ExMessage& msg)
{
    m_msg = msg;
    //如果鼠标没有在按钮上
    if (!isin())
    {
        cur_c = normal_c;
    }
    else
    {
        cur_c = hover_c;
    }
}

void PushButton::setBackgroundColor(COLORREF c)
{
    normal_c = c;
}

void PushButton::setHoverColor(COLORREF c)
{
    hover_c = c;
}

