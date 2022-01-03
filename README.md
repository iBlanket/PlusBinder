# Global key binding written in C++
 
 
 ```C++
 // Style:
 
 // Hungarian Notation for variables, eg.
 float flFloatingPoint;
 int iInteger;
 string szString;
 
 // Member variables are prefixxed with m_ ex.
 float m_flFloatingPoint;
 int m_iInteger;
 string m_szString;

 // Classes, Namespaces, Structs, and enums are PascalCase and use the following prefixes ex.
 class CClassName
 namespace n_NamespaceName
 struct MyStruct_t
 
 enum e_MyEnum{ // enum ex.
  SCREAMING_SNAKECASE = 1,
  SCREAMING_SNAKECASE2
 };
 
 // All functions are written in PascalCase ex.
 void MyFunction();
 
 ```


## Usage
 - Copy keyboard.h, vk_bind.h, and keyboard.c++ to your project.

### Initializing Key Manager

```C++
int main(){
// initializes keyboard hook and message loop (:
 n_KeyBoard::Initialize( );
}
```
### Key States Callbacks
```C++

void KeyDown( int vkKey ) {
	VirtualKey_t* vkBind = &n_KeyBoard::VirtualKeys[ vkKey ];

	// only call this in callbacks
	auto keyState = vkBind->GetKeyState( );


	switch ( keyState ) {
		case e_KeyState::KEY_HELD:
		{
			std::cout << "Key is held down\n";
		}
		break;

		case e_KeyState::KEY_PRESSED:
		{
			std::cout << "Key was pressed\n";
		}
		break;

		case e_KeyState::KEY_UNPRESSED:
		{
			std::cout << "Key was released\n";
		}
		break;
	}
}

void InitializeCallbacks(){
 // make sure you initialize keyboard before doing this
 // VirtualKeys is an array of all keys
 n_KeyBoard::VirtualKeys[ VK_LEFT ].OnKey.emplace_back( KeyDown );
}
```

### Checking Key States
```C++
// if youre in a keycallback use the above example ( vkBind->GetKeyState )
// however, if youre not, GetKeyState will most likely be incorrect due to the keyboard hook not being called twice upon a key being released lol.
// now for the actual example, if NOT in a key callback
 n_KeyBoard::VirtualKeys[ VK_LEFT ].m_bIsDown;
 // and
 n_KeyBoard::VirtualKeys[ VK_LEFT ].m_bWasDown; // was the key down or up the last time the keyhook was called.
```

- For more documentation simply read the code
