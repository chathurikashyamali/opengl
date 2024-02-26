//necessary header files for windows and OpenGL
//provide function functions for handling window creation and openGL rendering
#include <windows.h>
#include <glut.h>//glut stands for openGL utility Toolkit

//init() function initializes OpenGl settingsit sets the clear color to red.drawing color to white, 
//and sets up an orthographic projection matrix covering a cube from -1 to 1 along each axis.
void init()
{
	glClearColor (1.0, 0.0, 0.0, 1.0);//sets the clearing color for buffer
	//sets the color to red. four values. Four values represent red,green,blue and alpha components(RGBA), and they range from 0.0 to 1.0.

	glColor3f(1.0, 1.0, 1.0); // sets the current drawing color in RGB format.
	//Here, it sets the colorto white(maximum values for red, green, and blue).

	glMatrixMode (GL_PROJECTION); //'glMatrixMode' sets the current matrix mode.
	//it sets it to 'GL_PROJECTION', which means subsequent matrix operatin will affect the projection matrix.
	glLoadIdentity (); //replaces the current matrix with the identity matrix. It essentially resets the current matrix to a default state
	//'glOrtho' sets up an orthographic projection matrix. It defines the clipping volume in the coordinates specified.
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);  
}


//Draw a colored square
void mydisplay(){
    glClear(GL_COLOR_BUFFER_BIT);//clears the color buffer
	//essentially setting the entire window to the clear color specified in the 'glClearColor' function.
	//Tin line is commonly used at the begining of a rendering function to clear the screeen before drawing. 
	
	glBegin(GL_POLYGON); //marks the begining of a block of vertex data for a polygon
	//the type of primitive being drawn is specified as 'GL_POLYGON'. Subsequent calls to 'glVertex2f' provide the vertices for the polygon.

		glVertex2f(-0.5, -0.5);   //'glVertex' specifies the vertices of the polygon.     
		glVertex2f(-0.5, 0.5);        
		glVertex2f(0.5, 0.5);        
		glVertex2f(0.5, -0.5);    
		//These are 2D coordinates in the window space.

	glEnd();//marks the end of the block of vertex data for the polygon.This is necessary after specifying the  vertices using 'glVertex2f'

	glFlush();//ensures that all the issued OpenGl commands are executed as quickly as possible.
	//In this case, it ensures that the specified polygon is drawn to the screen.
}

//Draw four points
void mydisplay2(){
    glClear(GL_COLOR_BUFFER_BIT); //clears the color buffer,setting the entire window to the clear color specified in the 'glClearColor' function.
	//This line is used at the begining of a rendering function to clear the screen before drawing.

	glPointSize(10.0f);//sets the size of the points to be drawn.Here, it sets the point size to 10.0 pixels
	glBegin(GL_POINTS);//marks the begining of a block of vertex data for points.
	//The type of primitive being drawn is specified as 'GL_POINTS'. Subsequent calls to 'glVertex2f'provide the coordinates for each point.

		glVertex2f(-0.5, -0.5);//specifies the coordinates of the points.In this case , it defines four points.     
		glVertex2f(-0.5, 0.5);        
		glVertex2f(0.5, 0.5);        
		glVertex2f(0.5, -0.5);

	glEnd();//marks the end of the block of vertex data for points.
	//This is necessary after specifying the coordinates using 'glVertex2f'.

	glFlush(); //ensures that the all the issued opengl commmands are executed as quickly as possible.
	//it ensures that the specified points are drawn to the screen.
}
//Draw two lines
void mydisplay3(){
    glClear(GL_COLOR_BUFFER_BIT); //clears the color buffer
	//color buffer is a region of memory that stores the color values of each pixel on the screen.
	//'GL_COLOR_BUFFER_BIT' is a flag specifying which buffer to clear, in this case, the color buffer.
	
	glLineWidth(3.0f);//
	glBegin(GL_LINES);        
		glVertex2f(-0.5, -0.5);        
		glVertex2f(-0.5, 0.5);        
		glVertex2f(0.5, 0.5);        
		glVertex2f(0.25, -0.75);    
	glEnd();
	glFlush(); 
}

//Draw a four side polygon
void mydisplay4(){
    glClear(GL_COLOR_BUFFER_BIT); 
	glLineWidth(3.0f);
	//specifies that the vertices provided between glBegin and glEnd will form a closed loop
	glBegin(GL_LINE_LOOP);//connects each vertex to the next one and automatically connects the last vertex back to the first one to form a closed shape.        
		glVertex2f(-0.5, -0.5);        
		glVertex2f(-0.5, 0.5);        
		glVertex2f(0.5, 0.5);        
		glVertex2f(0.25, -0.75);    
	glEnd();
	glFlush(); 
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);  
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("simple");     
	glutDisplayFunc(mydisplay);  
	init();  
	glutMainLoop();
}