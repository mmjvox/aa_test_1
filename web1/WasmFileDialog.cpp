#include "WasmFileDialog.h"
#ifdef __EMSCRIPTEN__
#include <QFileDialog>
#endif
#include "ApiServer.h"

WasmFileDialog::WasmFileDialog(QQuickItem *parent)
  : QQuickItem{parent}
{

}

void WasmFileDialog::setImageItem(QQuickItem *imageItem)
{
  mImageItem = imageItem;
}

void WasmFileDialog::setApiItem(QQuickItem *apiItem)
{
  mApiItem = apiItem;
}

void WasmFileDialog::open()
{
#ifdef __EMSCRIPTEN__
  auto fileContentReady = [this](const QString &fileName, const QByteArray &fileContent) {
      if (fileName.isEmpty()) {
          qDebug()<<"file name is empty";
          return;
      }
      if (fileContent.isEmpty()) {
          qDebug()<<"file content is empty";
          return;
      }


//      qobject_cast<ApiServer*>(mApiItem)->sendSample();

      emit accepted(QSharedPointer<QByteArray>::create(fileContent), fileName, fileContent.toBase64().prepend("data:image/png;base64,") );
  };
  QFileDialog::getOpenFileContent("Images (*.png *.xpm *.jpg)",  fileContentReady);
#endif
}
