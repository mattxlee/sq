#ifndef SQ_CONNECTOR_H
#define SQ_CONNECTOR_H

#include <sqlite3.h>

#include <string>
#include <utility>

#include "sq_statement.h"
#include "sq_result.h"

namespace sq
{

class Result;
class Statement;

class Connector
{
 public:

  /**
   *  Create local database
   *
   *  @param filename The new database filename (warning, existing file will be override)
   *
   *  @return Returns true means create successfully
   */
  bool create(const std::string &filename);

  /**
   *  Open an existing local database
   *
   *  @param filename The local database filename
   *
   *  @return Returns true means open successfully, otherwise the database is not exists or corrupted file
   */
  bool open(const std::string &filename);

  /**
   *  Close currently database
   */
  void close();

  /**
   *  Check sqlite return value and throw if sqlite is failed
   *
   *  @param ret The sqlite return value
   */
  void check(int ret);

  /**
   *  Begin a new transaction
   */
  void begin_transaction();

  /**
   *  Rollback current transaction
   */
  void rollback_transaction();

  /**
   *  Commit current transaction
   */
  void commit_transaction();

  /**
   *  Execute a SQL statement
   *
   *  @param sql SQL statement string
   */
  void execute(const std::string &sql);

  /**
   *  Execute a SQL statement with one or more parameters
   *
   *  @param sql  SQL statement string
   *  @param vals Parameters
   */
  template <typename... T>
  void execute(const std::string &sql, T... vals)
  {
    Statement statement(*this, sql);
    execute(statement, 1, vals...);
  }

  /**
   *  Run a query and fetch results
   *
   *  @param sql SQL statement string
   *
   *  @return Query result set
   */
  Result query(const std::string &sql);

  /**
   *  Run a query with one or more parameters
   *
   *  @param sql  SQL statement string
   *  @param vals Parameters
   *
   *  @return Query result set
   */
  template <typename... T>
  Result query(const std::string &sql, T... vals)
  {
    Statement statement(*this, sql);
    return query(statement, 1, vals...);
  }

  /**
   *  Get sqlite original database pointer
   *
   *  @return Sqlite database pointer
   */
  sqlite3 *handler();

 private:
  void execute(Statement &statement, int index) { statement.execute(); }

  template <typename T, typename... Vals>
  void execute(Statement &statement, int index, T &&val, Vals... vals)
  {
    statement.bind(index, std::forward<T>(val));
    execute(statement, index + 1, vals...);
  }

  Result query(Statement &statement, int index) { return statement.query(); }

  template <typename T, typename... Vals>
  Result query(Statement &statement, int index, T &&val, Vals... vals)
  {
    statement.bind(index, std::forward<T>(val));
    return query(statement, index + 1, vals...);
  }

 private:
  sqlite3 *_sqlite = nullptr;
};

}  // namespace sq

#endif  // SQ_CONNECTOR_H
