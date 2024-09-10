#include <GL/glut.h>

// to use print point
#include<stdio.h>

int first = 0;
int xs=0,ys=0,xf=0,yf=0;

// initial point
char initialpoint[10], finalpoint[10];

void *font =GLUT_BITMAP_HELVETICA_18;

void showstring(int x,int y,char *string){
    // start write in position
    glRasterPos2i(x,y);

    int str_length = (int) strlen(string);
    for(int i=0 ; i<=str_length; i++)
        glutBitmapCharacter(font, string[i]);
}

void drawpixel(GLint x,GLint y) {
    glBegin(GL_POINTS);
         glVertex2i(x,y);
         glEnd();
}

void bressenham(int x1,int y1,int x2,int y2){
    int dx,dy,po;
    dx=x2-x1;
    dy=y2-y1;

    int Xinc=(dx<0)?-1:1;
    int Yinc=(dx<0)?-1:1;

    dx=abs(dx);
    dy=abs(dy);

    int xk=x1;
    int yk=y1;

    if (dy<dx) {
        po=2*dy-dx;
        drawpixel(x1,y1);
        for(int k=x1; k<= x2; k++) {
            if(po<0){
                drawpixel(++xk,yk);
                po+=2*dy;
            }
            else {
                drawpixel(++xk , yk= yk + Yinc);
                po+=2*dy-2*dx;
            }
        }
    }
    else {
        po=2*dx-dy;
        drawpixel(x1,y1);
        for(int k=y1; k<= y2; k++) {
            if(po<0){
                drawpixel(xk,++yk);
                po+=2*dx;
            }
            else {
                drawpixel(xk = xk + Xinc , ++yk);
                po+=2*dx-2*dy;
            }
        }
    }
}

void display () {
    glClearColor(1.0f,1.0f,0.0f,0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,0.0,0.0);
    // when was using two draw points
    //glPointSize(15);
    //drawpixel(xs,ys);
    //drawpixel(xf,yf);

    showstring(xs+5, ys, initialpoint);
    showstring(xf+5, yf, finalpoint);


    if (first==0) {
        int dx=xf-xs;
        int dy=yf-ys;

        if (abs(dy)< abs(dx)) {
            if (xs < xf)
                bressenham(xs,ys,xf,yf);
            else
               bressenham(xf,yf,xs,ys);
        }
        else {
            if (ys<yf)
                bressenham(xs,ys,xf,yf);
            else
                bressenham(xf,yf,xs,ys);
        }
    }
    glFlush();
    glFinish();
}


void mouse( int btn, int state, int x, int y) {
    if (btn==GLUT_LEFT_BUTTON && state== GLUT_DOWN)
    {
        switch(first){
        case 0:
            // initial value
            sprintf(initialpoint, " ");
            sprintf(finalpoint, " ");
            xs=x;
            ys=600 - y;
            sprintf(initialpoint, "(%d,%d)",xs,ys);
            first=1;
            break;
        case 1:
            xf=x;
            yf=600 - y;
            sprintf(finalpoint, "(%d,%d)",xf,yf);
            first=0;
           break;
        }
        //drawpixel(x, 600-y);

    }
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Bressenham LDA");
    gluOrtho2D(0,800,0,600);

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();

    return 0;
}
