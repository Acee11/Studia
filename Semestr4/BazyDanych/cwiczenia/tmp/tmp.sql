DROP DATABASE IF EXISTS test_db;

CREATE DATABASE test_db
	OWNER wb
	ENCODING 'Unicode';

\c test_db

CREATE TABLE Bombiarze (
	id SERIAL PRIMARY KEY,
	stopien int
);

CREATE TABLE Agenci (
	id SERIAL PRIMARY KEY,
	bombiarz int
);

INSERT INTO Bombiarze(id, stopien) VALUES (DEFAULT, 1);
INSERT INTO Bombiarze(id, stopien) VALUES (DEFAULT, 2);
INSERT INTO Bombiarze(id, stopien) VALUES (DEFAULT, 3);
INSERT INTO Bombiarze(id, stopien) VALUES (DEFAULT, 4);
INSERT INTO Bombiarze(id, stopien) VALUES (DEFAULT, 5);
INSERT INTO Bombiarze(id, stopien) VALUES (DEFAULT, 7);
INSERT INTO Bombiarze(id, stopien) VALUES (DEFAULT, 7);

INSERT INTO Agenci(id, bombiarz) VALUES (DEFAULT, NULL);
INSERT INTO Agenci(id, bombiarz) VALUES (DEFAULT, 1);
INSERT INTO Agenci(id, bombiarz) VALUES (DEFAULT, 2);
INSERT INTO Agenci(id, bombiarz) VALUES (DEFAULT, 3);
INSERT INTO Agenci(id, bombiarz) VALUES (DEFAULT, NULL);