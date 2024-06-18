#pragma once
#include"Configure.h"
class Window
{
public:
	Window(int w, int h, int flag);
	void setWindowTilte(const std::string& title);//设置窗口的标题
	int exec();

	static int width();
	static int height();
	static void clear();
	static void beginDraw();
	static void flushDraw();
	static void endDraw();

	//按键操作喝鼠标操作
	inline static bool hasMsg() { return peekmessage(&m_msg, EX_MOUSE | EX_KEY); }
	inline static const ExMessage& getMsg() { return m_msg; }
private:
	HWND m_handle;//窗口句柄
	inline static ExMessage m_msg;//消息
};

