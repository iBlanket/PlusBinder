#pragma once

/*
	i just stole this, i named it plus binder singleton to avoid it messing with other singleton classes
	and im honestly debating not using singletons entirely. they arent needed and are really dumb
	im just afraid of changing this project too much.

	its a few changes to remove and i dont want this code to be used as much as i just want it to
	be referenced. i know its annoying to have useless things in open source libs but its not that\
	difficult to remove.
*/

namespace plus_binder {

	template <typename T>
	class CPlusBinderSingleton {
	protected:
		CPlusBinderSingleton() { }
		~CPlusBinderSingleton() { }

		CPlusBinderSingleton(const CPlusBinderSingleton&) = delete;
		CPlusBinderSingleton& operator=(const CPlusBinderSingleton&) = delete;

		CPlusBinderSingleton(CPlusBinderSingleton&&) = delete;
		CPlusBinderSingleton& operator=(CPlusBinderSingleton&&) = delete;
	public:
		__forceinline static T& Get() {
			static T pInstance{ };
			return pInstance;
		}
	};

} // namespace plus_binder
