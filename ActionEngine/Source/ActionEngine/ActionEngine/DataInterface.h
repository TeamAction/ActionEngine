#pragma once
#include "ActorComponent.h" 
#include "drawHelper.h"

template <class T>
class DataInterface : public ActorComponent
{
public:
	DataInterface(T _data) : ActorComponent(DATA), data(_data) {}
	virtual T getData() = 0;
	virtual void setData(T _data) = 0;
protected:
	T data;
};