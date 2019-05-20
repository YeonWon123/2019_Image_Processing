// ImageFrameWndManager.cpp : implementation file
//

#include "StdAfx.h"
#include "ImageFrameWndManager.h"
#include "ImageFrameWnd.h"

CImageFrameWndManager::CImageFrameWndManager(void)
{
}

CImageFrameWndManager::~CImageFrameWndManager(void)
{
	CloseAll();
}

void CImageFrameWndManager::Add(CImageFrameWnd* pImageWnd)
{
	m_vpImageWnd.push_back(pImageWnd);
}

CImageFrameWnd* CImageFrameWndManager::FindWnd(const char* name)
{
	CImageFrameWnd* ret = NULL;
	if (name)
	{
		for (unsigned int i=0 ; i<m_vpImageWnd.size() ; i++)
		{
			CString wName;
			m_vpImageWnd.at(i)->GetWindowText(wName);
			if (wName == name) // 일치하는 문자열 발견
			{
				ret = m_vpImageWnd.at(i);
				break;
			}
		}
	}
	return ret;
}

void CImageFrameWndManager::Delete(CImageFrameWnd* pImageWnd)
{
 	for (unsigned int i=0 ; i<m_vpImageWnd.size() ; i++)
	{
		if (m_vpImageWnd.at(i) == pImageWnd)
		{
			delete m_vpImageWnd.at(i);
			m_vpImageWnd.erase(m_vpImageWnd.begin()+i);
			break;
		}
	}
}

void CImageFrameWndManager::CloseAll()
{
 	for (int i=m_vpImageWnd.size()-1 ; i>=0 ; i--)
 	{
		delete m_vpImageWnd.at(i);
		m_vpImageWnd.erase(m_vpImageWnd.begin()+i);
 	}
}

CImageFrameWndManager gImageFrameWndManager;
void ShowImage(const CByteImage& input, const char *name)
{
	CImageFrameWnd *pImageWnd = gImageFrameWndManager.FindWnd(name);
	if (pImageWnd) // 같은 이름의 창 발견
	{
		pImageWnd->GetImageView().SetImage(input);	 // 기존 창의 영상 갱신
		pImageWnd->GetImageView().Invalidate(false); // 화면 갱신 함수 호출
	}
	else // 같은 이름의 창이 없을 시 새 창을 생성하고 배열에 추가
	{
		gImageFrameWndManager.Add(new CImageFrameWnd(input, name));
	}
}

void CloseImage(const char* name)
{
	CImageFrameWnd* pImageWnd = gImageFrameWndManager.FindWnd(name);
	gImageFrameWndManager.Delete(pImageWnd);
}

void CloseAllImages()
{
	gImageFrameWndManager.CloseAll();
}
