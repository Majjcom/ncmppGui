#ifndef QLISTWIDGET_WITHDROP_H
#define QLISTWIDGET_WITHDROP_H

#include <QListWidget>
#include <QObject>
#include <QWidget>

class QListWidget_withDrop : public QListWidget
{
    Q_OBJECT
public:
    explicit QListWidget_withDrop(QWidget *parent = nullptr);
    QString getNextFile();
    int getFileCount();

protected:
    void dragEnterEvent(QDragEnterEvent* ev) override;
    void dropEvent(QDropEvent* ev) override;

signals:

};

#endif // QLISTWIDGET_WITHDROP_H
