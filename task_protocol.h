#ifndef TASK_PROTOCOL_H
#define TASK_PROTOCOL_H

//定义模拟任务结构
#include<QString>
#include<QVector>

struct TaskPoint{
    int x;
    int y;
};

struct TaskCommand{
    QVector<TaskPoint> points;
    QString operationType;// eg:巡检、拍照
};

struct RobotStatus{

    int posX;
    int posY;
    int battery;//百分比
    QString taskStates;
};

#endif // TASK_PROTOCOL_H
