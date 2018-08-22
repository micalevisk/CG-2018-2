/*
praticaCG012018.pptx
slide 14:
1) O que fazer para se ter uma imagem com tamanho diferente?
2) O que fazer para a imagem aparecer em outra posição da tela?
3) Por que o retângulo branco ocupa a metade da área da tela?

*/

// https://www.khronos.org/registry/OpenGL-Refpages/gl4/html
// https://www.opengl.org/resources/libraries/glut/spec3/spec3.html
#include <GL/gl.h>
#include <GL/glut.h>

// g++ aula1.c -o aula1 -lGL -lGLU -lglut

void display()
{
  glClear(GL_COLOR_BUFFER_BIT); // clear buffers to preset values
  //      ^ Indicates the buffers currently enabled for color writing

  // primitivas:
  // GL_POINTS     //individual points
  // GL_LINES      //pairs of vertices used to draw segments
  // GL_TRIANGLES  //triple of vertices used to draw triangles
  // GL_QUADS      //quandruples of vertices used to draw quadrilaterals
  // GL_POLYGON    //boundary of a polygon
  glBegin(GL_POLYGON);
  //--- commands ---
  glColor3f(1.0, 1.0, 0.0);

  glVertex2f(-0.5, -0.5);
  glVertex2f(-0.5, 0.5);
  glVertex2f(0.5, 0.5);
  glVertex2f(0.5, -0.5);
  glEnd();

  glBegin(GL_LINES);
  glColor3f(1.0f, 0.0f, 0.0f);

  glVertex2f(-1, 0);
  glVertex2f(1, 0);

  glVertex2f(0, -1);
  glVertex2f(0, 1);
  glEnd();

  glFlush(); //forces execution before the gathering is complete
}

void reshape(int width, int height)
{
  glViewport(0, 0, width, height);
  printf("%d x %d\n", width, height);
}

void init()
{
  // GFloat red, green, blue, alpha
  glClearColor(0.0, 0.0, 1.0, 0.0);
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA);
  glutInitWindowPosition(100, 100); // posiciona 100x100 pixels
  glutInitWindowSize(300, 300);

  glutCreateWindow("Aula 1"); // 300x300

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);

  init();
  glutMainLoop(); // iniciar o loop infinito do OpenGL
}
