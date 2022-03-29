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

void CKeyboard::OnLowLevelHook(int nCode, WPARAM wParam, LPARAM lParam) {

	/* lock mutex's up here */
	std::scoped_lock(m_KeyMutex);

	/* get KBDLLHOOKSTRUCT info */
	auto pKbdll = reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam);

	VirtualKey_t* pBindableKey = &m_VirtualKeys[pKbdll->vkCode];

	/* update key states */
	pBindableKey->m_bWasDown = pBindableKey->m_bIsDown;
	pBindableKey->m_bIsDown = wParam == WM_KEYDOWN && wParam != WM_KEYUP;

	/* call all our callbacks */
	if (pBindableKey->m_KeyCallback) // this shouldnt ever be hit
		pBindableKey->m_KeyCallback(*pBindableKey, pKbdll->vkCode);
}

VirtualKey_t CKeyboard::GetKeyInfo(const std::uint32_t uVkCode) {
	std::scoped_lock(m_KeyMutex);
	return m_VirtualKeys[uVkCode];
}

void CKeyboard::SetCallback(const std::uint32_t uVkCode, const std::function<void(VirtualKey_t, std::uint32_t)>& pCallbackFunction) {
	std::scoped_lock(m_KeyMutex);
	m_VirtualKeys[uVkCode].m_KeyCallback = pCallbackFunction;
}


LRESULT CALLBACK WinCallbackKBDLL(int nCode, WPARAM wParam, LPARAM lParam) {
	CKeyboard::Get().OnLowLevelHook(nCode, wParam, lParam);

	/* */
	return CallNextHookEx(hkKbdHook, nCode, wParam, lParam);
}

void CKeyboard::Initialize() {
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