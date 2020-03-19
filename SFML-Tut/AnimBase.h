#pragma once
#include "TextureManager.h"
#include "Directions.h"

class SpriteSheet;
using Frame = unsigned int;

class AnimBase
{
	friend class SpriteSheet;
public:
	AnimBase();
	virtual ~AnimBase() {}

public:
	void Play();
	void Pause();
	void Stop();
	void Reset();
	virtual void Update( const float& dt );
	friend std::stringstream& operator << ( std::stringstream& stream, AnimBase& a )
	{
		a.ReadIn( stream );
		return stream;
	}

protected:
	virtual void FrameStep() = 0;
	virtual void CropSprite() = 0;
	virtual void ReadIn( std::stringstream& stream ) = 0;

protected:
	Frame frameCurrent;
	Frame frameStart;
	Frame frameEnd;
	Frame frameRow;
	int frameActionStart;
	int frameActionEnd;
	float frameTime;
	float elapsedTime;
	bool loop;
	bool playing;
	SpriteSheet* spriteSheet;
};