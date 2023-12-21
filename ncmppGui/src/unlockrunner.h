#ifndef UNLOCKRUNNER_H
#define UNLOCKRUNNER_H

#include <QObject>
#include <QRunnable>

class UnlockRunner : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit UnlockRunner(QString path_, QString out_);

    void run() override;

private:
    QString path;
    QString out;

signals:
    void finish();
};

#endif // UNLOCKRUNNER_H
