#include <QtCore/QCoreApplication>

#include <QDebug>
#include <QVariant>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QStringList>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QStringList sl{"aaaa", "bbb"};
    QVariant v(sl);

    qDebug() << v.toString();

    return a.exec();
}
