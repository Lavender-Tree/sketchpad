#include <iostream>
#include <vector>
#include <set>
#include "shape/Shape.h"
#include <GL/glut.h>
#include <GL/gl.h>

// callback
void render();
void keyboard(unsigned char c, int x, int y);
void mouse(int button, int state, int x, int y);
void motion(int x, int y);
void passiveMotion(int x, int y);
void reSize(int width, int height);

// menu callback
void onClick(int menu);

// 
void init(int *argc, char **argv);
bool update();
SHAPE::Shape * selectShape(int x, int y);
void chooseMenu();
bool saveShape(const char *name, std::vector<SHAPE::Shape *> shape);
bool loadShape(const char *name, std::vector<SHAPE::Shape *>&);
//
void all();

// global
std::vector<SHAPE::Shape *> shape;
std::set< SHAPE::Shape *> selected;
bool isDraw = false;
bool isStart = false;
Coor preCoor(-1, -1);
int MENU = -1;

int main(int argc, char **argv)
{
	init(&argc, argv);

	glutMainLoop();

	return 0;
}

void init(int *argc, char **argv)
{
	// init
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE |GLUT_RGBA);
	glutInitWindowPosition(100, 100);

	glutInitWindowSize(getWinWidth(), getWinHeight());
	glutCreateWindow("Sketchpad");

	// register
	glutDisplayFunc(render);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutPassiveMotionFunc(passiveMotion);
	glutReshapeFunc(reSize);

	// menu
	glutCreateMenu(onClick);
	glutAddMenuEntry("Line", LINE);
	glutAddMenuEntry("Rect", RECT);
	glutAddMenuEntry("Circle", CIRCLE);
	glutAddMenuEntry("Move", MOVE);
	glutAddMenuEntry("Save", SAVE);
	glutAddMenuEntry("Load", LOAD);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void render()
{
	update();
}

void keyboard(unsigned char c, int x, int y)
{
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		// draw shape
		if (isDraw)
		{
			if (state == GLUT_DOWN && !isStart)
			{
				chooseMenu();
				shape.back()->start = Coor(x, y);
				isStart = true;
			}
			else if (state == GLUT_UP && isStart) {
				shape.back()->end = Coor(x, y);
				update();
				isStart = false;
			}
		}

		// move
		if (MENU == MOVE)
		{
			if (state == GLUT_DOWN)
			{
				isStart = true;
				SHAPE::Shape * ps = selectShape(x, y);
				if (ps)
				{
					if (selected.count(ps) > 0)
						selected.erase(ps);
					else selected.insert(ps);
				}
			}
		}
		preCoor = Coor(x, y);
	}
}

void motion(int x, int y)
{
	if(isDraw && isStart)
	{
		shape.back()->end = Coor(x, y);
		update();
	}
	else if (MENU == MOVE && isStart)
	{
		for (auto it = selected.begin(); it != selected.end(); it++)
		{
			(*it)->start.x += x - preCoor.x;
			(*it)->start.y += y - preCoor.y;
			(*it)->end.x += x - preCoor.x;
			(*it)->end.y += y - preCoor.y;
		}
		update();
		preCoor = Coor(x, y);
	}
}

void passiveMotion(int x, int y)
{
	if (MENU == MOVE)
	{
		SHAPE::Shape * p = selectShape(x, y);
		update();
	}
}

void onClick(int menu)
{
	if (menu == SAVE)
	{
		if (!saveShape("./test.ske", shape)) std::cout << "save error\n";
	}
	else if (menu == LOAD) {
		if (!loadShape("./test.ske", shape)) std::cout << "load error\n";
		else update();
	}

	MENU = menu;
	
	// recovery flag and clear seleced list
	isStart = false;
	selected.clear();
	selectShape(-1, -1);

	if (MENU == MOVE)
		isDraw = false;
	else isDraw = true;
}

bool update()
{
	glClearColor(1, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_BLEND);		 // 混合
	glutInitDisplayMode(GLUT_MULTISAMPLE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_NICEST);

	glViewport(0, 0, getWinWidth(), getWinHeight());
	for (auto it = shape.begin(); it != shape.end(); it++)
	{
		if ((*it)->start == (*it)->end)
		{
			delete(*it);
			shape.erase(it, it + 1);
			isStart = false;
			break;
		}
		else (*it)->draw((*it)->end);
	}
	glutSwapBuffers();

	return true;
}

void reSize(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	setWinSize(width, height);
}

void all()
{
	std::cout << "all shape\n";
	for(auto it = shape.begin(); it != shape.end(); it++)
		std::cout << "start( " << (*it)->start.x << ", " << (*it)->start.x << ")"
			 << " end(" << (*it)->end.x << ", " << (*it)->end.y << ")\n";
	std::cout << "all end\n";
}

SHAPE::Shape * selectShape(int x, int y)
{
	for (auto it = shape.begin(); it != shape.end(); it++)
	{
		if ((*it)->onShape(Coor(x, y)))
		{
			(*it)->co = Color(1.0, 1.0, 0.0);
			return *it;
		}
		else if (!((*it)->co == Color(0.0, 0.0, 0.0)) && selected.count(*it) <= 0)
		{
			(*it)->co = Color(0.0, 0.0, 0.0);
		}
	}
	return NULL;
}

void chooseMenu()
{
	switch (MENU)
	{
	case LINE:
	{
		isDraw = true;
		shape.push_back(new SHAPE::Line());
		break;
	}
	case RECT:
	{
		isDraw = true;
		shape.push_back(new SHAPE::Rect());
		break;
	}
	case CIRCLE:
	{
		isDraw = true;
		shape.push_back(new SHAPE::Circle());
		break;
	}
	case MOVE:
	{
		isDraw = false;
		break;
	}
	default:
		break;
	}
}