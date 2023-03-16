#ifndef APISERVER_H
#define APISERVER_H

#include <QObject>
#include <QQuickItem>
#include <QJsonObject>
#include <QSharedPointer>

class ApiServer : public QQuickItem
{
  Q_PROPERTY(int uploadPersent READ getUploadPersent NOTIFY uploadPersentChanged)
  Q_OBJECT
public:
  explicit ApiServer(QQuickItem *parent = nullptr);

  int getUploadPersent();

public slots:
  void sendSample(QString filePath);
  void sendSample(QSharedPointer<QByteArray> fileCOntent, QString fileName);
  void sendTarget(QString filePath);
  void sendTarget(QSharedPointer<QByteArray> fileCOntent, QString fileName);
  void requestClear();
  void requestCalc();
  //
  void sampleRespons(QByteArray respons);
  void calcRespons(QByteArray respons);
  void setUploadPersent(int persent);

signals:
  void uploadPersentChanged(int uploadPersent);
  void serverCalc(QString calc);

private:
  int mUploadPercent=0;


};

#endif // APISERVER_H
