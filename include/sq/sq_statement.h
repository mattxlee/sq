#ifndef SQ_STATEMENT_H
#define SQ_STATEMENT_H

#include <sqlite3.h>
#include <string>

namespace sq
{

class Connector;
class Result;

class Statement
{
 public:
  Statement(Connector &connector, const std::string &sql);

  void bind(int index, int value);
  void bind(int index, const std::string &value);
  void bind(int index, bool value);

  Result query();
  void execute();

 private:
  Connector &_connector;
  sqlite3_stmt *_stmt = nullptr;
};

}  // namespace sq

#endif  // SQ_STATEMENT_H
