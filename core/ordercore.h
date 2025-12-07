#ifndef ORDERCORE_H
#define ORDERCORE_H

#include "productcore.h"

enum class DebtType : uint8_t{
    NONE,
    MONTH,
    SEASON
};

struct OrderCore {
    QString id;
    QString saleDate;
    std::pair<QString, double> paymentHistory;
    double totalPrice;

    QString note;
};

#endif // ORDERCORE_H
