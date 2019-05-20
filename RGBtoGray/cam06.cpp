// cam06.cpp : Definiert das Klassenverhalten f? die Anwendung.
//

#include "stdafx.h"
#include "cam06.h"
#include "cam06Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ccam06App

BEGIN_MESSAGE_MAP(Ccam06App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// Ccam06App-Erstellung

Ccam06App::Ccam06App()
{
	// TODO: Hier Code zur Konstruktion einf?en
	// Alle wichtigen Initialisierungen in InitInstance positionieren
}


// Das einzige Ccam06App-Objekt

Ccam06App theApp;


// Ccam06App-Initialisierung

BOOL Ccam06App::InitInstance()
{
	CWinApp::InitInstance();

	// Standardinitialisierung
	// Wenn Sie diese Features nicht verwenden und die Größe
	// der ausf?rbaren Datei verringern m?hten, entfernen Sie
	// die nicht erforderlichen Initialisierungsroutinen.
	// Ändern Sie den Registrierungsschl?sel, unter dem Ihre Einstellungen gespeichert sind.
	// TODO: Ändern Sie diese Zeichenfolge entsprechend,
	// z.B. zum Namen Ihrer Firma oder Organisation.
	SetRegistryKey(_T("Vom lokalen Anwendungs-Assistenten generierte Anwendungen"));

	Ccam06Dlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: F?en Sie hier Code ein, um das Schlie?n des
		//  Dialogfelds ?er "OK" zu steuern
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: F?en Sie hier Code ein, um das Schlie?n des
		//  Dialogfelds ?er "Abbrechen" zu steuern
	}

	// Da das Dialogfeld geschlossen wurde, FALSE zur?kliefern, sodass wir die
	//  Anwendung verlassen, anstatt das Nachrichtensystem der Anwendung zu starten.
	return FALSE;
}
