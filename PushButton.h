#pragma once
#include "BasicWidget.h"
#include"Configure.h"
class PushButton :
    public BasicWidget
{
public:
    PushButton(const std::string &text = "Button", int x = 0, int y = 0, int w = 100, int h = 30);
    void show() override;
    //���Ա����
    bool isin();//�ж�����Ƿ��ڵ�ǰ��ť��(Ҫ����ɫ��ʾ��
    bool isClicked();//�ж�����Ƿ񱻵����

    //�����Ϣ����
    void eventLoop(const ExMessage& msg);
private:
    std::string m_text;

    ExMessage m_msg;//������Ϣ
private:
    COLORREF cur_c = RGB(2, 46, 91);
    COLORREF normal_c = RGB(2, 46, 91);
    COLORREF hover_c = RGB(13, 86, 159);
};

