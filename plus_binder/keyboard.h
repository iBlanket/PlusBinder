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
	//==============================================================
	// Purpose: Multi-Thread & Initialize the keyboard handler
	//==============================================================
	void Initialize( );


	//==============================================================
	// Purpose: Update m_VirtualKeys
	//==============================================================
	void OnLowLevelHook( int nCode, WPARAM wParam, LPARAM lParam );


	//==============================================================
	// Purpose: Thread safe get information about keys [ COPY ]
	//==============================================================
	VirtualKey_t GetKeyInfo( const std::uint32_t uVkCode );


	//==============================================================
	// Purpose: Set the key callback
	//==============================================================
	void SetCallback( const std::uint32_t uVkCode, const std::function<void( VirtualKey_t, std::uint32_t )>& pCallbackFunction );


private:
	std::mutex m_KeyMutex;

	VirtualKey_t m_VirtualKeys[ 256 ]{ };
};

