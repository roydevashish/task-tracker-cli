CREATE TABLE IF NOT EXISTS tasks (
  task_id integer primary key autoincrement,
  task_description text not null,
  task_status numeric not null default 0,
  task_created_at datetime default (datetime('now', 'localtime')),
  task_updated_at datetime default (datetime('now', 'localtime'))
);

CREATE TRIGGER IF NOT EXISTS update_tasks_task_updated_at 
AFTER UPDATE ON tasks
FOR EACH ROW
BEGIN
    UPDATE tasks 
    SET task_updated_at = datetime('now', 'localtime') 
    WHERE task_id = OLD.task_id;
END;

SELECT * FROM tasks;