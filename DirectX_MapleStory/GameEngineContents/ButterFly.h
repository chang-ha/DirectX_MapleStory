#pragma once

class ButterFly : public GameEngineActor
{
public:
	// constructer destructer
	ButterFly();
	~ButterFly();

	// delete function
	ButterFly(const ButterFly& _Ohter) = delete;
	ButterFly(ButterFly&& _Ohter) noexcept = delete;
	ButterFly& operator=(const ButterFly& _Other) = delete;
	ButterFly& operator=(ButterFly&& _Other) noexcept = delete;

protected:

private:

};

