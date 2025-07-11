#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"tcpclient.h"
#include"tcpserver.h"
#include<QTime>
#include<QTimer>
#include<QMessageBox>
#include"utils.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //地图点选+实时轨迹+CSV导出
    scene = new QGraphicsScene(this);
    ui->graphicsViewMap->setScene(scene);

    //初始化TcpServer
    server = new TcpServer(this);
    server->start(9999); //启动监听端口9999
    connect(server,&TcpServer::statusReceived,this,&MainWindow::onRobotStatus);

    //初始化TcpClient
    client = new TcpClient(this);
    client->connectToServer("127.0.0.1",9999);
    connect(client, &TcpClient::logMessage, this, &MainWindow::appendLog);
    
       connect(ui->btnSendTask,&QPushButton::clicked,this,&MainWindow::sendTask);
       connect(ui->btnStartMonitor,&QPushButton::clicked,this,&MainWindow::startMonitor);

       connect(ui->btnExportLog,&QPushButton::clicked,this,[=](){

             Utils::exportCSV(trackData,"task_log.csv");
             QMessageBox::information(this, "导出成功", "已保存轨迹到 task_log.csv");
       });

        // 初始化状态
        ui->labelStatus->setText("准备中...");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::appendLog(const QString &msg)
{
    ui->plainTextLog->appendPlainText(QTime::currentTime().toString("[hh:mm:ss]")+msg);
}

void MainWindow::sendTask()
{
    TaskCommand task;
    task.operationType="巡检";
    task.points = {{100,100},{200,200},{300,100}};//示例路径
    client->sendTask(task);
}

void MainWindow::startMonitor()
{
    //启动状态监听模拟（或连接TCP模拟）
    QTimer::singleShot(3000,this,[=]{

        RobotStatus status = {200,200,20,"运行中"};

    });
}

void MainWindow::updateStatus(const RobotStatus &status)
{
    ui->labelStatus->setText(QString("位置:(%1,%2)").arg(status.posX).arg(status.posY));
    ui->labelBattery->setText(QString("电量：%1%").arg(status.battery));
    ui->labelTaskState->setText("任务状态："+status.taskStates);

    if(status.battery<25)
    {
        QMessageBox::warning(this,"电量低告警","机器人电量不足,请返回及时充电",QMessageBox::Ok);
        appendLog("[告警],电量低告警触发");
    }
    else {
        appendLog("[状态]状态正常，电量充足");
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    
    QPointF scenePos = ui->graphicsViewMap->mapToScene(ui->graphicsViewMap->mapFromGlobal(event->globalPos()));
    scene->addEllipse(scenePos.x(),scenePos.y(),6,6,QPen(Qt::blue),QBrush(Qt::blue));
    taskpoints.append(QPoint(scenePos.x(),scenePos.y()));
}

void MainWindow::onRobotStatus(const RobotStatus& status)
{
    ui->labelStatus->setText(QString("位置:(%1,%2)").arg(status.posX).arg(status.posY));
    ui->labelBattery->setText(QString("电量：%1%").arg(status.battery));
    ui->labelTaskState->setText("任务状态："+status.taskStates);

    // 绘制轨迹点
      scene->addEllipse(status.posX, status.posY, 4, 4, QPen(Qt::red), QBrush(Qt::red));

      // 记录轨迹
      QString record = QString("%1,%2").arg(status.posX).arg(status.posY);
      trackData.append(record);

}
