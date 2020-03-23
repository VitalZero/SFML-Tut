#include "AnimDirectional.h"
#include "SpriteSheet.h"

void AnimDirectional::FrameStep()
{
	if ( frameStart > frameEnd )
	{
		++frameCurrent;
	}

	if ( (frameStart < frameEnd && frameCurrent > frameEnd) ||
		(frameStart > frameEnd && frameCurrent < frameEnd) )
	{
		if ( loop )
		{
			frameCurrent = frameStart;
		}
		else
		{
			frameCurrent = frameEnd;
			Pause();
		}
	}
}

void AnimDirectional::CropSprite()
{
	sf::IntRect rect(
		spriteSheet->GetSpriteSize().x * frameCurrent,
		spriteSheet->GetSpriteSize().y * (frameRow + (Frame)spriteSheet->GetDirection()),
		spriteSheet->GetSpriteSize().x,
		spriteSheet->GetSpriteSize().y );
	
	spriteSheet->CropSprite(rect);
}

void AnimDirectional::ReadIn( std::stringstream & stream )
{
	stream >> frameStart >> frameEnd >> frameRow >>
		frameTime >> frameActionStart >> frameActionEnd;
}
