#include <QMutex>
#include <QObject>

class workerObject : public QObject
{
    Q_OBJECT
   public slots:
    void runSomeBigWork();
    void stop();

   private:
    QMutex stopMutex_;
    bool isStopped_;
   signals:
    void resultUpdated(int i);
    void message(const QString& msg);
};