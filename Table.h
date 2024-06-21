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

    void setHeader(const std::string &header);//���ñ�ͷ
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
    //���ӵĿ�Ⱥ͸߶�
    int m_gridW;
    int m_gridH;

    std::string m_header;
    std::vector<std::string> m_datas;

private://��ҳ����
    int m_curPage;//��ǰҳ
    int m_maxPage;//���ҳ��
    int m_extraData;//���һҳ����������

private://��ť����һҳ����һҳ����ҳ��βҳ
    PushButton* m_prevBtn;
    PushButton* m_nextBtn;
    PushButton* m_firstBtn;
    PushButton* m_lastBtn;
};

