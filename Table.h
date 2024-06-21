#pragma once
#include "BasicWidget.h"
#include<string>
#include<iostream>
#include"Configure.h"
#include<vector>
#include"PushButton.h"
class Table :
    public BasicWidget
{
public:
    Table(int row = 0, int col = 0);
    ~Table();
    void setRowCount(int row);
    void setColCount(int col);
    void insertData(const std::string& data);

    void setHeader(const std::string &header);//设置表头
    void show();
    void drawTableGrid();
    void drawTableData();
    void drawButton();  
    void drawHeader();

    void clean_data();
       
    void eventLoop(const ExMessage& msg);

    static std::vector<std::string> split(std::string str, char separator = '\t');

    void updatePage();
private:
    int m_rows;
    int m_cols;
    //格子的宽度和高度
    int m_gridW;
    int m_gridH;

    std::string m_header;
    std::vector<std::string> m_datas;

private://分页处理
    int m_curPage;//当前页
    int m_maxPage;//最大页数
    int m_extraData;//最后一页的数据条数

private://按钮：下一页，上一页，首页，尾页
    PushButton* m_prevBtn;
    PushButton* m_nextBtn;
    PushButton* m_firstBtn;
    PushButton* m_lastBtn;
};

