#include "sendrequest.h"



SendRequest::SendRequest(QObject *parent) : QObject(parent)
{
    //qDebug()<<__func__;
    serverConn = ServerConn::SingletonProvider();

    timeOute=new QTimer(this);
    connect(timeOute,&QTimer::timeout,this,&SendRequest::timeOuted);
    timeOute->setSingleShot(true);
    nextTime=20000;
    tryCount=1;


//    QTimer *timerrttrr=new QTimer();
//    connect(timerrttrr,&QTimer::timeout,[=](){
////        if(timeOute->isActive())
//        qDebug()<<"HAHAHA"<<tempLink<<QTime::currentTime();
//    });
//    timerrttrr->start(10000);
}

SendRequest::~SendRequest()
{
    //qDebug()<<__func__<<tempLink<<"killed";
}

void SendRequest::sendRequest(QJsonObject params, QString link)
{
    tempParams=params;
    tempLink=link;
    //qDebug()<<__func__<<link;

    timeOute->start(nextTime);

    //QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    //QJsonDocument doc(params);

    //QHttpPart textPart;
    //textPart.setHeader( QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded" );
    //textPart.setBody(doc.toJson(QJsonDocument::Compact));
    //multiPart->append(textPart);

    QUrlQuery postData;

    for(const auto &key : params.keys())
    {
        postData.addQueryItem(key,params.value(key).toVariant().toString());
    }

        QUrl url(link);
        QNetworkRequest request(url);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

        reply = serverConn->networkManager.post(request, postData.toString(QUrl::FullyEncoded).toUtf8() );
        //multiPart->setParent(reply);

//        connect(reply, &QNetworkReply::uploadProgress, [=](){
////            qInfo()<<"... ";
//        });

        connect(reply, &QNetworkReply::finished, this, &SendRequest::respons);

        connect(reply, &QNetworkReply::downloadProgress, this, &SendRequest::onDownloadProgress );
}

void SendRequest::sendJSONRequest(QJsonObject params, QString link)
{
    tempParams=params;
    tempLink=link;
    //qDebug()<<__func__<<link;

//    timeOute->start(nextTime);

    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    QJsonDocument doc(params);
    QByteArray data = doc.toJson();

        QUrl url(link);
        QNetworkRequest request(url);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        reply = serverConn->networkManager.post(request, data);
        multiPart->setParent(reply);

//        connect(reply, &QNetworkReply::uploadProgress, [=](){
////            qInfo()<<"... ";
//        });

        connect(reply, &QNetworkReply::finished, this, &SendRequest::respons);

//        connect(reply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error),this,
//            [=](QNetworkReply::NetworkError code){ netError(code); });

        connect(reply, &QNetworkReply::downloadProgress, this, &SendRequest::onDownloadProgress );

        //        reply->deleteLater();
}

void SendRequest::sendFile(QString filePath, QString link, QString customName)
{
  tempLink=link;

  QFile *file = new QFile(filePath, this);

  if (!file->open(QIODevice::ReadOnly)) {
      // handle file open error
    netError(-1);
    return;
  }

  QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType, this);
  QHttpPart filePart;
  auto fileName = customName.isEmpty()? file->fileName() : customName;
  filePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"file\"; filename=\""+fileName+"\""));
  filePart.setBodyDevice(file);
  file->setParent(multiPart);
  multiPart->append(filePart);


      QUrl url(link);
      QNetworkRequest request(url);
      request.setHeader(QNetworkRequest::ContentTypeHeader, "multipart/form-data; boundary=" + multiPart->boundary());

      reply = serverConn->networkManager.post(request, multiPart);
      //multiPart->setParent(reply);

      connect(reply, &QNetworkReply::uploadProgress, this, [=](qint64 bytesSent, qint64 bytesTotal) {
              if (bytesTotal > 0)
              {
                  int percent = static_cast<int>((bytesSent * 100) / bytesTotal);
                  emit setUploadPersent(percent);
              }
      });

      connect(reply, &QNetworkReply::finished, this, &SendRequest::respons);

      connect(reply, &QNetworkReply::downloadProgress, this, &SendRequest::onDownloadProgress );
}

void SendRequest::sendFile(QSharedPointer<QByteArray> fileContent, QString link, QString customName)
{
  tempLink=link;

  if (fileContent->isEmpty()) {
      // handle file open error
    netError(-1);
    return;
  }

  QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType, this);
  QHttpPart filePart;
  filePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"file\"; filename=\""+customName+"\""));
  filePart.setBody(*fileContent);
  multiPart->append(filePart);


      QUrl url(link);
      QNetworkRequest request(url);
      request.setHeader(QNetworkRequest::ContentTypeHeader, "multipart/form-data; boundary=" + multiPart->boundary());

      reply = serverConn->networkManager.post(request, multiPart);
      //multiPart->setParent(reply);

      connect(reply, &QNetworkReply::uploadProgress, this, [this](qint64 bytesSent, qint64 bytesTotal) {
              if (bytesTotal > 0)
              {
                  int percent = static_cast<int>((bytesSent * 100) / bytesTotal);
                  emit setUploadPersent(percent);
              }
      });

      connect(reply, &QNetworkReply::finished, this, &SendRequest::respons);

      connect(reply, &QNetworkReply::downloadProgress, this, &SendRequest::onDownloadProgress );
}

void SendRequest::respons(){
//    timeOute->stop();
//    qDebug()<<__func__<<tempLink<<"finished:"<<reply->readAll();
    emit setRespons(reply->readAll());
//    emit finished();
//    if(!reply.isNull())
//        delete reply;
    reply->deleteLater();
    this->deleteLater();
}

void SendRequest::netError(int errorNum){
    qDebug()<<__func__<<errorNum<<tempLink;
    emit error();
//    if(!reply.isNull())
//        delete reply;
    reply->deleteLater();
    this->deleteLater();
}

void SendRequest::uploadDone(QByteArray data){
}

void SendRequest::uploadProgress(qint64 bytesSent, qint64 bytesTotal){

    qInfo()<<bytesSent/bytesTotal<<"   "<<bytesSent%bytesTotal;
}

void SendRequest::onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    nextTime=20000;
    timeOute->start(nextTime);
    //qDebug() << "Download progress:" << bytesReceived << bytesTotal;
}

void SendRequest::timeOuted()
{
    qDebug()<<__func__<<nextTime<<tryCount<<tempLink;
    disconnect(reply, &QNetworkReply::finished, this, &SendRequest::respons);
////    disconnect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit );
    disconnect(reply, &QNetworkReply::downloadProgress, this, &SendRequest::onDownloadProgress );

////    loop.exit();
//    reply->abort();

    if(tryCount<11){
        tryCount++;
        nextTime=40000+10000;
        sendRequest(tempParams, tempLink);
    } else {
        tryCount=1;
        nextTime=40000;
//        netError();
    }
    timeOute->start(nextTime);
}
