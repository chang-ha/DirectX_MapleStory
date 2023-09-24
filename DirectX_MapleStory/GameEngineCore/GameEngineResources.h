#pragma once
#include <GameEngineBase/GameEnginePath.h>


// 설명 :
template<typename ResourcesType>
class GameEngineResources
{
public:
	// constrcuter destructer
	GameEngineResources() {}
	~GameEngineResources() {}

	// delete Function
	//GameEngineResources(const GameEngineResources& _Other) = delete;
	//GameEngineResources(GameEngineResources&& _Other) noexcept = delete;
	//GameEngineResources& operator=(const GameEngineResources& _Other) = delete;
	//GameEngineResources& operator=(GameEngineResources&& _Other) noexcept = delete;

	static std::shared_ptr<ResourcesType> Find(std::string_view _Name)
	{
		std::string UpperName = GameEngineString::ToUpperReturn(_Name);

		// 템플릿으로 다른 템플릿을 사용할때도 꼬일때가 있다.
		// 꼬인거 풀려면 템플릿 안에서 다른 템플릿 사용할때 typename을 앞에 붙여주면 된다.
		typename std::map<std::string, std::shared_ptr<ResourcesType>>::iterator FindIter = NameRes.find(UpperName);

		if (FindIter == NameRes.end())
		{
			return nullptr;
		}

		return FindIter->second;
	}

	// 이름으로 로드한 애는 지울수 있습니다.
	static void Release(std::string_view _Name)
	{
		std::string UpperName = GameEngineString::ToUpperReturn(_Name);

		// 템플릿으로 다른 템플릿을 사용할때도 꼬일때가 있다.
		// 꼬인거 풀려면 템플릿 안에서 다른 템플릿 사용할때 typename을 앞에 붙여주면 된다.
		typename std::map<std::string, std::shared_ptr<ResourcesType>>::iterator FindIter = NameRes.find(UpperName);

		if (FindIter == NameRes.end())
		{
			MsgBoxAssert("존재하지도 않는 리소스를 지우려고 했습니다.");
			return;
		}

		NameRes.erase(FindIter);
	}

	void SetName(std::string_view _Name)
	{
		Name = _Name;
	}

	std::string_view GetName()
	{
		return Name;
	}

protected:

	static std::shared_ptr<ResourcesType> CreateRes()
	{
		std::shared_ptr<ResourcesType> NewRes = std::make_shared<ResourcesType>();
		UnNameRes.push_back(NewRes);
		return NewRes;
	}

	static std::shared_ptr<ResourcesType> CreateRes(std::string_view _Name)
	{
		std::string UpperName = GameEngineString::ToUpperReturn(_Name);
		std::shared_ptr<ResourcesType> NewRes = std::make_shared<ResourcesType>();
		NewRes->Name = UpperName;
		NameRes.insert(std::pair<std::string, std::shared_ptr<ResourcesType>>(UpperName, NewRes));
		return NewRes;
	}

	static std::shared_ptr<ResourcesType> CreateRes(std::string_view _Name, std::string_view _Path)
	{
		std::string UpperName = GameEngineString::ToUpperReturn(_Name);
		std::shared_ptr<ResourcesType> NewRes = std::make_shared<ResourcesType>(ResourcesType);
		NewRes->Name = UpperName;
		NewRes->Path = _Path.data();
		NameRes.insert(UpperName, NewRes);
	}

private:
	static std::map<std::string, std::shared_ptr<ResourcesType>> NameRes;
	static std::list<std::shared_ptr<ResourcesType>> UnNameRes;

	std::string Name;
	GameEnginePath Path;
};

// 템플릿 클래스 내부의 static변수 초기화 하는법
template<typename ResourcesType>
std::map<std::string, std::shared_ptr<ResourcesType>> GameEngineResources<ResourcesType>::NameRes;

template<typename ResourcesType>
std::list<std::shared_ptr<ResourcesType>> GameEngineResources<ResourcesType>::UnNameRes;

