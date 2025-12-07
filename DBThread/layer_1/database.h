#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QSqlDatabase>

class DataBase
{
public:
    explicit DataBase(const QString &connectionName = QString());
    ~DataBase();

    bool open(const QString &filePath);  // mở / tạo file SQLite
    bool createTables();                 // tạo toàn bộ bảng nếu chưa có
    inline bool isOpen() const { return m_db.isOpen(); }

private:
    bool createCustomersTable();
    bool createSuppliersTable();
    bool createProductsTable();
    bool createBatchesTable();
    bool createOrdersTable();
    bool createOrderItemsTable();
    bool createInterestTransactionsTable();
    bool createPaymentTransactionsTable();
    bool createCustomerStatsTable();

    bool execQuery(const QString &sql);

private:
    QSqlDatabase m_db;
};

#endif // DATABASE_H
