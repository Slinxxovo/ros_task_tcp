#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"task_protocol.h"
#include"tcpclient.h"
#include<QGraphicsScene>
#include"tcpserver.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void appendLog(const QString& msg);
    void sendTask();
    void startMonitor();
    void updateStatus(const RobotStatus& status);
    void mousePressEvent(QMouseEvent *event);
    void onRobotStatus(const RobotStatus& status);

private:
    Ui::MainWindow *ui;
    TcpClient* client;
    TcpServer* server;
    QGraphicsScene* scene;
    QString trackData; //保存轨迹点CSV
    QVector<QPointF> taskpoints; //地图点击的任务点
};

#endif // MAINWINDOW_H
