#pragma once

class ButterFly_Ball : public GameEngineActor
{
	// friend class ButterFly;
public:
	// constructer destructer
	ButterFly_Ball();
	~ButterFly_Ball();

	// delete function
	ButterFly_Ball(const ButterFly_Ball& _Ohter) = delete;
	ButterFly_Ball(ButterFly_Ball&& _Ohter) noexcept = delete;
	ButterFly_Ball& operator=(const ButterFly_Ball& _Other) = delete;
	ButterFly_Ball& operator=(ButterFly_Ball&& _Other) noexcept = delete;

protected:

private:

};

