#include <iostream>
#include <string>

#include "istorage.cpp"
#include "../source/sqlite3.h"
#include "../task/task.cpp"

using namespace std;

class SQLite : public iStorage
{
private:
  static SQLite *m_instance;

  sqlite3 *m_db;

  SQLite(char *db_path)
  {
    int err = sqlite3_open(db_path, &m_db);

    if (err)
    {
      cout << "DB Open Error: " << sqlite3_errmsg(m_db) << endl;
      return;
    }
  }

public:
  static SQLite *GetInstance(char *db_path)
  {
    if (m_instance == nullptr)
    {
      m_instance = new SQLite(db_path);
    }

    return m_instance;
  }

  Task CreateTask(string task_description)
  {
    sqlite3_stmt *stmt;
    char sql[] = "INSERT INTO tasks (task_description) VALUES (?);";

    int err = sqlite3_prepare_v2(m_db, sql, -1, &stmt, NULL);
    if (err != SQLITE_OK)
      return Task();

    err = sqlite3_bind_text(stmt, 1, task_description.c_str(), -1, SQLITE_STATIC);
    if (err != SQLITE_OK)
      return Task();

    err = sqlite3_step(stmt);
    if (err != SQLITE_DONE)
      return Task();

    err = sqlite3_finalize(stmt);
    if (err != SQLITE_OK)
      return Task();

    int row_id = sqlite3_last_insert_rowid(m_db);

    return GetTaskById(row_id);
  }

  Task UpdateTaskDescription(int task_id, string task_description)
  {
    sqlite3_stmt *stmt;
    char sql[] = "UPDATE tasks SET task_description = ? WHERE task_id = ?;";

    int err = sqlite3_prepare_v2(m_db, sql, -1, &stmt, NULL);
    if (err != SQLITE_OK)
      return Task();

    err = sqlite3_bind_text(stmt, 1, task_description.c_str(), -1, SQLITE_STATIC);
    if (err != SQLITE_OK)
      return Task();

    err = sqlite3_bind_int(stmt, 2, task_id);
    if (err != SQLITE_OK)
      return Task();

    err = sqlite3_step(stmt);
    if (err != SQLITE_DONE)
      return Task();

    err = sqlite3_finalize(stmt);
    if (err != SQLITE_OK)
      return Task();

    return GetTaskById(task_id);
  }

  Task UpdateTaskStatus(int task_id, TASK_STATUS task_status)
  {
    sqlite3_stmt *stmt;
    char sql[] = "UPDATE tasks SET task_status = ? WHERE task_id = ?;";

    int err = sqlite3_prepare_v2(m_db, sql, -1, &stmt, NULL);
    if (err != SQLITE_OK)
      return Task();

    err = sqlite3_bind_int(stmt, 1, task_status);
    if (err != SQLITE_OK)
      return Task();

    err = sqlite3_bind_int(stmt, 2, task_id);
    if (err != SQLITE_OK)
      return Task();

    err = sqlite3_step(stmt);
    if (err != SQLITE_DONE)
      return Task();

    err = sqlite3_finalize(stmt);
    if (err != SQLITE_OK)
      return Task();

    return GetTaskById(task_id);
  }

  Task GetTaskById(int task_id)
  {
    sqlite3_stmt *stmt;
    char sql[] = "SELECT * FROM tasks WHERE task_id = ?;";

    int err = sqlite3_prepare_v2(m_db, sql, -1, &stmt, NULL);
    if (err != SQLITE_OK)
      return Task();

    err = sqlite3_bind_int(stmt, 1, task_id);
    if (err != SQLITE_OK)
      return Task();

    Task task;
    while ((err = sqlite3_step(stmt)) == SQLITE_ROW)
    {
      int db_task_id = sqlite3_column_int(stmt, 0);
      const unsigned char *db_task_description = sqlite3_column_text(stmt, 1);
      int db_task_status = sqlite3_column_int(stmt, 2);
      const unsigned char *db_task_created_at = sqlite3_column_text(stmt, 3);
      const unsigned char *db_task_updated_at = sqlite3_column_text(stmt, 4);

      char *task_description = reinterpret_cast<char*>(const_cast<unsigned char*>(db_task_description));
      char *task_created_at = reinterpret_cast<char*>(const_cast<unsigned char*>(db_task_created_at));
      char *task_updated_at = reinterpret_cast<char*>(const_cast<unsigned char*>(db_task_updated_at));

      task.Set(db_task_id, task_description, TaskStatusIntToEnum(db_task_status), task_created_at, task_updated_at);
    }

    if (err != SQLITE_DONE)
      return Task();

    err = sqlite3_finalize(stmt);
    if (err != SQLITE_OK)
      return Task();

    return task;
  }

