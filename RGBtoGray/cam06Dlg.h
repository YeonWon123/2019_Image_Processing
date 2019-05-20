// cam06Dlg.h : 

#pragma once

// Ccam06Dlg
class Ccam06Dlg : public CDialog
{
// Konstruktion
public:
	Ccam06Dlg(CWnd* pParent = NULL);	

// Dialogfelddaten
	enum { IDD = IDD_cam06_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	

// Implementation
protected:
HWND hMyWindow;

protected:
	HICON m_hIcon;

	void RotateImage(void);

	// Generierte Funktionen f? die Meldungstabellen
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
