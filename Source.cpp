#include <iostream>
#include <sstream>
#include <SFML/graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Image.hpp>
#include <math.h>
#include <vector>

using namespace std;


int score;
sf::Texture t_Dino;
sf::Texture t_Obstacle;
sf::Texture tex;

auto constrain(float x, float a, float b) {
    if (x < a) {
        return a;
    }
    else if (b < x) {
        return b;
    }
    else
        return x;
}
class world {
    public:
        float x, y;
        sf::Sprite sprite;

        world() {
            this->x = 0.0f;
            this->y = 0.0f;
            tex.loadFromFile("background.png");
            sprite.setTexture(tex);
            sprite.setScale(0.65f,0.95f);
            sprite.setPosition(x,y);
        }
        sf::Sprite showsprite() {

            return sprite;
        }
};
class Dino
{
public:
    float x, y;
    double vy,gravity;
    sf::Sprite mSprite;
  
    Dino()
    {
        this->x = 20.0f;
        this->y = 720.0f;
        this->vy = 0.0f;
        this->gravity = 0.01f; 
        t_Dino.loadFromFile("dino.png");
        mSprite.setTexture(t_Dino);
        mSprite.setScale(0.1f, 0.1f);
        mSprite.setPosition(x, y);
    }
    sf::Sprite showsprite() {
      
        return mSprite;

    }
  
    void jump()
    {
        if (this->y ==720 )
        {
           this->vy = -3.8f;
        }
    }
    auto move()
    {
        this->y += this->vy;
        this->vy += this->gravity;
        this->y = constrain(this->y, 0, 720);   
        mSprite.setPosition(x, y);
    }
};
class Obstacle {
public:
    float x, y;
    
    sf::Sprite mSprite;
    Obstacle() {
        this->x = 940.0f;
        this->y = 750.0f;
        t_Obstacle.loadFromFile("cactus.png");
        mSprite.setTexture(t_Obstacle);
        mSprite.setScale(0.085f, 0.085f);
        mSprite.setPosition(x, y);
        
    }
    sf::Sprite showsprite() {
        
        return mSprite;
    }
    int move() {
        this->x -= 3.5f;
        if (this->x == -5.0f) {
            score++;
        }
        if (score == 10)
        {
            this->x -= 4.0f;
            score++;
        }
        mSprite.setPosition(x, y);
        return x;
    }
    ~Obstacle() {
    }
   
};
std::string toString()
{
    std::ostringstream buffer;
    buffer << score;
    return buffer.str();
}

int main()

{
    Dino *d = new Dino();
    world* w = new world();
    std::vector<std::shared_ptr<Obstacle>> ob;
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "DinoByNazish");
    sf::Font font;
    if (!font.loadFromFile("filxgirl.ttf")) {
        return EXIT_FAILURE;
    }
   
    sf::Text text("Score", font, 100);
    text.setFillColor(sf::Color::Black);
    text.setPosition(50, 0);

    sf::Text text1;
    text1.setFont(font);
    text1.setFillColor(sf::Color::Black);
    text1.setPosition(240, 40);
    text1.setScale(2, 2);

    while (window.isOpen()) {
        
        window.clear(sf::Color::White);
        window.draw(w->showsprite());
        text1.setString(toString());
        sf::Event event;
         window.draw(d->showsprite());
        d->move();
        while (window.pollEvent(event)) {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Space) {
                        d->jump();
                    }
                }
        } 
        if (rand()<=9)
        {
            {
                    auto obs = std::make_shared<Obstacle>(Obstacle());
                ob.push_back(obs); 
            }
               
        }
        for (auto o : ob)
        {
            { o->move();
            window.draw(o->showsprite());
            if (d->mSprite.getGlobalBounds().intersects(o->mSprite.getGlobalBounds())) {
                cout << "Game over" << endl;
                sf::Text text2;
                text2.setFont(font);
                text2.setFillColor(sf::Color::Black);
                text2.setPosition(250, 320);
                text2.setScale(5, 5);
                text2.setString("Game Over");
                window.draw(text2);
                sf::Text text3;
                text3.setFont(font);
                text3.setFillColor(sf::Color::Black);
                text3.setPosition(250, 500);
                text3.setScale(4, 4);
                text3.setString("Score: ");
                window.draw(text3);
                sf::Text text4;
                text4.setFont(font);
                text4.setFillColor(sf::Color::Black);
                text4.setPosition(510, 530);
                text4.setScale(3, 3);
                text4.setString(std::to_string(score));
                window.draw(text4);
                window.display();
                system("pause");
            }
            }
        }
        
        window.draw(text);
        window.draw(text1);
        
        window.display();
       
    }
   
}
   
    
