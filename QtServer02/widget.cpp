#include "widget.h"
#include "ui_widget.h"
#include <QtGlobal>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    m_tcpserver = new TcpServer(this);

    //开始的时候服务器没有工作
    serverisworking = false;

}

Widget::~Widget()
{
    delete ui;

}

//用以显示新的连接进入
void Widget::showNewConnection(qintptr sockDesc)
{
    ui->textBrowser_ServerMess->append("有新的连接！，新接入"+QString::number(sockDesc));
    ui->comboBox_CilentID->addItem(QString("%1").arg(sockDesc), sockDesc);
}


//用以显示连接断开
void Widget::showDisconnection(qintptr sockDesc)
{
    ui->textBrowser_ServerMess->append(QString::number(sockDesc)+"断开了连接");

    int index = ui->comboBox_CilentID->findData(sockDesc);

    ui->comboBox_CilentID->removeItem(index);
}


//当服务器发送消息后，通知主窗口更新信号
void Widget::UpdateServerMsg(qintptr Desc, const QByteArray &msg)
{
    ui->textBrowser_ServerMess->append("服务器："+msg+"------------------to "+QString::number(Desc));
}



//点击开始启动服务器
void Widget::on_pushButton_StartServer_clicked()
{
     if (!this->serverisworking) {
        if(this->m_tcpserver->listen(QHostAddress::Any,ui->lineEdit_Port->text().toUShort())){
            QMessageBox::information(this,"成功！","启动成功！");
            ui->pushButton_StartServer->setText("关闭服务器");
            this->serverisworking = true;
        }
        else {
            QMessageBox::critical(this,"失败!","服务器启动失败请检查设置!");
        }
    }
     else if(this->serverisworking) {
         m_tcpserver->close();
         if(!m_tcpserver->isListening()){
             ui->pushButton_StartServer->setText("启动服务器");
             this->serverisworking = false;
             QMessageBox::information(this,"提示","关闭成功!");
         }
         else {
             QMessageBox::critical(this,"错误","关闭失败,请重试！");
             return;
         }

     }
}

//点击发送
void Widget::on_pushButton_Trans_clicked()
{
    if(serverisworking){

        //如果连接个数大于0，发送发送消息的信号
        if(ui->comboBox_CilentID->count() >0)
        {
            //发射 发送信号
            emit sendData( ui->comboBox_CilentID->currentText().toInt(), ui->textEdit_SendMess->toPlainText().toUtf8());
            qDebug()<<"发送了sendData信号"<<endl;
            ui->textEdit_SendMess->clear();
        }

    }
    else {
        QMessageBox::critical(this,"错误","请检查连接");
        return;
    }

}



//当客户端发送消息，服务器收到后，显示消息
void Widget::RecvMsg(QString Desc,const QByteArray &msg)
{
    ui->textBrowser_ServerMess->append(Desc+":"+msg);
}




