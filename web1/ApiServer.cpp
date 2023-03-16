#include "ApiServer.h"
#include "ServerConn/sendrequest.h"

#include <QImage>
#include <QDebug>

ApiServer::ApiServer(QQuickItem *parent)
  : QQuickItem{parent}
{

}

int ApiServer::getUploadPersent(){
  return mUploadPercent;
}

void ApiServer::sendSample(QString filePath)
{
  QUrl fileUrl(filePath);
  if(fileUrl.isLocalFile()){
    filePath = fileUrl.toLocalFile();
  }

  mUploadPercent= 0;

 SendRequest *request = new SendRequest();
 connect(request, &SendRequest::setRespons, this, &ApiServer::sampleRespons);
 connect(request, &SendRequest::setUploadPersent, this, &ApiServer::setUploadPersent);
 request->sendFile(filePath,"http://127.0.0.1:5000/setsample");
}

void ApiServer::sendSample(QSharedPointer<QByteArray> fileCOntent, QString fileName)
{
  mUploadPercent= 0;

 SendRequest *request = new SendRequest();
 connect(request, &SendRequest::setRespons, this, &ApiServer::sampleRespons);
 connect(request, &SendRequest::setUploadPersent, this, &ApiServer::setUploadPersent);
 request->sendFile(fileCOntent,"http://127.0.0.1:5000/setsample",fileName);
}

void ApiServer::sendTarget(QString filePath)
{
  QUrl fileUrl(filePath);
  if(fileUrl.isLocalFile()){
    filePath = fileUrl.toLocalFile();
  }

  mUploadPercent= 0;

 SendRequest *request = new SendRequest();
 connect(request, &SendRequest::setRespons, this, &ApiServer::sampleRespons);
 connect(request, &SendRequest::setUploadPersent, this, &ApiServer::setUploadPersent);
 request->sendFile(filePath,"http://127.0.0.1:5000/settarget");
}

void ApiServer::sendTarget(QSharedPointer<QByteArray> fileCOntent, QString fileName)
{
  mUploadPercent= 0;

 SendRequest *request = new SendRequest();
 connect(request, &SendRequest::setRespons, this, &ApiServer::sampleRespons);
 connect(request, &SendRequest::setUploadPersent, this, &ApiServer::setUploadPersent);
 request->sendFile(fileCOntent,"http://127.0.0.1:5000/settarget",fileName);
}

void ApiServer::requestClear()
{
  SendRequest *request = new SendRequest();
  connect(request, &SendRequest::setRespons, this, &ApiServer::sampleRespons);
  request->sendRequest({},"http://127.0.0.1:5000/clear");
}

void ApiServer::requestCalc()
{
  SendRequest *request = new SendRequest();
  connect(request, &SendRequest::setRespons, this, &ApiServer::calcRespons);
  request->sendRequest({},"http://127.0.0.1:5000/calc");
}

void ApiServer::sampleRespons(QByteArray respons)
{
  qDebug()<<respons;
}

void ApiServer::calcRespons(QByteArray respons)
{
  emit serverCalc(respons.data());
}

void ApiServer::setUploadPersent(int persent)
{
  mUploadPercent = persent;
  emit uploadPersentChanged(mUploadPercent);
}
