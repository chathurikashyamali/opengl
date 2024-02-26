#include <glut.h>  
#include <math.h>  
#include <stdio.h>

int ww = 800, wh = 850;  
int first = 0;  
int xi, yi, xf, yf;  
int h0,h1,k0,k1,r0,r1;

//x and Y values of hexagon
int xvalue[] = {200,300,500,600,500,300};
int yvalue[] = {wh-400,wh-573,wh-573,wh-400,wh-227,wh-227};

void putPixel (int x, int y)  
{  
	if( (x>=200 && x<=600) && (y>=wh-573 && y<=wh-227) )
	{
		glPointSize(3.0);
		glBegin (GL_POINTS);  
		glVertex2i (x, y);
		glEnd (); 
	}
    glFlush ();  
} 

//midPoint Circle Algorithm
void plotCircle(int h, int k, int x, int y)
{
	putPixel((x+h), (y+k)); //x,y
	putPixel((y+h), (x+k));//y, x
	putPixel((-y+h), (x+k));//-y, x
	putPixel((-x+h), (y+k));//-x, y
	putPixel((-x+h), (-y+k));//-x,-y
	putPixel((-y+h), (-x+k));//-y,-x
	putPixel((y+h), (-x+k));//y,-x
	putPixel((x+h), (-y+k));//x,-y

}




//bresenham line algorithm
void bresenhamAlg (int x0, int y0, int x1, int y1)  
{  
  int dx = abs (x1 - x0);  
  int dy = abs (y1 - y0);  
  int x, y;  
  if (dx >= dy)  
  {  
   int d = 2*dy-dx;  
   int ds = 2*dy;  
   int dt = 2*(dy-dx);  
       if (x0 < x1)   
       {  
            x = x0;  
            y = y0;  
        }  
        else  
        {   
            x = x1;  
            y = y1;  
            x1 = x0;  
            y1 = y0;  
        }  
  putPixel (x, y);  
  while (x < x1)  
  {  
    if (d < 0)  
        d += ds;  
        else {  
             if (y < y1) {  
               y++;  
               d += dt;  
				}   
             else {  
				y--;  
				d += dt;             
			 }  
		}  
        x++;  
		putPixel (x, y);  
    }  
}  
       else {   
           int d = 2*dx-dy;  
             int ds = 2*dx;  
             int dt = 2*(dx-dy);  
             if (y0 < y1) 
			 {  
				 x = x0;  
				 y = y0;  
             }  
             else 
			 {   
				 x = x1;  
				 y = y1;  
				 y1 = y0;  
				x1 = x0;  
             }  
            putPixel (x, y);   
        while (y < y1)  
        {  
              if (d < 0)  
                 d += ds;  
             else {  
                   if (x < x1)
				   {  
						x++;  
						d += dt;  
					} else 
					{  
						x--;  
						d += dt;  
					}                
				}  
			y++;  
             putPixel (x, y);
			 
       }        
	}  
}  




void display()  
{  
   glClearColor(1.0, 1.0, 1.0, 1.0);  
   //glColor3f(0.2, 0.3, 0.3);  
   glClear(GL_COLOR_BUFFER_BIT);
   glFlush();  
}  
//circle filling functions
void drawHorizontalLine(int x1,int y1,int x2,int y2)
{	
	glPointSize(3.0);
	glBegin(GL_LINES);
		glVertex2i(x1, y1);
		glVertex2i(x2, y2);
	glEnd();
	glFlush();
}

void horizontalLine(int h, int k, int x, int y)
{
	glColor3f (0.0, 0.0, 1.0);
	drawHorizontalLine(-x+h,y+k,x+h,y+k);
	drawHorizontalLine(-y+h,x+k,y+h,x+k);
	drawHorizontalLine(-y+h,-x+k,y+h,-x+k);
	drawHorizontalLine(-x+h,-y+k,x+h,-y+k);
}

//midpoint circle algorithm
void midPointCircle(int h, int k, int r)
{
	int x=0, y=r, p=1-r;
	while(x <= y)
	{
		plotCircle(h, k, x, y);
		horizontalLine(h, k, x, y);
		if(p<0)
		{
			p = p + 2*x + 3; 
		}
		else
		{
			p = p + 2*(x-y) + 5;
			y--;
		}
		x++;
	}
}

//To draw external circles
void midPointCircleWithoutFill(int h, int k, int r)
{
	
	int x=0, y=r, p=1-r;
	while(x <= y)
	{
		plotCircle(h, k, x, y);
		if(p<0)
		{
			p = p + 2*x + 3; 
		}
		else
		{
			p = p + 2*(x-y) + 5;
			y--;
		}
		x++;
	}
}



void mouse(int btn, int state, int x, int y)
{
    if (btn == GLUT_LEFT_BUTTON)
        if (state == GLUT_DOWN)
        {
            xi = x;
            yi = (wh - y);
        }
        else if (state == GLUT_UP) {
            xf = x;
            yf = (wh - y);

			
            
            // Calculate the radius of the new circle
            int r = (int)sqrt((double)(xi - xf) * (xi - xf) + (yi - yf) * (yi - yf));

            // Draw the original circle
            midPointCircle(400, wh-400, 200);

            //Draw externel circles
			glColor3f (1,0, 0);//red
            midPointCircleWithoutFill(200, wh-400, 200);
			midPointCircleWithoutFill(500, wh-573.2, 200);
			glColor3f(0.0, 1.0, 0.0); // Set color to green

			midPointCircleWithoutFill(300,wh-573.2, 200);
			midPointCircleWithoutFill(300, wh-226.8, 200);
			midPointCircleWithoutFill(600, wh-400, 200);
			glColor3f (1,0, 0);//red
			midPointCircleWithoutFill(500, wh-226.8, 200);

			glColor3f (1,1, 1);//white

			//drawing hexagon
			int a = 0;
			while(a<6)
			{
				xi = xvalue[a];
				yi = yvalue[a];
				xf = xvalue[(a+1)%6];
				yf = yvalue[(a+1)%6];
				bresenhamAlg( xi,  yi,  xf, yf);
				a++;
			}


			
			
			glColor3f(1.0, 1.0, 0.0); // Set color to yellow
			bresenhamAlg (200, wh-400, 600, wh-400);
			bresenhamAlg (500, wh-573.2, 300, wh-226.8);
			bresenhamAlg (300, wh-573.2, 500, wh-226.8);
			
			

            glFlush();
			


        }
    if (btn == GLUT_RIGHT_BUTTON) {
        glClear(GL_COLOR_BUFFER_BIT);
        glFlush();
    }
}


void myinit()  
{        
     glViewport(0,0,ww,wh);  
     glMatrixMode(GL_PROJECTION);  
     glLoadIdentity();  
     gluOrtho2D(0.0,(GLdouble)ww,0.0,(GLdouble)wh);  
     glMatrixMode(GL_MODELVIEW);  
} 


int main(int argc, char** argv)  
{  
     glutInit(&argc,argv);  
     glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);  
     glutInitWindowSize(ww,wh); 
	 glutCreateWindow("Flower");
     glutDisplayFunc(display);  
     myinit();  
     glutMouseFunc(mouse);  
     glutMainLoop();  
     return 0;  
}  