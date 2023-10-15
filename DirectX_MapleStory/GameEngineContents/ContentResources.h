#pragma once

class ContentResources
{
public:
	// constructer destructer
	ContentResources();
	~ContentResources();

	// delete function
	ContentResources(const ContentResources& _Ohter) = delete;
	ContentResources(ContentResources&& _Ohter) noexcept = delete;
	ContentResources& operator=(const ContentResources& _Other) = delete;
	ContentResources& operator=(ContentResources&& _Other) noexcept = delete;

	static void ContentResourcesInit();

protected:

private:

};

