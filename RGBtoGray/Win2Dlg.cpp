// Win2Dlg.cpp: 
// *** orgler electronics "Bozen South Tyrol Italy" *** 

#include "stdafx.h"
#include "cam06.h"
#include "Win2Dlg.h"

#define ImageX 600  
#define ImageY 480

extern unsigned char arrImage1 [4 * ImageX * ImageY];	
extern unsigned char arrImage2 [4 * ImageX * ImageY];	

extern BITMAPINFO	bmpDestination;
int iFlagGray;

int rectFlag;
CRect RectWin2;

// CWin2Dlg

IMPLEMENT_DYNAMIC(CWin2Dlg, CDialog)

CWin2Dlg::CWin2Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWin2Dlg::IDD, pParent)
{
}

CWin2Dlg::~CWin2Dlg()
{
}

void CWin2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CWin2Dlg, CDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUT_COL_GRAY, &CWin2Dlg::OnBnClickedButColGray)
END_MESSAGE_MAP()




void CWin2Dlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	if(rectFlag==0)
	{
	GetClientRect(&RectWin2);
	rectFlag=1;
	}

	int imgx = bmpDestination.bmiHeader.biWidth;
    int imgy = bmpDestination.bmiHeader.biHeight;

	// copy memory arrImage2 to window 
	SetDIBitsToDevice((HDC) dc , 0, 0, imgx, imgy, 0, 0, 0, imgy, arrImage2, &bmpDestination, DIB_RGB_COLORS);
}


void CWin2Dlg::OnBnClickedButColGray()
{
 if(iFlagGray==0) iFlagGray=1; else iFlagGray=0;
}
