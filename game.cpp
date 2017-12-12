#include "game.h"
#include "ui_game.h"
#include "qdatetime.h"

void game::createFieldPlayer()
{
    for(int i=0; i<11; i++)
    {
        for(int j=0; j<11; j++)
        {
            if(i==0&&j>0)
            {
                QString temp = QString::fromLatin1("btPlayer ") + QString::number(i) + QString::fromLatin1(" ") + QString::number(j);
                QString text = QString::number(j);
                QPushButton *bt = new QPushButton(text, this);
                bt->setGeometry(60+i*30,80+j*30,30,30);
                bt->setObjectName(temp);
                bt->setStyleSheet(QString::fromLatin1("background-color: rgb(255, 255, 255); color: rgb(87, 123, 255); font: 75 16pt;"));
                connect(bt, SIGNAL(clicked(bool)), this, SLOT(on_btplayer_clicked()));
            }
            else if(j==0&&i>0)
            {
                QString temp = QString::fromLatin1("btPlayer ") + QString::number(i) + QString::fromLatin1(" ") + QString::number(j);
                QChar text = QChar((int)'A'+i-1);
                QPushButton *bt = new QPushButton(text, this);
                bt->setGeometry(60+i*30,80+j*30,30,30);
                bt->setObjectName(temp);
                bt->setStyleSheet(QString::fromLatin1("background-color: rgb(255, 255, 255); color: rgb(87, 123, 255); font: 75 16pt;"));
                connect(bt, SIGNAL(clicked(bool)), this, SLOT(on_btplayer_clicked()));
            }
            else
            {
                QString temp = QString::fromLatin1("btPlayer ") + QString::number(i) + QString::fromLatin1(" ") + QString::number(j);
                QPushButton *bt = new QPushButton( this);
                bt->setGeometry(60+i*30,80+j*30,30,30);
                bt->setObjectName(temp);
                bt->setStyleSheet(QString::fromLatin1("background-color: rgb(255, 255, 255); color: rgb(87, 123, 255); font: 75 16pt;"));
                connect(bt, SIGNAL(clicked(bool)), this, SLOT(on_btplayer_clicked()));
            }
        }
    }
}

void game::on_btplayer_clicked()
{
    if(!isStarted)
    {
        ui->ll_enterInfo->setText("");
        QString text_for = ui->ll_numOfSheeps_for->text();
        QString text_three= ui->ll_numOfSheeps_three->text();
        QString text_two = ui->ll_numOfSheeps_two->text();
        QString text_one = ui->ll_numOfSheeps_one->text();
        int iFirstNum;
        int iSecondNum;
        QPushButton *bt = qobject_cast<QPushButton *>(sender());
        QString d = (QString)bt->objectName();
        qetClickCoords(d, &iFirstNum, &iSecondNum);

        if(pressed_ship == 4 && text_for.toInt() < 1) { ui->ll_enterInfo->setText("Невозможно разместить корабль"); return; }
        if(pressed_ship == 3 && text_three.toInt() < 1) { ui->ll_enterInfo->setText("Невозможно разместить корабль"); return; }
        if(pressed_ship == 2 && text_two.toInt() < 1) { ui->ll_enterInfo->setText("Невозможно разместить корабль"); return; }
        if(pressed_ship == 1 && text_one.toInt() < 1) { ui->ll_enterInfo->setText("Невозможно разместить корабль"); return; }

        if(checkShipPos(pressed_ship, iFirstNum, iSecondNum))
        {
            for(int i=0; i<pressed_ship; i++)
            {
                bool currentTurn = true;
                if(pressed_ship == 4) currentTurn = for_turn;
                else if(pressed_ship == 3) currentTurn = three_turn;
                else if(pressed_ship == 2) currentTurn = two_turn;
                if(currentTurn)
                {
                    playerAr[iFirstNum+i][iSecondNum]=1;
                    QString text = "btPlayer "+ QString::number(iFirstNum +i) + " " + QString::number(iSecondNum);
                    QPushButton *button = this->findChild<QPushButton *>(text);
                    button->setStyleSheet("background-color: rgb(61, 80, 255);");
                }
                else
                {
                    playerAr[iFirstNum][iSecondNum+i]=1;
                    QString text = "btPlayer "+ QString::number(iFirstNum) + " " + QString::number(iSecondNum+i);
                    QPushButton *button = this->findChild<QPushButton *>(text);
                    button->setStyleSheet("background-color: rgb(61, 80, 255);");
                }
            }
            if(pressed_ship == 4) { ui->ll_numOfSheeps_for->setText(QString::number(text_for.toInt() - 1)); }
            if(pressed_ship == 3) { ui->ll_numOfSheeps_three->setText(QString::number(text_three.toInt() - 1)); }
            if(pressed_ship == 2) { ui->ll_numOfSheeps_two->setText(QString::number(text_two.toInt() - 1)); }
            if(pressed_ship == 1) { ui->ll_numOfSheeps_one->setText(QString::number(text_one.toInt() - 1)); }
        }
        else
        {
            ui->ll_enterInfo->setText("Невозможно разместить корабль");
        }
    }
}

