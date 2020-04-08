#include "client.h"
#include "regist.h"
#include <iostream>
using namespace std;

QTcpSocket *Regist::m_clisocket;

Regist::Regist(QWidget *parent) : QWidget(parent)
{
    userStr = QString(tr("Regist"));
//    parent->setObjectName(QStringLiteral("Clien"));
//    parent->resize(500, 400);
//    userStr = QString(tr("Pokemon Regist"));

    lineEdit_name = new QLineEdit;
    lineEdit_passwd = new QLineEdit;

    label_title = new QLabel(parent);
    label_notice = new QLabel(parent);
    label_name = new QLabel(parent);
    label_passwd = new QLabel(parent);

    label_title->setText("Regist");
    label_notice->setText("all input spaces will be ignored");
    label_name->setText("username:");
    label_passwd->setText("password:");
    lineEdit_passwd->setEchoMode(QLineEdit::Password);

    clearBtn = new QPushButton("clear");
    connect(clearBtn,SIGNAL(clicked()),this,SLOT(clearLineEdit()));

    registBtn = new QPushButton("regist");
    connect(registBtn,SIGNAL(clicked()),this,SLOT(registServer()));

//	label_state->setGeometry(QRect(0,20,100,20));
//  label_name->setGeometry(QRect(20, 60, 100, 20));
//	label_passwd->setGeometry(QRect(20, 100,100, 20));
//	lineEdit_name->setGeometry(QRect(20, 140,100, 20));
//	lineEdit_passwd->setGeometry(QRect(20, 180,100, 20));
//	registBtn->setGeometry(QRect(20, 220,100, 20));
//  loginBtn->setGeometry(QRect(120, 220,100, 20));

    QHBoxLayout *layout1 = new QHBoxLayout;
    layout1->addWidget(label_title);
    QHBoxLayout *layout2 = new QHBoxLayout;
    layout2->addWidget(label_name);
    layout2->addWidget(lineEdit_name);
    QHBoxLayout *layout3 = new QHBoxLayout;
    layout3->addWidget(label_passwd);
    layout3->addWidget(lineEdit_passwd);
    QHBoxLayout *layout4 = new QHBoxLayout;
    layout1->addWidget(label_notice);

    QHBoxLayout *bottomlayout = new QHBoxLayout;
    bottomlayout->addWidget(registBtn);
    bottomlayout->addWidget(clearBtn);

    QVBoxLayout *mainlayout = new QVBoxLayout;
    mainlayout->addLayout(layout1);
    mainlayout->addLayout(layout2);
    mainlayout->addLayout(layout3);
    mainlayout->addLayout(layout4);
    mainlayout->addLayout(bottomlayout);

    setLayout(mainlayout);
}

void Regist::clearLineEdit(){
    lineEdit_name->setText(QString(""));
    lineEdit_passwd->setText(QString(""));
}

bool Regist::connectTcpServer()
{
    Regist::m_clisocket = new QTcpSocket(this);
    Regist::m_clisocket->abort();
    Regist::m_clisocket->connectToHost(QHostAddress::LocalHost,16666);//ip por
    return true;
}

void Regist::registServer()
{
    label_notice->setText("连接服务器......");

    if(connectTcpServer()){
        //connect(Regist::m_clisocket,SIGNAL(connected()),this,SLOT(connectedServer()));
        connect(Regist::m_clisocket,SIGNAL(connected()),this,SLOT(readMessage()));
        if(sendRegistInfo()){
            label_notice->setText("注册成功！");
            //close widge;
            //another page to enter game;
        }
    }
}
bool Regist::sendRegistInfo()
{
    QString infoStr;
    QString name, passwd;
    cout << "init"<<endl;
    name = lineEdit_name->text().replace(QString(" "), QString(""));
    passwd = lineEdit_passwd->text().replace(QString(" "), QString(""));
    infoStr = name + QString("\n") + passwd;
    cout << "get name & passwd" << endl;
    sendMessage(QString("110 ") + infoStr);

    cout << "send message" << endl;
    //tcp open here for readMessage of Regist
    connect(Client::m_clisocket,SIGNAL(connected()),this,SLOT(readMessage()));
    while(1){
        if(Client::flag == 3){
            QMessageBox::information(NULL, QString("success"), QString("Regist Success"));
            Client::flag = 0;
            return true;
        }
        else if(Client::flag == 4){
            QMessageBox::information(NULL, QString("error"), QString(wrongMsg));
            Client::flag = 0;
            return false;
        }
        else if(Client::flag == 0){
            label_title->setText("断网了！请重新注册");
            return false;
        }
    }
}

void Regist::readMessage()
{
    QString string;
    QByteArray block = Client::m_clisocket->readAll();
    QDataStream in(block);
    in.setVersion(QDataStream::Qt_4_7);
    in>>string;
    infohandle(string);
//    textEdit->append(tr("用户有消息到来\n消息是:")+string+'\n');

}

void Regist::sendMessage(QString s)
{
    int type;
    type = 1;

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_7);
    out << "userStr";//can change in ip
    out << type;
    out << s;
    Client::m_clisocket->write(block);
    cout << "send ok"<<endl;
//    lineEdit->clear();
}

int Regist::infohandle(QString s)
{
    QString f;
    f=s.mid(0,3);
    if(f.compare(QString("111"))){
        Client::flag = 3;
        return Client::flag;
    }
    else if(f.compare(QString("112"))){
        Client::flag = 4;
        return Client::flag;
    }
    else{
        return -1;//unknown status
    }
    //connect receive forma & Client::flag
    return 0;

}



/* msg send and receive format
 * all message in format "200 from msg"
 * c->s:
 *      100 connect & login, /logname logpasswd/
 *      110 regist, /name passwd/
 *
 * s->c:
 *      101 return login success, /login OK/
 *      102 return login result, /ERROR(no name||wrong pass)/
 *      111 return regist success, /regist OK/
 *      112 return regist result, /ERROR(name valid)/
 *      113 return regist result, /ERROR(wrong and try a easy one)/
 *
 *
 */

