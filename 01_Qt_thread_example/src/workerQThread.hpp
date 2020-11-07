#include <QMutex>
#include <QThread>

class workerQThread : public QThread
{
    Q_OBJECT
    void run() override;

   public slots:
    void stop();

   private:
    QMutex stopMutex_;
    bool isStopped_;

   signals:
    void resultUpdated(const int i);
};

// void MyObject::startWorkInAThread()
// {
//     WorkerThread *workerThread = new WorkerThread(this);
//     connect(workerThread, &WorkerThread::resultReady, this,
//             &MyObject::handleResults);
//     connect(workerThread, &WorkerThread::finished, workerThread,
//             &QObject::deleteLater);
//     workerThread->start();
// }