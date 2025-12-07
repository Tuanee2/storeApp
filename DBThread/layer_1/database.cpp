#include "database.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

DataBase::DataBase(const QString &connectionName)
{
    const QString connName =
        connectionName.isEmpty() ? QStringLiteral("storeAppConnection") : connectionName;

    if (QSqlDatabase::contains(connName)) {
        m_db = QSqlDatabase::database(connName);
    } else {
        m_db = QSqlDatabase::addDatabase(QStringLiteral("QSQLITE"), connName);
    }
}

DataBase::~DataBase()
{
    if (m_db.isOpen()) {
        m_db.close();
    }
}

bool DataBase::open(const QString &filePath)
{
    if (!m_db.isValid()) {
        qWarning() << "[DataBase] Invalid QSqlDatabase";
        return false;
    }

    m_db.setDatabaseName(filePath);

    if (!m_db.open()) {
        qWarning() << "[DataBase] Failed to open database:"
                   << m_db.lastError().text();
        return false;
    }

    // Bật foreign keys của SQLite
    if (!execQuery(QStringLiteral("PRAGMA foreign_keys = ON;"))) {
        qWarning() << "[DataBase] Failed to enable foreign keys";
        return false;
    }

    return true;
}

bool DataBase::createTables()
{
    if (!isOpen()) {
        qWarning() << "[DataBase] Database is not open";
        return false;
    }

    if (!createCustomersTable())            return false;
    if (!createSuppliersTable())            return false;
    if (!createProductsTable())             return false;
    if (!createBatchesTable())              return false;
    if (!createOrdersTable())               return false;
    if (!createOrderItemsTable())           return false;
    if (!createInterestTransactionsTable()) return false;
    if (!createPaymentTransactionsTable())  return false;
    if (!createCustomerStatsTable())        return false;

    return true;
}

bool DataBase::execQuery(const QString &sql)
{
    QSqlQuery query(m_db);
    if (!query.exec(sql)) {
        qWarning() << "[DataBase] SQL error:"
                   << query.lastError().text()
                   << "\nQuery:" << sql;
        return false;
    }
    return true;
}

// ---------------------- CREATE TABLES ----------------------

bool DataBase::createCustomersTable()
{
    const QString sql = QStringLiteral(
        "CREATE TABLE IF NOT EXISTS customers ("
        "  id TEXT PRIMARY KEY,"
        "  name TEXT NOT NULL,"
        "  phone TEXT,"
        "  address TEXT,"
        "  note TEXT"
        ");"
        );
    return execQuery(sql);
}

bool DataBase::createSuppliersTable()
{
    const QString sql = QStringLiteral(
        "CREATE TABLE IF NOT EXISTS suppliers ("
        "  id TEXT PRIMARY KEY,"
        "  name TEXT NOT NULL,"
        "  phone TEXT,"
        "  address TEXT,"
        "  note TEXT"
        ");"
        );
    return execQuery(sql);
}

bool DataBase::createProductsTable()
{
    const QString sql = QStringLiteral(
        "CREATE TABLE IF NOT EXISTS products ("
        "  id TEXT PRIMARY KEY,"
        "  name TEXT NOT NULL,"
        "  price REAL NOT NULL DEFAULT 0,"
        "  note TEXT"
        ");"
        );
    return execQuery(sql);
}

bool DataBase::createBatchesTable()
{
    const QString sql = QStringLiteral(
        "CREATE TABLE IF NOT EXISTS batches ("
        "  id TEXT PRIMARY KEY,"
        "  product_id TEXT NOT NULL,"
        "  supplier_id TEXT,"
        "  import_date TEXT,"
        "  export_date TEXT,"
        "  expired_date TEXT,"
        "  import_price REAL NOT NULL DEFAULT 0,"
        "  export_price REAL NOT NULL DEFAULT 0,"
        "  original_quantity INTEGER NOT NULL DEFAULT 0,"
        "  remaining_quantity INTEGER NOT NULL DEFAULT 0,"
        "  note TEXT,"
        "  FOREIGN KEY(product_id) REFERENCES products(id) ON DELETE CASCADE,"
        "  FOREIGN KEY(supplier_id) REFERENCES suppliers(id) ON DELETE SET NULL"
        ");"
        );
    return execQuery(sql);
}

