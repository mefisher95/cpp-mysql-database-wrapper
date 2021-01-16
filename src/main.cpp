#include <iostream>
#include "Database.h"

int main()
{
    Database db;
    std::cout << db << std::endl;
    // db.show_databases();

    std::cout << db.is_database("tests") << std::endl;

    return 0;
}
