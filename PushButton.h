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
    //���Ա����
    bool isin();//�ж�����Ƿ��ڵ�ǰ��ť��(Ҫ����ɫ��ʾ��
    bool isClicked();//�ж�����Ƿ񱻵����

    //�����Ϣ����
    void eventLoop(const ExMessage& msg);

    void setBackgroundColor(COLORREF c);
    void setHoverColor(COLORREF c);

    //������Ϣ�󣬽���Ϣ�Ļ�0
    void correction();
protected:
    std::string m_text;
    inline static ExMessage m_msg;//������Ϣ
protected:
    COLORREF cur_c = RGB(2, 46, 91);
    COLORREF normal_c = RGB(2, 46, 91);
    COLORREF hover_c = RGB(13, 86, 159);
};

