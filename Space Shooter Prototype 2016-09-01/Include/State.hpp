#pragma once

#include <memory>

class State
{
public:
	typedef std::unique_ptr<State> Ptr;
	enum Type
	{
		Exit,
		Game,
		Loading,
	};
	
	virtual State::Type run() = 0;
};