
#pragma once

#include <memory>

#ifndef NDEBUG
#define ON_ENABLE_ASSERTS
#define ON_DEBUG
#endif // NDEBUG
// Platform detection using predefined macros
#ifdef _WIN32
	/* Windows x64/x86 */
#ifdef _WIN64
	/* Windows x64  */
#define ON_PLATFORM_WINDOWS
#else
	/* Windows x86 */
#error "x86 Builds are not supported!"
#endif
#elif defined(__APPLE__) || defined(__MACH__)
#include <TargetConditionals.h>
/* TARGET_OS_MAC exists on all the platforms
 * so we must check all of them (in this order)
 * to ensure that we're running on MAC
 * and not some other Apple platform */
#if TARGET_IPHONE_SIMULATOR == 1
#error "IOS simulator is not supported!"
#elif TARGET_OS_IPHONE == 1
#define ON_PLATFORM_IOS
#error "IOS is not supported!"
#elif TARGET_OS_MAC == 1
#define ON_PLATFORM_MACOS
#error "MacOS is not supported!"
#else
#error "Unknown Apple platform!"
#endif
 /* We also have to check __ANDROID__ before __linux__
  * since android is based on the linux kernel
  * it has __linux__ defined */
#elif defined(__ANDROID__)
#define ON_PLATFORM_ANDROID
#error "Android is not supported!"
#elif defined(__linux__)
#define ON_PLATFORM_LINUX
#error "Linux is not supported!"
#else
	/* Unknown compiler/platform */
#error "Unknown platform!"
#endif // End of platform detection

#ifdef ON_DEBUG
#if defined(ON_PLATFORM_WINDOWS)
#define ON_DEBUGBREAK() __debugbreak()
#elif defined(ON_PLATFORM_LINUX)
#include <signal.h>
#define ON_DEBUGBREAK() raise(SIGTRAP)
#else
#error "Platform doesn't support debugbreak yet!"
#endif
#define ON_ENABLE_ASSERTS
#else
#define ON_DEBUGBREAK()
#endif

#ifdef ON_ENABLE_ASSERTS
#define ON_ASSERT(x, ...) { if(!(x)) { ON_ERROR("Assertion Failed: {0}"); ON_DEBUGBREAK(); } }
#define ON_CORE_ASSERT(x, ...) { if(!(x)) { ON_CORE_ERROR("Assertion Failed: {0}"); ON_DEBUGBREAK(); } }
#else
#define ON_ASSERT(x, ...)
#define ON_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define ON_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

//TODO: 7/16/20 Add Buffers
#define ON_OPENGL

namespace ON {

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}