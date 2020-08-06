#include "Figure.cpp"
#include <vector>

class Engine
{
private:
    float scale = 1;
    int speed = 4;
    int activeFigure = 0;

    float getDistance(Point one, float omega, float gamma)
    {
        float cam_x = 500*cos(omega*GTR);
        float cam_y = 500*sin(omega*GTR);
        float cam_z = 500*sin(gamma*GTR);

        float x = cam_x - one.get_x();
        float y = cam_y - one.get_y();
        float z = cam_z - one.get_z();

        return sqrt(pow(x, 2)+pow(y, 2)+pow(z, 2));
    }

    std::vector<int> FigureSort(std::vector<std::vector<Point>> POINTS, int figuresNumber, float omega, float gamma)
    {
        std::vector<float> Distance;
        std::vector<int> Out;
        for(int i = 0; i<figuresNumber; i++)
            Out.push_back(i);

        for(int i = 0; i<figuresNumber; i++)
            Distance.push_back(getDistance(POINTS[i][POINTS[i].capacity()-1], omega, gamma));
        int temp;
        for(int i = 0; i<figuresNumber; i++)
        {
            for(int j = 0; j<figuresNumber; j++)
            {
                if(Distance[i]>Distance[j])
                       {
                           float temp = Distance[i];
                           Distance[i] = Distance[j];
                           Distance[j] = temp;

                           int Itemp = Out[i];
                           Out[i] = Out[j];
                           Out[j] = Itemp;
                       }
            }
        }
        if(gamma>-180&&gamma<0)
            std::reverse(Out.begin(), Out.end());
        return Out;
    }

    float getDistanceXY(Point one, float omega, float gamma)
    {
        float cam_x = 500*cos(omega*GTR);
        float cam_y = 500*sin(omega*GTR);

        float x = cam_x - one.get_x();
        float y = cam_y - one.get_y();

        return sqrt(pow(x, 2)+pow(y, 2));
    }

