#include "ApiServer.h"
#include "ServerConn/sendrequest.h"

#include <QImage>
#include <QDebug>

ApiServer::ApiServer(QObject *parent)
  : QObject{parent}
{

}

void ApiServer::api3(QJsonObject images)
{

  for(const QString key : images.keys())
  {
    images.insert(key, imagePathToBase64(images.value(key).toString()));
  }

 SendRequest *request = new SendRequest();
 connect(request, &SendRequest::setRespons, this, &ApiServer::api3Respons);
 request->sendRequest(images,"http://192.168.100.9:5000/api3");
}

void ApiServer::api3Respons(QByteArray respons)
{
  qDebug()<<respons;
}

QString ApiServer::imagePathToBase64(QString path)
{
  path=path.remove("file://");
  QImage image(path);
  QByteArray ba;
  QBuffer buffer(&ba);
  image.save(&buffer, "JPEG");

  QString base64String = ba.toBase64();
  qDebug()<<base64String;
  return base64String.prepend("data:image/jpeg;base64,");
}

