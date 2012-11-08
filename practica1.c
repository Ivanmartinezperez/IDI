#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#include <stdio.h>

typedef struct {
    float x;
    float y;
    float z;
} punto;
punto triangulo[3];
int contador=0;
int altura=800;
int anchura=800;
unsigned char action = 'n';
// Funcion de inicializacion de parametros para pantalla inicial
void initGL(void){
	glClearColor(0.0,0.0,0.0,0.0);
}
///////////////////////////////
//Funcion que se ejecuta al pulsar una tecla del teclado
void keyboard_action(unsigned char act,int x, int y){
    if (act=='h') {
        printf("Keyboard Actions\n");
        printf(" H: Activa el menu de ayuda.\n");
        printf(" T: Activa el modo dibujado de triangulo, cada vez que quiera dibujar\n    un nuevo triangulo debera presionar esta tecla y hacer click con el mouse\n    en tres puntos de la pantalla que seran los vertices de este.\n");
        printf(" P: Activa el modo pintura, en este modo puede hacer click\n    con el mouse en cualquier lugar de la pantalla, modificando\n    el color de fondo.\n");
    }
    if(act=='t'){
        contador=0;
        action='t';
    }
    if(act=='p') action = 'p';
    glutPostRedisplay();
}
//Funcion de transformacion de coordenadas a puntos dentro del rango opengl; R=[-1,1];
void coor_to_points(int x,int y){
    float x_2= x;
    float y_2= y;
    y_2= (y_2-altura) * -1; // tenemos y en coordenadas de pintado
    
    if(x_2 < (anchura/2)) x_2 = ((x_2-anchura)/(anchura/2))+1; //calculamos el punto pero en la mitad negativa de la pantalla
    else x_2 = (x_2 / (anchura/2)) -1; // calculamos el punto para la mitad positiva de la pantalla
    
    if(y_2 < (altura/2)) y_2 = ((y_2-altura)/(altura/2)) +1;
    else y_2 = (y_2 / (altura/2)) -1;
    
    triangulo[contador].x=x_2;
    triangulo[contador].y=y_2;
}
/////////////////////////
// Funcion que dibuja un triangulo
void pinta_triangulo(punto entrada[]){
    glBegin(GL_TRIANGLES);
        glColor3f(1.0,0.0,0.0);
        glVertex3f(entrada[0].x,entrada[0].y,0.0);
        glVertex3f(entrada[1].x,entrada[1].y,0.0);
        glVertex3f(entrada[2].x,entrada[2].y,0.0);
    glEnd();
}
//////////////////////////////////
// Funcion a la que llama el main para refrescar la pantalla; NOTA(Se ejecuta en cada iteracion del main);
void refresh(void){
	glClear(GL_COLOR_BUFFER_BIT);
    if(contador==3)pinta_triangulo(triangulo);
    glutSwapBuffers();
}
/////////////////////////////////////////
// Reajusta la pantalla, conservando las proporciones originales de las figuras
void resize(int ample, int alt){
    altura=alt;
    anchura=ample;
	if(ample>alt) glViewport((ample-alt)/2,0,alt,alt);
	
	else glViewport(0,(alt-ample)/2,ample,ample);
}
//////////////////////////////////////
//Funcion que se activa al hacer click con el mouse; Responde tanto a pulsado como a despulsado
void click_mouse(int boto,int no_pulsado,int x,int y){
	if(!no_pulsado & action=='t'){
        coor_to_points(x,y);// Convertimos cordenadas de la pantalla al rango de puntos opengl
        if(contador!=3)++contador;
    }
    if(!no_pulsado & action=='p'){
        float r = x;
        float g = y;
        r=r/anchura;
        g=g/anchura;
        float b = r+g;
        b = b/(anchura+altura);
        glClearColor(r,g,b,0.0);
    }
    glutPostRedisplay();
}

int main(int argc, const char **argv){

	glutInit(&argc,(char **) argv);//Necesaria
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);//Inecesaria
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