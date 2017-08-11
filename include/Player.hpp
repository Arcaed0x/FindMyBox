#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Text.hpp>

class Player {
	public:
	float speed;
	sf::CircleShape avatar;
	int score;
	sf::Vector2f bounds;
	sf::Text score_display;
	sf::Font f;

	Player(float w, float h):
	score(0), speed(130.f), bounds(sf::Vector2f(w, h))
	{
		f.loadFromFile("/usr/share/fonts/oiio/DroidSans.ttf");
		score_display = sf::Text("score: " + std::to_string(score), f, 20);
		score_display.setFillColor(sf::Color::White);
		score_display.setPosition((bounds.x / 2.0f) , 0.0f);

		score_display.move(-(score_display.findCharacterPos(100) - score_display.getPosition())/ 2.0f);

		// score_display.setOutlineColor(sf::Color::White);
		// score_display.setOutlineThickness(1.0f);

		avatar = sf::CircleShape(20.f);
		avatar.setPosition((bounds.x / 2.0f) - avatar.getRadius(),
		 					(bounds.y / 2.0f) - avatar.getRadius());
		avatar.setFillColor(sf::Color::Blue);
	}

	void move_up(float dt){
		avatar.move(sf::Vector2f(0.0f, -speed)*dt);
		check_in_bounds();
	}

	void move_down(float dt){
		avatar.move(sf::Vector2f(0.0f, speed)*dt);
		check_in_bounds();
	}

	void move_right(float dt){
		avatar.move(sf::Vector2f(speed, 0.0f)*dt);
		check_in_bounds();
	}

	void move_left(float dt){
		avatar.move(sf::Vector2f(-speed, 0.0f)*dt);
		check_in_bounds();
	}

	sf::Vector2f get_size() const {
		return sf::Vector2f(avatar.getRadius() * 2.0f, avatar.getRadius() * 2.0f);
	}

	sf::Vector2f get_pos() const {
		return avatar.getPosition();
	}

	void draw(sf::RenderWindow& w)
	{
		w.draw(avatar);
	}

	void increment_score(){
		score++;
	}

	void draw_score(sf::RenderWindow& w){
		score_display.setString("score: " + std::to_string(score));
		w.draw(score_display);
	}

	private:
	void check_in_bounds(){
		const sf::Vector2f& avatar_pos = avatar.getPosition();
		sf::Vector2f avatar_new_pos = sf::Vector2f();
		avatar_new_pos.x = avatar_pos.x;
		avatar_new_pos.y = avatar_pos.y;

		if (avatar_pos.x < 0.0f - (avatar.getRadius() * 2.0f)){
			avatar_new_pos.x = bounds.x - 10.0f;
		}

		if (avatar_pos.y < 0.0f){
			avatar_new_pos.y = 0.0f;
		}

		if (avatar_pos.x > bounds.x){
			avatar_new_pos.x = 0.0f - (avatar.getRadius() * 2.0f) + 10.0f;
		}

		if (avatar_pos.y + (avatar.getRadius() * 2.0f) > bounds.y ){
			avatar_new_pos.y = bounds.y - (avatar.getRadius() * 2.0f);
		}

		avatar.setPosition(avatar_new_pos);
	}
};
