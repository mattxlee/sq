#include "sq_statement.h"
#include "sq_connector.h"
#include "sq_result.h"

namespace sq {

Statement::Statement(Connector &connector, const std::string &sql)
    : _connector(connector) {
    connector.check(sqlite3_prepare_v2(
                        _connector.handler(), sql.c_str(), -1, &_stmt,
                        nullptr));
}

void Statement::bind(int index, int value) {
    _connector.check(sqlite3_bind_int(_stmt, index, value));
}

void Statement::bind(int index, const std::string &value) {
    _connector.check(sqlite3_bind_text(
                         _stmt, index, value.c_str(), -1, nullptr));
}

void Statement::bind(int index, bool value) {
    _connector.check(sqlite3_bind_int(_stmt, index, value != 0 ? 1 : 0));
}

Result Statement::query() {
    Result result(_connector, _stmt);
    return result;
}

void Statement::execute() {
    _connector.check(sqlite3_step(_stmt));
    _connector.check(sqlite3_finalize(_stmt));
    _stmt = nullptr;
}

} // namespace sq
