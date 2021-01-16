#include "Database.h"


std::string Database::current_database() const { return database_; }
void Database::use_database(const std::string &newdatabase) { database_ = newdatabase; }

void Database::create_database(const std::string &name)
{
    std::string sql = "CREATE DATABASE " + std::string(name) + ";";
    mysql_free_result(commit(sql.c_str()));
}

void Database::drop_database(const std::string &name)
{
    std::string sql = "DROP DATABASE " + std::string(name) + ";";
    mysql_free_result(commit(sql.c_str()));
}


void Database::create_table(const std::string &name,
                            const std::vector<std::string> &xfields)
{
    std::string sql = "CREATE TABLE ";
    sql += std::string(name) + "(";

    for (int i = 0; i < fields.size(); ++i)
    {
        sql.append(fields[i]);
        if (i < fields.size() - 1) sql.append(",");
    }

    sql += ") engine=innodb;";

    // remember to always free the result pointer!
    mysql_free_result(commit(sql.c_str()));
}

void Database::drop_table(const std::string &name)
{
    std::string sql = "DROP TABLE ";
    sql.append(name);
    sql.append(";");
    std::cout << sql << std::endl;

    // remember to always free the result pointer!
    mysql_free_result(commit(sql.c_str()));
}

RESULT_VEC Database::desc_table(const std::string &name)
{
    std::string sql = "DESC " + std::string(name) + ";";
    std::cout << sql << std::endl;

    MYSQL_RES* result = commit(sql.c_str());
    MYSQL_ROW result_row;

    MYSQL_FIELD *field;
    int field_count = 0;

    for (;(field = mysql_fetch_field(result)); ++field_count){}

    RESULT_VEC fields;
    while ((result_row =mysql_fetch_row(result)) != NULL)
    {
        std::vector<std::string> param;
        for (int i = 0; i < field_count; ++i)
        {
            param.push_back((result_row[i] ? result_row[i] : "NULL"));
        }
        fields.push_back(param);
    }

    mysql_free_result(result);
    return fields;
}

RESULT_VEC Database::select(const std::string &paramaters,
                            const std::string &target)
{
    std::string sql = "SELECT ";
    sql.append(paramaters);
    sql += " FROM ";
    sql.append(target);
    sql += ";";

    MYSQL_RES* result = commit(sql.c_str());
    MYSQL_ROW result_row;
    MYSQL_FIELD *field;
    int field_count = 0;

    for (;(field = mysql_fetch_field(result)); ++field_count){}

    RESULT_VEC select_vector;

    while ((result_row =mysql_fetch_row(result)) != NULL)
    {
        std::vector< std::string > row_vector;
        for (int i =0; i < field_count; ++i)
        {
            row_vector.push_back(result_row[i]);
        }

        select_vector.push_back(row_vector);
    }
    mysql_free_result(result);
    return select_vector;
}

MYSQL_RES* Database::commit(const char* sql_request)
{
    MYSQL mysql;
    mysql_init(&mysql);
    MYSQL* conn = mysql_real_connect(&mysql, host_.c_str(),
                                     user_.c_str(), password_.c_str(),
                                     database_.c_str(), 0, 0, 0);
    if (conn == NULL)
    {
        const char* error = mysql_error(&mysql);
        std::cout << error << std::endl;
        throw MySQLException(0, error);
    }

    int state = mysql_query(conn, sql_request);

    if (state)
    {
        const char* error = mysql_error(&mysql);
        throw MySQLException(1, error);
    }
    MYSQL_RES* result = mysql_store_result(conn);

    mysql_close(conn);
    log_error(sql_request, "sql_request.log");
    return result;
}

std::ostream &operator<<(std::ostream &cout, const Database &db)
{
    cout << "<Database object " << &db << " conn=" << db.database() << ">";
    return cout;
}

std::ostream &operator<<(std::ostream &cout, const RESULT_VEC &result_vector)
{
    for (int i = 0; i < result_vector.size(); ++i)
    {
        for (int k = 0; k < result_vector[i].size(); ++k)
        {
            cout << result_vector[i][k] << ' ';
        }
        cout << std::endl;
    }
    return cout;
}
