PRAGMA journal_mode = OFF;
PRAGMA synchronous = OFF;
PRAGMA foreign_keys = ON;

CREATE TABLE IF NOT EXISTS main.users (
  id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE NOT NULL,
  username TEXT,
  password TEXT,
  deleted INTEGER
);

CREATE TABLE IF NOT EXISTS main.transactions (
  id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE NOT NULL,
  amount REAL,
  no_sold INTEGER,
  deleted INTEGER
);

CREATE TABLE IF NOT EXISTS main.suppliers (
  id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE NOT NULL,
  name TEXT,
  deleted INTEGER
);

CREATE TABLE IF NOT EXISTS main.types (
  	id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE NOT NULL,
	ref TEXT UNIQUE NOT NULL,
	description TEXT,
  deleted INTEGER
);

create table if not exists main.stock (
  	id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE NOT NULL,
	ref TEXT UNIQUE NOT NULL,
	supplier_id INTEGER,
	type_id INTEGER,
	foreign_price REAL,
	exchange_rate REAL,
	local_price REAL,
  	deleted INTEGER,
	FOREIGN KEY (type_id) REFERENCES types(id),
	FOREIGN KEY (supplier_id) REFERENCES suppliers(id)
);

CREATE TABLE IF NOT EXISTS main.transaction_stock (
	transaction_id INTEGER,
	stock_id INTEGER,
	trans_date INTEGER,
	FOREIGN KEY (transaction_id) REFERENCES transactions(id),
	FOREIGN KEY (stock_id) REFERENCES stock(id)
);
