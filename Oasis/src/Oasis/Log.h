#pragma once

#include "Core.h"
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
namespace Oasis {

	class OE_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

// Core log macros
#define OE_CORE_TRACE(...)    ::Oasis::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define OE_CORE_INFO(...)     ::Oasis::Log::GetCoreLogger()->info(__VA_ARGS__)
#define OE_CORE_WARN(...)     ::Oasis::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define OE_CORE_ERROR(...)    ::Oasis::Log::GetCoreLogger()->error(__VA_ARGS__)
#define OE_CORE_FATAL(...) ::Oasis::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define OE_TRACE(...)         ::Oasis::Log::GetClientLogger()->trace(__VA_ARGS__)
#define OE_INFO(...)          ::Oasis::Log::GetClientLogger()->info(__VA_ARGS__)
#define OE_WARN(...)          ::Oasis::Log::GetClientLogger()->warn(__VA_ARGS__)
#define OE_ERROR(...)         ::Oasis::Log::GetClientLogger()->error(__VA_ARGS__)
#define OE_FATAL(...)      ::Oasis::Log::GetClientLogger()->critical(__VA_ARGS__)