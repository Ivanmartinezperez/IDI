#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#include <stdio.h>

typedef struct {
    float x;
    float y;
    float z;
} punto;
punto triangulo[3];
punto triangulo2[3];
int contador=0;
int contador2=0;
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
        glLoadIdentity();
    }
    if(act=='q'){
        contador2=0;
        action='q';
        glLoadIdentity();
    }
    if(act=='p') action = 'p';
    if(act=='m') action = 'm';
    if(act=='s') action= 's';
    if(act=='r') action= 'r';
    //glutPostRedisplay();
    
}
//Funcion de transformacion de coordenadas a puntos dentro del rango opengl; R=[-1,1];
void coor_to_points(int x,int y,int control){
    float x_2= x;
    float y_2= y;
    y_2= (y_2-altura) * -1; // tenemos y en coordenadas de pintado
    
    if(x_2 < (anchura/2)) x_2 = ((x_2-anchura)/(anchura/2))+1; //calculamos el punto pero en la mitad negativa de la pantalla
    else x_2 = (x_2 / (anchura/2)) -1; // calculamos el punto para la mitad positiva de la pantalla
    
    if(y_2 < (altura/2)) y_2 = ((y_2-altura)/(altura/2)) +1;
    else y_2 = (y_2 / (altura/2)) -1;
    
    if(control==0){
        printf("control0\n");
        triangulo[contador].x=x_2;
        triangulo[contador].y=y_2;
    }
    else if(control==1){
        printf("control1");
        triangulo2[contador2].x=x_2;
        triangulo2[contador2].y=y_2;
    }
}
/////////////////////////
// Funcion que dibuja un triangulo
void pinta_triangulo(punto entrada[]){
    
    printf("%f---%f\n",entrada[0].x,entrada[0].y);
    printf("%f---%f\n",entrada[1].x,entrada[1].y);
    printf("%f---%f\n",entrada[2].x,entrada[2].y);
    
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
    glutWireSphere(0.5,90,90);
    glutWireSphere(0.25,90,90);
    glRotatef(15,0.0,1.1,0.0);
    if(contador==3)pinta_triangulo(triangulo);
    if(contador2==3)pinta_triangulo(triangulo2);
    glutSwapBuffers();
    //glLoadIdentity();
    
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
        coor_to_points(x,y,0);// Convertimos cordenadas de la pantalla al rango de puntos opengl
        if(contador!=3)++contador;
    }
    if(!no_pulsado & action=='q'){
        coor_to_points(x,y,1);// Convertimos cordenadas de la pantalla al rango de puntos opengl
        if(contador2!=3)++contador2;
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
    if(!no_pulsado & action=='m'){
        float r=0;
        float g=0;
        scanf("%f",&r);
        scanf("%f",&g);
        glTranslatef(r,g,0.0);
    }
    if(!no_pulsado & action=='r'){
        float angle=0;
        char g='x';
        scanf("%f",&angle);
        scanf("%c",&g);
        if(g=='x')glRotatef(angle,1.0,0.0,0.0);
        else if(g=='y') glRotatef(angle,0.0,1.0,0.0);
        else glRotatef(angle,0.0,0.0,1.0);
    }
    if(!no_pulsado & action=='s'){
        float r=0;
        float g=0;
        scanf("%f",&r);
        scanf("%f",&g);
        glScalef(r,g,0.0);
    }
    if(!no_pulsado)glutPostRedisplay();
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