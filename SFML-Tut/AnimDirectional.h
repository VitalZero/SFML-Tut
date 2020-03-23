#pragma once
#include "AnimBase.h"

class AnimDirectional : public AnimBase
{
protected:
	void FrameStep();
	void CropSprite();
	void ReadIn( std::stringstream& stream );
};