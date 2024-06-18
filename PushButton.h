#pragma once
#include "BasicWidget.h"
#include"Configure.h"
class PushButton :
    public BasicWidget
{
public:
    PushButton(const std::string &text = "Button", int x = 0, int y = 0, int w = 100, int h = 30);
    void show() override;
    //可以被点击
    bool isin();//判断鼠标是否在当前按钮上(要有颜色提示）
    bool isClicked();//判断鼠标是否被点击了

    //检测消息函数
    void eventLoop(const ExMessage& msg);
private:
    std::string m_text;

    ExMessage m_msg;//接受消息
private:
    COLORREF cur_c = RGB(2, 46, 91);
    COLORREF normal_c = RGB(2, 46, 91);
    COLORREF hover_c = RGB(13, 86, 159);
};

