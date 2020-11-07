#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>

QT_BEGIN_NAMESPACE
namespace Ui
{
class mainWindow;
}
QT_END_NAMESPACE

class workerObject;
class mainWindow : public QMainWindow
{
    Q_OBJECT

   public:
    mainWindow(QWidget *parent = nullptr);
    ~mainWindow();

   public slots:

   private:
    Ui::mainWindow *ui;
    QThread workerThread_;
    workerObject *workerObject_;

   private slots:
    void updateThreadProgress(const int i);
    void receiveMessage(const QString &msg);
    void startWorkerQThread();
};
#endif  // MAINWINDOW_H
