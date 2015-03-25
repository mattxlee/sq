# SQ库
SQ库是一个简单的sqlite的c++ wrap库，使用它可以方便的操作sqlite

## 编译要求
需要C++11支持，所以编译器需要gcc4.8+或者clang

## 简单的例子
随手写了一个简单的创建库、表和读取的例子，没有试过可不可以编译通过，你们看着办吧。
```c++
#include <sq.h>

int main() {
  sq::Connector _sq;
  _sq.create("hello.db");
  _sq.execute("create table hello (id, name, value)");
  _sq.execute("insert into hello (id, name, value) values (?, ?, ?)", 10, "Matthew", "100");
  sq::Result _res = _sq.query("select name from hello where id = ?", 10);
  if (_res.next()) {
    std::cout << _res.strValue(0) << std::endl;
  }
  return 0;
}
```

## 测试用例
现在还没有测试用例，争取有空写一个。
