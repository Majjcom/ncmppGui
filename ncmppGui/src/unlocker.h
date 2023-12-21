#ifndef UNLOCKER_H
#define UNLOCKER_H

#include "qlistwidget_withdrop.h"
#include <QObject>
#include <QThreadPool>
#include <QThread>

class Unlocker : public QThread
{
    Q_OBJECT
public:
    explicit Unlocker(QObject* parent = nullptr);
    void setUp(QListWidget_withDrop* list_obj_, QString out_dir_);

protected:
    void run() override;

private slots:
    void runner_finished();

private:
    QListWidget_withDrop* list_obj;
    QThreadPool* pool;
    QString out_dir;
    int unlocked_count;
    int count = 0;

signals:
    void unlocked(int count, int total);
};

#endif // UNLOCKER_H
