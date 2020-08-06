#include "PolygoneNoGraph.cpp"
#include <cmath>
#include <iostream>
#include <vector>
class Cube
{
private:
    int PointNumber;
    int PointBound;

    float diffAngle;
    float FigureHeight;
    float Radius;
    std::vector<Polygone> Polygons;

    Point cent;
public:
    std::vector<Point> POINTS;
    std::vector<Point> createPoints()
    {
        for(float i = 0; i<360; i+=diffAngle)
        {
            float x = cent.get_x()+Radius*cos((i+45)*GTR);
            float y = cent.get_y()+Radius*sin((i+45)*GTR);
            float z = cent.get_z()-(FigureHeight/2);
            Point temp_neg (x,y,z);
            POINTS.push_back(temp_neg);
        }
        for(float i = 0; i<360; i+=diffAngle)
        {
            float x = cent.get_x()+Radius*cos((i+45)*GTR);
            float y = cent.get_y()+Radius*sin((i+45)*GTR);
            float z = cent.get_z()+(FigureHeight/2);
            Point temp_pos (x,y,z);
            POINTS.push_back(temp_pos);
        }
        Point Bottom(cent.get_x(), cent.get_y(), cent.get_z()-FigureHeight/2);
        Point Upper(cent.get_x(), cent.get_y(), cent.get_z()+FigureHeight/2);
        POINTS.push_back(Bottom);
        POINTS.push_back(Upper);
        POINTS.push_back(cent);

        return POINTS;
    }

    std::vector<Polygone> createPolygons() //We push index of POINTS to use it via render-engine
    {
        for(int i=0; i<PointBound; i++)
        {
            Polygone temp_one;
            Polygone temp_two;
            if(i!=3)
            {
                temp_one = Polygone(i+PointBound, i+1, i, POINTS);
                temp_two = Polygone(i+PointBound, i+1, i+PointBound+1, POINTS);
            }
            else
            {
                temp_one = Polygone(i+PointBound, 0, i+1, POINTS);
                temp_two = Polygone(i+PointBound, 0, i, POINTS);
            }
            Polygons.push_back(temp_one);
            Polygons.push_back(temp_two);
        }
        for(int i=0; i<PointBound; i++)
        {
            Polygone temp_bottom;
            if(i!=3)
                temp_bottom = Polygone(i, i+1, (PointBound*2), POINTS);
            else
                temp_bottom = Polygone(i, 0, (PointBound*2), POINTS);
            Polygons.push_back(temp_bottom);
        }
        for(int i=0; i<PointBound; i++)
        {
            Polygone temp_bottom;
            if(i!=3)
                temp_bottom = Polygone(i+PointBound, i+1+PointBound, (PointBound*2)+1, POINTS);
            else
                temp_bottom = Polygone(i+PointBound, PointBound, (PointBound*2)+1, POINTS);
            Polygons.push_back(temp_bottom);
        }

        return Polygons;
    }
    std::vector<Polygone> getTriangle()
    {
            return Polygons;
    }
    std::vector<Point> getPOINTS()
    {
        return POINTS;
    }

    Cube(float BasicLine, Point cent)
    {
        this->cent = cent;
        FigureHeight = Radius = BasicLine;
        PointNumber = 8;
        diffAngle = 90;
        POINTS=createPoints();
        Polygons = createPolygons();
    }

    int getPointBound()
    {
        return PointBound;
    }
    int getPointNumber()
    {
        return PointNumber;
    }
};
///---------PRISM-CYLINDER---------------------------------------------------
class Prism_Cylinder
{
private:
    int PointNumber;
    int PointBound;

    float diffAngle;
    float FigureHeight;
    float Radius;

    Point cent;

