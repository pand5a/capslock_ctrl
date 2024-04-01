
// capslock_ctrlDlg.h : 头文件
//

#pragma once


// Ccapslock_ctrlDlg 对话框
class Ccapslock_ctrlDlg : public CDialogEx
{
// 构造
public:
	Ccapslock_ctrlDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CAPSLOCK_CTRL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	NOTIFYICONDATA m_notifyIcon;  //系统托盘类

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:


public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnClose();

	afx_msg LRESULT OnSystemtray(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedCancel();
	afx_msg void OnDestroy();
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);

	// 菜单消息
	afx_msg void OnExit();
	afx_msg void OnAbout();
};
