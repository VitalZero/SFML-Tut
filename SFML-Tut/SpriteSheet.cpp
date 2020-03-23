#include "SpriteSheet.h"
#include <fstream>
#include <sstream>
#include "AnimDirectional.h"

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

bool SpriteSheet::LoadSheet( const std::string & file )
{
	std::ifstream sheet;
	sheet.open( Utils::GetWorkingDirectory() + file );

	if ( sheet )
	{
		ReleaseSheet();
		std::string line;

		while ( std::getline( sheet, line ) )
		{
			if ( line[0] == '|' )
			{
				continue;
			}
			std::stringstream keystream( line );
			std::string type;

			keystream >> type;

			if ( type == "Texture" )
			{
				if ( texture != "" )
				{
					std::cerr << "Duplicate texture entries in: " << file << std::endl;
					continue;
				}
				std::string tmpTexture;
				keystream >> tmpTexture;

				if ( !textureManager->RequireResources( tmpTexture ) )
				{
					std::cerr << "Could not setup the texture: " << tmpTexture << std::endl;
					continue;
				}

				texture = tmpTexture;
				sprite.setTexture( *textureManager->GetResources( texture ) );
			}
			else if ( type == "Size" )
			{
				keystream >> spriteSize.x >> spriteSize.y;
				SetSpriteSize( spriteSize );
			}
			else if ( type == "Scale" )
			{
				keystream >> spriteScale.x >> spriteScale.y;
				sprite.setScale( spriteScale );
			}
			else if ( type == "AnimationType" )
			{
				keystream >> animType;
			}
			else if ( type == "Animation" )
			{
				std::string tmpName;
				keystream >> tmpName;

				if ( animations.find( tmpName ) != animations.end() )
				{
					std::cerr << "Duplicate animation! ( " << tmpName <<
						" ) in: " << file << std::endl;
					continue;
				}

				AnimBase* anim = nullptr;
				if ( animType == "Directional" )
				{
					anim = new AnimDirectional();
				}
				else
				{
					std::cerr << "Unknown animation type: " << animType << std::endl;
					continue;
				}

				keystream >> *anim;
				anim->SetSpriteSheet( this );
				anim->SetName( tmpName );
				anim->Reset();
				animations.emplace( tmpName, anim );

				if ( animationCurrent )
				{
					continue;
				}

				animationCurrent = anim;
				animationCurrent->Play();
			}
		}

		return true;
	}

	std::cerr << "Failed loading sprite sheet: " << file << std::endl;

	return false;
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

sf::Vector2i SpriteSheet::GetSpriteSize()
{
	return spriteSize;
}

Direction SpriteSheet::GetDirection()
{
	return direction;
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
