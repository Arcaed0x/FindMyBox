#pragma once

#include <algorithm>
#include <cstdlib>
#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Text.hpp>

class Box {
	public:
	sf::RectangleShape rect;
    sf::Vector2f bounds;

	Box(float w, float h):rect(sf::RectangleShape()), bounds(sf::Vector2f(w, h)){
		sf::Vector2f size = sf::Vector2f(30.0f, 30.0f);
		rect.setSize(size);
		rect.setFillColor(sf::Color::Red);
	}

	sf::Vector2f get_size(){
		return rect.getSize();
	}

	sf::Vector2f get_pos() const {
		return rect.getPosition();
	}

	void relocate(sf::Vector2f v){
		srand (time(NULL));

		float x_pos = (float) (rand() % (int) bounds.x);
		float y_pos = (float) (rand() % (int) bounds.y);

		while(std::abs(std::max(v.x, x_pos) - std::min(v.x, x_pos)) <= 300.0f
			|| std::abs(std::max(v.y, y_pos) - std::min(v.y, y_pos)) <= 300.0f){
			x_pos = (float) (rand() % (int) bounds.x);
			y_pos = (float) (rand() % (int) bounds.y);
		}

		rect.setPosition(x_pos, y_pos);
	}



	void draw(sf::RenderWindow& w)
	{
		w.draw(rect);
	}
};
