// g++ -std=c++11 aula5.c -o aula5 -lGL -lGLU -lglut
// g++ -std=c++11 aula5.c -o aula5 -lglu32 -lglut32 -lopengl32
/*
ESC - finaliza o programa
r   - reset

x - aumentar eyex
y - aumentar eyey
z - aumentar eyez

j - diminuir eyex
k - diminuir eyey
l - diminuir eyez

X - aumentar centerx
Y - aumentar centery
Z - aumentar centerz

left mouse  - incrementa 0.1 na razão de aspecto do frustum
rigth mouse - decrementa 0.1 na razão de aspecto do frustum

mouse scroll up   - incrementa em 5 o campo de visão (zoom-in)
mouse scroll down - incrementa em 5 o campo de visão (zoom-out)
*/

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cstdlib>
#include <cstdio>

GLfloat angle, fAspect;
GLfloat eyex, eyey, eyez;
GLfloat centerx, centery, centerz;

GLfloat fator = 5;

int MOUSE_SCROLL_UP = 3, MOUSE_SCROLL_DOWN = 4;


void definirParametrosPadroes(void) {
  angle = 50;
  fAspect = 1.25;
  eyex = 0;
  eyey = 80;
  eyez = 200;
  centerx = centery = centerz = 0;
}


void especificaParametrosVisualizacao(void) {
  // especifíca sistema de coordenadas de projeção
  glMatrixMode(GL_PROJECTION);
  // inicializa sistema de coordenadas de projeção
  glLoadIdentity();

  // Especifica a projeção perspectiva (matriz para visão perspectiva simétrica)
  gluPerspective(angle, fAspect, 0.1, 500);
  //              |       |
  //              |       +--- aspect ratio do frustum
  //              +--- field of view = campo de visão

  //glFrustum(left, right, bottom, top, near, far);

  // Especifica sistema de coordenadas do modelo
  glMatrixMode(GL_MODELVIEW);
  // Inicializa sistema de coordenadas do modelo
  glLoadIdentity();

  // Especifica posição do observador e do alvo
  gluLookAt(eyex, eyey, eyez, // eye = centro de projeção da câmera (referenciado em relação ao sistema de referência global)
            centerx, centery, centerz, // center = ponto de interesse
            0, 1, 0); // up = coordenadas do vetor view up, que perpendicula a câmera (orientando-a)
}


void alteraTamanhoJanela(GLsizei w, GLsizei h) {
  // Para previnir uma divisão por zero
  if (!h) h = 1;

  // Especifica o tamanho da viewport
  glViewport(0, 0, w, h);

  // Calcula a correção do aspecto
  fAspect = (GLfloat)w/(GLfloat)h;

  especificaParametrosVisualizacao();
}


void gerenciaMouse(int button, int state, int x, int y) {
  if (button == MOUSE_SCROLL_UP) {
    if (state == GLUT_DOWN) {  // Zoom-in
      if (angle >= 10) angle -= 5;
    }
  } else if (button == MOUSE_SCROLL_DOWN) {
    if (state == GLUT_DOWN) {  // Zoom-out
      if (angle <= 130) angle += 5;
    }
  } else if (button == GLUT_LEFT_BUTTON) {
    fAspect += 0.1;
  } else if (button == GLUT_RIGHT_BUTTON) {
    fAspect -= 0.1;
  }


  especificaParametrosVisualizacao();
  glutPostRedisplay();
}


void desenha(void) {
  glClear(GL_COLOR_BUFFER_BIT);

  glLineWidth(1);
  glColor3f(0, 0, 1.0);
  // desenha o teapot com a cor corrente (wire-frame)
  glutWireTeapot(20.0);

  glTranslatef(0,-50,0);
  glColor3f(1, 0, 0);
  glLineWidth(2);
  glutWireCube(50.0f);

  glLineWidth(1);
  glColor3f(0, 1, 0);
  glutWireSphere(12, 10, 10);

  // executa os comandos opengl
  glutSwapBuffers();
}

void init() {
  glClearColor(1.0, 1.0, 1.0, 1.0);
  //glColor3f(1.0, 0.0, 0.0);
  glViewport(0, 0, 240, 240);
  // criar a matriz para uma visão paralelo ortográfico
  gluOrtho2D(0.0, 260.0, 4.9, 120.0);

  definirParametrosPadroes();
}


void keyboard(unsigned char key, int x, int y) {
  switch (key) {
    case 'x':
      eyex += fator;
      break;
    case 'X':
      centerx += fator;
      break;
    case 'y':
      eyey += fator;
      break;
    case 'Y':
      centery += fator;
      break;
    case 'z':
      eyez += fator;
      break;
    case 'Z':
      centerz += fator;
      break;
    case 'j':
      eyex -= fator;
      break;
    case 'k':
      eyey -= fator;
      break;
    case 'l':
      eyez -= fator;
      break;

    case 'r':
      definirParametrosPadroes();
      break;
    case 27:
      exit(1);
 }

  especificaParametrosVisualizacao();
  glutPostRedisplay();
}




int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(500, 400);

  glutCreateWindow("Visualizacao 3D - Teapot");
  glutDisplayFunc(desenha);
  glutReshapeFunc(alteraTamanhoJanela);
  glutMouseFunc(gerenciaMouse);
  glutKeyboardFunc(keyboard);

  init();
  glutMainLoop();
}
