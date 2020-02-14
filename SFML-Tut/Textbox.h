#pragma once
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

using MessageContainer = std::vector<std::string>;

class Textbox
{
public:
	Textbox();
	Textbox( int visible, int charSize, int width, sf::Vector2f screenPos );
	~Textbox();

public:
	void Setup( int visible, int charSize, int width, sf::Vector2f screenPos );
	void Add( std::string message );
	void Clear();
	void Render( sf::RenderWindow& window );

private:
	MessageContainer messages;
	int numVisible;
	sf::RectangleShape backdrop;
	sf::Font font;
	sf::Text content;
};