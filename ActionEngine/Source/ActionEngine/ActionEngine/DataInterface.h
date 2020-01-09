#pragma once
#include "ActorComponent.h" 
#include "drawHelper.h"

template <class T>
class DataInterface : public ActorComponent
{
public:
	DataInterface(T _data) : ActorComponent(TYPE::DATA), data(_data) {}
	
	T getData()
	{
		return data;
	}

	void setData(T _data)
	{
		data = _data;
	}
protected:
	T data;
};