    std::vector<int> PolygoneSort(std::vector<Polygone> Poly, float omega, float gamma)
    {
        std::vector<float> Distance;
        std::vector<int> Out;
        for(int i = 0; i<Poly.size(); i++)
        {
            Distance.push_back(getDistance(Poly[i].get_distanceTest(), omega, gamma));
            Out.push_back(i);

        }

        for(int i = 0; i<Distance.size(); i++)
        {
            for(int j = 0; j<Distance.size(); j++)
            {
                if(Distance[i]>Distance[j])
                {
                    float temp = Distance[i];
                    Distance[i] = Distance[j];
                    Distance[j] = temp;

                    int Itemp = Out[i];
                    Out[i] = Out[j];
                    Out[j] = Itemp;
                }
            }
        }
        for(int i = 0; i<Distance.size(); i++)
        {
            Distance[Out[i]] = Poly[Out[i]].get_distanceTest().get_z();
        }
        if(gamma<90)
        {
            std::reverse(Out.begin(), Out.end());
            std::reverse(Distance.begin(), Distance.end());
        }
        if(gamma>=-180&&gamma<-90)
        {
            std::reverse(Out.begin(), Out.end());
            std::reverse(Distance.begin(), Distance.end());
        }

        return Out;
    }
public:
    Engine(int win_width, int win_height, std::vector<std::vector<Point>> POINTS, std::vector<std::vector<Polygone>> POLYGONES, int figuresNumber)
    {
        int center_x, center_y;
        float omega, gamma;

        omega = 0; float& omega_ref = omega;
        gamma = 0;  float& gamma_ref = gamma;

        center_x = win_width/2;
        center_y = win_height/2;

        sf::RenderWindow Engine(sf::VideoMode(win_width, win_height), "Window");

        sf::CircleShape X(3.f);
        X.setFillColor(sf::Color::Red);
        sf::CircleShape Y(3.f);
        Y.setFillColor(sf::Color::Green);
        sf::CircleShape Z(3.f);
        Z.setFillColor(sf::Color::Blue);

        Point X_axys(100, 0, 0, X);
        Point Y_axys(0, 100, 0, Y);
        Point Z_axys(0, 0, 100, Z);

        std::vector <Point> Axys;
        Axys.push_back(X_axys);
        Axys.push_back(Y_axys);
        Axys.push_back(Z_axys);

        for(int i = 0; i<Axys.capacity(); i++)
            Axys[i].setPoint(omega_ref, gamma_ref, center_x, center_y, scale);

        for(int i = 0; i<POLYGONES.size(); i++)
            PolygoneSort(POLYGONES[i], omega, gamma);

        std::vector<int> Order = FigureSort(POINTS, POLYGONES.size(), omega, gamma);
        std::vector<std::vector<int>> Order_two;

        for(int i = 0; i<POLYGONES.size(); i++)
        {
            for(int j = 0; j<POLYGONES[i].size(); j++)
                POLYGONES[i][j].setPolygon(omega_ref, gamma_ref,
                                                         center_x, center_y,
                                                         scale, POINTS[i]);

            Order_two.push_back(PolygoneSort(POLYGONES[i], omega, gamma));
        }

        Engine.setFramerateLimit(60);

        while (Engine.isOpen())
        {

            sf::Event event;
            while (Engine.pollEvent(event))
            {
                switch (event.type)
                {
                    case sf::Event::Closed:
                        Engine.close();
                        break;
                    case sf::Event::KeyPressed:
                        switch(event.key.code)
                        {
                            case sf::Keyboard::Q:
                                scale+=0.2;
                                for(int i = 0; i<Axys.capacity(); i++)
                                    Axys[i].setPoint(omega_ref, gamma_ref, center_x, center_y, scale);
                                for(int i = 0; i<figuresNumber; i++)
                                {
                                    for(int j = 0; j<POINTS[i].capacity(); j++)
                                        POINTS[i][j].setPoint(omega_ref, gamma_ref, center_x, center_y, scale);
                                    for(int j = 0; j<POLYGONES[i].capacity(); j++)
                                        POLYGONES[i][j].setPolygon(omega_ref, gamma_ref, center_x, center_y,
                                                                                 scale, POINTS[i]);
                                }
                                break;
                            case sf::Keyboard::E:
                                if(scale>0.4)
                                    scale-=0.2;
                                for(int i = 0; i<Axys.capacity(); i++)
                                    Axys[i].setPoint(omega_ref, gamma_ref, center_x, center_y, scale);
                                for(int i = 0; i<figuresNumber; i++)
                                {
                                    for(int j = 0; j<POINTS[i].capacity(); j++)
                                        POINTS[i][j].setPoint(omega_ref, gamma_ref, center_x, center_y, scale);
                                    for(int j = 0; j<POLYGONES[i].capacity(); j++)
                                        POLYGONES[i][j].setPolygon(omega_ref, gamma_ref, center_x, center_y,
                                                                                 scale, POINTS[i]);
                                }
                                break;
                            case sf::Keyboard::LShift:
                                speed++;
                                break;
                            case sf::Keyboard::LAlt:
                                if(speed>1)
                                    speed--;
                                break;
                            case sf::Keyboard::Up:
                                gamma_ref-=speed;
                                std::cout<<gamma<<", "<<omega<<"\n";
                                for(int i = 0; i<Axys.capacity(); i++)
                                    Axys[i].setPoint(omega_ref, gamma_ref, center_x, center_y, scale);
                                for(int i = 0; i<figuresNumber; i++)
                                {
                                    for(int j = 0; j<POINTS[i].capacity(); j++)
                                        POINTS[i][j].setPoint(omega_ref, gamma_ref, center_x, center_y, scale);
                                    for(int j = 0; j<POLYGONES[i].capacity(); j++)
                                        POLYGONES[i][j].setPolygon(omega_ref, gamma_ref, center_x, center_y,
                                                                                 scale, POINTS[i]);
                                }
                                break;
                            case sf::Keyboard::Down:
                                gamma_ref+=speed;
                                for(int i = 0; i<Axys.capacity(); i++)
                                    Axys[i].setPoint(omega_ref, gamma_ref, center_x, center_y, scale);
                                for(int i = 0; i<figuresNumber; i++)
                                {
                                    for(int j = 0; j<POINTS[i].capacity(); j++)
                                        POINTS[i][j].setPoint(omega_ref, gamma_ref, center_x, center_y, scale);
                                    for(int j = 0; j<POLYGONES[i].capacity(); j++)
                                        POLYGONES[i][j].setPolygon(omega_ref, gamma_ref, center_x, center_y,
                                                                                 scale, POINTS[i]);
                                }
                                break;
                            case sf::Keyboard::Right:
                                omega_ref+=speed;

                                for(int i = 0; i<Axys.capacity(); i++)
                                    Axys[i].setPoint(omega_ref, gamma_ref, center_x, center_y, scale);

                                for(int i = 0; i<figuresNumber; i++)
                                {
                                    for(int j = 0; j<POINTS[i].capacity(); j++)
                                        POINTS[i][j].setPoint(omega_ref, gamma_ref, center_x, center_y, scale);
                                    for(int j = 0; j<POLYGONES[i].capacity(); j++)
                                        POLYGONES[i][j].setPolygon(omega_ref, gamma_ref, center_x, center_y,
                                                                                 scale, POINTS[i]);
                                }

                                break;
                            case sf::Keyboard::Left:
                                omega_ref-=speed;
                                for(int i = 0; i<Axys.capacity(); i++)
                                    Axys[i].setPoint(omega_ref, gamma_ref, center_x, center_y, scale);
                                for(int i = 0; i<figuresNumber; i++)
                                {
                                    for(int j = 0; j<POINTS[i].capacity(); j++)
                                        POINTS[i][j].setPoint(omega_ref, gamma_ref, center_x, center_y, scale);
                                    for(int j = 0; j<POLYGONES[i].capacity(); j++)
                                        POLYGONES[i][j].setPolygon(omega_ref, gamma_ref, center_x, center_y,
                                                                                 scale, POINTS[i]);
                                }
                                break;
                            case sf::Keyboard::F:
                                activeFigure++;
                                if(activeFigure==figuresNumber)
                                    activeFigure = 0;
                                break;

                            case sf::Keyboard::Space:

                                for(int j = 0; j<POINTS[activeFigure].capacity(); j++)
                                        POINTS[activeFigure][j].set_z(POINTS[activeFigure][j].get_z()+speed*5);
                                for(int j = 0; j<POLYGONES[activeFigure].capacity(); j++)
                                        POLYGONES[activeFigure][j].setPolygon(omega_ref, gamma_ref,
                                                                                 center_x, center_y,
                                                                                 scale, POINTS[activeFigure]);
                                break;
                            case sf::Keyboard::LControl:
                                for(int j = 0; j<POINTS[activeFigure].capacity(); j++)
                                        POINTS[activeFigure][j].set_z(POINTS[activeFigure][j].get_z()-speed*5);
                                for(int j = 0; j<POLYGONES[activeFigure].capacity(); j++)
                                        POLYGONES[activeFigure][j].setPolygon(omega_ref, gamma_ref,
                                                                                 center_x, center_y,
                                                                                 scale, POINTS[activeFigure]);
                                break;
                            case sf::Keyboard::W:
                                for(int j = 0; j<POINTS[activeFigure].capacity(); j++)
                                        POINTS[activeFigure][j].set_x(POINTS[activeFigure][j].get_x()+speed*5);
                                for(int j = 0; j<POLYGONES[activeFigure].capacity(); j++)
                                        POLYGONES[activeFigure][j].setPolygon(omega_ref, gamma_ref,
                                                                                 center_x, center_y,
                                                                                 scale, POINTS[activeFigure]);
                                break;
                            case sf::Keyboard::S:
                                for(int j = 0; j<POINTS[activeFigure].capacity(); j++)
                                        POINTS[activeFigure][j].set_x(POINTS[activeFigure][j].get_x()-speed*5);
                               for(int j = 0; j<POLYGONES[activeFigure].capacity(); j++)
                                        POLYGONES[activeFigure][j].setPolygon(omega_ref, gamma_ref,
                                                                                 center_x, center_y,
                                                                                 scale, POINTS[activeFigure]);

                                break;
                            case sf::Keyboard::D:
                                for(int j = 0; j<POINTS[activeFigure].capacity(); j++)
                                        POINTS[activeFigure][j].set_y(POINTS[activeFigure][j].get_y()-speed*5);
                                for(int j = 0; j<POLYGONES[activeFigure].capacity(); j++)
                                        POLYGONES[activeFigure][j].setPolygon(omega_ref, gamma_ref,
                                                                                 center_x, center_y,
                                                                                 scale, POINTS[activeFigure]);
                                break;
                            case sf::Keyboard::A:
                                for(int j = 0; j<POINTS[activeFigure].capacity(); j++)
                                        POINTS[activeFigure][j].set_y(POINTS[activeFigure][j].get_y()+speed*5);
                                for(int j = 0; j<POLYGONES[activeFigure].capacity(); j++)
                                        POLYGONES[activeFigure][j].setPolygon(omega_ref, gamma_ref,
                                                                                 center_x, center_y,
                                                                                 scale, POINTS[activeFigure]);

                                break;
                            default:
                                break;
                        }
                }
            }

            Order = FigureSort(POINTS, figuresNumber, omega, gamma);
            Order_two.clear();
            for(int i = 0; i<POLYGONES.size(); i++)
                Order_two.push_back(PolygoneSort(POLYGONES[i], omega, gamma));

            Engine.clear(sf::Color::White);

            for(int i = 0; i<POLYGONES.size(); i++)
            {
                for(int j = 0; j<POLYGONES[Order[i]].size(); j++)
                    Engine.draw(POLYGONES[Order[i]][Order_two[Order[i]][j]].getTriangle(POINTS[Order[i]]));
            }

           for(int i = 0; i<POINTS.size(); i++)
            {
                for(int j = 0; j<POINTS[Order[i]].size(); j++)
                {
                    Engine.draw(POINTS[Order[i]][j].getShape());
                }
            }

            for(int i = 0; i<Axys.capacity(); i++)
                Engine.draw(Axys[i].getShape());

            Engine.display();
            }
    }

