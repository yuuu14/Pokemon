#ifndef REGIST_H
#define REGIST_H
#include <QWidget>
#include <QtGui>
#include <QtNetwork>
#include <QtWidgets>
#include "client.h"

class Regist : public QWidget
{
    Q_OBJECT
public:
    explicit Regist(QWidget *parent = 0);
    static QTcpSocket *m_clisocket;

private:
    QString userStr;
    QString wrongMsg;
    QLabel *label_title;
    QLabel *label_passwd;
    QLabel *label_name;
    QLabel *label_notice;
    QLineEdit *lineEdit_name;
    QLineEdit *lineEdit_passwd;
    QPushButton *clearBtn;
    QPushButton *registBtn;

//    QTcpSocket *m_tcpsocket;
//    QString userStr;//username

private slots:
    void readMessage();
    void registServer();
    void sendMessage(QString);
    int infohandle(QString);
    void clearLineEdit();
    bool connectTcpServer();
    bool sendRegistInfo();
};

#endif // REGIST_H

