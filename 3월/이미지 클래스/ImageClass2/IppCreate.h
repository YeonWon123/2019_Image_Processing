
// IppCreate.h : IppCreate ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CIppCreateApp:
// �� Ŭ������ ������ ���ؼ��� IppCreate.cpp�� �����Ͻʽÿ�.
//

class CIppCreateApp : public CWinApp
{
public:
	CIppCreateApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CIppCreateApp theApp;
