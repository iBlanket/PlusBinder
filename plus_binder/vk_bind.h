//=================================================
// File: vk_bind.h
// Written By: Blanket
// 
// Purpose: Representing Virtual Key Data
// 
//=================================================


#pragma once
#include <vector>
#include <functional>
#include <bitset>

struct VirtualKey_t {
	//========================================================================================================
	// Constructor
	//========================================================================================================
	VirtualKey_t( ) = default;


	//enum e_KeyFlag {
	//	KEY_DOWN = 0,
	//	KEY_WAS_DOWN
	//};
	//std::bitset<4> m_fKeyData{ };

	bool m_bIsDown = false;
	bool m_bWasDown = false;

	std::function<void( VirtualKey_t /* this */, std::uint32_t /* vkCode */ )> m_KeyCallback;
};
