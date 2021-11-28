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
    CircleShape c1;


public:
    

    Shapee(int R, int G, int B, float x, float y) {
        R = R; G = G; B = B;
        this->setFillColor(Color(R, G, B));
        r = abs(rand() % 51 - 100);
        this->setRadius(r);
        this->setPosition(x,y);
        this->setOrigin(r,r);
    }
    
};

float check_in_circle(float x1, float x2, float y1, float y2)
{
    return(sqrt((pow(x1 - x2, 2)) + (pow(y1 - y2, 2))));
}

float length(float x1, float x2)
{
    return (sqrt(pow(x1, 2) + pow(x2, 2)));
}


int main()
{
    int phi = 30 , fps = 30;
    srand(time(NULL));
   
   
    RenderWindow window(VideoMode(), "курсовая", Style::Fullscreen);
    window.setFramerateLimit(fps);
    

    vector <Shapee> circles;    

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
        Vector2i position = Mouse::getPosition();

        //добавление объектов при помощи мыши
        
        
        
        if (Mouse::isButtonPressed(Mouse::Left))
        {
            circles.push_back(Shapee(250, 250, 0, position.x, position.y));
        }
        
        if (Mouse::isButtonPressed(Mouse::Right))
        {
            for (int i = 0; i < circles.size(); i++)
            {
                
                float length = check_in_circle(position.x, circles[i].getPosition().x, position.y, circles[i].getPosition().y);
                if (length <= circles[i].getRadius())
                {
                    circles.erase(circles.begin() + i);
                }
            }
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

        /*VertexArray line(Triangles, 3);
        X1 = cos(phi * M_PI/180) * position.x - sin(phi * M_PI / 180) * position.y;
        Y1 = sin(phi * M_PI / 180) * position.x + cos(phi * M_PI / 180) * position.y;
        X2 = cos(phi * M_PI / 180) * position.x + sin(phi * M_PI / 180) * position.y;
        Y2 = -sin(phi * M_PI / 180) * position.x + cos(phi * M_PI / 180) * position.y;
        line[0].position = Vector2f(0, 0);
        line[1].position = Vector2f(X1, Y1);
        line[2].position = Vector2f(X2, Y2);

        line[0].color = Color::White;
        line[1].color = Color(255, 255, 255, 0);
        line[2].color = Color(255, 255, 255, 0);*/

        int ksi = phi;
        
        


        //отрисовка объектов
        window.clear(Color::Black);


        

        //лайны
        VertexArray lines_1(LinesStrip, 2);
        
        for (int i = 0; i < 2 * phi; ++i)
        {
            ksi--;
            X1 = cos(ksi * M_PI / 180) * position.x + sin(ksi * M_PI / 180) * position.y;
            Y1 = -sin(ksi * M_PI / 180) * position.x + cos(ksi * M_PI / 180) * position.y;
            lines_1[0].position = Vector2f(X1, Y1);
            float check = -1;
            
            if (circles.size() != 0)
            {
                float min_to_cirlce = length(circles[0].getPosition().x, circles[0].getPosition().y);
                for (int j = 0; j < circles.size(); ++j)
                {
                    
                    float vect_lenght = length(X1, Y1);                             //длина вектора
                    Vector2f norm_lenght(X1 / (vect_lenght), Y1 / (vect_lenght));  // нормирую вектор
                    
                    float lenght_circles = length(circles[j].getPosition().x, circles[j].getPosition().y); // c 0;0 до окр

                    if (lenght_circles <= min_to_cirlce)
                    {
                        min_to_cirlce = lenght_circles;
                    }
                  

                    norm_lenght.x = norm_lenght.x * lenght_circles;    //увеличиваю вектор до длины окружности
                    norm_lenght.y = norm_lenght.y * lenght_circles;
                    
                    float length_in_circles = check_in_circle(norm_lenght.x, circles[j].getPosition().x, norm_lenght.y, circles[j].getPosition().y); //длина положения конца вектора до окружности
                    if (check == 1 and lenght_circles <= min_to_cirlce)
                    {
                        if (length_in_circles <= circles[j].getRadius() and lenght_circles <= vect_lenght)
                        {
                            lines_1[0].position = Vector2f(norm_lenght.x, norm_lenght.y);
                        }
                    }
                    if (length_in_circles <= circles[j].getRadius() and lenght_circles <= vect_lenght and check == -1) //проверка находится ли положения конца вектора в окружности
                    {
                        check = 1;
                        lines_1[0].position = Vector2f(norm_lenght.x, norm_lenght.y);  //если да, то принимает координаты, внутри окр-ти
                    }
                    
                }
            }
            
            window.draw(lines_1);
        }

        for (auto& s : circles) 
        {
            window.draw(s);

        }
        window.display();
    }
    
    return 0;
}