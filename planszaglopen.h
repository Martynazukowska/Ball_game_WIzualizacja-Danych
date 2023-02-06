#ifndef PLANSZAGLOPEN_H
#define PLANSZAGLOPEN_H

#include <QGLWidget>
#include <QTimer>
#include <QGLFunctions>
#include <QGLShader>
#include <QGLBuffer>
#include <QGLShaderProgram>
#include "ob.h"
#include "podsumowanie.h"

/*!
 *
 * \brief Klasa odpowiedzialna za Widget w którym jest generowana docelowa gra
 *
 */
class planszaGLopen : public QGLWidget
{
    Q_OBJECT
public:
    explicit planszaGLopen(QWidget *parent=0);
    /*!
     * \brief Funkcja inicjalizująca
     */
    void initializeGL();
    /*!
     * \brief Funkcja która cały czas generuje obiekty w Widgecie
     *  Tu tworzone jest 6 losowych przeszkód ,,napływających z dołu"
     *  tylko i wyłącznie w momecie gdy zmienna pomocnicza jest równa 0.
     *
     *  Następnie dane ptzeszkody są po prostu nadpisywane i zmieniane.

     *  Jest to tworzone w tej funkcji ponieważ gdybyśmy wygenerowali je
     *  w funkcji initializeGL() nie mglibyśmy uzależnić niketórych zmiennych
     *  od poprawnych wartości wysokości i szerekości okienka.
     *  Następnie również w tym miejscu jest rysowana i przemieszczana piłeczka
     *  odpowiednio do flag oraz jest sprawdzana kolizja i naliczanie punktów.
     */
    void paintGL();
    /*!
     * \brief Funkcja odpwoiedzialna za skolowanie
     */
    void resizeGL(int w, int h);

    /*!
     * \brief Funkcja odpwoiedzialna za sprawdzanie kolizji pilka-przeszkody
     * \param[in] x - połozenie piłeczki w poziomie
     * \param[in] y - położenie piłeczki w pionie
     * \param[in] R - promien piłeczki
     * \param[in,out] live - ilość pozostałych żyć
     */
    int sprawdz_kolizje(float x,float y,double R,int live);

    /*!
     * \brief Funkcja odpwoiedzialna za generowanie dlugości wszytskich nowych przeszkód
     * \param[in] los - losowo generowana wartosc
     * \param[in] pom2 - pomocnicza wartośc wskazująca na szerokość okienka
     */
    void losuj_nowe_przeszkody(int los,GLfloat pom2);

    /*!
     * \brief Funkcja odpwoiedzialna za pnieniesienie przeszkod
     * \param[in] pom3 - pomocnicza wartośc wskazująca na wysokość okienka
     * \param[in] gap - pokazuje wartość odstępu między przeszkodami
     */
    void przenies_przeszkody(GLfloat pom3,float gap);

    /*!
     * \brief Funkcja odpwoiedzialna sprawdzenie czy pokonalismy dane przeszkody
     * \param[in,out] wynik- wartość dotychczas zebranych punktów
     */
    int sprawdz_Score(int wynik);

    /*!
     * \brief Funkcja odpwoiedzialna sprawdzenie czy pokonalismy dane przeszkody
     * \param[in] live- ilosc pozostalych zyc w grze
     * \param[in] ang - kat obrotu zyc
     */
    void draw_live(int live,float ang);

    double R;
    float x,y,z;
    bool wired;

    int tryb;
    int wynik;

    float ang,zjedz;
    int punkty;
    int o_ile;

    int koniec;
    int live;

    przeszkoda przeszkoda1;
    przeszkoda przeszkoda2;
    przeszkoda przeszkoda3;
    przeszkoda przeszkoda4;
    przeszkoda przeszkoda5;
    przeszkoda przeszkoda6;


private:
    void InitShader();
    void InitBuffer();
private:
    QTimer timer;
    QGLShaderProgram shader;
    QGLBuffer* vertexBuffer;
    QGLBuffer* indexBuffer;
     podsumowanie *pod;
    float viewPortWidth;
    float viewPortHeight;
};



#endif // PLANSZAGLOPEN_H
