
// capslock_ctrl.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Ccapslock_ctrlApp: 
// �йش����ʵ�֣������ capslock_ctrl.cpp
//

class Ccapslock_ctrlApp : public CWinApp
{
public:
	Ccapslock_ctrlApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Ccapslock_ctrlApp theApp;