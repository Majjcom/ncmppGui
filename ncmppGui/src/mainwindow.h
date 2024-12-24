#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include "unlocker.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void updateProgressbar();

protected slots:
    void fileButtonClicked();
    void doButtonClicked();
    void importButtonClicked();
    void resetThreadCountButtonClicked();
    void unlocked(int count, int total);
    void threadFinished();

private:
    Ui::MainWindow *ui;
    Unlocker* unlockThread = nullptr;
};
#endif // MAINWINDOW_H
