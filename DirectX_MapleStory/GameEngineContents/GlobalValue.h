#pragma once

// Ό³Έν :
class GlobalValue
{
public:
	// constrcuter destructer
	GlobalValue();
	~GlobalValue();

	// delete Function
	GlobalValue(const GlobalValue& _Other) = delete;
	GlobalValue(GlobalValue&& _Other) noexcept = delete;
	GlobalValue& operator=(const GlobalValue& _Other) = delete;
	GlobalValue& operator=(GlobalValue&& _Other) noexcept = delete;

	static float4 WinScale;
protected:

private:

};