    std::vector<Polygone> Polygons;
public:
    std::vector<Point> POINTS;
    Point getCenter()
    {
        return cent;
    }
    std::vector<Point> createPoints()
    {
        for(float i = 0; i<360; i+=diffAngle)
        {
            float x = cent.get_x()+Radius*cos((i+45)*GTR);
            float y = cent.get_y()+Radius*sin((i+45)*GTR);
            float z = cent.get_z()-(FigureHeight/2);

            Point temp_neg (x,y,z);
            POINTS.push_back(temp_neg);
        }
        for(float i = 0; i<360; i+=diffAngle)
        {
            float x = cent.get_x()+Radius*cos((i+45)*GTR);
            float y = cent.get_y()+Radius*sin((i+45)*GTR);
            float z = cent.get_z()+(FigureHeight/2);

            Point temp_pos (x,y,z);
            POINTS.push_back(temp_pos);
        }
        Point Bottom(cent.get_x(), cent.get_y(), cent.get_z()-FigureHeight/2);
        Point Upper(cent.get_x(), cent.get_y(), cent.get_z()+FigureHeight/2);
        POINTS.push_back(Bottom);
        POINTS.push_back(Upper);

        POINTS.push_back(cent);

        return POINTS;
    }

    std::vector<Polygone> createPolygons() //We push index of POINTS to use it via render-engine
    {
        for(int i=0; i<PointBound; i++)
        {
            Polygone temp_one;
            Polygone temp_two;
            if(i!=PointBound-1)
            {
                temp_one = Polygone(i+1, i, i+PointBound, POINTS);
                temp_two = Polygone(i+1, i+PointBound, i+1+PointBound, POINTS);
            }
            else
            {
                temp_one = Polygone(0, i, i+PointBound, POINTS);
                temp_two = Polygone(0, PointBound, i+PointBound, POINTS);
            }
            Polygons.push_back(temp_one);
            Polygons.push_back(temp_two);
        }
        for(int i = 0; i<PointBound; i++)
        {
            Polygone temp_one;
            if(i!=PointBound-1)
                temp_one = Polygone(PointNumber, i, i+1, POINTS);
            else
                temp_one = Polygone(PointNumber, i, 0, POINTS);
            Polygons.push_back(temp_one);
        }
        for(int i = 0; i<PointBound; i++)
        {
            Polygone temp_two;
            if(i!=PointBound-1)
                temp_two = Polygone(PointNumber+1, i+PointBound, i+1+PointBound, POINTS);
            else
                temp_two = Polygone(PointNumber+1, i+PointBound, PointBound, POINTS);
            Polygons.push_back(temp_two);
        }
        return Polygons;
    }

    std::vector<Polygone> getTriangle()
    {
        return Polygons;
    }
    std::vector<Point> getPOINTS()
    {
        return POINTS;
    }
    Prism_Cylinder(float BasicLine, float R, int number, Point cent)
    {
        this->cent = cent;
        FigureHeight = BasicLine;
        Radius = R;
        PointNumber = number;
        diffAngle = 720/number;
        POINTS=createPoints();
    }
};
///-----------PYRAMID-CONE-----------------------------------------------------------
class Pyramid_Cone
{
private:
    int PointNumber;

    float diffAngle;
    float FigureHeight;
    float Radius;

    std::vector<Polygone> Polygons;
    Point cent;
public:
    std::vector<Point> POINTS;
    Point getCenter()
    {
        return cent;
    }
    std::vector<Point> createPoints()
    {
        int ind = 0;
        Point S (cent.get_x(), cent.get_y(), cent.get_z()+FigureHeight/2);
        POINTS.push_back(S);
        Point antiS (cent.get_x(), cent.get_y(), cent.get_z()-FigureHeight/2);
        POINTS.push_back(antiS);


        for(float i = 0; i<360; i+=diffAngle)
        {
            float x = cent.get_x()+Radius*cos((i+45)*GTR);
            float y = cent.get_y()+Radius*sin((i+45)*GTR);
            float z = cent.get_z()-(FigureHeight/2);
            Point temp_neg (x,y,z);
            POINTS.push_back(temp_neg);
        }
        POINTS.push_back(cent);
        return POINTS;
    }

    std::vector<Polygone> createPolygons()    //We push index of POINTS to use it via render-engine
    {
        for (int i = 2; i<=PointNumber; i++)
        {
            Polygone temp;
            if(i!=PointNumber)
                temp = Polygone(0,i,i+1, POINTS);
            else
                temp = Polygone(0,PointNumber,2, POINTS);
            Polygons.push_back(temp);
        }
        for (int i = 2; i<=PointNumber; i++)
        {
            Polygone antiTemp;
            if(i!=PointNumber)
                antiTemp = Polygone(1,i,(i+1), POINTS);
            else
                antiTemp = Polygone(1,PointNumber,2, POINTS);
            Polygons.push_back(antiTemp);
        }
        return Polygons;
    }