void game::createFieldEnemy()
{
    for(int i=0; i<11; i++)
    {
        for(int j=0; j<11; j++)
        {
            if(i==0&&j>0)
            {
                QString temp = QString::fromLatin1("btEnemy ") + QString::number(i) + QString::fromLatin1(" ") + QString::number(j);
                QString text = QString::number(j);
                QPushButton *bt = new QPushButton(text, this);
                bt->setGeometry(420+i*30,80+j*30,30,30);
                bt->setObjectName(temp);
                bt->setStyleSheet(QString::fromLatin1("background-color: rgb(255, 255, 255); color: rgb(87, 123, 255); font: 75 16pt;"));
                connect(bt, SIGNAL(clicked(bool)), this, SLOT(on_btenemy_clicked()));
            }
            else if(j==0&&i>0)
            {
                QString temp = QString::fromLatin1("btEnemy ") + QString::number(i) + QString::fromLatin1(" ") + QString::number(j);
                QChar text = QChar((int)'A'+i-1);
                QPushButton *bt = new QPushButton(text, this);
                bt->setGeometry(420+i*30,80+j*30,30,30);
                bt->setObjectName(temp);
                bt->setStyleSheet(QString::fromLatin1("background-color: rgb(255, 255, 255); color: rgb(87, 123, 255); font: 75 16pt;"));
                connect(bt, SIGNAL(clicked(bool)), this, SLOT(on_btenemy_clicked()));
            }
            else
            {
                QString temp = QString::fromLatin1("btEnemy ") + QString::number(i) + QString::fromLatin1(" ") + QString::number(j);
                QPushButton *bt = new QPushButton( this);
                bt->setGeometry(420+i*30,80+j*30,30,30);
                bt->setObjectName(temp);
                bt->setStyleSheet(QString::fromLatin1("background-color: rgb(255, 255, 255); color: rgb(87, 123, 255); font: 75 16pt;"));
                connect(bt, SIGNAL(clicked(bool)), this, SLOT(on_btenemy_clicked()));
            }
        }
    }

    int ships_one = 4;
    int ships_two = 3;
    int ships_three = 2;
    int ships_for = 1;
    qsrand (QDateTime::currentMSecsSinceEpoch());
    QVector<QString> vector = QVector<QString>();
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            vector.insert(vector.length(), QString::number(i)+QString::number(j));
        }
    }
    enemyAr = new int*[11];

    for(int i=0; i<11; i++)
    {
        enemyAr[i] = new int [11];
    }

    for(int i=0; i<11; i++)
    {
        for(int j=0; j<11; j++)
        {
            enemyAr[i][j] = 0;
        }
    }
    while(ships_for > 0)
    {
        int rotate = qrand() % 2;
        if(rotate == 0)
        {
            int in = qrand() % vector.length();
            QString index = vector.at(in);
            int xPos = QString(index.at(0)).toInt() + 1;
            int yPos = QString(index.at(1)).toInt() + 1;
            if(checkShipPosEnemy(4, true, xPos, yPos))
            {
                ships_for--;
                setShipPos(4, true, xPos, yPos, &vector);
                for(int i=0; i<4; i++)
                {
                    enemyAr[xPos+i][yPos]=1;
                    QString text = "btEnemy "+ QString::number(xPos +i) + " " + QString::number(yPos);
                    //QPushButton *button = this->findChild<QPushButton *>(text);
                    //button->setStyleSheet("background-color: rgb(61, 80, 255);");
                }
            }
        }
        else
        {
            int in = qrand() % vector.length();
            QString index = vector.at(in);
            int xPos = QString(index.at(0)).toInt() + 1;
            int yPos = QString(index.at(1)).toInt() + 1;
            if(checkShipPosEnemy(4, false, xPos, yPos))
            {
                ships_for--;
                setShipPos(4, false, xPos, yPos, &vector);
                for(int i=0; i<4; i++)
                {
                    enemyAr[xPos][yPos+i]=1;
                    QString text = "btEnemy "+ QString::number(xPos) + " " + QString::number(yPos+i);
                    //QPushButton *button = this->findChild<QPushButton *>(text);
                    //button->setStyleSheet("background-color: rgb(61, 80, 255);");
                }
            }
        }
    }
    while(ships_three > 0)
    {
        int rotate = qrand() % 2;
        if(rotate == 0)
        {
            int in = qrand() % vector.length();
            QString index = vector.at(in);
            int xPos = QString(index.at(0)).toInt() + 1;
            int yPos = QString(index.at(1)).toInt() + 1;
            if(checkShipPosEnemy(3, true, xPos, yPos))
            {
                ships_three--;
                setShipPos(3, true, xPos, yPos, &vector);
                for(int i=0; i<3; i++)
                {
                    enemyAr[xPos+i][yPos]=1;
                    QString text = "btEnemy "+ QString::number(xPos +i) + " " + QString::number(yPos);
                    //QPushButton *button = this->findChild<QPushButton *>(text);
                    //button->setStyleSheet("background-color: rgb(61, 80, 255);");
                }
            }
        }
        else
        {
            int in = qrand() % vector.length();
            QString index = vector.at(in);
            int xPos = QString(index.at(0)).toInt() + 1;
            int yPos = QString(index.at(1)).toInt() + 1;
            if(checkShipPosEnemy(3, false, xPos, yPos))
            {
                ships_three--;
                setShipPos(3, false, xPos, yPos, &vector);
                for(int i=0; i<3; i++)
                {
                    enemyAr[xPos][yPos+i]=1;
                    QString text = "btEnemy "+ QString::number(xPos) + " " + QString::number(yPos+i);
                    //QPushButton *button = this->findChild<QPushButton *>(text);
                    //button->setStyleSheet("background-color: rgb(61, 80, 255);");
                }
            }
        }
    }
    while(ships_two > 0)
    {
        int rotate = qrand() % 2;
        if(rotate == 0)
        {
            int in = qrand() % vector.length();
            QString index = vector.at(in);
            int xPos = QString(index.at(0)).toInt() + 1;
            int yPos = QString(index.at(1)).toInt() + 1;
            if(checkShipPosEnemy(2, true, xPos, yPos))
            {
                ships_two--;
                setShipPos(2, true, xPos, yPos, &vector);
                for(int i=0; i<2; i++)
                {
                    enemyAr[xPos+i][yPos]=1;
                    QString text = "btEnemy "+ QString::number(xPos +i) + " " + QString::number(yPos);
                    //QPushButton *button = this->findChild<QPushButton *>(text);
                    //button->setStyleSheet("background-color: rgb(61, 80, 255);");
                }
            }
        }
        else
        {
            int in = qrand() % vector.length();
            QString index = vector.at(in);
            int xPos = QString(index.at(0)).toInt() + 1;
            int yPos = QString(index.at(1)).toInt() + 1;
            if(checkShipPosEnemy(2, false, xPos, yPos))
            {
                ships_two--;
                setShipPos(2, false, xPos, yPos, &vector);
                for(int i=0; i<2; i++)
                {
                    enemyAr[xPos][yPos+i]=1;
                    QString text = "btEnemy "+ QString::number(xPos) + " " + QString::number(yPos+i);
                    //QPushButton *button = this->findChild<QPushButton *>(text);
                    //button->setStyleSheet("background-color: rgb(61, 80, 255);");
                }
            }
        }
    }
    while(ships_one > 0)
    {
        int in = qrand() % vector.length();
        QString index = vector.at(in);
        int xPos = QString(index.at(0)).toInt() + 1;
        int yPos = QString(index.at(1)).toInt() + 1;
        if(checkShipPosEnemy(1, true, xPos, yPos))
        {
            ships_one--;
            setShipPos(1, true, xPos, yPos, &vector);
            enemyAr[xPos][yPos]=1;
            QString text = "btEnemy "+ QString::number(xPos) + " " + QString::number(yPos);
            //QPushButton *button = this->findChild<QPushButton *>(text);
            //button->setStyleSheet("background-color: rgb(61, 80, 255);");
        }
    }
}
void game::setShipPos(int pressed_ships, bool currentTurn, int iFirstNum, int iSecondNum, QVector<QString> *vector)
{
    if(currentTurn)
    {
        for(int i=iFirstNum-1; i<=iFirstNum+pressed_ships; i++)
        {
            for(int j=iSecondNum-1; j<=iSecondNum+1; j++)
            {
                if((i > 0 && i < 11)&&(j > 0 && j < 11))
                {
                    int pos = vector->indexOf(QString::number(i-1) + QString::number(j-1));
                    if(pos > -1)
                    {
                        vector->removeAt(vector->indexOf(QString::number(i-1) + QString::number(j-1)));
                    }
                }
            }
        }

    }
    else
    {
        for(int i=iFirstNum-1; i<=iFirstNum+1; i++)
        {
            for(int j=iSecondNum-1; j<=iSecondNum+pressed_ships; j++)
            {
                if((i > 0 && i < 11)&&(j > 0 && j < 11))
                {
                    int pos = vector->indexOf(QString::number(i-1) + QString::number(j-1));
                    if(pos > -1)
                    {
                        vector->removeAt(vector->indexOf(QString::number(i-1) + QString::number(j-1)));
                    }
                }
            }
        }
    }
}
void game::on_btenemy_clicked()
{
    ui->ll_enterInfo->setText("");
    QPushButton *bt = qobject_cast<QPushButton *>(sender());
    QString d = (QString)bt->objectName();
    int iFirstNum = 0;
    int iSecondNum = 0;
    bool ship_one_player=true;
    qetClickCoords(d, &iFirstNum, &iSecondNum);
    if(enemyAr[iFirstNum][iSecondNum] != 2&&enemyAr[iFirstNum][iSecondNum] != 3&&enemyAr[iFirstNum][iSecondNum]!=4)
    {
        if(isStarted&&iFirstNum>0&&iSecondNum>0)
        {
            if(enemyAr[iFirstNum][iSecondNum] == 1)
            {
                for(int i=iFirstNum-1;i<=iFirstNum+1;i++)
                {
                    for(int j= iSecondNum-1; j<=iSecondNum+1;j++)
                    {
                        if(i!=iFirstNum||j!=iSecondNum)
                        {
                            if(checkPressedShip(i,j,1))
                            {
                                ship_one_player=false;
                            }
                        }
                    }
                }
                if(ship_one_player)
                {
                    bt->setStyleSheet("background-color: #E60003;");
                    enemyAr[iFirstNum][iSecondNum]=3;
                }
                else
                {
                    bt->setStyleSheet("background-color: #E6CE00;");
                    enemyAr[iFirstNum][iSecondNum]=2;
                }
            }
            else if(enemyAr[iFirstNum][iSecondNum] == 0)
            {
                bt->setStyleSheet("background-color: #C3EAF8;");
                enemyAr[iFirstNum][iSecondNum]=4;
            }


            int in = qrand() % vectorFieldPlayerForEnemy.length();
            QString index = vectorFieldPlayerForEnemy.at(in);
            int xPos = QString(index.at(0)).toInt() + 1;
            int yPos = QString(index.at(1)).toInt() + 1;
            bool ship_one_enemy=true;
            bool go=true;
            while(go)
            {
                if(lastPos.length()!=0)
                {
                    int num1 = (qrand() % 3) - 1;
                    int num2 = (qrand() % 3) - 1;
                    QList<int> iFirstNum,iSecondNum;
                    int f, s;
                    for(int i=0;i<lastPos.length();i++)
                    {
                        qetClickCoords(lastPos.at(i), &f, &s);
                        iFirstNum.append(f);
                        iSecondNum.append(s);
                    }
                    if(iFirstNum.length()>1)
                    {
                        if(iFirstNum.at(0) == iFirstNum.at(1))
                        {
                            xPos=iFirstNum.at(0);
                            if(num2>0)
                            {
                                if(iSecondNum.at(0)<iSecondNum.at(iSecondNum.length()-1))
                                {
                                    yPos=iSecondNum.at(iSecondNum.length()-1)+num2;
                                }
                                else yPos=iSecondNum.at(0)+num2;
                            }
                            else if(num2<0)
                            {
                                if(iSecondNum.at(0)<iSecondNum.at(iSecondNum.length()-1))
                                {
                                    yPos=iSecondNum.at(0)+num2;
                                }
                                else
                                {
                                     yPos=iSecondNum.at(iSecondNum.length()-1)+num2;
                                }

                            }
                            else
                            {
                                if(iSecondNum.at(0)<iSecondNum.at(iSecondNum.length()-1))
                                {
                                    yPos=iSecondNum.at(iSecondNum.length()-1)+1;
                                }
                                else
                                {
                                    yPos=iSecondNum.at(0)+1;
                                }
                            }
                        }

                        if(iSecondNum.at(0)==iSecondNum.at(1))
                        {
                            yPos=iSecondNum.at(0);
                            if(num1>0)
                            {
                                if(iFirstNum.at(0)<iFirstNum.at(iFirstNum.length()-1))
                                {
                                    xPos=iFirstNum.at(iFirstNum.length()-1)+num1;
                                }
                                else
                                {
                                    xPos= iFirstNum.at(0)+num1;
                                }

                            }
                            else if(num1<0)
                            {
                                if(iFirstNum.at(0)<iFirstNum.at(iFirstNum.length()-1))
                                {
                                    xPos=iFirstNum.at(0)+num1;
                                }
                                else
                                {
                                   xPos=iFirstNum.at(iFirstNum.length()-1)+num1;
                                }
                            } else
                            {
                                if(iFirstNum.at(0)<iFirstNum.at(iFirstNum.length()-1))
                                {
                                    xPos=iFirstNum.at(iFirstNum.length()-1)+1;
                                }
                                else
                                {
                                    xPos=iFirstNum.at(0)+1;
                                }
                            }
                        }
                    }
                    else if (num1==0&&num2!=0)
                    {
                        xPos=iFirstNum.at(0) + num1;
                        yPos=iSecondNum.at(0) + num2;
                    } else if(num1!=0 && num2==0)
                    {
                        xPos=iFirstNum.at(0) + num1;
                        yPos=iSecondNum.at(0) + num2;
                    } else if(num1!=0 && num2!=0)
                    {
                        xPos=iFirstNum.at(0) + num1;
                        yPos=iSecondNum.at(0);
                    } else
                    {
                        xPos=iFirstNum.at(0) + 1;
                        yPos=iSecondNum.at(0);
                    }

                    //ui->ll_enterInfo->setText(QString::number(xPos)+lastPos);

                    int pos = vectorFieldPlayerForEnemy.indexOf(QString::number(xPos-1) + QString::number(yPos-1));
                    if(pos>-1)
                    {
                        go=false;
                    }
                } else go = false;
            }
            if(playerAr[xPos][yPos]==1)
            {
                for(int i=xPos-1;i<=xPos+1;i++)
                {
                    for(int j= yPos-1; j<=yPos+1;j++)
                    {
                        if(i!=xPos||j!=yPos)
                        {
                            if(checkPressedShipPlayer(i,j,1))
                            {
                                ship_one_enemy=false;
                            }
                        }
                    }
                }
                if(ship_one_enemy)
                {
                    for(int i=xPos-1;i<=xPos+1;i++)
                    {
                        for(int j= yPos-1; j<=yPos+1;j++)
                        {
                            int pos = vectorFieldPlayerForEnemy.indexOf(QString::number(i-1) + QString::number(j-1));


                            playerAr[xPos][yPos]=3;
                            ui->ll_enterInfo->setText(QString::number(xPos)+QString::number(yPos));
                            lastPos.clear();

                            if(i<11&&j<11&&pos>-1)
                            {
                                vectorFieldPlayerForEnemy.removeAt(vectorFieldPlayerForEnemy.indexOf(QString::number(i-1) + QString::number(j-1)));
                                QString text = "btPlayer "+ QString::number(xPos) + " " + QString::number(yPos);
                                QPushButton *button = this->findChild<QPushButton *>(text);
                                button->setStyleSheet("background-color: #E60003;");

                            }
                        }
                    }

                }
                else
                {
                    int pos = vectorFieldPlayerForEnemy.indexOf(QString::number(xPos-1) + QString::number(yPos-1));
                    if(xPos<11&&yPos<11&&pos>-1)
                    {
                        vectorFieldPlayerForEnemy.removeAt(vectorFieldPlayerForEnemy.indexOf(QString::number(xPos-1) + QString::number(yPos-1)));
                        QString text = "btPlayer "+ QString::number(xPos) + " " + QString::number(yPos);
                        QPushButton *button = this->findChild<QPushButton *>(text);
                        button->setStyleSheet("background-color: #E6CE00;");


                        playerAr[xPos][yPos]=2;
                        lastPos.append(" "+QString::number(xPos)+" "+QString::number(yPos));
                        ui->ll_enterInfo->setText(QString::number(xPos)+QString::number(yPos));
                    }

                }
            }
            else if(playerAr[xPos][yPos] == 0)
            {
                int pos = vectorFieldPlayerForEnemy.indexOf(QString::number(xPos-1) + QString::number(yPos-1));
                if(xPos<11&&yPos<11&&pos>-1)
                {
                    vectorFieldPlayerForEnemy.removeAt(vectorFieldPlayerForEnemy.indexOf(QString::number(xPos-1) + QString::number(yPos-1)));
                }
                QString text = "btPlayer "+ QString::number(xPos) + " " + QString::number(yPos);
                QPushButton *button = this->findChild<QPushButton *>(text);
                button->setStyleSheet("background-color: #C3EAF8;");
            }

            ship_one_enemy=true;
            ship_one_player=true;
            for(int i=1; i<11;i++)
            {
                for(int j=1; j<11; j++)
                {
                    if(enemyAr[i][j]==1)ship_one_enemy=false;
                    if(playerAr[i][j]==1)ship_one_player=false;
                }
            }
            if(ship_one_enemy&&ship_one_player)ui->ll_enterInfo->setText("Ничья!");
            if(ship_one_enemy)ui->ll_enterInfo->setText("Вы выиграли!");
            if(ship_one_player)ui->ll_enterInfo->setText("Победил противник!");
        }
        else ui->ll_enterInfo->setText("Вы вышли за границы поля!");
    }
    else ui->ll_enterInfo->setText("Сюда вы уже стреляли!");
}

