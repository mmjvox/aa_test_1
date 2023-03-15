#include "serverconn.h"

ServerConn *ServerConn::ServerConnInstance = nullptr;



ServerConn::ServerConn(QObject *parent) : QObject(parent)
{
//    networkManager= new QNetworkAccessManager;
}

ServerConn::~ServerConn(){}

