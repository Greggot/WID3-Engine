#include <iostream>
#include "PointNoGraph.cpp"
class Polygone
{
private:
    int one, two, three;
    Point distanceTest;
    float distance;
public:
    Polygone (){}
    Polygone(int one, int two, int three, std::vector<Point> P)
             {
                float x = (P[one].get_x()+P[two].get_x())/2;
                float y = (P[one].get_y()+P[two].get_y())/2;
                float z = (P[one].get_z()+P[three].get_z())/2;
                Point temp(x,y,z);
                distanceTest = temp;
                this->one = one;
                this->two = two;
                this->three = three;
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

};
