#ifndef APISERVER_H
#define APISERVER_H

#include <QObject>
#include <QJsonObject>

class ApiServer : public QObject
{
  Q_OBJECT
public:
  explicit ApiServer(QObject *parent = nullptr);

public slots:
  void api3(QJsonObject images);
  void api3Respons(QByteArray respons);

signals:


private:
  QString imagePathToBase64(QString path);

};

#endif // APISERVER_H
