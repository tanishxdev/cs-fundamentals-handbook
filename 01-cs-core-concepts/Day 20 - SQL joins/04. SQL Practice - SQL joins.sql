-- ============================================
-- SQL Practice
-- Topics: Operators, Aggregate Functions, GROUP BY, HAVING, Subqueries, Joins, Self Join, Natural Join
-- ============================================

-- ================================
-- 1. Create Database
-- ================================
CREATE DATABASE IF NOT EXISTS geeks;
USE geeks;

-- ================================
-- 2. Tables for Operators/Subqueries
-- ================================
CREATE TABLE IF NOT EXISTS STUDENT (
    S_ID VARCHAR(5) PRIMARY KEY,
    S_NAME VARCHAR(50),
    S_ADDRESS VARCHAR(50),
    S_PHONE VARCHAR(15),
    S_AGE INT
);

CREATE TABLE IF NOT EXISTS COURSE (
    C_ID VARCHAR(5) PRIMARY KEY,
    C_NAME VARCHAR(50)
);

CREATE TABLE IF NOT EXISTS STUDENT_COURSE (
    S_ID VARCHAR(5),
    C_ID VARCHAR(5),
    FOREIGN KEY (S_ID) REFERENCES STUDENT(S_ID),
    FOREIGN KEY (C_ID) REFERENCES COURSE(C_ID)
);

-- ================================
-- 3. Insert Sample Data
-- ================================
INSERT INTO STUDENT VALUES
('S1','RAM','DELHI','9455123451',18),
('S2','RAMESH','GURGAON','9652431543',18),
('S3','SUJIT','ROHTAK','9156253131',20),
('S4','SURESH','DELHI','9156768971',18);

INSERT INTO COURSE VALUES
('C1','DSA'),
('C2','Programming'),
('C3','DBMS');

INSERT INTO STUDENT_COURSE VALUES
('S1','C1'),
('S1','C3'),
('S2','C1'),
('S3','C2'),
('S4','C2'),
('S4','C3');

-- ================================
-- 4. Queries: Subqueries / Operators
-- ================================
-- Students enrolled in DSA or DBMS
SELECT S_NAME FROM STUDENT
WHERE S_ID IN (
    SELECT S_ID FROM STUDENT_COURSE
    WHERE C_ID IN (
        SELECT C_ID FROM COURSE WHERE C_NAME IN ('DSA','DBMS')
    )
);

-- Students NOT enrolled in DSA or DBMS
SELECT S_ID FROM STUDENT
WHERE S_ID NOT IN (
    SELECT S_ID FROM STUDENT_COURSE
    WHERE C_ID IN (
        SELECT C_ID FROM COURSE WHERE C_NAME IN ('DSA','DBMS')
    )
);

-- Age comparisons
SELECT S_NAME FROM STUDENT
WHERE S_AGE > ANY (
    SELECT S_AGE FROM STUDENT WHERE S_ADDRESS='DELHI'
);

SELECT S_NAME FROM STUDENT
WHERE S_AGE > ALL (
    SELECT S_AGE FROM STUDENT WHERE S_ADDRESS='DELHI'
);

-- ================================
-- 5. Tables for Joins
-- ================================
CREATE TABLE IF NOT EXISTS StudentJoin (
    ROLL_NO INT PRIMARY KEY,
    NAME VARCHAR(50),
    ADDRESS VARCHAR(50),
    PHONE VARCHAR(15),
    AGE INT
);

CREATE TABLE IF NOT EXISTS StudentCourseJoin (
    COURSE_ID INT,
    ROLL_NO INT
);

INSERT INTO StudentJoin VALUES
(1,'HARSH','DELHI','XXXXXXXXXX',18),
(2,'PRATIK','BIHAR','XXXXXXXXXX',19),
(3,'RIYANKA','SILIGURI','XXXXXXXXXX',20),
(4,'DEEP','RAMNAGAR','XXXXXXXXXX',18);

INSERT INTO StudentCourseJoin VALUES
(1,1),
(2,2),
(2,3),
(3,4);

-- ================================
-- 6. Queries: Joins
-- ================================
-- INNER JOIN
SELECT StudentCourseJoin.COURSE_ID, StudentJoin.NAME, StudentJoin.AGE
FROM StudentJoin
INNER JOIN StudentCourseJoin
ON StudentJoin.ROLL_NO = StudentCourseJoin.ROLL_NO;

-- LEFT JOIN
SELECT StudentJoin.NAME, StudentCourseJoin.COURSE_ID
FROM StudentJoin
LEFT JOIN StudentCourseJoin
ON StudentCourseJoin.ROLL_NO = StudentJoin.ROLL_NO;

-- RIGHT JOIN
SELECT StudentJoin.NAME, StudentCourseJoin.COURSE_ID
FROM StudentJoin
RIGHT JOIN StudentCourseJoin
ON StudentCourseJoin.ROLL_NO = StudentJoin.ROLL_NO;

-- FULL JOIN (MySQL does not support FULL JOIN directly, use UNION)
SELECT StudentJoin.NAME, StudentCourseJoin.COURSE_ID
FROM StudentJoin
LEFT JOIN StudentCourseJoin
ON StudentJoin.ROLL_NO = StudentCourseJoin.ROLL_NO
UNION
SELECT StudentJoin.NAME, StudentCourseJoin.COURSE_ID
FROM StudentJoin
RIGHT JOIN StudentCourseJoin
ON StudentJoin.ROLL_NO = StudentCourseJoin.ROLL_NO;

-- ================================
-- 7. Table for Self Join
-- ================================
CREATE TABLE IF NOT EXISTS GFGemployees (
    employee_id INT PRIMARY KEY, 
    employee_name VARCHAR(50), 
    manager_id INT
);

INSERT INTO GFGemployees VALUES
(1,'Zaid',3),
(2,'Rahul',3),
(3,'Raman',4),
(4,'Kamran',NULL),
(5,'Farhan',4);

-- Self Join: Employee and Manager
SELECT e.employee_name AS employee, m.employee_name AS manager
FROM GFGemployees AS e
JOIN GFGemployees AS m
ON e.manager_id = m.employee_id;

-- ================================
-- 8. Tables for Natural Join
-- ================================
CREATE TABLE IF NOT EXISTS department (
   DEPT_NAME VARCHAR(20),
   MANAGER_NAME VARCHAR(255)
);

CREATE TABLE IF NOT EXISTS employee (
   EMP_ID INT,
   EMP_NAME VARCHAR(20),
   DEPT_NAME VARCHAR(255)
);

INSERT INTO department VALUES
('IT','ROHAN'),
('SALES','RAHUL'),
('HR','TANMAY'),
('FINANCE','ASHISH'),
('MARKETING','SAMAY');

INSERT INTO employee VALUES
(1,'SUMIT','HR'),
(2,'JOEL','IT'),
(3,'BISWA','MARKETING'),
(4,'VAIBHAV','IT'),
(5,'SAGAR','SALES');

-- Natural Join
SELECT *
FROM employee
NATURAL JOIN department;
