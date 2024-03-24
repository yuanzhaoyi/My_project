#include "serverthread.h"

ServerThread::ServerThread(qintptr sockDesc,QObject *parent) : QThread(parent)
{
    this->m_socketDesc = sockDesc;
}

void ServerThread::run()
{
    m_socket = new ServerSocket(this->m_socketDesc);

    //绑定套接字标识符绑定给自定义套接字对象
    if (!m_socket->setSocketDescriptor(this->m_socketDesc)) {
        return ;
    }



    //当套接字断开时，发送底层的disconnected信号
    connect(m_socket, &ServerSocket::disconnected, this, [=]{

        //此信号可以出发server的槽函数然后再调用widget中combobox清除该socketDesc
        emit disconnectTCP(this->m_socketDesc);

        //让该线程中的套接字断开连接
        m_socket->disconnectFromHost();//断开连接

        //线程退出
        this->quit();
    });



    //套接字发出有消息的信号，然后触发线程中发出有消息的信号
    connect(m_socket, &ServerSocket::socket_getmsg, this,[=](QString Desc,const QByteArray &msg){


                emit socket_getmsg_thread(Desc,msg);

    });


    //当线程收到sendData信号时候，通知socket发送消息
    connect(this,&ServerThread::sendData,m_socket,&ServerSocket::sendData);


    //socket 发送 writeorver 通知线程发送writeover 用来提醒server中的widget更新消息
    connect(m_socket,&ServerSocket::writeover,this,[=](qintptr Desc, const QByteArray& msg){
            emit writeover(Desc,msg);
    });


    this->exec();//在Qt中启动消息机制
}

ServerThread::~ServerThread()
{
    delete  m_socket;
}

void ServerThread::sendDataSlot(qintptr Desc, const QByteArray &msg)
{

     emit sendData(Desc, msg);
}
