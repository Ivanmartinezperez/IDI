#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#include <stdio.h>
  
  static int year = 0, day = 0, moon=0;
  //Variables de Control
  
  void init(void){
     glClearColor (0.0, 0.0, 0.0, 0.0);
     //glShadeModel (GL_FLAT);
 }
 
 void display(void){
     glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     glDepthFunc(GL_LEQUAL);
     glEnable(GL_DEPTH_TEST);
     glClearDepth(1.0);
     glColor3f (1.0, 0.0, 0.0);
     glPushMatrix();
         glutWireSphere(0.7, 20, 16);
         /* Dibuja el Sol */
         //glRotatef (15, 0.0, 0.0, 1.0);    //angulo constante de inclinacion en z
         glRotatef ((GLfloat) year, 0.0, 1.0, 0.0);    //angulo segun el año
         glTranslatef (2.0, 0.0, 0.0);    //Distancia entre el sol y le planeta
         glPushMatrix();
             glColor3f (0.0, 0.0, 1.0);
             glRotatef ((GLfloat) day, 0.0, 1.0, 0.0);    //angulo del planeta Dia
             glutWireSphere(0.3, 10, 8);                //planeta
         glPopMatrix();
         /* Dibuja un planeta */
         //glRotatef (-25, 0.0, 0.0, 1.0);                //Angulo constante de la luna
         glRotatef ((GLfloat) moon, 0.0, 1.0, 0.0);    //Angulo de la luna segun la hora
         glTranslatef (0.5, 0.0, 0.0);                //Distancia planeta luna
         glColor3f (0.7, 0.7, 0.7);
         glutWireSphere(0.07, 10, 8);                //luna
         /* draw smaller planet */
     glPopMatrix();
     glutSwapBuffers();
 }
 
 void reshape (int w, int h)
 {
     glViewport (0, 0, (GLsizei) w, (GLsizei) h);
     glMatrixMode (GL_PROJECTION);
     glLoadIdentity ();
     gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
     gluLookAt (0.0, 1.0, 6.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
 }
 
 void keyboard (unsigned char key, int x, int y)
 {
     switch (key) {
         case 'd':
             day = (day + 10) % 360;
             glutPostRedisplay();
             break;
         case 'D':
             day = (day - 10) % 360;
             glutPostRedisplay();
             break;
         case 'y':
             year = (year + 5) % 360;
             glutPostRedisplay();
             break;
         case 'Y':
             year = (year - 5) % 360;
             glutPostRedisplay();
             break;
         case 'm':
             moon = (moon + 10) % 360;
             glutPostRedisplay();
             break;
         case 'M':
             moon = (moon - 10) % 360;
             glutPostRedisplay();
             break;
         default:
             break;
     }
 }
 
 int main(int argc, char** argv)
 {
     glutInit(&argc, argv);
     glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
     glutInitWindowSize (500, 500);
     glutInitWindowPosition (100, 100);
     glutCreateWindow (argv[0]);
     init ();
     glutDisplayFunc(display);
     glutReshapeFunc(reshape);
     glutKeyboardFunc(keyboard);
     glutMainLoop();
     return 0;
 }
