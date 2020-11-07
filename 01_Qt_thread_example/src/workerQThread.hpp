#include <QMutex>
#include <QThread>

class workerQThread : public QThread
{
    Q_OBJECT
   protected:
    void run() override;

   public slots:
    void stop();

   private:
    QMutex stopMutex_;
    bool isStopped_;

   signals:
    void resultUpdated(const int i);
    void message(const QString& msg);
};