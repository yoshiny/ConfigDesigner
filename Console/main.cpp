#include <QtCore/QCoreApplication>

#include <QDebug>
#include <QVariant>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QStringList>

struct MyStruct {
    int a{99};

    MyStruct() {
		static int _reg = []() {
			int reg = qRegisterMetaType<MyStruct>();
			bool suc = false;
			/*bool suc = QMetaType::registerComparators<MyStruct>();
			Q_ASSERT(suc);*/

			suc = QMetaType::registerConverter<MyStruct, QVariant>();
			Q_ASSERT(suc);

			suc = QMetaType::registerConverter<MyStruct, QString>();
			Q_ASSERT(suc);

			suc = QMetaType::registerConverter<MyStruct, QJsonValue>();
			Q_ASSERT(suc);
			return reg;
		}();
    }

    operator QJsonValue() const {
        return QJsonValue(a);
    }

	operator QVariant() const {
		auto impl = static_cast<const MyStruct *>(this);
		return QVariant::fromValue<MyStruct>(*impl);
	}

	operator QString() const {
		return QString::number(a);
	}
}; Q_DECLARE_METATYPE(MyStruct)


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

	QVariant v = MyStruct();

    qDebug() << v.toString();
    qDebug() << v.toJsonValue();
	qDebug() << qvariant_cast<QJsonValue>(v);

	double d1 = 0.0, d2 = 0;

	qDebug() << (d1 == d2);

	QJsonObject jo = { {"d", LLONG_MAX} };
	QJsonDocument jd(jo);

	qDebug() << jd.toJson(QJsonDocument::Indented);

	QJsonValue jv(LLONG_MAX);

	qDebug() << jv.toDouble();
	qDebug() << (qlonglong)jv.toDouble();

	qDebug() << QString::number(LLONG_MAX, 16);

    return a.exec();
}
