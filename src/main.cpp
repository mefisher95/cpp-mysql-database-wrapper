#include <iostream>
#include "Database.h"

int main()
{
    Database db;
    std::cout << db << std::endl;
    std::vector<std::string> v;
    v.push_back("Fields1 INT");
    v.push_back("Fields2 VARCHAR(200)");
    std::string name = "test_table2";
    // db.create_table(name, v);
    // db.drop_table(name);

    name = "test_table3";
    db.create_table(name, v);
    db.drop_table(name);

    RESULT_VEC result_vector = db.select("*", "test_table2");
    // std::cout << db.select("*", "test_table2").size() << std::endl;

    std::cout << result_vector << std::endl;

    for (int i = 0; i < result_vector.size(); ++i)
    {
        const int index = std::stoi(result_vector[i][0]);
        const std::string string = result_vector[i][1];
        std::cout << index << ' ' << string << std::endl;
    }

    db.desc_table("test_table2");

    db.create_database("example");
    db.drop_database("example");

    return 0;
}
