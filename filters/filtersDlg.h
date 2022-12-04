
// filtersDlg.h: файл заголовка
//
#include "Drawer.h"
#include <iostream>
#include <math.h>
#include "Sign.h"


#pragma once

using namespace std;

// Диалоговое окно CfiltersDlg
class CfiltersDlg : public CDialogEx
{
// Создание
public:
	CfiltersDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FILTERS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit2();
	double A1;
	double A2;	//Амплитуды синусоид
	double A3;

	double F1;
	double F2;	//Частоты синусоид
	double F3;

	double F01;
	double F02;	//Начальные фазы синусоид
	double F03;

	int N;	//количество точек
	double fd;	//частота дискретизации
	double Alpha;	//процент шума
	double N_Win;	//ширина окна

	CString Best_Filter;	//строка с лучшим фильтром

	double E_1;		
	double E_2;
	double E_3;		//Энергии ошибок
	double E_4;
	double E_5;

	Drawer
		Graph1,
		Graph2,
		Graph3;

	afx_msg void OnEnChangeEdit20();
	
	afx_msg void OnBnClickedOk();
	double D; //Дисперсия

	void CreateFilters(Filter & One, Filter& Two, Filter& Three, Filter& Four, Filter& Five, Sign_Analizer Sign); //производит все операции для фильтров
	double Find_Max(double One, double Two, double Three, double Four, double Five, double Sign); // максимум в векторх
	double Find_Min(double One, double Two, double Three, double Four, double Five, double Sign); // мин в векторх
	void Find_Best();	//находит лучший фильтр
};
