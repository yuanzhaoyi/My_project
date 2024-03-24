#include "serversocket.h"
#include<QHostAddress>
ServerSocket::ServerSocket(qintptr socketDesc,QObject *parent) : QTcpSocket(parent)
{
    this->m_sockDesc = socketDesc;


    connect(this,&ServerSocket::readyRead,this,[=]{

        QString name = QString::number(m_sockDesc);

        QByteArray msg = readAll();

        emit socket_getmsg(name,msg);

    });
}





void ServerSocket::sendData(qintptr Desc, const QByteArray &msg)
{
    if (Desc == m_sockDesc && !msg.isEmpty()) {
        this->write(msg);

        //发送完毕，发出信号，通知主页面更新聊天框
        emit writeover(Desc,msg);
    }
}
