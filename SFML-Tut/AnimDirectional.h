#pragma once
#include "AnimBase.h"
#include "Directions.h"

class AnimDirectional : public AnimBase
{
protected:
	void FrameStep();
	void CropSprite();
	void ReadIn( std::stringstream& stream );
};