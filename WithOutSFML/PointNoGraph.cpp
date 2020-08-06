#include <iostream>
#include <cmath>
#include <vector>

    float const GTR = 0.0174533;
    float const RTG = 1/GTR;


class Point
{
private:
    float x, y, z;
    float x_render, y_render;
public:
    Point(){}
     Point(float x, float y, float z)
    {;
        this->x = x;
        this->y = y;
        this->z = z;
    }
    float Angle_to_X(float &omega)
    {
        float sign = 1;
        float cam_x = cos(GTR*omega);
        float cam_y = sin(GTR*omega);

        float ch = cam_x*x+cam_y*y;
        float zn = sqrt(pow(cam_x, 2)+pow(cam_y, 2))*
                    sqrt(pow(x, 2)+pow(y, 2));
        if(x<0)
            sign*=-1;

        float output;
        if(ch==0)
        output = sqrt(pow(x, 2)+pow(y, 2))*sign;
        else
        output = sqrt(pow(x, 2)+pow(y, 2))*sin(acos(ch/zn))*sign;

        if (omega>180)
            omega-=360;
        if (omega<-180)
            omega-=-360;
        //std::cout<<x<<" "<<y<<"  "<<z<<" : "<<atan(y/x)/GTR<<std::endl;
        if((omega>180+(atan(y/x)/GTR)&&omega<360+(atan(y/x)/GTR))
        ||(omega<(atan(y/x)/GTR)&&omega>-180+(atan(y/x)/GTR)))
            output*=-1;

        return output;
    }

    float Angle_to_Y(float &gamma, float Axy_90)
    {
        float sign = 1;
        float cam_xy = cos(GTR*gamma);
        float cam_z = sin(GTR*gamma);

        float ch = cam_xy*z+cam_z*Axy_90;
        float zn = sqrt(pow(cam_xy, 2)+pow(cam_z, 2))*
				sqrt(pow(z, 2)+pow(Axy_90, 2));

        if(z<0)
            sign*=-1;

		float  output;
        if(ch==0)
        output = sqrt(pow(z,2)+pow(Axy_90,2))*sign;
        else
        output = sqrt(pow(z,2)+pow(Axy_90,2))*sin(acos(ch/zn))*sign;

        if (gamma>180)
            gamma-=360;
        if (gamma<-180)
            gamma-=-360;

        if((gamma>180+(atan(Axy_90/z)/GTR)&&gamma<360+(atan(Axy_90/z)/GTR))
        ||(gamma<(atan(Axy_90/z)/GTR)&&gamma>-180+(atan(Axy_90/z)/GTR)))
            output*=-1;
        return output;
    }

    void setPoint (float &omega, float &gamma,
                   float center_x, float center_y, float scale) //Temp function
    {
        float omega_90 = omega-90;
        x_render = center_x + Angle_to_X(omega)*scale;
        y_render = center_y + Angle_to_Y(gamma, Angle_to_X(omega_90))*scale;
    }

    float get_x()
    {
        return x;
    }
    float get_y()
    {
        return y;
    }
    float get_z()
    {
        return z;
    }
    void set_x(float x)
    {
        this->x=x;
    }
    void set_y(float y)
    {
        this->y=y;
    }
    void set_z(float z)
    {
        this->z=z;
    }

    float get_x_render()
    {
        return x_render;
    }
    float get_y_render()
    {
        return y_render;
    }

    void RenderOut()
    {
        std::cout<<x_render<<", "<<y_render<<"\n";
    }

    void Out()
    {
        std::cout<<"("<<x<<", "<<y<<", "<<z<<")"<<std::endl;
    }
};

