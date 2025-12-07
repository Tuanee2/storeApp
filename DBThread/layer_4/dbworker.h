#ifndef DBWORKER_H
#define DBWORKER_H

#include <QObject>

class DBWorker : public QObject
{
    Q_OBJECT
public:
    explicit DBWorker(QObject *parent = nullptr);
    void connection();

signals:
};

#endif // DBWORKER_H
