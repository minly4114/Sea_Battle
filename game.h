#ifndef GAME_H
#define GAME_H

#include <QMainWindow>
#include <QPushButton>
#include "qpushbutton.h"
#include <QVector>
namespace Ui {
class game;
}

class game : public QMainWindow
{
    Q_OBJECT

public:
    explicit game(QWidget *parent = 0);
    bool for_turn=true, three_turn=true, two_turn=true;
    QString temp;
    QList<QString> lastPos;
    QVector<QString> vectorFieldPlayerForEnemy;
    int **playerAr;
    int **enemyAr;
    ~game();

private slots:
    void on_commandLinkButton_clicked();

    void on_rb_for_clicked();

    void on_rb_three_clicked();

    void on_rb_two_clicked();

    void on_rb_one_clicked();

    void on_clb_turn_clicked();

    void on_btplayer_clicked();

    void on_btenemy_clicked();

    void on_pb_startGame_clicked();

private:
    void createFieldPlayer();
    bool checkCurrentPos(int iFirstNum, int iSecondNum);
    bool checkCurrentPosEnemy(int iFirstNum, int iSecondNum);
    void createFieldEnemy();
    void qetClickCoords(QString d, int *iFirstNum, int *iSecondNum);
    bool checkShipPos(int pressed_ships, int iFirstNum, int iSecondNum);
    void setShipPos(int pressed_ships, bool currentTurn, int iFirstNum, int iSecondNum, QVector<QString> *vector);
    bool checkShipPosEnemy(int pressed_ships, bool currentTurn, int iFirstNum, int iSecondNum);
    bool checkPressedShip(int iFirstNum,int iSecondNum, int status);
    bool checkPressedShipPlayer(int iFirstNum,int iSecondNum, int status);
    int pressed_ship;
    bool isStarted = false;
    Ui::game *ui;
};

#endif // GAME_H
