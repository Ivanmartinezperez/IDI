#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#include "model.h"
#include <iostream>
using namespace std;


unsigned char action = 'n';
Model mod;
int altura = 500;
int anchura = 500;
int valor=15;
int maxx,minx,maxy,miny,maxz,minz;
double x = -1;
double y = -19;
double z = 12;
double x1 = 0;
double y1 = 0;
double z1 = 0;
int mode=GL_FILL;
int norm = 0;
float amb[4]={1.0,1.0,1.0,1.0};
float diff[4]={1.0,1.0,1.0,1.0};
float spec[4]={1.0,1.0,1.0,1.0};
float posl1[4];
float posl2[4];
float posl3[4];
float posl4[4];
// Funcion de inicializacion de parametros para pantalla inicial
void initGL(void){
	glClearColor(0.0,0.0,0.0,0.0);
    //glEnable(GL_LIGHT0);// Encen una llum de camara;
    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_AMBIENT, amb);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diff);
    glLightfv(GL_LIGHT1, GL_SPECULAR, spec);
    glLightfv(GL_LIGHT2, GL_AMBIENT, amb);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, diff);
    glLightfv(GL_LIGHT2, GL_SPECULAR, spec);
    glLightfv(GL_LIGHT3, GL_AMBIENT, amb);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, diff);
    glLightfv(GL_LIGHT3, GL_SPECULAR, spec);
    glLightfv(GL_LIGHT4, GL_AMBIENT, amb);
    glLightfv(GL_LIGHT4, GL_DIFFUSE, diff);
    glLightfv(GL_LIGHT4, GL_SPECULAR, spec);
    mod.load("legoman.obj");
    mod.dumpStats();
    mod.dumpModel();
    maxx=mod.vertices()[0];minx=maxx;maxy=mod.vertices()[1];miny=maxy;maxz=mod.vertices()[2];minz=maxz;
    for (int i=3; i<mod.vertices().size(); ++i) {
        if(i%3==0){
            if(mod.vertices()[i] > maxx) maxx = mod.vertices()[i];
            if(mod.vertices()[i] < minx) minx = mod.vertices()[i];
        }
        if(i%3==1){
            if(mod.vertices()[i] > maxy) maxy = mod.vertices()[i];
            if(mod.vertices()[i] < miny) miny = mod.vertices()[i];
        }
        if(i%3==2){
            if(mod.vertices()[i] > maxz) maxz = mod.vertices()[i];
            if(mod.vertices()[i] < minz) minz = mod.vertices()[i];
        }
    }
    cout << maxx << " " << minx << " " << maxy << " " << miny << " " << maxz << " " << minz << endl;
    x= -118;//(maxx+minx)/2;
    y=372;//(maxy+miny)/2;
    z=210;//abs(((maxz+minz)/2)*6);
    x1= (maxx+minx)/2;
    y1=(maxy+miny)/2;
    z1=((maxz+minz)/2);
    posl1[0]=minx*4;posl2[0]=minx*4;posl3[0]=maxx*4;posl4[0]=maxx*4;
    posl1[1]=maxy;posl2[1]=maxy;posl3[1]=maxy;posl4[1]=maxy;
    posl1[2]=minz*4;posl2[2]=maxz*4;posl3[2]=minz*4;posl4[2]=maxz*4;
    posl1[3]=1.0;posl2[3]=1.0;posl3[3]=1.0;posl4[3]=1.0;
}
///////////////////////////////
//Funcion que se ejecuta al pulsar una tecla del teclado
void keyboard_action(unsigned char act,int x2, int y2){
    if(act=='a') z+=valor;
    if(act=='z') z-=valor;
    if(act=='s') y+=valor;
    if(act=='x') y-=valor;
    if(act=='d') x+=valor;
    if(act=='c') x-=valor;
    if(act=='A') z1+=valor;
    if(act=='Z') z1-=valor;
    if(act=='S') y1+=valor;
    if(act=='X') y1-=valor;
    if(act=='D') x1+=valor;
    if(act=='C') x1-=valor;
    if(act=='1') glEnable(GL_LIGHT1);
    if(act=='q') glDisable(GL_LIGHT1);
    if(act=='2') glEnable(GL_LIGHT2);
    if(act=='w') glDisable(GL_LIGHT2);
    if(act=='3') glEnable(GL_LIGHT3);
    if(act=='e') glDisable(GL_LIGHT3);
    if(act=='4') glEnable(GL_LIGHT4);
    if(act=='r') glDisable(GL_LIGHT4);
    if(act=='7') mode = GL_POINT;
    if(act=='8') mode = GL_LINE;
    if(act=='9') mode = GL_FILL;
    if(act=='V'){
        cin >> valor;
    }
    if(act=='n') norm=!norm;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt (x, y, z, x1, y1, z1, 0.0, 1.0, 0.0);
    cout << x << " " << y << " " << z << endl;
    cout << x1 << " " << y1 << " " << z1 << endl;
    glutPostRedisplay();
}

