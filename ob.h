#ifndef OB_H
#define OB_H

#include <GL/glut.h>
#include "math.h"

/*!
 *
 * \brief Zawiera definicję klasy przeszkody
 *
 */


class przeszkoda
{
public:
    float Xpos;
    float Ypos;

    float width1_f;
    float width2_f;
    float height_f;

    GLfloat width1;
    GLfloat width2;
    GLfloat height;

    float gap;

    int zaliczona;
    int wpadniety;
    int wylosowane;
    /*!
     *\brief
     * Konstruktor
     * \param[in] x - wartość głównego początkowego wierzchołka przeszkody
     * \param[in] y - wartość głównego początkowego wierzchołka przeszkody
     * \param[in] długość - długość przeszkody po prawej
     * \param[in] długość2 - długość przeszkody po lewej
     * \param[in] wysokość - wysykość obu tworzonych przeszkód
     * \param[in] Width1 - analogiczna długość
     * \param[in] Width2 - analogiczna długość 2
     * \param[in] Height - analogiczna wysokość
     *
     */
    przeszkoda(float x,float y,float dlugosc,float dlugosc2,float wysokosc,GLfloat Width1, GLfloat Width2, GLfloat Height);
    /*!
     *
     * \brief Zwykły konstrukot
     */
    przeszkoda();
    /*!
     *
     * \brief Funkcja sprawiająca wygenerowanie się przeszkody w widgecie
     * \param[in] pom potrzebny do zdefiniowania szerokości okienka
     * \param[in] zjedz do wiadomości o ile przesunięta powinna być przeszkoda w osi Y (efekt przesówających się przeszkód)
     *
     */
    void draw(GLfloat pom, float zjedz);
    /*!
     *
     * \brief Funkcja równe przeszkody o różnej długości
     * \param[in] los losowa zmienna wcześńiej wygenerowana potrzebna do wybrania rozmieszczenia przeszkody
     * \param[in] pom potrzebna do zweryfikowanie wysokości okienka
     *
     */
    void losuj(int los,GLfloat pom);
    /*!
     *
     * \brief Przeciążenie operatora =
     */
    przeszkoda &operator =( const przeszkoda &pom );
    /*!
     *
     * \brief Funkcja sprawdzjąca kolizje przeszkody z napływającą piłeczka
     * Po koleji sprawdzane są wierzchołki części przeszkody z prawej i lewej strony, a następnie w polu figury
     * \param[in] X_ball współrzędna X położenia piłeczki
     * \param[in] Y_ball współrzędna Y położenia piłeczki
     * \param[in] r Wartość promienia rysowanej piłeczki
     *
     */
    int IfCollisionDetect(float X_ball, float Y_ball, double r);

    /*!
     *
     * \brief Funkcja do zliczanie punktów za pokonane przeszkody
     * \param[in] Y_ball współrzędna y położenia piłeczki umożliwiająca sprawdzenie minięcia przeszkody
     */
    int IfScore(float Y_ball);
    /*!
     *
     * \brief Funkcja do dodawania przerwy na poczatku gry
     * \param[in] ile o ile zwiększyć początkową przerwe
     */
    void Dodaj_gap(int ile);



};
#endif // OB_H
