#pragma once
#ifndef WINDOWIMPL_H_UTH
#define WINDOWIMPL_H_UTH

#include <UtH/Platform/WindowSettings.hpp>


namespace uth
{
	class CommonWindowImpl
	{
	public:

		CommonWindowImpl();
		~CommonWindowImpl();

		static void* create(const WindowSettings& settings);
		static void* destroy(void* handle);

		static void clear(
			const float r,
			const float g,
			const float b,
			const float a = 1.f,
			const bool clearDepth = true,
			const bool clearStencil = false
			);

		static void swapBuffers(void* handle);

		// return true while window should remain open
		static bool processMessages(void* handle);

	};
}

#endif
