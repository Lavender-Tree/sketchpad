#ifndef DATA_H

    #define DATA_H

    // coordinate
    struct Coor
    {
        int x;
        int y;
        Coor(int x, int y): x(x), y(y){}
        Coor(){}
    };

	struct Coor_f
	{
		float x;
		float y;
		Coor_f(float x, float y) :x(x), y(y) {}
		Coor_f() {}
	};

    struct Color
    {
        float r;
        float g;
        float b;
        Color(float r, float g, float b): r(r), g(g), b(b){}
    };
    
	struct VECT
	{
		int x;
		int y;
		VECT(int x, int y) : x(x), y(y) {}
	};

    int getWinWidth();
    int getWinHeight();
    void setWinSize(int width, int height);
    
    // convert relative coordinate to GL coordinate
    Coor convertCoor(Coor coor);
	Coor_f convertCoor_f(Coor coor);
    
    bool operator == (const Coor a, const Coor b);
	
	bool operator == (const Color a, const Color b);

	int operator * (const VECT a, const VECT b);
	float M(VECT v);


	bool onLine(Coor pos, Coor start, Coor end);

	// menu id
	const int LINE = 0;
	const int RECT = 1;
	const int CIRCLE = 2;
	const int MOVE = 3;
	const int SAVE = 4;
	const int LOAD = 5;
	const float PI = 3.14;
#endif
