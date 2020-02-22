SET DEFINE OFF;

--Delete preexisting tables 
DROP TABLE boats cascade constraints;
DROP TABLE reserves cascade constraints;
DROP TABLE sailors cascade constraints;

--remove any ghost tables
PURGE RECYCLEBIN;

--create tables
CREATE TABLE boats(  bid	integer,
					 bname	char(20),
				     color	char(20),
				     PRIMARY KEY (bid));
						
CREATE TABLE sailors(	sid	integer,
						sname	char(30),
						rating	number,
						age	number,
						PRIMARY KEY (sid));
						
CREATE TABLE reserves(	sid	integer,
						bid	integer,
						day	date,
						PRIMARY KEY (sid,bid,day),
						CONSTRAINT FK_BID_RES FOREIGN KEY (bid) REFERENCES boats(bid),
						CONSTRAINT FK_SID_RES FOREIGN KEY (sid) REFERENCES sailors(sid));
						
						
--insert data into tables
--boats
INSERT INTO boats VALUES (101,	'Interlake', 'blue');
INSERT INTO boats VALUES (102,	'Interlake', 'red');
INSERT INTO boats VALUES (103,	'Clipper', 'green');
INSERT INTO boats VALUES (104,	'Marine', 'red');
commit;

--sailors
INSERT INTO sailors VALUES (22,	'Dustin', 7, '45.0');
INSERT INTO sailors VALUES (29,	'Brutus', 1, '33.0');
INSERT INTO sailors VALUES (31,	'Lubber', 8, '55.5');
INSERT INTO sailors VALUES (32,	'Andy', 8, '25.5');
INSERT INTO sailors VALUES (58,	'Rusty', 10, '35.0');
INSERT INTO sailors VALUES (64,	'Horatio', 7, '35.0');
INSERT INTO sailors VALUES (71,	'Zorba', 10, '16.0');
INSERT INTO sailors VALUES (74,	'Horatio', 9, '35.0');
INSERT INTO sailors VALUES (85,	'Art', 3, '25.5');
INSERT INTO sailors VALUES (95,	'Bob', 3, '63.5');
commit;

--reserves
INSERT INTO reserves VALUES (22, 101, TO_DATE('1998-10-10','YYYY-MM-DD'));
INSERT INTO reserves VALUES (22, 102, TO_DATE('1998-10-10','YYYY-MM-DD'));
INSERT INTO reserves VALUES (22, 103, TO_DATE('1998-10-08','YYYY-MM-DD'));
INSERT INTO reserves VALUES (22, 104, TO_DATE('1998-10-07','YYYY-MM-DD'));
INSERT INTO reserves VALUES (31, 102, TO_DATE('1998-11-10','YYYY-MM-DD'));
INSERT INTO reserves VALUES (31, 103, TO_DATE('1998-11-06','YYYY-MM-DD'));
INSERT INTO reserves VALUES (31, 104, TO_DATE('1998-11-12','YYYY-MM-DD'));
INSERT INTO reserves VALUES (64, 101, TO_DATE('1998-09-05','YYYY-MM-DD'));
INSERT INTO reserves VALUES (64, 102, TO_DATE('1998-09-08','YYYY-MM-DD'));
INSERT INTO reserves VALUES (74, 103, TO_DATE('1998-09-08','YYYY-MM-DD'));
commit;