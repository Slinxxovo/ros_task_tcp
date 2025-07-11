#include "utils.h"
#include<QFile>
#include<QTextStream>

Utils::Utils(QObject *parent) : QObject(parent)
{

}

void Utils::exportCSV(const QString &trackData, const QString &filename)
{
    QFile file(filename);
    if(file.open(QIODevice::WriteOnly)){
        QTextStream out(&file);
        out<<"X,Y\n";
        for(const QString& row:trackData)
        {
            out<<row<<"\n";
        }
        file.close();
    }
}
