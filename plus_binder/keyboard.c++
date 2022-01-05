//=================================================
// File: main.cpp
// Written By: Blanket
// 
// Purpose: keyboard.h
// 
//=================================================

#include <thread>
#include "keyboard.h"

HHOOK* hkKbdHook = nullptr;


LRESULT CALLBACK CallbackKBDLL( int nCode, WPARAM wParam, LPARAM lParam ) {

	auto pKbdll = ( KBDLLHOOKSTRUCT* )lParam;

	// save/set our key bind data
	{
		VirtualKey_t* pBindableKey = &n_KeyBoard::VirtualKeys[ pKbdll->vkCode ];

		pBindableKey->m_bWasDown = pBindableKey->m_bIsDown;
		pBindableKey->m_bIsDown = wParam == WM_KEYDOWN && wParam != WM_KEYUP;


		for ( const auto pFuncPtr : pBindableKey->m_KeyCallbacks )
			pFuncPtr( pKbdll->vkCode );
	}


	return CallNextHookEx( *hkKbdHook, nCode, wParam, lParam );
}


void n_KeyBoard::Initialize( ) {
	// ensure we dont initialize more than once
	if ( hkKbdHook )
		return;
	hkKbdHook = ( HHOOK* )malloc( sizeof( HHOOK ) );

	auto ThreadedInitialize = [ ]( ) {

		// Initialize Key Hook
		*hkKbdHook = SetWindowsHookEx( WH_KEYBOARD_LL, ( HOOKPROC )CallbackKBDLL, 0, 0 );

		// Message loop
		{
			MSG* pMsg = nullptr; // we dont malloc here as getmessage should (hopefully) do that?

			while ( 1 ) {	/* use global for exit here so we dont run forever */
				GetMessage( pMsg, nullptr, NULL, NULL );
				TranslateMessage( pMsg );
				DispatchMessage( pMsg );
			}
		}
	};

	std::thread thdMsgLoop( ThreadedInitialize );
	thdMsgLoop.detach( );
}