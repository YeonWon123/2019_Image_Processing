#pragma once

#include "MyImage.h"

// CImageView view

class CImageView : public CView
{
public:
	CImageView();
	virtual ~CImageView();
	BOOL CreateEx(CWnd* pWnd);
	void SetImage(const CByteImage& input);

protected:
	virtual void OnDraw(CDC* pDC);

	CByteImage	m_image;
};


