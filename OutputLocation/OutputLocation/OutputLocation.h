
// OutputLocation.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// COutputLocationApp:
// �йش����ʵ�֣������ OutputLocation.cpp
//

class COutputLocationApp : public CWinApp
{
public:
	COutputLocationApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern COutputLocationApp theApp;