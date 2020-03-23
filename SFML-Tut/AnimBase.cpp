#include "AnimBase.h"
#include "SpriteSheet.h"

AnimBase::AnimBase()
	:
	frameCurrent( 0 ),
	frameStart( 0 ),
	frameEnd( 0 ),
	frameRow( 0 ),
	frameTime( 0.f ),
	elapsedTime( 0.f ),
	frameActionStart( -1 ),
	frameActionEnd( -1 ),
	loop( false ),
	playing( false )
{
}

void AnimBase::Reset()
{
	frameCurrent = frameStart;
	elapsedTime = 0.0f;
	CropSprite();
}

void AnimBase::Update( const float & dt )
{
	if ( playing )
	{
		elapsedTime += dt;

		if ( elapsedTime >= frameTime )
		{
			FrameStep();
			CropSprite();
			elapsedTime = 0.0f;
		}
	}
}

void AnimBase::SetSpriteSheet( SpriteSheet * sheet )
{
	spriteSheet = sheet;
}

void AnimBase::SetFrame( const unsigned int & frame )
{
	if ( (frame >= frameStart && frame >= frameEnd) ||
		(frame >= frameEnd && frame >= frameStart) )
	{
		frameCurrent = frame;
	}
}

bool AnimBase::IsInAction()
{
	if ( frameActionStart == -1 || frameActionEnd == -1 )
	{
		return true;
	}
	return ( frameCurrent >= (Frame)frameActionStart && frameCurrent >= (Frame)frameActionEnd );
}

void AnimBase::SetName( const std::string & newName )
{
	name = newName;
}

void AnimBase::SetLooping( bool newLoop )
{
	loop = newLoop;
}
