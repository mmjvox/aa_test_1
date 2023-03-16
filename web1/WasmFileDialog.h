#ifndef WASMFILEDIALOG_H
#define WASMFILEDIALOG_H

#include <QQuickItem>

class WasmFileDialog : public QQuickItem
{
  Q_PROPERTY(QQuickItem* imageItem  WRITE setImageItem)
  Q_PROPERTY(QQuickItem* apiItem  WRITE setApiItem)
  Q_OBJECT
public:
  WasmFileDialog(QQuickItem *parent = nullptr);

  void setImageItem(QQuickItem* imageItem);
  void setApiItem(QQuickItem* apiItem);

public slots:
  void open();

signals:
  void accepted(QSharedPointer<QByteArray> fileContent, QString fileName, QString base64);


private:
  QQuickItem *mImageItem;
  QQuickItem *mApiItem;
};

#endif // WASMFILEDIALOG_H
