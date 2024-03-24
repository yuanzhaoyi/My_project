#pragma once
#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include <QObject>
#include<QTcpSocket>



class ServerSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit ServerSocket(qintptr socketDesc,QObject *parent = nullptr);

signals:
    void socket_getmsg(QString Desc, const QByteArray &msg);

     void writeover(qintptr Desc,const QByteArray &msg);

public slots:
    void sendData(qintptr Desc, const QByteArray &data);

private:
        qintptr m_sockDesc;
};

#endif // SERVERSOCKET_H
