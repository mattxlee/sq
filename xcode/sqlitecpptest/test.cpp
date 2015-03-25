//
//  main.cpp
//  sqlitecpptest
//
//  Created by Matthew Lee on 15/3/25.
//  Copyright (c) 2015年 mattxlee. All rights reserved.
//

#include <gtest/gtest.h>
#include "sq.h"

TEST(sqlitecpptest, create_database)
{
  sq::Connector _connector;
  EXPECT_TRUE(_connector.create("hello.db"));
}

TEST(sqlitecpptest, open_database)
{
  sq::Connector _connector;
  EXPECT_TRUE(_connector.open("hello.db"));
}

TEST(sqlitecpptest, create_table)
{
  sq::Connector _connector;
  ASSERT_TRUE(_connector.open("hello.db"));
  _connector.execute("create table if not exists sample (id, name, value)");
  _connector.execute("insert into sample (id, name, value) values (?, ?, ?)",
                     10, "Matthew", 100);
  sq::Result _res =
      _connector.query("select name, value from sample where id = ?", 10);
  ASSERT_TRUE(_res.next());
  EXPECT_EQ(_res.strValue(0), "Matthew");
  EXPECT_EQ(_res.intValue(1), 100);
}