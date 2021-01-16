#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <mysql.h>
#include <string>
#include <vector>
#include "util.h"

typedef std::vector<std::vector<std::string>> RESULT_VEC;
typedef std::vector<std::string> STRING_VEC;


class MySQLException
{
public:
    MySQLException(int error_code, const char* error);
    int error_code() const;
    std::string error_message() const;

private:
    int error_code_;
    std::string error_message_;
};

class Database
{
public:
    Database(std::string user = "root", std::string pasw = "root",
             std::string database = "", std::string host = "127.0.0.1");

    std::string current_database() const;
    void use_database(const std::string &);
    void create_database(const std::string &);
    void drop_database(const std::string &);
    STRING_VEC show_databases();
    bool is_database(const std::string &);

    void create_table(const std::string &, const std::vector<std::string> &);
    void drop_table(const std::string &);
    RESULT_VEC desc_table(const std::string &);
    STRING_VEC show_tables();
    bool is_table(const std::string &);

    void insert_row(const std::string &, const std::vector<std::string> &, const RESULT_VEC &);
    void update_row(const std::string &, const std::string &, const std::string &);
    void delete_row(const std::string &, const std::string &);

    RESULT_VEC select(const std::string &, const std::string&);
    RESULT_VEC select(const std::string &);


private:
    // Member variables

    std::string user_;
    std::string password_;
    std::string database_;
    std::string host_;

    // Private Methods

    MYSQL_RES* commit(const char*);

};

std::ostream &operator<<(std::ostream &cout, const Database &);
std::ostream &operator<<(std::ostream &cout, const RESULT_VEC &);
std::ostream &operator<<(std::ostream &cout, const STRING_VEC &);
std::ostream &operator<<(std::ostream &cout, const MySQLException &);


#endif
