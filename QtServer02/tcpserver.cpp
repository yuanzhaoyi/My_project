#include "tcpserver.h"



TcpServer::TcpServer(QObject *parent) : QTcpServer(parent)
{
     m_widget = dynamic_cast<Widget *>(parent);

}


//当有新的连接进来的时候会自动调用这个函数，不需要你去绑定信号槽
void TcpServer::incomingConnection(qintptr sockDesc)
{
    //将标识符保存进list
    m_socketList.append(sockDesc);

    //产生线程用于通信
    ServerThread *thread = new ServerThread(sockDesc);

    //窗口中显示有新的连接
    m_widget->showNewConnection(sockDesc);

    //线程中发出断开tcp连接，触发widget中显示断开
    connect(thread, &ServerThread::disconnectTCP, this,[=]{
         m_widget->showDisconnection(sockDesc);
    });



    //当socket 底层有readyread信号的时候  -> 发送socket_getmsg信号  -> 发送socket_getmsg_thread
    //将socket_getmsg_thread 与 widget中 RecvMsg 绑定，RecvMsg 用于处理将收到的消息进行显示
    connect(thread,&ServerThread::socket_getmsg_thread,this->m_widget,&Widget::RecvMsg);

    //当点击发送的时候-> 产生一个SendData 信号  -> 调用线程中SendDataSlot函数用于发送sendData信号来使socket来发送消息
    connect(this->m_widget,&Widget::sendData,thread,&ServerThread::sendDataSlot);

    //当服务器给客户端发送下消息后，会产生一个writeover信号-> 触发线程发送writeover信号给 Tcpserver -> Tcpserver中widget更新消息
    connect(thread,&ServerThread::writeover,[=](qintptr Desc,const QByteArray &msg){
           m_widget->UpdateServerMsg(Desc,msg);
    });


    thread->start();
}

