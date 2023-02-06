#include "planszaglopen.h"
#include <GL/glut.h>
#include <cmath>

#define ilosc 5
#define SZEROKOSC 4
#define ZYCIE 3


planszaGLopen::planszaGLopen(QWidget *parent):
    QGLWidget(parent)
{
    this->R=1;
    this->wired=false;
    this->ang=0.5;
    this->zjedz=0;
    connect(&timer,SIGNAL(timeout()),this,SLOT(updateGL()));
    timer.start(16);
    tryb=1;
    wynik=0;
    o_ile=0;
    punkty=0;
    koniec=0;
    live=ZYCIE;

}

void planszaGLopen::initializeGL()
{

    //white
    glClearColor(1,1,1,1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);

}


void planszaGLopen::paintGL()
{
    if(live==0)
    {
        live=ZYCIE;
        wired=0;
        tryb=1;
        koniec=1;
        if(koniec==1)
        {
            koniec=0;
            pod=new podsumowanie(this,wynik);
            pod->show();
        }
        przeszkoda1.wpadniety=0;
        przeszkoda2.wpadniety=0;
        przeszkoda3.wpadniety=0;
        przeszkoda4.wpadniety=0;
        przeszkoda5.wpadniety=0;
        przeszkoda6.wpadniety=0;

    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,0,5,  0,0,0, 0,1,0);


    GLfloat pom2,pom3;
    float pom2_f,pom3_f;

    pom2=((GLfloat)width())/200;
    pom3=((GLfloat)height())/100;
    pom2_f=(float)pom2;
    pom3_f=(float)pom3;

    float width1_f=1;
    float width2_f=1;
    float height_f=0.3;

    GLfloat width1=1;
    GLfloat width2=1;
    GLfloat height=0.3;

    float gap = ((pom3_f/3)-height_f);
    GLfloat GLgap=((pom3/3)-height);


    if(tryb==1&&wired)
    {

        float Y_f=gap;

        przeszkoda Przeszkoda1(-pom2_f,Y_f,width1_f,width2_f,height_f,width1,width2,height);
        Y_f-=GLgap;
        przeszkoda Przeszkoda2(-pom2_f,Y_f,width1_f,width2_f,height_f,width1,width2,height);
         Y_f-=GLgap;
        przeszkoda Przeszkoda3(-pom2_f,Y_f,width1_f,width2_f,height_f,width1,width2,height);
         Y_f-=GLgap;
        przeszkoda Przeszkoda4(-pom2_f,Y_f,width1_f,width2_f,height_f,width1,width2,height);
         Y_f-=GLgap;
        przeszkoda Przeszkoda5(-pom2_f,Y_f,width1_f,width2_f,height_f,width1,width2,height);
        Y_f-=GLgap;
        przeszkoda Przeszkoda6(-pom2_f,Y_f,width1_f,width2_f,height_f,width1,width2,height);
        Y_f-=GLgap;


        this->przeszkoda1=Przeszkoda1;
        this->przeszkoda2=Przeszkoda2;
        this->przeszkoda3=Przeszkoda3;
        this->przeszkoda4=Przeszkoda4;
        this->przeszkoda5=Przeszkoda5;
        this->przeszkoda6=Przeszkoda6;

        o_ile+=5;

        przeszkoda1.Dodaj_gap(o_ile);
        przeszkoda2.Dodaj_gap(o_ile);
        przeszkoda3.Dodaj_gap(o_ile);
        przeszkoda4.Dodaj_gap(o_ile);
        przeszkoda5.Dodaj_gap(o_ile);
        przeszkoda6.Dodaj_gap(o_ile);
      tryb=0;
    }

    int los;

    los=2;


    if(wired)
    {
        glPushMatrix();

        losuj_nowe_przeszkody(los,pom2);

        przenies_przeszkody(pom3,gap);

        live=sprawdz_kolizje(x,y,R,live);

        wynik=sprawdz_Score(wynik);

        zjedz+=0.01;

        glPopMatrix();

        draw_live(live,ang);

        //poczatek rozgrywki
        glPushMatrix();
        glTranslatef(x,y,z);
        glRotatef(ang,1,1,1);
        glColor3f(1,0,0);
        glutWireSphere(R,20,20);
        glPopMatrix();

    }
    ang+=0.5;

    if(tryb==1 && wired==0)
    {
        //zaczynamy w punkcie 0,0,0 duża piłeczka na srodku gry
        glTranslatef(0,0,0);
        glRotatef(ang,1,1,1);
        glColor3f(1,0,0);
        glutSolidSphere(1,20,20);
    }


//    if(wired)
//    {
//        glBegin(GL_POLYGON);
//        for(float x=-1.139;x<1.139;x+=0.001)
//        {
//            float delta=cbrt(x*x)*cbrt(x*x)-4*x*x+4;
//            float y1=(cbrt(x*x)+sqrt(delta))/2;
//            float y2=(cbrt(x*x)-sqrt(delta))/2;
//            glColor3f(1,0,0);
//            glVertex3f(x/6+1.5,y1/6+1.7,0);
//            glColor3f(1,0,0);
//            glVertex3f(x/6+1.5,y2/6+1.7,0);
//        }
//        glEnd();
//        glBegin(GL_POLYGON);
//        for(float x=-1.139;x<1.139;x+=0.001)
//        {
//            float delta=cbrt(x*x)*cbrt(x*x)-4*x*x+4;
//            float y1=(cbrt(x*x)+sqrt(delta))/2;
//            float y2=(cbrt(x*x)-sqrt(delta))/2;
//            glVertex3f(x/6+2,y1/6+1.7,0);
//            glVertex3f(x/6+2,y2/6+1.7,0);
//        }
//        glEnd();
//        glBegin(GL_POLYGON);
//        for(float x=-1.139;x<1.139;x+=0.001)
//        {
//            float delta=cbrt(x*x)*cbrt(x*x)-4*x*x+4;
//            float y1=(cbrt(x*x)+sqrt(delta))/2;
//            float y2=(cbrt(x*x)-sqrt(delta))/2;
//            glVertex3f(x/6+2.5,y1/6+1.7,0);
//            glVertex3f(x/6+2.5,y2/6+1.7,0);
//        }
//        glEnd();
//    }

}

