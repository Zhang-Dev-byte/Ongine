#pragma once
#include "onpch.h"
#include <glad/glad.h>
#include "Log.h"
#include "Base.h"

#define glCall(x) glClearError();\
	x;\
	ON_CORE_ASSERT(glCheckError())
extern void glClearError();
extern bool glCheckError();