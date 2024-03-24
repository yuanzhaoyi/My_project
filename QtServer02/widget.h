#pragma once
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QMessageBox>
#include"tcpserver.h"

namespace Ui {
class Widget;
}

class TcpServer;

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

public:
    //当有新连接的时候在页面上显示
    void showNewConnection(qintptr sockDesc);

    //断开时显示
    void showDisconnection(qintptr sockDesc);

    //当服务器发送消息后，通知窗口更新消息
    void UpdateServerMsg(qintptr Desc,const QByteArray &msg);


private slots:

    //按钮被触发
    void on_pushButton_StartServer_clicked();

    void on_pushButton_Trans_clicked();


public slots:

    //当服务器收到客户端发送的消息后，更新消息
    void RecvMsg(QString Desc,const QByteArray &msg);


signals :
   void  sendData(qintptr Desc ,const QByteArray &msg);

private:
    Ui::Widget *ui;

    TcpServer *m_tcpserver;

    bool serverisworking;
};

#endif // WIDGET_H