bool DataBase::createOrdersTable()
{
    const QString sql = QStringLiteral(
        "CREATE TABLE IF NOT EXISTS orders ("
        "  id TEXT PRIMARY KEY,"
        "  customer_id TEXT NOT NULL,"
        "  sale_date TEXT,"
        "  total_price REAL NOT NULL DEFAULT 0,"
        "  remaining_principal REAL NOT NULL DEFAULT 0,"
        "  total_interest_accrued REAL NOT NULL DEFAULT 0,"
        "  remaining_interest REAL NOT NULL DEFAULT 0,"
        "  total_paid REAL NOT NULL DEFAULT 0,"
        "  debt_type INTEGER NOT NULL DEFAULT 0,"
        "  current_interest_rate REAL NOT NULL DEFAULT 0,"
        "  debt_start_date TEXT,"
        "  last_interest_calc_date TEXT,"
        "  status INTEGER NOT NULL DEFAULT 0,"
        "  note TEXT,"
        "  FOREIGN KEY(customer_id) REFERENCES customers(id) ON DELETE CASCADE"
        ");"
        );
    return execQuery(sql);
}

bool DataBase::createOrderItemsTable()
{
    const QString sql = QStringLiteral(
        "CREATE TABLE IF NOT EXISTS order_items ("
        "  id TEXT PRIMARY KEY,"
        "  order_id TEXT NOT NULL,"
        "  product_id TEXT NOT NULL,"
        "  batch_id TEXT,"
        "  quantity INTEGER NOT NULL DEFAULT 0,"
        "  unit_price REAL NOT NULL DEFAULT 0,"
        "  discount REAL NOT NULL DEFAULT 0,"
        "  principal_amount REAL NOT NULL DEFAULT 0,"
        "  current_interest_rate REAL NOT NULL DEFAULT 0,"
        "  note TEXT,"
        "  FOREIGN KEY(order_id) REFERENCES orders(id) ON DELETE CASCADE,"
        "  FOREIGN KEY(product_id) REFERENCES products(id),"
        "  FOREIGN KEY(batch_id) REFERENCES batches(id)"
        ");"
        );
    return execQuery(sql);
}

bool DataBase::createInterestTransactionsTable()
{
    const QString sql = QStringLiteral(
        "CREATE TABLE IF NOT EXISTS interest_transactions ("
        "  id TEXT PRIMARY KEY,"
        "  order_id TEXT NOT NULL,"
        "  order_item_id TEXT,"
        "  from_date TEXT,"
        "  to_date TEXT,"
        "  interest_rate REAL NOT NULL DEFAULT 0,"
        "  base_amount REAL NOT NULL DEFAULT 0,"
        "  interest_amount REAL NOT NULL DEFAULT 0,"
        "  note TEXT,"
        "  FOREIGN KEY(order_id) REFERENCES orders(id) ON DELETE CASCADE,"
        "  FOREIGN KEY(order_item_id) REFERENCES order_items(id) ON DELETE SET NULL"
        ");"
        );
    return execQuery(sql);
}

bool DataBase::createPaymentTransactionsTable()
{
    const QString sql = QStringLiteral(
        "CREATE TABLE IF NOT EXISTS payment_transactions ("
        "  id TEXT PRIMARY KEY,"
        "  order_id TEXT NOT NULL,"
        "  order_item_id TEXT,"
        "  pay_date TEXT,"
        "  amount REAL NOT NULL DEFAULT 0,"
        "  type INTEGER NOT NULL DEFAULT 0,"
        "  note TEXT,"
        "  FOREIGN KEY(order_id) REFERENCES orders(id) ON DELETE CASCADE,"
        "  FOREIGN KEY(order_item_id) REFERENCES order_items(id) ON DELETE SET NULL"
        ");"
        );
    return execQuery(sql);
}

bool DataBase::createCustomerStatsTable()
{
    const QString sql = QStringLiteral(
        "CREATE TABLE IF NOT EXISTS customer_stats ("
        "  customer_id TEXT PRIMARY KEY,"
        "  total_orders INTEGER NOT NULL DEFAULT 0,"
        "  total_spent REAL NOT NULL DEFAULT 0,"
        "  total_paid REAL NOT NULL DEFAULT 0,"
        "  last_order_date TEXT,"
        "  rank_level TEXT,"
        "  FOREIGN KEY(customer_id) REFERENCES customers(id) ON DELETE CASCADE"
        ");"
        );
    return execQuery(sql);
}
