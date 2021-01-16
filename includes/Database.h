#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <mysql.h>
#include <string>
#include <vector>
#include "util.h"

typedef std::vector<std::vector<std::string>> RESULT_VEC;


class MySQLException
{
public:
    MySQLException(int error_code, const char* error)
    : error_code_(error_code), error_message_(error)
    {
        std::string message = "MySQLException error " +
                              std::to_string(error_code_) +
                              ": " + error_message_;
        // std::cout << error_message_ << std::endl;
        log_error(message.c_str(), "error.log");
    }
    int error_code() const { return error_code_; }
    std::string error_message() const { return error_message_; }

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

    std::string current_database() const;
    void use_database(const std::string &);
    void create_database(const std::string &);
    void drop_database(const std::string &);
    std::vector<std::string> show_databases();
    bool is_database(const std::string &);

    void create_table(const std::string &, const std::vector<std::string> &);
    void drop_table(const std::string &);
    RESULT_VEC desc_table(const std::string &);

    void insert_row(const std::string &, const std::vector<std::string> &, const RESULT_VEC &);
    void update_row(const std::string &, const std::string &, const std::string &);
    void delete_row(const std::string &, const std::string &);

    RESULT_VEC select(const std::string &, const std::string&);

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
std::ostream &operator<<(std::ostream &cout, const MySQLException &);

#endif
