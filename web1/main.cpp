#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "ApiServer.h"
#include "WasmFileDialog.h"

int main(int argc, char *argv[])
{
  QGuiApplication app(argc, argv);


  qmlRegisterType<ApiServer>("ApiServer", 1,0, "ApiServer");
  qmlRegisterType<WasmFileDialog>("WasmFileDialog", 1,0, "WasmFileDialog");


  QQmlApplicationEngine engine;

#ifdef __EMSCRIPTEN__
  engine.rootContext()->setContextProperty("wasm_platform",true);
#else
  engine.rootContext()->setContextProperty("wasm_platform",false);
#endif

  const QUrl url("qrc:/web1/main.qml");
  QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                   &app, [url](QObject *obj, const QUrl &objUrl) {
    if (!obj && url == objUrl)
      QCoreApplication::exit(-1);
  }, Qt::QueuedConnection);
  engine.load(url);

  return app.exec();
}
