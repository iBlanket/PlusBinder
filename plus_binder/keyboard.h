//=================================================
// File: keyboard.h
// Written By: Blanket
// 
// Purpose: Handling & processing keyboard info & data
// 
//=================================================

#pragma once
#include <iostream>
#include <Windows.h>
#include <mutex>

#include "vk_bind.h"
#include "singleton.h"


class CKeyboard : public CSingleton<CKeyboard> {
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
	void OnLowLevelHook(int nCode, WPARAM wParam, LPARAM lParam);


	//===========================================================================================
	// Purpose	: Get / Copy Key info
	// Input	: uVkCode - index / key code to get data for
	//===========================================================================================
	VirtualKey_t GetKeyInfo(const std::uint32_t uVkCode);


	//===========================================================================================
	// Purpose	: Set the key callback
	// Input	: uVkCode - key code for callback, pCallbackFunction - callback
	//===========================================================================================
	void SetCallback(const std::uint32_t uVkCode, const std::function<void(VirtualKey_t, std::uint32_t)>& pCallbackFunction);


private:
	/* the main purpose for this is the callback std::function, we dont want it being accessed from multiple threads in any weird ways */
	std::mutex m_KeyMutex{};

	VirtualKey_t m_VirtualKeys[256]{ };
};

