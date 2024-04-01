
// capslock_ctrlDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "capslock_ctrl.h"
#include "capslock_ctrlDlg.h"
#include "afxdialogex.h"

#include <Windows.h>
#include <WinUser.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define   WM_SYSTEMTRAY WM_USER+5


// Hook 系列 BEGIN
HHOOK _hook;
KBDLLHOOKSTRUCT kbdStruct;

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {

	if (nCode == HC_ACTION) {
		// CString str;

		kbdStruct = *((KBDLLHOOKSTRUCT*)lParam);
		if (kbdStruct.vkCode == VK_CAPITAL) {
			UINT8 keyStatus = kbdStruct.flags & 0x80;

			if (wParam == WM_KEYDOWN) {
				keybd_event(VK_CONTROL, 0, 0, 0);
			}


			if (wParam == WM_KEYUP) {
				keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
			}

			return TRUE;
		}

	}

	return CallNextHookEx(_hook, nCode, wParam, lParam);
}

void SetHook()
{
	if (!(_hook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0))) {
		MessageBox(NULL, L"Failed to install hook!", L"Error", MB_ICONERROR);
	}
}


void ReleaseHook()
{
	UnhookWindowsHookEx(_hook);
}


// Hook 系列 END



// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// Ccapslock_ctrlDlg 对话框



Ccapslock_ctrlDlg::Ccapslock_ctrlDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CAPSLOCK_CTRL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Ccapslock_ctrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Ccapslock_ctrlDlg, CDialogEx)
	ON_MESSAGE(WM_SYSTEMTRAY, &Ccapslock_ctrlDlg::OnSystemtray)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &Ccapslock_ctrlDlg::OnBnClickedOk)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDCANCEL, &Ccapslock_ctrlDlg::OnBnClickedCancel)
	ON_COMMAND(ID_EXIT, &Ccapslock_ctrlDlg::OnExit)
	ON_COMMAND(ID_ABOUT, &Ccapslock_ctrlDlg::OnAbout)
	ON_WM_DESTROY()
	ON_WM_CREATE()
	ON_WM_WINDOWPOSCHANGING()
END_MESSAGE_MAP()


// Ccapslock_ctrlDlg 消息处理程序

BOOL Ccapslock_ctrlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//设置系统托盘
	m_notifyIcon.cbSize = sizeof(NOTIFYICONDATA);
	//NotifyIcon.hIcon=AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_notifyIcon.hIcon = m_hIcon;  //上面那句也可以
	m_notifyIcon.hWnd = m_hWnd;
	lstrcpy(m_notifyIcon.szTip, _T(""));
	m_notifyIcon.uCallbackMessage = WM_SYSTEMTRAY;
	m_notifyIcon.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	Shell_NotifyIcon(NIM_ADD, &m_notifyIcon);   //添加系统托盘


	// 设置hook
	SetHook();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Ccapslock_ctrlDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Ccapslock_ctrlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR Ccapslock_ctrlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Ccapslock_ctrlDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();

}

void Ccapslock_ctrlDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	this->ShowWindow(HIDE_WINDOW);
	//ReleaseHook();
	//CDialogEx::OnClose();
}

afx_msg LRESULT Ccapslock_ctrlDlg::OnSystemtray(WPARAM wParam, LPARAM lParam)
{
	//wParam接收的是图标的ID，而lParam接收的是鼠标的行为
	//  if(wParam!=IDR_MAINFRAME)     
	//      return    1;     
	switch (lParam)
	{
		//右键起来时弹出快捷菜单
		case  WM_RBUTTONDOWN: {

			CMenu menuexit;
			//menu.LoadMenuW(IDR_MENU1);//加载菜单资源
			menuexit.LoadMenu(IDR_POPMENU);
			CMenu *pPopup = menuexit.GetSubMenu(0);
			CPoint mypoint;
			GetCursorPos(&mypoint);
			//ClientToScreen(&mypoint);//将客户区坐标转换为屏幕坐标
			SetForegroundWindow();
			PostMessage(WM_NULL, 0, 0);


			//显示右键菜单，由视类窗口拥有。
			pPopup->TrackPopupMenu(TPM_LEFTALIGN, mypoint.x, mypoint.y, this);
		}
		break;
	}
	return 0;
}


void Ccapslock_ctrlDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}



void Ccapslock_ctrlDlg::OnDestroy()
{

	Shell_NotifyIcon(NIM_DELETE, &m_notifyIcon);//消除托盘图标
	CDialogEx::OnDestroy();
}



void Ccapslock_ctrlDlg::OnWindowPosChanging(WINDOWPOS* lpwndpos)
{
	// 隐藏主窗口
	lpwndpos->flags &= ~SWP_SHOWWINDOW;
	CDialogEx::OnWindowPosChanging(lpwndpos);
}


void Ccapslock_ctrlDlg::OnExit()
{

	// 防止在退出之前还按着caps，导致caps替换的ctrl始终为按压状态，所以在退出时模拟一次ctrl up
	keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
	ReleaseHook();
	DestroyWindow();
}

void Ccapslock_ctrlDlg::OnAbout()
{
	CAboutDlg dlg;
	dlg.DoModal();
}


