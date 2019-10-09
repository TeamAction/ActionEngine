#pragma once
#include "DataInterface.h"
#include "drawHelper.h"

class Transform : public DataInterface<v2>
{
public:
	Transform(v2 _transform) : DataInterface(_transform) {}
	virtual v2 getData();
	virtual void setData(v2 _data);
};

