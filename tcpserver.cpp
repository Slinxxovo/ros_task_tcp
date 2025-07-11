#include "tcpserver.h"
#include<QDataStream>
#include<QRandomGenerator>

TcpServer::TcpServer(QObject *parent) : QObject(parent)
{
    this->server = new QTcpServer(this);
    this->timer = new QTimer(this);

    connect(server,&QTcpServer::newConnection,this,&TcpServer::newConnection);
    connect(timer,&QTimer::timeout,this,&TcpServer::sendStatus);
}

void TcpServer::start(int port)
{
    server->listen(QHostAddress::Any,port);
}

void TcpServer::newConnection()
{
    socket = server->nextPendingConnection();
    timer->start(2000);
}

void TcpServer::sendStatus()
{
    if(!socket)
    {
        return;
    }
    RobotStatus status;
    status.posX = QRandomGenerator::global()->bounded(0,400);
    status.posY = QRandomGenerator::global()->bounded(0,300);
    status.battery = 50 + QRandomGenerator::global()->bounded(0,50);
    status.taskStates = "运行中";

    QByteArray data;
    QDataStream out(&data,QIODevice::WriteOnly);
    out<<status.posX<<status.posY<<status.battery<<status.taskStates;

    socket->write(data);
}
