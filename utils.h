#ifndef UTILS_H
#define UTILS_H

#include <QObject>

class Utils : public QObject
{
    Q_OBJECT
public:
    explicit Utils(QObject *parent = nullptr);
    void static exportCSV(const QString& trackData,const QString& filename);

signals:

public slots:
};

#endif // UTILS_H
