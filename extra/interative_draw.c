// (c) https://www.opengl.org/discussion_boards/showthread.php/168825-interactive-mouse-drawing-points

#include <GL/glut.h>
#include <GL/gl.h>

#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500

GLfloat cx = 0;
GLfloat cy = 0;


void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  glFlush();
}

void drawSquare(int x, int y)
{
  cx = x;
  cy = WINDOW_WIDTH - y;

  glPointSize(10);
  glColor3f(cx / WINDOW_HEIGHT, .0f, .0f);
  glBegin(GL_POINTS);
  glVertex2f(cx, cy);
  glEnd();

  glFlush();
}

void mouse(int bin, int state, int x, int y)
{
  if (state == GLUT_DOWN)
  {
    if (bin == GLUT_LEFT_BUTTON) drawSquare(x, y);
    else if (bin == GLUT_RIGHT_BUTTON) glutPostRedisplay(); // limpar
  }
}

void init(void)
{
  /* select clearing (background) color */
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  // glViewport(0, 0, 500, 500);
  glMatrixMode(GL_PROJECTION);
  glOrtho(.0, 500.0, .0, 500.0, 1.0, -1.0);

  /* initialize viewing values */
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

/*Main*/

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
  /*Set the posotion of window*/
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Draw with cursor");
  glutDisplayFunc(display);
  glutMotionFunc(drawSquare);
  glutMouseFunc(mouse);
  init();
  glutMainLoop();
}
