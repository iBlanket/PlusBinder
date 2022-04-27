//=================================================
// File: main.cpp
// Written By: Blanket
// 
// Purpose: keyboard.h
// 
//=================================================

#include <thread>
#include "keyboard.h"

HHOOK hkKbdHook = 0;

void plus_binder::CKeyboard::OnLowLevelHook(uint32_t nCode, WPARAM wParam, LPARAM lParam) {

	/* lock mutex's up here */
	std::scoped_lock(m_KeyMutex);

	/* get KBDLLHOOKSTRUCT info */
	auto pKbdll = reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam);

	VirtualKey_t* pBindableKey = &m_VirtualKeys[pKbdll->vkCode];

	/* update key states */
	pBindableKey->m_uLastWParam = wParam;

	/* call all our callbacks */
	if (pBindableKey->m_KeyCallback) // this shouldnt ever be hit
		pBindableKey->m_KeyCallback(*pBindableKey, pKbdll->vkCode);
}

LRESULT CALLBACK WinCallbackKBDLL(int nCode, WPARAM wParam, LPARAM lParam) {
	plus_binder::CKeyboard::Get().OnLowLevelHook(nCode, wParam, lParam);

	/* */
	return CallNextHookEx(hkKbdHook, nCode, wParam, lParam);
}


void plus_binder::CKeyboard::Initialize() {
	/* ensure we dont initialize more than once */
	if (hkKbdHook)
		return;

	/* yes, theres no way to safely exit this thread, it shouldnt be a significant issue though. */
	std::thread([]() {

		/* initialize key hook */
		hkKbdHook = SetWindowsHookEx(WH_KEYBOARD_LL, reinterpret_cast<HOOKPROC>(WinCallbackKBDLL), 0, 0);

		/* message loop */
		{
			MSG* pMsg = nullptr;

			while (1) {
				GetMessage(pMsg, nullptr, NULL, NULL);
				TranslateMessage(pMsg);
				DispatchMessage(pMsg);
			}
		}
		}
	).detach();
}