/*
  MIT License

  Copyright (c) 2019 rbellek

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

// OpenGL Simple Text Render Sample App

#include <iostream>
#include <GL/glut.h>

#include <simpledrawtext.h>

constexpr unsigned int windowWidth = 800, windowHeight = 600;

GLfloat rotate = 0.f;

static float vertices[] = 
{
  1.f,  1.f,  1.f, -1.f,  1.f,  1.f, -1.f, -1.f,  1.f,  1.f, -1.f,  1.f,
  1.f,  1.f,  1.f,  1.f, -1.f,  1.f,  1.f, -1.f, -1.f,  1.f,  1.f, -1.f,
  1.f,  1.f,  1.f,  1.f,  1.f, -1.f, -1.f,  1.f, -1.f, -1.f,  1.f,  1.f,
 -1.f, -1.f, -1.f, -1.f,  1.f, -1.f,  1.f,  1.f, -1.f,  1.f, -1.f, -1.f,
 -1.f, -1.f, -1.f, -1.f, -1.f,  1.f, -1.f,  1.f,  1.f, -1.f,  1.f, -1.f,
 -1.f, -1.f, -1.f,  1.f, -1.f, -1.f,  1.f, -1.f,  1.f, -1.f, -1.f,  1.f 
};

static float colors[] =
{
  1.f, 0.f, 1.f, 1.f, 0.f, 1.f, 1.f, 0.f, 1.f, 1.f, 0.f, 1.f,
  1.f, 1.f, 0.f, 1.f, 1.f, 0.f, 1.f, 1.f, 0.f, 1.f, 1.f, 0.f,
  0.f, 1.f, 0.f, 0.f, 1.f, 0.f, 0.f, 1.f, 0.f, 0.f, 1.f, 0.f,
  0.f, 1.f, 1.f, 0.f, 1.f, 1.f, 0.f, 1.f, 1.f, 0.f, 1.f, 1.f,
  0.f, 0.f, 1.f, 0.f, 0.f, 1.f, 0.f, 0.f, 1.f, 0.f, 0.f, 1.f,
  1.f, 0.f, 0.f, 1.f, 0.f, 0.f, 1.f, 0.f, 0.f, 1.f, 0.f, 0.f,
};

SimpleDrawText sdt;

void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  glRotatef(rotate, 1.f, 1.f, 0.f);

  glVertexPointer(3, GL_FLOAT, 0, vertices);
  glColorPointer(3, GL_FLOAT, 0, colors);

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);

  glDrawArrays(GL_QUADS, 0, sizeof(vertices) / (sizeof(float) * 3));

  sdt.drawText("Merhaba", 250, 550, 1, 0, 0);
  sdt.render();

  glutSwapBuffers();
}

void init()
{
  sdt.addText("Deneme");
  for (int i = 0; i < 10; i++)
    sdt.addText(std::to_string(i) + ". Naber? :D", 500 * i);

  glMatrixMode(GL_PROJECTION);
  gluPerspective(45, 8. / 6, 1, 50);
  gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);
  glMatrixMode(GL_MODELVIEW);

  glEnable(GL_DEPTH_TEST);
  glClearColor(0, 0, 0, 1);
}

void update(int value)
{
  constexpr unsigned int fps = 30;
  constexpr unsigned int delay = 1000 / fps;
  glutTimerFunc(delay, update, 0);
  rotate += 1;
  glutPostRedisplay();
}

void processKeys(unsigned char key, int x, int y)
{
  switch (key)
  {
    case 27:
      exit(0);
      break;
    default:
      break;
  }
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(windowWidth, windowHeight);
  glutInitWindowPosition(windowWidth / 3, windowHeight / 3);
  glutCreateWindow("Draw simple text...");
  init();
  glutDisplayFunc(display);
  glutKeyboardFunc(processKeys);
  glutTimerFunc(10, update, 0);
  glutMainLoop();
  return 0;
}