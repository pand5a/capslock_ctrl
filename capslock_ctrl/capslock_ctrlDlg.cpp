
// capslock_ctrlDlg.cpp : ʵ���ļ�
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


// Hook ϵ�� BEGIN
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


// Hook ϵ�� END



// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// Ccapslock_ctrlDlg �Ի���



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


// Ccapslock_ctrlDlg ��Ϣ�������

BOOL Ccapslock_ctrlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	//����ϵͳ����
	m_notifyIcon.cbSize = sizeof(NOTIFYICONDATA);
	//NotifyIcon.hIcon=AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_notifyIcon.hIcon = m_hIcon;  //�����Ǿ�Ҳ����
	m_notifyIcon.hWnd = m_hWnd;
	lstrcpy(m_notifyIcon.szTip, _T(""));
	m_notifyIcon.uCallbackMessage = WM_SYSTEMTRAY;
	m_notifyIcon.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	Shell_NotifyIcon(NIM_ADD, &m_notifyIcon);   //���ϵͳ����


	// ����hook
	SetHook();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void Ccapslock_ctrlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR Ccapslock_ctrlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Ccapslock_ctrlDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();

}

void Ccapslock_ctrlDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	this->ShowWindow(HIDE_WINDOW);
	//ReleaseHook();
	//CDialogEx::OnClose();
}

afx_msg LRESULT Ccapslock_ctrlDlg::OnSystemtray(WPARAM wParam, LPARAM lParam)
{
	//wParam���յ���ͼ���ID����lParam���յ���������Ϊ
	//  if(wParam!=IDR_MAINFRAME)     
	//      return    1;     
	switch (lParam)
	{
		//�Ҽ�����ʱ������ݲ˵�
		case  WM_RBUTTONDOWN: {

			CMenu menuexit;
			//menu.LoadMenuW(IDR_MENU1);//���ز˵���Դ
			menuexit.LoadMenu(IDR_POPMENU);
			CMenu *pPopup = menuexit.GetSubMenu(0);
			CPoint mypoint;
			GetCursorPos(&mypoint);
			//ClientToScreen(&mypoint);//���ͻ�������ת��Ϊ��Ļ����
			SetForegroundWindow();
			PostMessage(WM_NULL, 0, 0);


			//��ʾ�Ҽ��˵��������ര��ӵ�С�
			pPopup->TrackPopupMenu(TPM_LEFTALIGN, mypoint.x, mypoint.y, this);
		}
		break;
	}
	return 0;
}


void Ccapslock_ctrlDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}



void Ccapslock_ctrlDlg::OnDestroy()
{

	Shell_NotifyIcon(NIM_DELETE, &m_notifyIcon);//��������ͼ��
	CDialogEx::OnDestroy();
}



void Ccapslock_ctrlDlg::OnWindowPosChanging(WINDOWPOS* lpwndpos)
{
	// ����������
	lpwndpos->flags &= ~SWP_SHOWWINDOW;
	CDialogEx::OnWindowPosChanging(lpwndpos);
}


void Ccapslock_ctrlDlg::OnExit()
{

	// ��ֹ���˳�֮ǰ������caps������caps�滻��ctrlʼ��Ϊ��ѹ״̬���������˳�ʱģ��һ��ctrl up
	keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
	ReleaseHook();
	DestroyWindow();
}

void Ccapslock_ctrlDlg::OnAbout()
{
	CAboutDlg dlg;
	dlg.DoModal();
}


