// cam07Dlg.cpp 
// *** orgler electronics "Bozen South Tyrol Italy" *** 

#include "stdafx.h"
#include "cam07.h"
#include "cam07Dlg.h"
#include "Win2Dlg.h"

#include <vfw.h>  //!!!! insert vfw32.lib in project cam_properties configuration Linker-Input 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern int iFilterValue;

#define ImageX 600  
#define ImageY 480

unsigned char arrImage1 [4 * ImageX * ImageY];  // original data	
unsigned char arrImage2 [4 * ImageX * ImageY];	// data for WIN2
unsigned char arrImage3 [4 * ImageX * ImageY];	// data from arrImage2 after a low pass filter 
unsigned int  arrImage4[4 * ImageX * ImageY];   // memory for low pass filter
                                                // must be integer  
unsigned int iNewValue;
unsigned int iOldValue;


BITMAPINFO	bmpSource;
BITMAPINFO	bmpDestination;
CBitmap capture_map; 
int iBitmapFlag=0;

CWin2Dlg  dlgWin2;   // like a pointer to CWin2Dlg class
extern CRect RectWin2;


Ccam07Dlg::Ccam07Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(Ccam07Dlg::IDD, pParent)
{
    bmpSource.bmiHeader.biSize			= sizeof(BITMAPINFOHEADER);
    bmpSource.bmiHeader.biWidth			= ImageX;
    bmpSource.bmiHeader.biHeight		= ImageY;
    bmpSource.bmiHeader.biPlanes		= 1;
    bmpSource.bmiHeader.biBitCount		= 32;
    bmpSource.bmiHeader.biCompression	= BI_RGB;
    bmpSource.bmiHeader.biSizeImage		= 0;
    bmpSource.bmiHeader.biXPelsPerMeter	= 0;
    bmpSource.bmiHeader.biYPelsPerMeter	= 0;
    bmpSource.bmiHeader.biClrUsed		= 0;
    bmpSource.bmiHeader.biClrImportant	= 0;

    bmpDestination = bmpSource;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Ccam07Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Ccam07Dlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_TIMER()
END_MESSAGE_MAP()



BOOL Ccam07Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			
	SetIcon(m_hIcon, FALSE);

	// TODO: 

	hMyWindow = capCreateCaptureWindow("handle", WS_CHILD | WS_VISIBLE, 0, 0, ImageX, ImageY, this->m_hWnd, 1);

    // connect the driver with the webcam 
	BOOL xx = capDriverConnect(hMyWindow,0);
    if(xx == false)
	{
		AfxMessageBox("Webcam not found ",0,0);
		return false;
	}

   //==== create and shows the second dialog window =========
	dlgWin2.Create(IDD_WIN2,this);
	dlgWin2.ShowWindow(SW_SHOW);

	//----------- Set the Timer to grab new images -----------
	SetTimer(1,40,0);

	return TRUE;  
}

void Ccam07Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); 

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR Ccam07Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void Ccam07Dlg::OnTimer(UINT_PTR nIDEvent)
{
    if(nIDEvent == 1)
	{

	capGrabFrame(hMyWindow);  // grab a new image 

	CDC *dc = GetDC(); 
	CDC     capture_dc;

	if(iBitmapFlag==0)  // create a Bitmap only once 
	{
	capture_map.CreateCompatibleBitmap( dc , ImageX, ImageY ); 
	iBitmapFlag=1;
	}

	capture_dc.CreateCompatibleDC( dc ); 
	capture_dc.SelectObject( &capture_map ); 
	capture_dc.BitBlt( 0, 0, ImageX, ImageY, dc, 0, 0, SRCCOPY );  //copy image to bitmap 

	//======= copy the image from bitmap to memory (arrImage1)===============
	LPBYTE lpBits = arrImage1;   // pointer 
    int xx,err;
	xx = GetDIBits(capture_dc, capture_map, 0, ImageY, lpBits, &bmpSource, DIB_RGB_COLORS);
	if(xx == 0)   err = GetLastError(); // only for debug
 
	capture_dc.DeleteDC();
	ReleaseDC(dc);

   //============= copy arrImage1 to arrImage2  with grayscale =================
	 int iLine,iCol,index1,index2;
	 int grayred,graygreen,grayblue,grayall;

    	index2  = 0;       // the destination image starts always with index zero
        iLine  = 0;
		while(iLine < ImageY)
		{
        iCol=0;
		while(iCol < ImageX)
		{
		index1 = ((iLine * ImageX) + iCol);
		index1 *= 4;

		grayblue  = arrImage1[index1];     // add 11%
		grayblue *= 28;
		graygreen = arrImage1[index1+1];   // add 59%
		graygreen *= 151;
		grayred   = arrImage1[index1+2];   // add 30%
        grayred  *= 77;
		grayall = grayblue + graygreen + grayred;
		grayall /= 256;
  
		arrImage2[index2++] = grayall;  // blue
		arrImage2[index2++] = grayall;  // green
		arrImage2[index2++] = grayall;  // red 
		arrImage2[index2++] = 0;        // this byte is not used
		iCol++;
		}
		iLine++;
		}

    //========== low pass filter ======================
	
    	index2  = 0;       // the destination image starts always with index zero
        iLine  = 0;
		while(iLine < ImageY)
		{
        iCol=0;
		while(iCol < ImageX)
		{
		index1 = ((iLine * ImageX) + iCol);
		index1 *= 4;
        iNewValue = arrImage2[index1];
		iNewValue *= 256;

		iOldValue = arrImage4[index2];
	    iNewValue = iOldValue - (iOldValue/iFilterValue) + iNewValue/iFilterValue;
        arrImage4[index2]    =  iNewValue; 
        arrImage4[index2+1]  =  iNewValue;
        arrImage4[index2+2]  =  iNewValue;
	    iNewValue /= 256;
		
		arrImage3[index2]    =  iNewValue; 
        arrImage3[index2+1]  =  iNewValue;
        arrImage3[index2+2]  =  iNewValue;
        index2 += 4;
	    iCol++;
		}
		iLine++;
		}

  	dlgWin2.InvalidateRect(RectWin2,false); // repaint WIN2  with arrImage2
	}
	CDialog::OnTimer(nIDEvent);
}
