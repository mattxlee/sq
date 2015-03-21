#ifndef SQ_RESULT_H
#define SQ_RESULT_H

#include <sqlite3.h>
#include <string>

namespace sq {

class Connector;

class Result {
public:
    Result(const Result &) = delete;
    Result &operator=(const Result &) = delete;

    Result(Connector &connector, sqlite3_stmt *stmt);
    Result(Result &&rhs);
    Result &operator=(Result &&rhs);
    ~Result();

    bool next();

    int intValue(int column) const;
    std::string strValue(int column) const;
    bool boolValue(int column) const;

private:
    Connector &_connector;
    sqlite3_stmt *_stmt = nullptr;
};

} // namespace sq

#endif // SQ_RESULT_H
