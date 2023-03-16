#ifndef SENDREQUEST_H
#define SENDREQUEST_H

#include <QObject>
#include <QJsonDocument>
#include <QByteArray>
#include <QBuffer>
#include <QJsonObject>
#include <QHttpMultiPart>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QDebug>
#include <QTimer>
#include <QTime>
#include <QPointer>
#include <QFile>
#include <QSharedPointer>
#include "ServerConn/serverconn.h"

QT_BEGIN_NAMESPACE

class SendRequest : public QObject
{
    Q_OBJECT
public:

    enum ConnectType{
      form_data,
      JSON
    };


    explicit SendRequest(QObject *parent = nullptr);
    ~SendRequest();

    ServerConn *serverConn;

    void sendRequest(QJsonObject params, QString link);
    void sendJSONRequest(QJsonObject params, QString link);
    void sendFile(QString file, QString link, QString customName="");
    void sendFile(QSharedPointer<QByteArray> fileContent, QString link, QString customName="");
    void uploadDone(QByteArray data);

    QPointer<QNetworkReply> reply;
    QTimer *timeOute;
    int nextTime;
    QJsonObject tempParams;
    QString tempLink;
    int tryCount;

signals:
     void setRespons(QByteArray data);
     void setUploadPersent(int  percent);
     void finished();
     void error();

public slots:
      void respons();
      void uploadProgress(qint64 bytesSent, qint64 bytesTotal);
      void onDownloadProgress(qint64 bytesSent, qint64 bytesTotal);
      void timeOuted();
      void netError(int errorNum);

};

#endif // SENDREQUEST_H
