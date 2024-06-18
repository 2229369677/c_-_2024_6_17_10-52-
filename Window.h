#pragma once
#include"Configure.h"
class Window
{
public:
	Window(int w, int h, int flag);
	void setWindowTilte(const std::string& title);//���ô��ڵı���
	int exec();

	static int width();
	static int height();
	static void clear();
	static void beginDraw();
	static void flushDraw();
	static void endDraw();

	//����������������
	inline static bool hasMsg() { return peekmessage(&m_msg, EX_MOUSE | EX_KEY); }
	inline static const ExMessage& getMsg() { return m_msg; }
private:
	HWND m_handle;//���ھ��
	inline static ExMessage m_msg;//��Ϣ
};

