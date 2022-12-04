
// filtersDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "filters.h"
#include "filtersDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Диалоговое окно CfiltersDlg



CfiltersDlg::CfiltersDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FILTERS_DIALOG, pParent)
	, A1(1)
	, A2(1)
	, A3(1)
	, F1(2)
	, F2(2)
	, F3(3)
	, F01(0)
	, F02(0)
	, F03(0)
	, N(256)
	, fd(256)
	, Alpha(50)
	, N_Win(100)
	, Best_Filter(_T(""))
	, E_1(0)
	, E_2(0)
	, E_3(0)
	, E_4(0)
	, E_5(0)
	
	, D(10)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CfiltersDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, A1);
	DDX_Text(pDX, IDC_EDIT2, A2);
	DDX_Text(pDX, IDC_EDIT4, A3);
	DDX_Text(pDX, IDC_EDIT3, F1);
	DDX_Text(pDX, IDC_EDIT5, F2);
	DDX_Text(pDX, IDC_EDIT6, F3);
	DDX_Text(pDX, IDC_EDIT8, F02);
	DDX_Text(pDX, IDC_EDIT9, F03);
	DDX_Text(pDX, IDC_EDIT10, N);
	DDX_Text(pDX, IDC_EDIT11, fd);
	DDX_Text(pDX, IDC_EDIT12, Alpha);
	DDX_Text(pDX, IDC_EDIT13, N_Win);
	DDX_Text(pDX, IDC_EDIT19, Best_Filter);
	DDX_Text(pDX, IDC_EDIT14, E_1);
	DDX_Text(pDX, IDC_EDIT15, E_2);
	DDX_Text(pDX, IDC_EDIT16, E_3);
	DDX_Text(pDX, IDC_EDIT17, E_4);
	DDX_Text(pDX, IDC_EDIT18, E_5);
	DDX_Text(pDX, IDC_EDIT20, F01);
	DDX_Text(pDX, IDC_EDIT21, D);
}

BEGIN_MESSAGE_MAP(CfiltersDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT2, &CfiltersDlg::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT20, &CfiltersDlg::OnEnChangeEdit20)
	ON_BN_CLICKED(IDOK, &CfiltersDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// Обработчики сообщений CfiltersDlg

BOOL CfiltersDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	Graph1.Create(GetDlgItem(IDC_SIGNAL)->GetSafeHwnd());
	Graph2.Create(GetDlgItem(IDC_ACH)->GetSafeHwnd());
	Graph3.Create(GetDlgItem(IDC_CLEAN)->GetSafeHwnd());

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CfiltersDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CfiltersDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CfiltersDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CfiltersDlg::OnEnChangeEdit2()
{
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// функция и вызов CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Добавьте код элемента управления
}


void CfiltersDlg::OnEnChangeEdit20()
{
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// функция и вызов CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Добавьте код элемента управления
}

//производит все операции с фильтрами
void CfiltersDlg::CreateFilters(Filter& One, Filter& Two, Filter& Three, Filter& Four, Filter& Five, Sign_Analizer Signal) {
	One.CreateFilterOne();
	Two.CreateFilterTwo();
	Three.CreateFilterThree();
	Four.CreateFilterFour(D);
	Five.CreateFilterFive();

	Filter *mas[5] = { &One, &Two, &Three, &Four, &Five };
	double *mas2[5] = { &E_1, &E_2, &E_3, &E_4, &E_5 };

	for (int i = 0; i < 5; i++) {
		mas[i]->FFT(-1);
		mas[i]->Get_Spectrum(mas[i]->Sdata, mas[i]->Skeys);		
		mas[i]->Filtration(Signal.Re, Signal.Im);
		*mas2[i] = mas[i]->Get_Error(Signal.data);  
	}
}

//находит максимум 
double CfiltersDlg::Find_Max(double One, double Two, double Three, double Four, double Five, double Sign) {
	double mas[6] = { One,Two,Three, Four,Five, Sign };
	double max = mas[0];
	for (int i = 0; i < 6; i++)
		if (max <= mas[i])
			max = mas[i];
	return max;
}
//находит мин 
double CfiltersDlg::Find_Min(double One, double Two, double Three, double Four, double Five, double Sign) {
	double mas[6] = { One,Two,Three, Four,Five, Sign };
	double max = mas[0];
	for (int i = 0; i < 6; i++)
		if (max >= mas[i])
			max = mas[i];
	return max;
}

void CfiltersDlg::OnBnClickedOk()
{
	UpdateData();

	Graph1.DrawW();
	Graph2.DrawW();
	Graph3.DrawW();

	//класс с изначальным сигналом
	Sign_Analizer Signal(N, fd);
	
	Signal.Get_Signal(A1, A2, A3, F1, F2, F3, F01, F02, F03); //Создали чистый сигнал
	Signal.Noise(Alpha);	//наложили шум

	Graph1.DrawOne(Signal.Ndata, 0, N / fd, Signal.NdataMin, Signal.NdataMax, 'A', 't', Signal.keys);

	Signal.FFT(-1);
	Signal.Get_Spectrum(Signal.Sdata,Signal.Skeys);	  //нашли спектр исходного сигнала

	Filter
		One(N, fd, N_Win),
		Two(N, fd, N_Win),
		Three(N, fd, N_Win),
		Four(N, fd, N_Win),
		Five(N, fd, N_Win);		//проинициализировали фильтры

	CreateFilters(One, Two, Three, Four, Five, Signal);
	
	Graph2.DrawSix(Signal.Sdata, One.Sdata, Two.Sdata, Three.Sdata, Four.Sdata, Five.Sdata, 0,  fd, 0, 
		Find_Max(One.SdataMax, Two.SdataMax, Three.SdataMax, Four.SdataMax, Five.SdataMax, Signal.SdataMax)
		, 'A', 'f', Signal.Skeys);

	Graph3.DrawSix(Signal.data, One.Ndata, Two.Ndata, Three.Ndata, Four.Ndata, Five.Ndata, 0, N/fd
		,Find_Min(One.NdataMin, Two.NdataMin, Three.NdataMin, Four.NdataMin, Five.NdataMin, Signal.NdataMin)
		,Find_Max(One.NdataMax, Two.NdataMax, Three.NdataMax, Four.NdataMax, Five.NdataMax, Signal.NdataMax)
		, 'A', 't', Signal.keys);
	
	UpdateData(false);
}
