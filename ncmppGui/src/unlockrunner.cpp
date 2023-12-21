#include "unlockrunner.h"

#include "ncmdump.h"

UnlockRunner::UnlockRunner(QString path_, QString out_)
    : QObject{}
    , QRunnable{}
    , path(path_)
    , out(out_)
{
    setAutoDelete(true);
}

void UnlockRunner::run()
{
    ncm::ncmDump(path, out);
    emit finish();
}
