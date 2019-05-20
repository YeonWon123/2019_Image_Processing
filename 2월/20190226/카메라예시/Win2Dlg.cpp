// Win2Dlg.cpp: 
// *** orgler electronics "Bozen South Tyrol Italy" *** 

#include "stdafx.h"
#include "cam07.h"
#include "Win2Dlg.h"

#define ImageX 600  
#define ImageY 480

extern unsigned char arrImage1 [4 * ImageX * ImageY];	
extern unsigned char arrImage2 [4 * ImageX * ImageY];	
extern unsigned char arrImage3 [4 * ImageX * ImageY];	

extern BITMAPINFO	bmpDestination;
int iFlagImage;
int iFilterValue = 8;  // default filter value

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
	ON_BN_CLICKED(IDC_BUT_MINUS, &CWin2Dlg::OnBnClickedButMinus)
	ON_BN_CLICKED(IDC_BUT_PLUS, &CWin2Dlg::OnBnClickedButPlus)
	ON_BN_CLICKED(IDC_BUT_FILTER_ON_OFF, &CWin2Dlg::OnBnClickedButFilterOnOff)
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
	if(iFlagImage==0)
	SetDIBitsToDevice((HDC) dc , 0, 0, imgx, imgy, 0, 0, 0, imgy, arrImage2, &bmpDestination, DIB_RGB_COLORS);
	else
	SetDIBitsToDevice((HDC) dc , 0, 0, imgx, imgy, 0, 0, 0, imgy, arrImage3, &bmpDestination, DIB_RGB_COLORS);

	if(iFlagImage==0) 
		 dc.TextOutA(130,505,"view Image2 original         ");
	else dc.TextOutA(130,505,"Image3 low pass filtered");
	CString strx;
	strx.Format(" %2d ",iFilterValue);
    dc.TextOutA(400,510,strx);
}



void CWin2Dlg::OnBnClickedButMinus()
{
if(iFilterValue >= 2) iFilterValue/= 2; 
}

void CWin2Dlg::OnBnClickedButPlus()
{
if(iFilterValue < 64) iFilterValue *= 2; 
}

void CWin2Dlg::OnBnClickedButFilterOnOff()
{
 if(iFlagImage==0) iFlagImage=1; else iFlagImage=0;
}
