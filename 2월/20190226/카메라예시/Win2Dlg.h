#pragma once

class CWin2Dlg : public CDialog
{
	DECLARE_DYNAMIC(CWin2Dlg)

public:
	CWin2Dlg(CWnd* pParent = NULL);   
	virtual ~CWin2Dlg();

	enum { IDD = IDD_WIN2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButMinus();
	afx_msg void OnBnClickedButPlus();
	afx_msg void OnBnClickedButFilterOnOff();
};
