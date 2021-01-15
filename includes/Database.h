#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <mysql.h>
#include <string>
#include <vector>
#include "util.h"


class MySQLException
{
public:
    MySQLException(int error_code, const char* error)
    : error_code_(error_code), error_message_(error)
    {
        error_message_ = "MySQLException error " +
                         std::to_string(error_code_) +
                         ": " + error_message_;
        std::cout << error_message_ << std::endl;
        log_error(error_message_.c_str());
    }

private:
    int error_code_;
    std::string error_message_;
};

class Database
{
public:
    Database(std::string user = "root", std::string pasw = "root",
             std::string database = "test", std::string host = "127.0.0.1")
    :user_(user), password_(pasw), database_(database), host_(host)
    {}

    std::string database() const;
    void use_database(const std::string & newdatabase);
    void create_table(const char* name, const std::vector<const char*> fields);
    void drop_table(const char* name);
    std::vector<std::vector<char*>> select(const char* paramaters, const char* target);

private:
    // Member variables

    std::string user_;
    std::string password_;
    std::string database_;
    std::string host_;

    // Private Methods

    MYSQL_RES* commit(const char* sql_request);

};

std::ostream &operator<<(std::ostream &cout, const Database &db);

#endif
