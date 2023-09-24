#pragma once
#include <string>
#include <assert.h>

//// Ό³Έν :
namespace GameEngineDebug
{
	void LeakCheck();
};

#define MsgBoxAssert(Text) \
std::string Value = Text; \
MessageBoxA(nullptr, Value.c_str(), "Error", MB_OK); assert(false);
