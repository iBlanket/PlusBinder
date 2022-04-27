//=================================================
// File: keyboard.h
// Written By: Blanket
// 
// Purpose: Handling & processing keyboard info & data
// 
//=================================================

#pragma once
#include <iostream>
#include <mutex>

#include <Windows.h>

#include "singleton.h"
#include "virtual_key.h"

namespace plus_binder {


	class CKeyboard : public CPlusBinderSingleton<CKeyboard> {
	public:

		//===========================================================================================
		// Purpose	: Multi-Thread & Initialize the keyboard handler
		// Input	: None
		//===========================================================================================
		void Initialize();


		//===========================================================================================
		// Purpose	: Update m_VirtualKeys
		// Input	: nCode - vkCode, wParam - WPARAM, lParam - LPARAM
		//===========================================================================================
		void OnLowLevelHook(uint32_t nCode, WPARAM wParam, LPARAM lParam);


		//===========================================================================================
		// Purpose	: Get / Copy Key info
		// Input	: uVkCode - index / key code to get data for
		//===========================================================================================
		__forceinline VirtualKey_t GetKeyInfo(const uint32_t& uVkCode) {
			std::scoped_lock(m_KeyMutex);
			return m_VirtualKeys[uVkCode];
		}


		//===========================================================================================
		// Purpose	: Set the key callback
		// Input	: uVkCode - key code for callback, pCallbackFunction - callback
		//===========================================================================================
		__forceinline void SetCallback(const uint32_t& uVkCode, const std::function<void(VirtualKey_t, uint32_t)>& pCallbackFunction) {
			std::scoped_lock(m_KeyMutex);
			m_VirtualKeys[uVkCode].m_KeyCallback = pCallbackFunction;
		}



	private:
		/* the main purpose for this is the callback std::function, we dont want it being accessed from multiple threads in any weird ways */
		std::mutex m_KeyMutex{};

		VirtualKey_t m_VirtualKeys[256]{ };
	};


} // namespace plus_binder