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


class Circle : public CircleShape
{
public:
    Circle(int R, int G, int B, float x, float y, int r)
    {
        R = R; G = G; B = B;
        this->setFillColor(Color(R, G, B));

        this->setRadius(r);
        this->setPosition(x, y);
        this->setOrigin(r, r);
    }
};

class polygon : public ConvexShape
{
public:
    polygon(vector <Vector2f> xy)
    {
        this->setPointCount(xy.size());
        for (int i = 0; i < xy.size(); i++)
        {
            this->setPoint(i, xy[i]);
        }
        this->setFillColor(Color::White);
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

bool intersect(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float& x, float& y)
{
    
    float Ua, Ub, numerator_a, numerator_b, denominator;

    denominator = (y4 - y3) * (x1 - x2) - (x4 - x3) * (y1 - y2);
    if (denominator == 0) {
        if ((x1 * y2 - x2 * y1) * (x4 - x3) - (x3 * y4 - x4 * y3) * (x2 - x1) == 0 && (x1 * y2 - x2 * y1) * (y4 - y3) - (x3 * y4 - x4 * y3) * (y2 - y1) == 0)
            return true;
        else false;
    }
    else {
        numerator_a = (x4 - x2) * (y4 - y3) - (x4 - x3) * (y4 - y2);
        numerator_b = (x1 - x2) * (y4 - y2) - (x4 - x2) * (y1 - y2);
        Ua = numerator_a / denominator;
        Ub = numerator_b / denominator;
        x = Ua * x1 + (1 - Ua) * x2;
        y = Ua * y1 + (1 - Ua) * y2;
        return (Ua >= 0 && Ua <= 1 && Ub >= 0 && Ub <= 1);
    }
}

int main()
{

    int phi = 30, fps = 30, type = 2;
    float x, y;
    srand(time(NULL));


    RenderWindow window(VideoMode(), "курсовая", Style::Fullscreen);
    //window.setKeyRepeatEnabled(false);
    window.setFramerateLimit(fps);


    vector <Circle> circles;    //вектор окружностей
    vector <Circle> pol;        //вектор вершин многоугольников
    vector <polygon> polygons;  //вектор многоугольников
    vector <Vector2f> point_xy; //вектор с координатами вершин многоульников

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


        //добавление объектов при помощи мыши
        Vector2i position = Mouse::getPosition();

        if (Keyboard::isKeyPressed(Keyboard::Space))            //менять объекты на пробел
        {
            type = (type + 1) % 2;
        }


        if (type == 1 or type == 2)                             // многульники
        {                               /// перенести в конструктор какого-то объекта
            static bool lock_click;
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left && lock_click != true)
                {
                    point_xy.push_back(Vector2f(position.x, position.y));     //добавляет в вектор координаты
                    pol.push_back(Circle(250, 250, 0, position.x, position.y, 3));
                    if (point_xy.size() > 5)
                    {
                        polygons.push_back(polygon(point_xy));          //добавляет много-ики в вектор
                        pol.clear();
                        point_xy.clear();
                    }

                    lock_click = true;
                }
            }
            if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    lock_click = false;
                }
            }
        }
        

        if (type == 0)
        {
            static bool lock_click;
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left && lock_click != true)
                {
                    circles.push_back(Circle(250, 250, 0, position.x, position.y, 50)); //добавляет окру-ти в вектор

                    lock_click = true;
                }
            }
            if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    lock_click = false;
                }
            }
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

            for (int i = 0; i < polygons.size(); i++)
            {
                int count_intersect = 0;
                
                for (int j = 0; j < polygons[i].getPointCount() - 1; j++)
                {
                    if (intersect(0, 0, position.x, position.y, polygons[i].getPoint(j).x, polygons[i].getPoint(j).y,
                        polygons[i].getPoint(j + 1).x, polygons[i].getPoint(j + 1).y, x, y))
                    {
                        count_intersect++;
                        cout << count_intersect << endl;
                    }
                }

                if (count_intersect % 2 != 0 and count_intersect != 0)
                {
                    polygons.erase(polygons.begin() + i);
                }
            }
        }
        //лучик
        //поворот
        float X1, Y1, X2, Y2;
        if (Keyboard::isKeyPressed(Keyboard::Up)) {

            phi = phi + 1;
        }
        if (Keyboard::isKeyPressed(Keyboard::Down)) {

            phi = phi - 1;
        }

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
            float length_polygon = 10000000;
            float min_length_polygon = 10000000;
            if (polygons.size() != 0)
            { 
                for (int i = 0; i < polygons.size(); i++)
                {
                    for (int j = 0; j < polygons[i].getPointCount() - 1; j++)
                    {
                        if (intersect(0, 0, X1, Y1, polygons[i].getPoint(j).x, polygons[i].getPoint(j).y,
                            polygons[i].getPoint(j + 1).x, polygons[i].getPoint(j + 1).y, x, y))
                        {
                            check = 1;
                            length_polygon = length(x, y);
                            if (length_polygon <= min_length_polygon)
                            {
                                lines_1[0].position = Vector2f(x, y);
                                min_length_polygon = length_polygon;
                            }
                        }
                    }
                }
            }

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

                    //проверка окружности до полигона
                    float length_in_circles = check_in_circle(norm_lenght.x, circles[j].getPosition().x, norm_lenght.y, circles[j].getPosition().y); //длина положения конца вектора до окружности

                    if (check == 1 and length_polygon < lenght_circles)
                    {
                        if (length_in_circles <= circles[j].getRadius() and lenght_circles <= vect_lenght)
                        {
                            continue;
                        }
                    }
                    
                    if (check == 1 and lenght_circles <= min_to_cirlce or length_polygon >= lenght_circles)
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
        for (auto& s : pol)
        {
            window.draw(s);
        }
        for (auto& s : polygons)
        {
            window.draw(s);
        }
        window.display();
    }

    return 0;
}