# Global key binding written in C++

i was originally very happy with this project, im not having much fun with it and im sorry if the code quality in recent updates has cause a decrease in this project. this is the last update to clear all stuff up before a break from this. if you want to contribute the todo list is as follows.

TODO:
Flag management
Remove singletons
Fix thread safety being aids
Move everything to 1 header to increase ease of use.
inline some functions.
get rid of the endless thread.

## Usage Examples
 - Copy singleton.h, keyboard.h, vk_bind.h, and keyboard.c++ to your project.

### Initializing Key Manager

```C++
int main(){
// initializes keyboard hook and message loop (:
 CKeyboard::Get().Initialize();
}
```
### Key States Callbacks
```C++

void KeyDown(VirtualKey_t VkKey, std::uint32_t uVkCode ) {
// see main.c++ and vk_bind.h
}

void InitializeCallbacks(){
 // make sure you initialize keyboard before doing this
 // GetKey is thread safe now (:
 auto vkInfo = CKeyboard::Get().SetCallback(VK_OUR_KEY, KeyDown);
}
```

### Checking Key States
```C++
// see main.c++ for more examples and usage of key states, down and was down (:
// outside of callbacks only use is down
CKeyboard::Get().GetKeyInfo(VK_OUR_KEY).m_bIsDown; // 

```
## Code Style
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
 
 // functions are documented via comment "headers" where they are declared. ex.
 
 //================================================
 // Purpose: Show how functions are documented
 // uArg1: Meaningless argument 
 // Returns: 0
 //================================================
 void MyFunction(const std::uint32_t uArg1);
 
 ```
