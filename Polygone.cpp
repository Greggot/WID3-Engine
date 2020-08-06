#include "Point.cpp"
class Polygone
{
private:
    int one, two, three;
    Point distanceTest;
    sf::VertexArray triangle;
    float distance;
public:
    Polygone (){}
    Polygone(int one, int two, int three, std::vector<Point> P)
             {
                float x = (P[one].get_x()+P[two].get_x()+P[three].get_x())/3;
                float y = (P[one].get_y()+P[two].get_y()+P[three].get_y())/3;
                float z = (P[one].get_z()+P[two].get_z()+P[three].get_z())/3;

                Point temp(x,y,z);
                distanceTest = temp;
                this->one = one;
                this->two = two;
                this->three = three;
                triangle = sf::VertexArray(sf::Triangles, 3);
                triangle[0].color = P[one].getColor();
                triangle[1].color = P[two].getColor();
                triangle[2].color = P[three].getColor();
             }
    void setPolygon(float &omega, float &gamma,
                    float center_x, float center_y, float scale,
                    std::vector<Point> P)
    {
        float cam_x = scale*cos(GTR*omega);
        float cam_y = scale*sin(GTR*omega);
        float cam_z = scale*sin(GTR*gamma);

        float x = cam_x - distanceTest.get_x();
        float y = cam_y - distanceTest.get_y();
        float z = cam_z - distanceTest.get_z();

        distance = pow(x,2)+pow(y,2)+pow(z,2);

        P[one].setPoint(omega, gamma, center_x, center_y, scale);
        P[two].setPoint(omega, gamma, center_x, center_y, scale);
        P[three].setPoint(omega, gamma, center_x, center_y, scale);

        triangle[0].position = sf::Vector2f(P[one].get_x_render(), P[one].get_y_render());
        triangle[1].position = sf::Vector2f(P[two].get_x_render(), P[two].get_y_render());
        triangle[2].position = sf::Vector2f(P[three].get_x_render(), P[three].get_y_render());
    }
	 Point get_distanceTest()
    {
        return distanceTest;
    }
    void Out()
    {
        std::cout<<"["<<one<<", "<<two<<", "<<three<<"]\n";
    }

    float get_distance()
    {
        return distance;
    }

    void testPointOut()
    {
        std::cout<<"//"<<distanceTest.get_x()<<", "<<distanceTest.get_y()<<", "<<distanceTest.get_z()<<"//\n";
    }

    sf::VertexArray getTriangle(std::vector<Point> P)
    {
        return triangle;
    }
    float getTwo()
    {
        return two;
    }
};
