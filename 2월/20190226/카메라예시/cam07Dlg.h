// cam07Dlg.h : 

#pragma once

// Ccam07Dlg
class Ccam07Dlg : public CDialog
{
// Konstruktion
public:
	Ccam07Dlg(CWnd* pParent = NULL);	

// Dialogfelddaten
	enum { IDD = IDD_cam07_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	

// Implementation
protected:
HWND hMyWindow;

protected:
	HICON m_hIcon;

	void RotateImage(void);

	// Generierte Funktionen für die Meldungstabellen
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
