all:p4

p4:model.o practica4.o
	g++ -o p4 practica4.o model.o -framework OpenGL -framework glut

model.o:model.cpp
	g++ -c model.cpp
    
practica4.o:practica4.c
	g++ -c practica4.c
    
clean:
	rm *o p4
        
