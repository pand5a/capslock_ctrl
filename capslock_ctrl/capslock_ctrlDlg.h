
// capslock_ctrlDlg.h : ͷ�ļ�
//

#pragma once


// Ccapslock_ctrlDlg �Ի���
class Ccapslock_ctrlDlg : public CDialogEx
{
// ����
public:
	Ccapslock_ctrlDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CAPSLOCK_CTRL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	NOTIFYICONDATA m_notifyIcon;  //ϵͳ������

	// ���ɵ���Ϣӳ�亯��
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

	// �˵���Ϣ
	afx_msg void OnExit();
	afx_msg void OnAbout();
};
