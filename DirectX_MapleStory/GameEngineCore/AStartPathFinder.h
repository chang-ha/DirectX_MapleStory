#pragma once
#include <list>
#include <map>
#include <set>
#include <memory>
#include <vector>
#include <GameEngineBase/GameEngineMath.h>

class PathPoint
{
public:
	union 
	{
		struct 
		{
			int X;
			int Y;
		};

		__int64 Key;
	};

	PathPoint operator+(const PathPoint& _Other)
	{
		return PathPoint{ X + _Other.X, Y + _Other.Y };
	}

	float4 GetFloat4()
	{
		return float4(static_cast<float>(X), static_cast<float>(Y));
	}

	float Distance(PathPoint _PathPoint)
	{
		return (GetFloat4() - _PathPoint.GetFloat4()).Size();
	}
};

class PathFindNode
{
public:
	PathPoint Index;
	PathFindNode* Parent = nullptr;
	float H;
	float G;
	float F; // H + G

	void CalF() 
	{
		F = G + H;
	}
};

// 설명 : 타일맵 전용 모든 타일맵에서 사용이 가능하게 만들려고 한다.
class AStartPathFinder
{
public:
	std::function<bool(PathPoint)> IsBlockCallBack;

	
public:
	AStartPathFinder();
	~AStartPathFinder();

	// delete Function
	AStartPathFinder(const AStartPathFinder& _Other) = delete;
	AStartPathFinder(AStartPathFinder&& _Other) noexcept = delete;
	AStartPathFinder& operator=(const AStartPathFinder& _Other) = delete;
	AStartPathFinder& operator=(AStartPathFinder&& _Other) noexcept = delete;

	std::list<PathPoint> PathFind(PathPoint _Start, PathPoint _End);

protected:
	// std::map<

	std::multimap<float, std::shared_ptr<PathFindNode>/*, std::less<float>*/> OpenList;
	std::set<__int64> OpenIndex;

	std::list<std::shared_ptr<PathFindNode>> CloseList;
	std::set<__int64> CloseIndex;

private:
	std::shared_ptr<PathFindNode> CreateNode(PathFindNode* _Parent, PathPoint _Start, PathPoint _End);


};

