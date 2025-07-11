#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include<QTcpSocket>
#include"task_protocol.h"

class TcpClient : public QObject
{
    Q_OBJECT
public:
    explicit TcpClient(QObject *parent = nullptr);
    void sendTask(const TaskCommand& task);

signals:

    void logMessage(const QString& msg);

public slots:

private:
    QTcpSocket* socket;
};

#endif // TCPCLIENT_H
