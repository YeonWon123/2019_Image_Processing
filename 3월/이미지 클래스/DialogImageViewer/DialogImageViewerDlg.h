
// DialogImageViewerDlg.h : ��� ����
//

#pragma once

#include "imageSrc\ImageFrameWnd.h"

// CDialogImageViewerDlg ��ȭ ����
class CDialogImageViewerDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CDialogImageViewerDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOGIMAGEVIEWER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();

	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedButtonViewImage();
	afx_msg void OnBnClickedButtonCloseImage();

protected:
	CImageFrameWnd* m_pImageWnd;
public:
	afx_msg void OnBnClickedButton2();
};
