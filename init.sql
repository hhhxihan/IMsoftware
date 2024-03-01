
-- database:IM
USE IM;
DROP TABLE IF exists user;

CREATE TABLE user(
    _id int(9) ZEROFILL AUTO_INCREMENT PRIMARY KEY,
    _username varchar(32) NOT NULL,
    _password varchar(32) NOT NULL,
    _state int
 ) AUTO_INCREMENT = 100000000;

DROP TABLE IF exists offlinemsg;

CREATE TABLE offlinemsg(
    _id int(9) AUTO_INCREMENT PRIMARY KEY,
    _fromid int(9) NOT NULL,
    _toid int(9) NOT NULL,
    _type int NOT NULL,
    _msg varchar(1024)
);

DROP TABLE IF EXISTS friend;

CREATE TABLE friend(
    _id int(9) AUTO_INCREMENT PRIMARY KEY,
    _userid int(9) NOT NULL,
    _friendid int(9) NOT NULL,
    _state int
);