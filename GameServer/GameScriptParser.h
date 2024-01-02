#pragma once
#include "IScriptParser.h"
class GameScriptParser : public IScriptParser
{
public:
	//TODO 필요한 스크립트들 여기서 다 로드할 수 있게 만들자
};

using GameScriptParserPtr = shared_ptr<GameScriptParser>;