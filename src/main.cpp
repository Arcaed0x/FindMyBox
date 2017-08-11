#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include "Player.hpp"
#include "Box.hpp"

bool has_collided(Player& p, Box& b);
void update_world(float dt, Player& p, Box& b);

void update_world(float dt, Player& p, Box& b){
	if (dt > 0.15f){
		dt = 0.15f;
	}

	// Check input and carry out appropriate action

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
	    // 'D' pressed: Move Right
	    p.move_right(dt);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		// 'A' pressed: Move Left
		p.move_left(dt);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		// 'S' pressed: Move Down
		p.move_down(dt);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		// 'W' pressed: Move Up
		p.move_up(dt);
	}

	if (has_collided(p, b)){
		b.relocate(p.get_pos());
		p.increment_score();
	}
}
bool has_collided(Player& p, Box& b){
	bool result = false;

	sf::Vector2f a_pos = p.get_pos();
	sf::Vector2f b_pos = b.get_pos();

	sf::Vector2f a_size = p.get_size();
	sf::Vector2f b_size = b.get_size();

	// Check X collision
	if (a_pos.x < b_pos.x ){
		// A is on left ,B is on right
		if (std::min((a_pos.x + a_size.x), b_pos.x) == b_pos.x){
			if (a_pos.y < b_pos.y){
				// A is above B
				if (std::min((a_pos.y + a_size.y), b_pos.y) == b_pos.y){
					result = true;
				}
			} else if (a_pos.y > b_pos.y) {
				// B is above A
				if (std::min(a_pos.y, (b_pos.y + b_size.y)) == a_pos.y){
					result = true;
				}
			}
		}
	} else if (a_pos.x > b_pos.x ) {
		// B is on left, A is on right
		if (std::min(a_pos.x, (b_pos.x + b_size.x)) == a_pos.x){
			if (a_pos.y < b_pos.y){
				// A is above B
				if (std::min((a_pos.y + a_size.y), b_pos.y) == b_pos.y){
					result = true;
				}
			} else if (a_pos.y > b_pos.y) {
				// B is above A
				if (std::min(a_pos.y, (b_pos.y + b_size.y)) == a_pos.y){
					result = true;
				}
			}
		}
	} else if  (a_pos == b_pos){
		// A is right on top of B
		result = true;
	}



	return result;
}


int main()
{
	int w = 1280, h = 720; // Change your desired resolution here.

    sf::RenderWindow window(sf::VideoMode(w, h), "Find My Box 1.0.0");
	Player p((float) w, (float) h);
	Box b((float) w, (float) h);
	b.relocate(p.get_pos());

	sf::Clock clock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

		sf::Time elapsed = clock.restart();
		update_world(elapsed.asSeconds(), p, b);
        window.clear();
		b.draw(window);
        p.draw(window);
		p.draw_score(window);
        window.display();
    }

}
