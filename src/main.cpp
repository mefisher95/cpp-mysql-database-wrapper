#include <iostream>
#include "Database.h"

int main()
{
    Database db;
    std::cout << db << std::endl;

    db.insert("test_table2", ["test", "test2"], []);

    return 0;
}
