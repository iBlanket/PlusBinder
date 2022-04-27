#pragma once

#include <functional>

namespace plus_binder {

	class CKeyboard;

	struct VirtualKey_t {
		VirtualKey_t() = default;

		__forceinline uintptr_t GetLastWParam() {
			return this->m_uLastWParam;
		}

	private:
		uint32_t m_uLastWParam{};

		std::function<void(VirtualKey_t /* this key */, uint32_t /* vkCode */)> m_KeyCallback;

		friend class CKeyboard;
	};

} // namespace plus_binder