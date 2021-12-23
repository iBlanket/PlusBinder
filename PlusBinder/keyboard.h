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
#include "vk_bind.h"

namespace n_KeyBoard {

	//==============================================================
	// Purpose: Storing data on all keys
	//==============================================================
	inline VirtualKey_t VirtualKeys[ 256 ]{ };


	//==============================================================
	// Purpose: Multi-Thread & Initialize the keyboard handler
	//==============================================================
	void Initialize( );
}

