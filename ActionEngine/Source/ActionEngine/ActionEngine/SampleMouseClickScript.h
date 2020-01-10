#pragma once
#include "ScriptInterface.h"
#include "DataInterface.h"

class SampleActorMouseClick : public ScriptInterface
{
private:
	virtual void onTick(float dt);
	virtual void onStart(float dt);
	virtual void mouseClickTest(int x,int y);
};
