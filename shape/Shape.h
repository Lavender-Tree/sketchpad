#ifndef SHAPE_H
    #define SHAPE_H

    #include "Data.h"
    #include <GL/glut.h>

    namespace SHAPE
    {
        // Base Shape
        class Shape
        {
        public:
            Shape(){}
            ~Shape(){}

            int type;
            Coor start = Coor(0, 0);
            Coor end = Coor(0, 0);
			Color co = Color(0.0, 0.0, 0.0);
            
            virtual bool draw(Coor pos, Color co = Color(0.0, 0.0, 0.0));
            virtual bool onShape(Coor pos);
        };

        class Line: public Shape
        {
        public:
            Line(){ type = LINE;}

            bool draw(Coor pos, Color co = Color(0.0, 0.0, 0.0));
            bool onShape(Coor pos);
        };

		class Rect : public Shape
		{
		public:
			Rect() { type = RECT; }

			bool draw(Coor pos, Color co = Color(0.0, 0.0, 0.0));
			bool onShape(Coor pos);
		};

		class Circle : public Shape
		{
		public:
			Circle() { type = CIRCLE; }

			double r = 0;

			bool draw(Coor pos, Color co = Color(0.0, 0.0, 0.0));
			bool onShape(Coor pos);
		};
    }

#endif