// cam07.h : Hauptheaderdatei f�r die PROJECT_NAME-Anwendung
//

#pragma once

#ifndef __AFXWIN_H__
	#error "\"stdafx.h\" vor dieser Datei f�r PCH einschlie�en"
#endif

#include "resource.h"		// Hauptsymbole


// Ccam07App:
// Siehe cam07.cpp f�r die Implementierung dieser Klasse
//

class Ccam07App : public CWinApp
{
public:
	Ccam07App();

// �berschreibungen
	public:
	virtual BOOL InitInstance();

// Implementierung

	DECLARE_MESSAGE_MAP()
};

extern Ccam07App theApp;