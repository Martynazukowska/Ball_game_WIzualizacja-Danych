#include "ob.h"

przeszkoda::przeszkoda(float x,float y,float dlugosc1,float dlugosc2,float wysokosc,GLfloat Width1, GLfloat Width2, GLfloat Height)
{
    Xpos=x;
    Ypos=y;

    width1_f=dlugosc1;
    width2_f=dlugosc2;
    height_f=wysokosc;

    width1=Width1;
    width2=Width2;
    height=Height;
    wylosowane=0;
    zaliczona=0;
    wpadniety=0;
    gap=y;
}

przeszkoda::przeszkoda()
{
    Xpos=0;
    Ypos=0;

    width1_f=0;
    width2_f=0;
    height_f=0;

    width1=0;
    width2=0;
    height=0;
    wylosowane=0;
    zaliczona=0;
    gap=0;

}

void przeszkoda::losuj(int los, GLfloat pom)
{
    if(wylosowane==0)
    {
        los=rand() % 4;
        switch(los)
        {
        case 0:
            //prawa strona
            width1=pom/4;
            width2=pom;
            width1_f=pom/4;
            width2_f=pom;
            wylosowane=1;
            break;
        case 1:
            //lewa
            width1=pom;
            width2=pom/4;
            width1_f=pom;
            width2_f=pom/4;
            wylosowane=1;
            break;
        case 2:
            //srodek
            width1=pom/2;
            width2=pom/2.5;
            width1_f=pom/2;
            width2_f=pom/2.5;
            wylosowane=1;
            zaliczona=0;
            break;
        case 3:
            width1=pom/2.5;
            width2=pom/2;
            width1_f=pom/2.5;
            width2_f=pom/4;
            wylosowane=1;
            break;
        }
    }
}


przeszkoda &przeszkoda::operator =(const przeszkoda &pom)
{
    width1=pom.width1;
    width2=pom.width2;
    width1_f=pom.width1_f;
    width2_f=pom.width2_f;
    wylosowane=pom.wylosowane;
    Xpos=pom.Xpos;
    Ypos=pom.Ypos;
    height=pom.height;
    height_f=pom.height_f;
    gap=pom.gap;
    zaliczona=pom.zaliczona;

    return *this;
}

double length(float z,float y)
{
    return sqrt((z*z)+(y*y));
}


int przeszkoda::IfCollisionDetect(float X_ball, float Y_ball, double r)
{
    if(wpadniety==0)
    {
        if(length(-Xpos - X_ball, Ypos - Y_ball)< r)
        {
            wpadniety=1;
            return 1;
        }

        if(length(-Xpos - width1 - X_ball, Ypos - Y_ball)	< r)
        {
            wpadniety=1;
            return 1;
        }

        if(length(-Xpos - X_ball, Ypos + height - Y_ball)< r)
        {
            wpadniety=1;
            return 1;
        }

        if(length(-Xpos - width1 - X_ball, Ypos + height - Y_ball)< r)
        {
            wpadniety=1;
            return 1;
        }
        if(length(Xpos - X_ball, Ypos - Y_ball)< r)
        {
            wpadniety=1;
            return 1;
        }

        if(length(Xpos + width2 - X_ball, Ypos - Y_ball)	< r)
        {
            wpadniety=1;
            return 1;
        }

        if(length(Xpos - X_ball, Ypos + height - Y_ball)< r)
        {
            wpadniety=1;
            return 1;
        }

        if(length(Xpos + width2 - X_ball, Ypos + height - Y_ball)< r)
        {
            wpadniety=1;
            return 1;
        }
        if(Y_ball + (2*r) > Ypos && Y_ball - (2*r) < Ypos)
        {
            if(X_ball > -Xpos - width1 && X_ball < -Xpos )
            {
                wpadniety=1;
                return 1;
            }
        }

        if(Y_ball + (2*r) > Ypos && Y_ball - (2*r) < Ypos)
        {
            if(X_ball > Xpos && X_ball < Xpos + width2)
            {
                wpadniety=1;
                return 1;
            }
        }
    }
    return 0;
}

int przeszkoda::IfScore(float Y_ball)
{
    if(zaliczona==0 && wpadniety==0)
    {
        if(Y_ball<Ypos+height)
        {
            zaliczona=1;

            return 1;
        }
    }
    return 0;
}

void przeszkoda::Dodaj_gap(int ile)
{
    gap=gap-ile;
}

void przeszkoda::draw(GLfloat pom2, float zjedz) // mozliwe miejsce na skalowanie
{
    Xpos=-pom2;
    Ypos=zjedz+gap;

        glBegin(GL_QUADS);
        //przeszkoda po lewej
            glNormal3f(0,0,-1);
            glVertex3f(-pom2,Ypos,0);
            glVertex3f(-pom2,Ypos+height,0);
            glVertex3f(-pom2+width2,Ypos+height,0);
            glVertex3f(-pom2+width2,Ypos,0);
        glEnd();




    glBegin(GL_QUADS);
    //przeszkoda po prawej
        glNormal3f(0,0,-1);
        glVertex3f(pom2,Ypos,0);
        glVertex3f(pom2,Ypos+height,0);
        glVertex3f(pom2-width1,Ypos+height,0);
        glVertex3f(pom2-width1,Ypos,0);
    glEnd();
}


