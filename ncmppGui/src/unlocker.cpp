#include "unlocker.h"

#include "unlockrunner.h"
#include "ncmdump.h"

Unlocker::Unlocker(QObject *parent)
    : pool(new QThreadPool(this))
    , unlocked_count(0)
{
    this->setParent(parent);
}

void Unlocker::setUp(QListWidget_withDrop* list_obj_, QString out_dir_)
{
    this->list_obj = list_obj_;
    this->out_dir = out_dir_;
}

void Unlocker::run()
{
    count = this->list_obj->getFileCount();
    for (int i = 0; i < count; i++)
    {
        QString file = this->list_obj->getNextFile();
        UnlockRunner* runner = new UnlockRunner(file, this->out_dir);
        connect(runner, SIGNAL(finish()), this, SLOT(runner_finished()));
        bool ok = false;
        while (!ok)
        {
            ok = pool->tryStart(runner);
        }
    }
    pool->waitForDone();
    this->exit();
}

void Unlocker::runner_finished()
{
    unlocked_count++;
    emit unlocked(unlocked_count, count);
}