  vector<Task> GetAllTasks()
  {
    sqlite3_stmt *stmt;
    char sql[] = "SELECT * FROM tasks;";

    int err = sqlite3_prepare_v2(m_db, sql, -1, &stmt, NULL);
    if (err != SQLITE_OK)
      return {};

    vector<Task> output;
    while ((err = sqlite3_step(stmt)) == SQLITE_ROW)
    {
      int task_id = sqlite3_column_int(stmt, 0);
      const unsigned char *db_task_description = sqlite3_column_text(stmt, 1);
      int task_status = sqlite3_column_int(stmt, 2);
      const unsigned char *db_task_created_at = sqlite3_column_text(stmt, 3);
      const unsigned char *db_task_updated_at = sqlite3_column_text(stmt, 4);

      char *task_description = reinterpret_cast<char*>(const_cast<unsigned char*>(db_task_description));
      char *task_created_at = reinterpret_cast<char*>(const_cast<unsigned char*>(db_task_created_at));
      char *task_updated_at = reinterpret_cast<char*>(const_cast<unsigned char*>(db_task_updated_at));

      output.push_back(Task(task_id, task_description, TaskStatusIntToEnum(task_status), task_created_at, task_updated_at));
    }
    if (err != SQLITE_DONE)
      return {};

    err = sqlite3_finalize(stmt);
    if (err != SQLITE_OK)
      return {};

    return output;
  }

  vector<Task> GetTasksByTaskStatus(TASK_STATUS task_status)
  {
    sqlite3_stmt *stmt;
    char sql[] = "SELECT * FROM tasks WHERE task_status = ?;";

    int err = sqlite3_prepare_v2(m_db, sql, -1, &stmt, NULL);
    if (err != SQLITE_OK)
      return {};

    err = sqlite3_bind_int(stmt, 1, task_status);
    if (err != SQLITE_OK)
      return {};

    vector<Task> output;
    while ((err = sqlite3_step(stmt)) == SQLITE_ROW)
    {
      int task_id = sqlite3_column_int(stmt, 0);
      const unsigned char *db_task_description = sqlite3_column_text(stmt, 1);
      int task_status = sqlite3_column_int(stmt, 2);
      const unsigned char *db_task_created_at = sqlite3_column_text(stmt, 3);
      const unsigned char *db_task_updated_at = sqlite3_column_text(stmt, 4);

      char *task_description = reinterpret_cast<char*>(const_cast<unsigned char*>(db_task_description));
      char *task_created_at = reinterpret_cast<char*>(const_cast<unsigned char*>(db_task_created_at));
      char *task_updated_at = reinterpret_cast<char*>(const_cast<unsigned char*>(db_task_updated_at));

      output.push_back(Task(task_id, task_description, TaskStatusIntToEnum(task_status), task_created_at, task_updated_at));
    }
    if (err != SQLITE_DONE)
      return {};

    err = sqlite3_finalize(stmt);
    if (err != SQLITE_OK)
      return {};

    return output;
  }

  int DeleteTask(int task_id)
  {
    sqlite3_stmt *stmt;
    char sql[] = "DELETE FROM tasks WHERE task_id = ?;";

    int err = sqlite3_prepare_v2(m_db, sql, -1, &stmt, NULL);
    if (err != SQLITE_OK)
      return -1;

    err = sqlite3_bind_int(stmt, 1, task_id);
    if (err != SQLITE_OK)
      return -1;

    err = sqlite3_step(stmt);
    if (err != SQLITE_DONE)
      return -1;

    err = sqlite3_finalize(stmt);
    if (err != SQLITE_OK)
      return -1;

    return task_id;
  }
};

SQLite *SQLite::m_instance = nullptr;