    std::vector<Polygone> getTriangle()
    {
        return Polygons;
    }
    std::vector<Point> getPOINTS()
    {
        return POINTS;
    }

    Pyramid_Cone(float FigureHeight, float Radius, int PointNumber, Point cent)
    {
        this->FigureHeight = FigureHeight;
        this->Radius = Radius;
        this->PointNumber = PointNumber;
        this->cent = cent;
        diffAngle = 360/(PointNumber-1);
        POINTS=createPoints();
    }
};
///------SPHERE------------------------------------------------------
class Sphere
{
private:
    int PointNumber;
    int PointPack;
    float Radius;
    float diffAngle;

    std::vector<Polygone> Polygons;
    std::vector<Point> POINTS;

    Point cent;
public:
    std::vector<Point> createPoints(Point cent)
    {
        Point Upper (cent.get_x(), cent.get_y(), cent.get_z()+Radius);
        Point Bottom (cent.get_x(), cent.get_y(), cent.get_z()-Radius);
        POINTS.push_back(Upper);
        Point temp;
        for(int j =90-diffAngle; j>=-90+diffAngle; j-=diffAngle)
        {
            float z = cent.get_z()+Radius*sin(j*GTR);
            float Radius_xy = Radius*cos(j*GTR);
            for(float i = 0; i<360;i+=diffAngle)
            {

                float x = cent.get_x()+Radius_xy*cos(i*GTR);
                float y = cent.get_y()+Radius_xy*sin(i*GTR);

                temp = Point(x,y,z);
                POINTS.push_back(temp);
            }
        }

        POINTS.push_back(Bottom);
        POINTS.push_back(cent);

        return POINTS;
    }

    std::vector<Polygone> createPolygons()    //We push index of POINTS to use it via render-engine
    {
       std::cout<<PointPack<<std::endl;
       for(int i = 1; i<=PointPack; i++)
       {
           Polygone temp;
           if(i!=PointPack)
                temp = Polygone(0, i, i+1, POINTS);
            else
                temp = Polygone(0, i, 1, POINTS);
            Polygons.push_back(temp);
       }

       for(int k = 0;k<((PointNumber-2)/(PointPack))-1; k++)
       {
           std::cout<<"\n\n"<<k<<"\n\n";
           for(int i = k*PointPack+1; i<=k*PointPack+PointPack; i++)
           {
               Polygone temp_one;
               Polygone temp_two;
               if(i!=k*PointPack+PointPack)
               {
                   temp_one = Polygone (i, i+PointPack, i+1+PointPack, POINTS);
                   temp_two = Polygone(i, i+1+PointPack, i+1, POINTS);
               }
               else
               {
                   temp_one = Polygone (i, i+PointPack, k*PointPack+1+PointPack, POINTS);
                   temp_two = Polygone(i, k*PointPack+1+PointPack, k*PointPack+1, POINTS);
               }
               temp_one.Out();
               temp_two.Out();
                Polygons.push_back(temp_one);
                Polygons.push_back(temp_two);
           }
       }

       for(int i = PointNumber-PointPack-1; i<=PointNumber-2; i++)
       {
           Polygone temp;
           if(i!=PointNumber-2)
                temp = Polygone(PointNumber-1, i, i+1, POINTS);
            else
                temp = Polygone(PointNumber-1,PointNumber-2,PointNumber-PointPack-1,  POINTS);
            Polygons.push_back(temp);
       }

        return Polygons;
    }

    std::vector<Polygone> getTriangle()
    {
        return Polygons;
    }
    std::vector<Point> getPOINTS()
    {
        return POINTS;
    }

    Sphere (float Radius, float diffAngle)
    {
        this->Radius = Radius;
        this->cent = cent;
        this->diffAngle = diffAngle;
        PointPack = 360/diffAngle;
        PointNumber = 2+((PointPack/2)-1)*PointPack;;
    }
};
