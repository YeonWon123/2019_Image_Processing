
// WebCAM01Dlg.h : header file
//

#pragma once


// CWebCAM01Dlg dialog
class CWebCAM01Dlg : public CDialogEx
{
// Construction
public:
	CWebCAM01Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_WEBCAM01_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
HWND hMyWindow;

protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
