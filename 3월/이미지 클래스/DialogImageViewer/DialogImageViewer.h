
// DialogImageViewer.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CDialogImageViewerApp:
// �� Ŭ������ ������ ���ؼ��� DialogImageViewer.cpp�� �����Ͻʽÿ�.
//

class CDialogImageViewerApp : public CWinApp
{
public:
	CDialogImageViewerApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CDialogImageViewerApp theApp;