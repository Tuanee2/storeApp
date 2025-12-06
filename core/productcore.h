#ifndef PRODUCTCORE_H
#define PRODUCTCORE_H

#include "vector"
#include "batchcore.h"

struct ProductCore {

    QString id;
    QString name;
    double price;
    std::vector<BatchCore> batches;
    QString note;
};

#endif // PRODUCTCORE_H
