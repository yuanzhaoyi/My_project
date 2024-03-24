#pragma once
#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include<QTcpServer>

#include <widget.h>
#include"serverthread.h"
class Widget;
class TcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit TcpServer(QObject *parent = nullptr);

private:

    //重写虚函数
    void incomingConnection(qintptr sockDesc);

private:

    //用来保存连接进来的套接字
    QList<qintptr> m_socketList;

    Widget *m_widget;


};

#endif // TCPSERVER_H
