CREATE TABLE IF NOT EXISTS main.users (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  username TEXT,
  password TEXT,
  admin INTEGER
);

CREATE TABLE IF NOT EXISTS main.transactions (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  trans_date TEXT
);

CREATE TABLE IF NOT EXISTS main.suppliers (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  name TEXT,
  profit REAL,
  expenditure REAL,
  last_transaction INTEGER,
  FOREIGN KEY (last_transaction) REFERENCES transactions(id)
);

