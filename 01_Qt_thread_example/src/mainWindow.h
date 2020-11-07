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
class workerQThread;
class mainWindow : public QMainWindow
{
    Q_OBJECT

   public:
    mainWindow(QWidget *parent = nullptr);
    ~mainWindow();

   public slots:
    void receiveMessage(const QString &msg);

   private:
    Ui::mainWindow *ui;
    QThread workerThread_;
    workerObject *workerObject_;

   private slots:
    void updateThreadProgress(const int i);
};
#endif  // MAINWINDOW_H