//Funcion de transformacion de coordenadas a puntos dentro del rango opengl; R=[-1,1];

/////////////////////////
// Funcion que dibuja un
//////////////////////////////////
// Funcion a la que llama el main para refrescar la pantalla; NOTA(Se ejecuta en cada iteracion del main);
void refresh(void){
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0);
    glPolygonMode(GL_FRONT_AND_BACK,(GLenum) mode);
    glEnable(GL_LIGHTING);
    glPushMatrix();
    for(int i=0;i<mod.faces().size();++i){
            glBegin(GL_TRIANGLES);
            glColor3f(1.0,0.0,0.0);
            //DEFINICION DE LA NORMAL PARA LOS VERTICES DE LA CARA(ILUMINACION)
            if(norm==0)glNormal3f(mod.faces()[i].normalC[0],mod.faces()[i].normalC[1],mod.faces()[i].normalC[2]);
            ////////////////////////////////////////
            // DEFINICION DEL MATERIAL POR CARAS(MATERIAL)
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, Materials[mod.faces()[i].mat].ambient);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Materials[mod.faces()[i].mat].diffuse);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Materials[mod.faces()[i].mat].specular);
            glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, Materials[mod.faces()[i].mat].shininess);
            ////////////////////////////////////////
            if(norm==1)glNormal3f(mod.normals()[mod.faces()[i].n[0]],mod.normals()[mod.faces()[i].n[0]+1],mod.normals()[mod.faces()[i].n[0]+2]);
            glVertex3f(mod.vertices()[mod.faces()[i].v[0]],mod.vertices()[mod.faces()[i].v[0]+1],mod.vertices()[mod.faces()[i].v[0]+2]);
            if(norm==1)glNormal3f(mod.normals()[mod.faces()[i].n[1]],mod.normals()[mod.faces()[i].n[1]+1],mod.normals()[mod.faces()[i].n[1]+2]);
            glVertex3f(mod.vertices()[mod.faces()[i].v[1]],mod.vertices()[mod.faces()[i].v[1]+1],mod.vertices()[mod.faces()[i].v[1]+2]);
            if(norm==1)glNormal3f(mod.normals()[mod.faces()[i].n[2]],mod.normals()[mod.faces()[i].n[2]+1],mod.normals()[mod.faces()[i].n[2]+2]);
            glVertex3f(mod.vertices()[mod.faces()[i].v[2]],mod.vertices()[mod.faces()[i].v[2]+1],mod.vertices()[mod.faces()[i].v[2]+2]);
            glEnd();
    }
    glPopMatrix();
    glLightfv(GL_LIGHT1, GL_POSITION, posl1);
    glLightfv(GL_LIGHT2, GL_POSITION, posl2);
    glLightfv(GL_LIGHT3, GL_POSITION, posl3);
    glLightfv(GL_LIGHT4, GL_POSITION, posl4);
    glPushMatrix();
    glBegin(GL_QUADS);
    glNormal3f(0.0,1.0,0.0);
        glVertex3f(minx*4,miny,minz*4);
        glVertex3f(minx*4,miny,maxz*4);
        glVertex3f(maxx*4,miny,maxz*4);
        glVertex3f(maxx*4,miny,minz*4);
    glEnd();
    glPopMatrix();
    glutSolidSphere(0.7, 20, 16);
    glutSwapBuffers();
}
/////////////////////////////////////////
// Reajusta la pantalla, conservando las proporciones originales de las figuras
void resize(int ample, int alt){
    altura=alt;
    anchura=ample;
	if(ample>alt) glViewport((ample-alt)/2,0,alt,alt);
	else glViewport(0,(alt-ample)/2,ample,ample);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(60.0,1.0,1.0,100000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt (x, y, z,x1,y1, z1, 0.0, 1.0, 0.0);
   
}
//////////////////////////////////////
//Funcion que se activa al hacer click con el mouse; Responde tanto a pulsado como a despulsado
void click_mouse(int boto,int no_pulsado,int x,int y){
	if(!no_pulsado){
        
    }
    glutPostRedisplay();
}

int main(int argc, const char **argv){

	glutInit(&argc,(char **) argv);//Necesaria
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);//Inecesaria
	glutInitWindowSize(altura,anchura);//Necesaria, aunque el tamaño estandar ya es 800x600
	glutCreateWindow("IDI:Practicas OpenGL");//Necesaria, crea la ventana
	initGL();
	glutDisplayFunc(refresh);//Necesaria si queremos usar nuestra funcion
	glutReshapeFunc(resize);
	glutMouseFunc(click_mouse);
    glutKeyboardFunc(keyboard_action);
    //glutMotionFunc(cambia_triangulo);
	glutMainLoop();//Muy necesaria, lanza el programa
	return 0;
}