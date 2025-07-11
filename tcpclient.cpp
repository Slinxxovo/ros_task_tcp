#include "tcpclient.h"
#include<QDataStream>

TcpClient::TcpClient(QObject *parent) : QObject(parent)
{

}

void TcpClient::connectToServer(const QString& host, int port)
{
    socket->connectToHost(host, port);
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
