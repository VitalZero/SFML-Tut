#include "SpriteSheet.h"

SpriteSheet::SpriteSheet( TextureManager * textMgr )
	:
	textureManager( textMgr ),
	animationCurrent( nullptr),
	spriteScale( 1.f, 1.f ),
	direction( Direction::Right )
{
}

SpriteSheet::~SpriteSheet()
{
	ReleaseSheet();
}

void SpriteSheet::CropSprite( sf::IntRect & rect )
{
	sprite.setTextureRect( rect );
}

void SpriteSheet::ReleaseSheet()
{
	textureManager->ReleaseResource( texture );
	animationCurrent = nullptr;
	
	while ( animations.begin() != animations.end() )
	{
		delete animations.begin()->second;
		animations.erase( animations.begin() );
	}
}

void SpriteSheet::SetSpriteSize( const sf::Vector2i& sprSize )
{
	spriteSize = sprSize;
	sprite.setOrigin( spriteSize.x / 2.0f, spriteSize.y / 2.0f );
}

void SpriteSheet::SetSpritePosition( const sf::Vector2f & pos )
{
	sprite.setPosition( pos );
}

void SpriteSheet::SetDirection( const Direction & dir )
{
	if ( dir != direction )
	{
		direction = dir;
		animationCurrent->CropSprite();
	}

}

AnimBase * SpriteSheet::GetCurrentAnim()
{
	return animationCurrent;
}

bool SpriteSheet::SetAnimation( const std::string & name, const bool & play, const bool & loop )
{
	auto itr = animations.find( name );
	if ( itr == animations.end() )
	{
		return false;
	}
	if ( itr->second == animationCurrent )
	{
		return false;
	}
	if ( animationCurrent )
	{
		animationCurrent->Stop();
	}

	animationCurrent = itr->second;
	animationCurrent->SetLooping( loop );

	if ( play )
	{
		animationCurrent->Play();
	}

	animationCurrent->CropSprite();

	return true;
}

void SpriteSheet::Update( const float & dt )
{
	animationCurrent->Update( dt );
}

void SpriteSheet::Draw( sf::RenderWindow* window )
{
	window->draw( sprite );
}
