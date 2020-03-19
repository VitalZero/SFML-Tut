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
