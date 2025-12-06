#ifndef BATCHCORE_H
#define BATCHCORE_H

#include <QString>

struct BatchCore {
    QString id;
    QString productId;
    QString supplierId;
    QString exportDate;
    QString importDate;
    QString expiredDate;

    double importPrice;
    double exportPrice;
    int originalQuantity;
    int remainingQuantity;

    QString note;
};

#endif // BATCHCORE_H
