#include "sq_connector.h"
#include "sq_result.h"
#include "sq_statement.h"

namespace sq
{

bool Connector::create(const std::string &filename)
{
  remove(filename.c_str());
  check(sqlite3_open(filename.c_str(), &_sqlite));
  return true;
}

bool Connector::open(const std::string &filename)
{
  FILE *fp = fopen(filename.c_str(), "r");
  if (fp) {
    fclose(fp);
    check(sqlite3_open(filename.c_str(), &_sqlite));
    return true;
  } else {
    // failed to open file
    return false;
  }
}

void Connector::close() { check(sqlite3_close(_sqlite)); }

void Connector::check(int ret)
{
  if (ret != SQLITE_OK && ret != SQLITE_DONE) {
    // failed
    std::string msg = sqlite3_errmsg(_sqlite);
    throw std::runtime_error(msg);
  }
}

void Connector::begin_transaction() { execute("begin"); }

void Connector::rollback_transaction() { execute("rollback"); }

void Connector::commit_transaction() { execute("commit"); }

void Connector::execute(const std::string &sql)
{
  Statement statement(*this, sql);
  statement.execute();
}

Result Connector::query(const std::string &sql)
{
  Statement statement(*this, sql);
  return statement.query();
}

sqlite3 *Connector::handler() { return _sqlite; }

std::int64_t Connector::lastInsertId()
{
  return sqlite3_last_insert_rowid(_sqlite);
}

}  // namespace sq
