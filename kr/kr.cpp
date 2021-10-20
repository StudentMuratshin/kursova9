#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <map>
#define _USE_MATH_DEFINES
#include <math.h>
using namespace sf;
using namespace std;



class Shapee: public CircleShape {
private:
    int r, R, G, B;
    float x, y;
    CircleShape c2;


public:
    

    Shapee(int R, int G, int B) {
        R = R; G = G; B = B;
        this->setFillColor(Color(R, G, B));
        r = abs(rand() % 51 - 100);
        this->setRadius(r);
        this->setPosition(1920-(rand() % 960), rand() % 1080);
        //this->setPosition(1693,41);
    }
    

    //пересечение
    int do_intersect(CircleShape c1){
        this->c2 = c2;
        float s = sqrt((pow((c1.getPosition().x) - c2.getPosition().x, 2)) + 
            (pow((c1.getPosition().y) - c2.getPosition().y, 2)));
        if ((c1.getRadius() + c2.getRadius()) >= s) {
            c2.setPosition(1920 - (rand() % 960), rand() % 1080);
            return true;
        }
        return false;
    }
};




int main()
{
    int n, fps = 30;
    int phi = 30;
    cin >> n;
    srand(time(NULL));
   
   
    //RenderWindow window(VideoMode(1920, 1080), "xD");
    RenderWindow window(VideoMode(), "курсовая", Style::Fullscreen);
    window.setFramerateLimit(fps);
    

    vector <Shapee> circles;

   //вектор объектов
    Shapee concrete_circle(250, 250, 0);
    circles.push_back(concrete_circle);
    for (int i = 0; i < n - 1; i++) {
        circles.push_back(Shapee(250, 250, 0));
    }
    
    
    
    

    

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (Keyboard::isKeyPressed(Keyboard::Escape))
                window.close();

            if (event.type == Event::Closed)
                window.close();
        }
        
        
        //лучик
        //поворот
        
        float X1, Y1, X2, Y2;
        if (Keyboard::isKeyPressed(Keyboard::Up)) {
            
            phi = phi + 1 ;
        }
        if (Keyboard::isKeyPressed(Keyboard::Down)) {

            phi = phi - 1;
        }
        VertexArray line(Quads, 4);
        Vector2i position = Mouse::getPosition();
        X1 = cos(phi * M_PI/180) * position.x - sin(phi * M_PI / 180) * position.y;
        Y1 = sin(phi * M_PI / 180) * position.x + cos(phi * M_PI / 180) * position.y;
        X2 = cos(phi * M_PI / 180) * position.x + sin(phi * M_PI / 180) * position.y;
        Y2 = -sin(phi * M_PI / 180) * position.x + cos(phi * M_PI / 180) * position.y;
        line[0].position = Vector2f(0, 538.5);
        line[1].position = Vector2f(0, 542.5);
        line[2].position = Vector2f(X1, Y1);
        line[3].position = Vector2f(X2, Y2);

        line[0].color = Color::White;
        line[1].color = Color::White;
        line[2].color = Color(255, 255, 255, 0);
        line[3].color = Color(255, 255, 255, 0);

        //цикл
        /*while (true) {

            Vector2i position = Mouse::getPosition();
            line[2].position = Vector2f(X1, Y1);
            line[3].position = Vector2f(X2, Y2);
            line[2].color = Color(255, 255, 255, 0);
            line[3].color = Color(255, 255, 255, 0);

            if (Mouse::isButtonPressed(Mouse::Left))
            {
                break;
            }
            
        }*/

        



        //отрисовка объектов
        window.clear(Color::Black);
        for (auto& s:circles){
            window.draw(s);
            
        }
        window.draw(line);
        window.display();
    }
    
    return 0;
}