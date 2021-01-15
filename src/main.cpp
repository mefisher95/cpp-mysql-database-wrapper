#include <iostream>
#include "Database.h"

int main()
{
    std::cout << "hello world" << std::endl;

    Database db;
    std::cout << db << std::endl;
    std::vector<const char*> v;
    v.push_back("Fields1 INT");
    v.push_back("Fields2 VARCHAR(200)");
    const char* name = "test_table2";
    // db.create_table(name, v);
    // db.drop_table(name);

    name = "test_table3";
    db.create_table(name, v);
    db.drop_table(name);

    std::vector<std::vector<char*>> result_vector = db.select("*", "test_table2");
    // std::cout << db.select("*", "test_table2").size() << std::endl;
    for (int i = 0; i < result_vector.size(); ++i)
    {
        const int index = atoi(result_vector[i][0]);
        const char* string = result_vector[i][1];
        std::cout << index << ' ' << string << std::endl;
    }

    return 0;
}
