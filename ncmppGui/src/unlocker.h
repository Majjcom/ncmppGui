#ifndef UNLOCKER_H
#define UNLOCKER_H

#include "qlistwidget_withdrop.h"
#include <QObject>
#include <QThread>

class Unlocker : public QThread
{
    Q_OBJECT
public:
    explicit Unlocker(QObject *parent = nullptr);
    void setUp(QListWidget_withDrop* list_obj_, QString out_dir_);

protected:
    void run() override;

private:
    QListWidget_withDrop* list_obj;
    QString out_dir;

signals:
    void unlocked(int count, int total);
};

#endif // UNLOCKER_H
