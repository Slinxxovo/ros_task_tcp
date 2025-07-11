#include "tcpclient.h"
#include<QDataStream>

TcpClient::TcpClient(QObject *parent) : QObject(parent)
{

    socket = new QTcpSocket(this);
    socket->connectToHost("127.0.0.1",9999);
}

void TcpClient::sendTask(const TaskCommand &task)
{
    if(!socket->isOpen())
    {
        return;
    }

    QByteArray data;
    QDataStream out(&data,QIODevice::WriteOnly);

    out<<(quint32)task.points.size();
    for (auto& pt:task.points) {
        out<<pt.x<<pt.y;
    }

    out<<task.operationType;
    socket->write(data);
    emit logMessage("[发送] 已发送任务指令");
}
