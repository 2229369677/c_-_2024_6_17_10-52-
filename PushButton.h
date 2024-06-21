#pragma once
#include "BasicWidget.h"
#include"Configure.h"
class PushButton :
    public BasicWidget
{
public:
    PushButton(const std::string &text = "Button", int x = 0, int y = 0, int w = 100, int h = 30);
    void show() override;
    std::string gettext();
    //可以被点击
    bool isin();//判断鼠标是否在当前按钮上(要有颜色提示）
    bool isClicked();//判断鼠标是否被点击了

    //检测消息函数
    void eventLoop(const ExMessage& msg);

    void setBackgroundColor(COLORREF c);
    void setHoverColor(COLORREF c);

    //接受消息后，将消息改回0
    void correction();
protected:
    std::string m_text;
    inline static ExMessage m_msg;//接受消息
protected:
    COLORREF cur_c = RGB(2, 46, 91);
    COLORREF normal_c = RGB(2, 46, 91);
    COLORREF hover_c = RGB(13, 86, 159);
};

