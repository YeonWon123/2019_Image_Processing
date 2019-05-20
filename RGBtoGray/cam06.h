// cam06.h : Hauptheaderdatei f? die PROJECT_NAME-Anwendung
//

#pragma once

#ifndef __AFXWIN_H__
	#error "\"stdafx.h\" vor dieser Datei f? PCH einschlie?n"
#endif

#include "resource.h"		// Hauptsymbole


// Ccam06App:
// Siehe cam06.cpp f? die Implementierung dieser Klasse
//

class Ccam06App : public CWinApp
{
public:
	Ccam06App();

// ?erschreibungen
	public:
	virtual BOOL InitInstance();

// Implementierung

	DECLARE_MESSAGE_MAP()
};

extern Ccam06App theApp;