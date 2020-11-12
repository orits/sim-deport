#pragma once
#include "observer.h"
class subject
{
public:
	subject();
	virtual ~subject() = default;;

	virtual void attach(observer* new_observer) = 0;
	virtual void detach(observer* old_observer) = 0;
	virtual void notify() = 0;    
};

