#include "sq_result.h"
#include "sq_connector.h"

namespace sq
{

Result::Result(Connector &connector, sqlite3_stmt *stmt)
    : _connector(connector), _stmt(stmt)
{
}

Result::Result(Result &&rhs) : _connector(rhs._connector)
{
  _stmt = rhs._stmt;
  rhs._stmt = nullptr;
}

Result &Result::operator=(Result &&rhs)
{
  if (this != &rhs) {
    _stmt = rhs._stmt;
    rhs._stmt = nullptr;
  }
  return *this;
}

Result::~Result()
{
  if (_stmt) {
    _connector.check(sqlite3_finalize(_stmt));
    _stmt = nullptr;
  }
}

bool Result::next()
{
  int ret = sqlite3_step(_stmt);
  if (ret == SQLITE_ROW) {
    return true;
  } else if (ret == SQLITE_DONE) {
    return false;
  } else {
    _connector.check(ret);
    return false;
  }
}

int Result::intValue(int column) const
{
  return sqlite3_column_int(_stmt, column);
}

std::string Result::strValue(int column) const
{
  return reinterpret_cast<const char *>(sqlite3_column_text(_stmt, column));
}

bool Result::boolValue(int column) const
{
  return sqlite3_column_int(_stmt, column) != 0;
}

}  // namespace sq