void planszaGLopen::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0,(float)w/h,0.01,100.0);
    updateGL();
}

int planszaGLopen::sprawdz_kolizje(float x,float y ,double R,int live)
{
    if(przeszkoda1.IfCollisionDetect(x,y,R)==1)
    {

        live-=1;

    }
    if(przeszkoda2.IfCollisionDetect(x,y,R)==1)
    {

        live-=1;

    }
    if(przeszkoda3.IfCollisionDetect(x,y,R)==1)
    {

        live-=1;

    }
    if(przeszkoda4.IfCollisionDetect(x,y,R)==1)
    {

        live-=1;

    }
    if(przeszkoda5.IfCollisionDetect(x,y,R)==1)
    {

        live-=1;
    }
    if(przeszkoda6.IfCollisionDetect(x,y,R)==1)
    {
        live-=1;

    }
    return live;


}

void planszaGLopen::losuj_nowe_przeszkody(int los,GLfloat pom2)
{
    przeszkoda1.losuj(los,pom2);
    przeszkoda1.draw(pom2,zjedz);


    przeszkoda2.losuj(los,pom2);
    przeszkoda2.draw(pom2,zjedz);

    przeszkoda3.losuj(los,pom2);
    przeszkoda3.draw(pom2,zjedz);

    przeszkoda4.losuj(los,pom2);
    przeszkoda4.draw(pom2,zjedz);

    przeszkoda5.losuj(los,pom2);
    przeszkoda5.draw(pom2,zjedz);

    przeszkoda6.losuj(los,pom2);
    przeszkoda6.draw(pom2,zjedz);

}

void planszaGLopen::przenies_przeszkody(GLfloat pom3,float gap)
{

    if(przeszkoda1.Ypos-przeszkoda1.height_f>=pom3)
    {
        przeszkoda1.gap=przeszkoda6.gap-gap;
        przeszkoda1.wylosowane=0;
        przeszkoda1.zaliczona=0;
        przeszkoda1.wpadniety=0;
    }
    if(przeszkoda2.Ypos-przeszkoda2.height_f>=pom3)
    {
        przeszkoda2.gap=przeszkoda1.gap-gap;
        przeszkoda2.wylosowane=0;
        przeszkoda2.zaliczona=0;
        przeszkoda2.wpadniety=0;
    }
    if(przeszkoda3.Ypos-przeszkoda3.height_f>=pom3)
    {
        przeszkoda3.gap=przeszkoda2.gap-gap;
        przeszkoda3.wylosowane=0;
        przeszkoda3.zaliczona=0;
        przeszkoda3.wpadniety=0;
    }
    if(przeszkoda4.Ypos-przeszkoda4.height_f>=pom3)
    {
        przeszkoda4.gap=przeszkoda3.gap-gap;
        przeszkoda4.wylosowane=0;
        przeszkoda4.zaliczona=0;
        przeszkoda4.wpadniety=0;
    }

    if(przeszkoda5.Ypos-przeszkoda5.height_f>=pom3)
    {
        przeszkoda5.gap=przeszkoda4.gap-gap;
        przeszkoda5.wylosowane=0;
        przeszkoda5.zaliczona=0;
        przeszkoda5.wpadniety=0;
    }

    if(przeszkoda6.Ypos-przeszkoda6.height_f>=pom3)
    {
        przeszkoda6.gap=przeszkoda5.gap-gap;
        przeszkoda6.wylosowane=0;
        przeszkoda6.zaliczona=0;
        przeszkoda6.wpadniety=0;
    }

}

int planszaGLopen::sprawdz_Score(int wynik)
{
    if(przeszkoda1.IfScore(y))
    {
        wynik+=1;
    }
    if(przeszkoda2.IfScore(y))
    {
        wynik+=1;
    }
    if(przeszkoda3.IfScore(y))
    {
        wynik+=1;
    }
    if(przeszkoda4.IfScore(y))
    {
        wynik+=1;
    }
    if(przeszkoda5.IfScore(y))
    {
        wynik+=1;
    }
    if(przeszkoda6.IfScore(y))
    {
        wynik+=1;
    }
    return wynik;
}

void planszaGLopen::draw_live(int live, float ang)
{

    glPushMatrix();
    glTranslatef(2,1.9,0);
    glRotatef(ang,1,1,1);
    if(live>=1)
    {
        glColor3f(0.6,1,0);
    }
    else
    {
        glColor3f(0,0,0);
    }
    glutSolidSphere(0.1,20,20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.3,1.9,0);
    glRotatef(ang,1,1,1);
    if(live>=2)
    {
        glColor3f(0.6,1,0);
    }
    else
    {
        glColor3f(0,0,0);
    }
    glutSolidSphere(0.1,20,20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.6,1.9,0);
    glRotatef(ang,1,1,1);
    if(live>=3)
    {
        glColor3f(0.6,1,0);
    }
    else
    {
        glColor3f(0,0,0);
    }
    glutSolidSphere(0.1,20,20);
    glPopMatrix();
}



