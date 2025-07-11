#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject> //TCPServer模拟机器人端
#include<QTcpSocket>
#include<QTcpServer>
#include<QTimer>
#include"task_protocol.h"

class TcpServer : public QObject
{
    Q_OBJECT
public:
    explicit TcpServer(QObject *parent = nullptr);
    void start(int port);

signals:
    void statusReceived(const RobotStatus& status);

private slots:
    void newConnection();
    void sendStatus();

private:
    QTcpServer* server;
    QTcpSocket* socket;
    QTimer* timer;
};

#endif // TCPSERVER_H
