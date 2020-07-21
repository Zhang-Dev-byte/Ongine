#pragma once

#include "Base.h"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace ON {

	class ON_API Log
	{
	public:
		static void Init();

		static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;
	};

}

// Core log macros
#define ON_CORE_TRACE(...)    ::ON::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ON_CORE_INFO(...)     ::ON::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ON_CORE_WARN(...)     ::ON::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ON_CORE_ERROR(...)    ::ON::Log::GetCoreLogger()->error(__VA_ARGS__)
#define ON_CORE_CRITICAL(...) ::ON::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define ON_TRACE(...)         ::ON::Log::GetClientLogger()->trace(__VA_ARGS__)
#define ON_INFO(...)          ::ON::Log::GetClientLogger()->info(__VA_ARGS__)
#define ON_WARN(...)          ::ON::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ON_ERROR(...)         ::ON::Log::GetClientLogger()->error(__VA_ARGS__)
#define ON_CRITICAL(...)      ::ON::Log::GetClientLogger()->critical(__VA_ARGS__)