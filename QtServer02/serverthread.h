#pragma once
#ifndef SERVERTHREAD_H
#define SERVERTHREAD_H

#include <QObject>

#include <QThread>
#include<serversocket.h>

class ServerThread : public QThread
{
    Q_OBJECT
public:

    //构造函数初始化套接字标识符
    explicit ServerThread(qintptr sockDesc,QObject *parent = nullptr);

    void run() override;

    ~ServerThread();

signals:
    void disconnectTCP(qintptr m_sockDesc);

    void sendData(qintptr Desc, const QByteArray& msg);

    void socket_getmsg_thread(QString Desc,const QByteArray &msg);

    void  writeover(qintptr Desc,const QByteArray &msg);

public  slots:
    void sendDataSlot(qintptr Desc, const QByteArray& msg);



private:
    qintptr m_socketDesc;

    ServerSocket *m_socket;

};



#endif // SERVERTHREAD_H
