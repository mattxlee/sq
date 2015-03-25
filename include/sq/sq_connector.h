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

  void check(int ret);

  void execute(const std::string &sql);

  template <typename... T>
  void execute(const std::string &sql, T... vals)
  {
    Statement statement(*this, sql);
    execute(statement, 1, vals...);
  }

  Result query(const std::string &sql);

  template <typename... T>
  Result query(const std::string &sql, T... vals)
  {
    Statement statement(*this, sql);
    return query(statement, 1, vals...);
  }

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