    Engine(int win_width, int win_height, std::vector<std::vector<Point>> POINTS, int figuresNumber)
    {
        int center_x, center_y;
        float omega, gamma;

        omega = 0; float& omega_ref = omega;
        gamma = 0;  float& gamma_ref = gamma;

        center_x = win_width/2;
        center_y = win_height/2;

        sf::RenderWindow Engine(sf::VideoMode(win_width, win_height), "Window");

        sf::CircleShape X(3.f);
        X.setFillColor(sf::Color::Red);
        sf::CircleShape Y(3.f);
        Y.setFillColor(sf::Color::Green);
        sf::CircleShape Z(3.f);
        Z.setFillColor(sf::Color::Blue);

        Point X_axys(100, 0, 0, X);
        Point Y_axys(0, 100, 0, Y);
        Point Z_axys(0, 0, 100, Z);

        std::vector <Point> Axys;
        Axys.push_back(X_axys);
        Axys.push_back(Y_axys);
        Axys.push_back(Z_axys);

        for(int i = 0; i<Axys.capacity(); i++)
            Axys[i].setPoint(omega_ref, gamma_ref, center_x, center_y, scale);


        std::vector<int> Order = FigureSort(POINTS, figuresNumber, omega, gamma);

        Engine.setFramerateLimit(60);

        while (Engine.isOpen())
        {

            sf::Event event;
            while (Engine.pollEvent(event))
            {
                switch (event.type)
                {
                    case sf::Event::Closed:
                        Engine.close();
                        break;
                    case sf::Event::KeyPressed:
                        switch(event.key.code)
                        {
                            case sf::Keyboard::Q:
                                scale+=0.2;
                                for(int i = 0; i<Axys.capacity(); i++)
                                    Axys[i].setPoint(omega_ref, gamma_ref, center_x, center_y, scale);
                                for(int i = 0; i<figuresNumber; i++)
                                {
                                    for(int j = 0; j<POINTS[i].capacity(); j++)
                                        POINTS[i][j].setPoint(omega_ref, gamma_ref, center_x, center_y, scale);
                                }
                                break;
                            case sf::Keyboard::E:
                                if(scale>0.4)
                                    scale-=0.2;
                                for(int i = 0; i<Axys.capacity(); i++)
                                    Axys[i].setPoint(omega_ref, gamma_ref, center_x, center_y, scale);
                                for(int i = 0; i<figuresNumber; i++)
                                {
                                    for(int j = 0; j<POINTS[i].capacity(); j++)
                                        POINTS[i][j].setPoint(omega_ref, gamma_ref, center_x, center_y, scale);
                                }
                                break;
                            case sf::Keyboard::LShift:
                                speed++;
                                break;
                            case sf::Keyboard::LAlt:
                                if(speed>1)
                                    speed--;
                                break;
                            case sf::Keyboard::Up:
                                gamma_ref-=speed;
                                std::cout<<gamma<<", "<<omega<<"\n";
                                for(int i = 0; i<Axys.capacity(); i++)
                                    Axys[i].setPoint(omega_ref, gamma_ref, center_x, center_y, scale);
                                for(int i = 0; i<figuresNumber; i++)
                                {
                                    for(int j = 0; j<POINTS[i].capacity(); j++)
                                        POINTS[i][j].setPoint(omega_ref, gamma_ref, center_x, center_y, scale);
                                }
                                break;
                            case sf::Keyboard::Down:
                                gamma_ref+=speed;
                                for(int i = 0; i<Axys.capacity(); i++)
                                    Axys[i].setPoint(omega_ref, gamma_ref, center_x, center_y, scale);
                                for(int i = 0; i<figuresNumber; i++)
                                {
                                    for(int j = 0; j<POINTS[i].capacity(); j++)
                                        POINTS[i][j].setPoint(omega_ref, gamma_ref, center_x, center_y, scale);
                                }
                                break;
                            case sf::Keyboard::Right:
                                omega_ref+=speed;

                                for(int i = 0; i<Axys.capacity(); i++)
                                    Axys[i].setPoint(omega_ref, gamma_ref, center_x, center_y, scale);

                                for(int i = 0; i<figuresNumber; i++)
                                {
                                    for(int j = 0; j<POINTS[i].capacity(); j++)
                                        POINTS[i][j].setPoint(omega_ref, gamma_ref, center_x, center_y, scale);
                                }

                                break;
                            case sf::Keyboard::Left:
                                omega_ref-=speed;
                                for(int i = 0; i<Axys.capacity(); i++)
                                    Axys[i].setPoint(omega_ref, gamma_ref, center_x, center_y, scale);
                                for(int i = 0; i<figuresNumber; i++)
                                {
                                    for(int j = 0; j<POINTS[i].capacity(); j++)
                                        POINTS[i][j].setPoint(omega_ref, gamma_ref, center_x, center_y, scale);

                                }
                                break;
                            case sf::Keyboard::F:
                                activeFigure++;
                                if(activeFigure==figuresNumber)
                                    activeFigure = 0;
                                break;

                            case sf::Keyboard::Space:

                                for(int j = 0; j<POINTS[activeFigure].capacity(); j++)
                                        POINTS[activeFigure][j].set_z(POINTS[activeFigure][j].get_z()+speed*5);

                                break;
                            case sf::Keyboard::LControl:
                                for(int j = 0; j<POINTS[activeFigure].capacity(); j++)
                                        POINTS[activeFigure][j].set_z(POINTS[activeFigure][j].get_z()-speed*5);
                                break;
                            case sf::Keyboard::W:
                                for(int j = 0; j<POINTS[activeFigure].capacity(); j++)
                                        POINTS[activeFigure][j].set_x(POINTS[activeFigure][j].get_x()+speed*5);
                                break;
                            case sf::Keyboard::S:
                                for(int j = 0; j<POINTS[activeFigure].capacity(); j++)
                                        POINTS[activeFigure][j].set_x(POINTS[activeFigure][j].get_x()-speed*5);

                                break;
                            case sf::Keyboard::D:
                                for(int j = 0; j<POINTS[activeFigure].capacity(); j++)
                                        POINTS[activeFigure][j].set_y(POINTS[activeFigure][j].get_y()-speed*5);
                                break;
                            case sf::Keyboard::A:
                                for(int j = 0; j<POINTS[activeFigure].capacity(); j++)
                                        POINTS[activeFigure][j].set_y(POINTS[activeFigure][j].get_y()+speed*5);

                                break;
                            default:
                                break;
                        }
                }
            }

            Order = FigureSort(POINTS, figuresNumber, omega, gamma);
            for(int i = 0; i<POINTS.size(); i++)
            {
                for(int j = 0; j<POINTS[Order[i]].size(); j++)
                {
                    Engine.draw(POINTS[Order[i]][j].getShape());
                }
            }

            for(int i = 0; i<Axys.capacity(); i++)
                Engine.draw(Axys[i].getShape());

            Engine.display();
            }
    }
};

int main()
{
    return 0;
}