game::game(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::game)
{
    ui->setupUi(this);
    createFieldPlayer();
    createFieldEnemy();

    playerAr = new int*[11];
    for(int i=0; i<11; i++)
    {
        playerAr[i]= new int [11];
    }

    for(int i=0; i<11; i++)
    {
        for(int j=0; j<11; j++)
        {
            playerAr[i][j]=0;
        }
    }
    vectorFieldPlayerForEnemy = QVector<QString>();
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            vectorFieldPlayerForEnemy.insert(vectorFieldPlayerForEnemy.length(), QString::number(i)+QString::number(j));
        }
    }
}

game::~game()
{
    delete ui;
}


void game::on_commandLinkButton_clicked()
{

}

void game::on_rb_for_clicked() { pressed_ship=4; }
void game::on_rb_three_clicked() { pressed_ship=3; }
void game::on_rb_two_clicked() { pressed_ship=2; }
void game::on_rb_one_clicked() { pressed_ship=1; }

void game::on_clb_turn_clicked()
{
    if(pressed_ship==4&&for_turn)
    {
        ui->ll_for->setStyleSheet("border-image: url(C:/Users/minly/Desktop/for-deck-turn.png);");
        ui->ll_for->setFixedSize(30,120);
        for_turn=false;
    }
    else if(pressed_ship==4&&!for_turn)
    {
        ui->ll_for->setStyleSheet("border-image: url(C:/Users/minly/Desktop/for-deck.png);");
        ui->ll_for->setFixedSize(120,30);
        for_turn=true;
    }
    else if(pressed_ship==3&&three_turn)
    {
        ui->ll_three->setStyleSheet("border-image: url(C:/Users/minly/Desktop/three-deck-turn.png);");
        ui->ll_three->setFixedSize(30,90);
        three_turn=false;
    }
    else if(pressed_ship==3&&!three_turn)
    {
        ui->ll_three->setStyleSheet("border-image: url(C:/Users/minly/Desktop/three-deck.png);");
        ui->ll_three->setFixedSize(90,30);
        three_turn = true;
    }
    else if(pressed_ship==2&&two_turn)
    {
        ui->ll_two->setStyleSheet("border-image: url(C:/Users/minly/Desktop/two-deck-turn.png);");
        ui->ll_two->setFixedSize(30,60);
        two_turn=false;
    }
    else if(pressed_ship==2&&!two_turn)
    {
        ui->ll_two->setStyleSheet("border-image: url(C:/Users/minly/Desktop/two-deck.png);");
        ui->ll_two->setFixedSize(60,30);
        two_turn=true;
    }
}
void game::qetClickCoords(QString d, int *iFirstNum, int *iSecondNum)
{
    bool isSpases = false;
    QString firstNum;
    for(int i=0; i< d.size(); i++)
    {
        if(d[i]==' '&&!isSpases)
        {
            isSpases=true;
            firstNum+=d[i];
        }
        else if(d[i]!=' '&&isSpases)
        {
            firstNum+=d[i];
        }
        else if(d[i]==' '&&isSpases)
        {
            *iFirstNum = firstNum.toInt();
            firstNum="";
        }
    }
    *iSecondNum = firstNum.toInt();
}
bool game::checkShipPos(int pressed_ships, int iFirstNum, int iSecondNum)
{
    bool isValid = true;
    bool currentTurn = true;
    if(pressed_ships == 4) currentTurn = for_turn;
    else if(pressed_ships == 3) currentTurn = three_turn;
    else if(pressed_ships == 2) currentTurn = two_turn;

    if(currentTurn)
    {
        if(iFirstNum+pressed_ships<12 && iFirstNum > 0 && iSecondNum > 0)
        {
            for(int i=iFirstNum-1; i<=iFirstNum+pressed_ships; i++)
            {
                for(int j=iSecondNum-1; j<=iSecondNum+1; j++)
                {
                    if(!checkCurrentPos(i,j))
                    {
                        isValid = false;
                    }
                }
            }
        } else return false;
    }
    else
    {
        if(iSecondNum+pressed_ships<12 && iSecondNum > 0 && iFirstNum > 0)
        {
            for(int i=iFirstNum-1; i<=iFirstNum+1; i++)
            {
                for(int j=iSecondNum-1; j<=iSecondNum+pressed_ships; j++)
                {
                    if(!checkCurrentPos(i,j))
                    {
                        isValid = false;
                    }
                }
            }
        } else return false;
    }
    if(isValid) return true;
    else return false;
}
bool game::checkCurrentPos(int iFirstNum, int iSecondNum)
{
    if(iFirstNum<1||iFirstNum>10) return true;
    if(iSecondNum<1||iSecondNum>10) return true;
    if(playerAr[iFirstNum][iSecondNum]==0) return true;
    else return false;
}
bool game::checkShipPosEnemy(int pressed_ships, bool currentTurn, int iFirstNum, int iSecondNum)
{
    bool isValid = true;

    if(currentTurn)
    {
        if(iFirstNum+pressed_ships<12 && iFirstNum > 0 && iSecondNum > 0)
        {
            for(int i=iFirstNum-1; i<=iFirstNum+pressed_ships; i++)
            {
                for(int j=iSecondNum-1; j<=iSecondNum+1; j++)
                {
                    if(!checkCurrentPosEnemy(i,j))
                    {
                        isValid = false;
                    }
                }
            }
        } else return false;
    }
    else
    {
        if(iSecondNum+pressed_ships<12 && iSecondNum > 0 && iFirstNum > 0)
        {
            for(int i=iFirstNum-1; i<=iFirstNum+1; i++)
            {
                for(int j=iSecondNum-1; j<=iSecondNum+pressed_ships; j++)
                {
                    if(!checkCurrentPosEnemy(i,j))
                    {
                        isValid = false;
                    }
                }
            }
        } else return false;
    }
    if(isValid) return true;
    else return false;
}
bool game::checkCurrentPosEnemy(int iFirstNum, int iSecondNum)
{
    if(iFirstNum<1||iFirstNum>10) return true;
    if(iSecondNum<1||iSecondNum>10) return true;
    if(enemyAr[iFirstNum][iSecondNum]==0) return true;
    else return false;
}
void game::on_pb_startGame_clicked()
{
    if(ui->ll_numOfSheeps_for->text().toInt() > 0) { ui->ll_enterInfo->setText("Расставьте все корабли!"); return; }
    if(ui->ll_numOfSheeps_three->text().toInt() > 0) { ui->ll_enterInfo->setText("Расставьте все корабли!"); return; }
    if(ui->ll_numOfSheeps_two->text().toInt() > 0) { ui->ll_enterInfo->setText("Расставьте все корабли!"); return; }
    if(ui->ll_numOfSheeps_one->text().toInt() > 0) { ui->ll_enterInfo->setText("Расставьте все корабли!"); return; }

    ui->ll_numOfSheeps_for->hide();
    ui->ll_numOfSheeps_three->hide();
    ui->ll_numOfSheeps_two->hide();
    ui->ll_numOfSheeps_one->hide();
    ui->clb_turn->hide();
    ui->ll_for->hide();
    ui->ll_three->hide();
    ui->ll_two->hide();
    ui->ll_one->hide();
    ui->pb_startGame->hide();
    ui->rb_for->hide();
    ui->rb_three->hide();
    ui->rb_two->hide();
    ui->rb_one->hide();
    isStarted = true;
}
bool game::checkPressedShip(int iFirstNum,int iSecondNum, int status)
{
    if(iFirstNum<1||iFirstNum>10) return false;
    if(iSecondNum<1||iSecondNum>10) return false;
    if(enemyAr[iFirstNum][iSecondNum]==status) return true;
    else return false;
}
bool game::checkPressedShipPlayer(int iFirstNum,int iSecondNum, int status)
{
    if(iFirstNum<1||iFirstNum>10) return false;
    if(iSecondNum<1||iSecondNum>10) return false;
    if(playerAr[iFirstNum][iSecondNum]==status) return true;
    else return false;
}

