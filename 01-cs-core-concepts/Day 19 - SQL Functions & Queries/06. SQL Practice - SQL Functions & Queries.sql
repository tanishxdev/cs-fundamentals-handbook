-- ======================================================
-- SQL PRACTICE
-- Topics: Operators, Aggregate Functions, GROUP BY, HAVING, Subqueries/Nested Queries
-- Author: Tanish Kumar
-- ======================================================

-- ==========================
-- 1. CREATE TABLES
-- ==========================

-- Student Table
CREATE TABLE STUDENT (
    S_ID VARCHAR(5) PRIMARY KEY,
    S_NAME VARCHAR(50),
    S_ADDRESS VARCHAR(50),
    S_PHONE BIGINT,
    S_AGE INT
);

-- Course Table
CREATE TABLE COURSE (
    C_ID VARCHAR(5) PRIMARY KEY,
    C_NAME VARCHAR(50)
);

-- Student_Course Table (Many-to-Many relationship)
CREATE TABLE STUDENT_COURSE (
    S_ID VARCHAR(5),
    C_ID VARCHAR(5),
    PRIMARY KEY(S_ID, C_ID),
    FOREIGN KEY (S_ID) REFERENCES STUDENT(S_ID),
    FOREIGN KEY (C_ID) REFERENCES COURSE(C_ID)
);

-- Employee Table (For Aggregates, GROUP BY, HAVING)
CREATE TABLE EMP (
    EMP_NO INT PRIMARY KEY,
    NAME VARCHAR(50),
    SAL DECIMAL(10,2),
    AGE INT
);

-- ==========================
-- 2. INSERT SAMPLE DATA
-- ==========================

-- STUDENT data
INSERT INTO STUDENT VALUES
('S1','RAM','DELHI',9455123451,18),
('S2','RAMESH','GURGAON',9652431543,18),
('S3','SUJIT','ROHTAK',9156253131,20),
('S4','SURESH','DELHI',9156768971,18);

-- COURSE data
INSERT INTO COURSE VALUES
('C1','DSA'),
('C2','Programming'),
('C3','DBMS');

-- STUDENT_COURSE data
INSERT INTO STUDENT_COURSE VALUES
('S1','C1'),
('S1','C3'),
('S2','C1'),
('S3','C2'),
('S4','C2'),
('S4','C3');

-- EMPLOYEE data
INSERT INTO EMP VALUES
(1, 'Liam', 50000.00, 25),
(2, 'Emma', 60000.50, 30),
(3, 'Noah', 75000.75, 35),
(4, 'Olivia', 45000.25, 28),
(5, 'Ethan', 80000.00, 32),
(6, 'Sophia', 65000.00, 27),
(7, 'Mason', 55000.50, 29),
(8, 'Isabella', 72000.75, 31),
(9, 'Logan', 48000.25, 26),
(10, 'Mia', 83000.00, 33);

-- ==========================
-- 3. SQL QUERIES FOR PRACTICE
-- ==========================

-- 3a. Operators
-- Select students older than 18
SELECT * FROM STUDENT WHERE S_AGE > 18;

-- Select students from DELHI or GURGAON
SELECT * FROM STUDENT WHERE S_ADDRESS IN ('DELHI','GURGAON');

-- ==========================
-- 3b. Aggregate Functions
-- ==========================

-- Count total employees
SELECT COUNT(*) AS TotalEmployees FROM EMP;

-- Sum of salaries
SELECT SUM(SAL) AS TotalSalary FROM EMP;

-- Average salary
SELECT AVG(SAL) AS AvgSalary FROM EMP;

-- Minimum and Maximum salary
SELECT MIN(SAL) AS MinSalary, MAX(SAL) AS MaxSalary FROM EMP;

-- ==========================
-- 3c. GROUP BY & HAVING
-- ==========================

-- Count employees by age
SELECT AGE, COUNT(*) AS CountByAge
FROM EMP
GROUP BY AGE;

-- Employees with total salary greater than 60000
SELECT NAME, SUM(SAL) AS TotalSalary
FROM EMP
GROUP BY NAME
HAVING SUM(SAL) > 60000;

-- Average salary by age, filter > 60000
SELECT AGE, AVG(SAL) AS AvgSalary
FROM EMP
GROUP BY AGE
HAVING AVG(SAL) > 60000;

-- ==========================
-- 3d. Subqueries / Nested Queries
-- ==========================

-- Independent Nested Query: Students enrolled in DSA or DBMS
SELECT S_ID 
FROM STUDENT_COURSE 
WHERE C_ID IN (
    SELECT C_ID FROM COURSE WHERE C_NAME IN ('DSA','DBMS')
);

-- Correlated Nested Query: Students enrolled in course C1
SELECT S_NAME 
FROM STUDENT S
WHERE EXISTS (
    SELECT 1 
    FROM STUDENT_COURSE SC
    WHERE S.S_ID = SC.S_ID AND SC.C_ID = 'C1'
);

-- Nested query with IN: Student names enrolled in DSA or DBMS
SELECT S_NAME 
FROM STUDENT
WHERE S_ID IN (
    SELECT S_ID 
    FROM STUDENT_COURSE
    WHERE C_ID IN (
        SELECT C_ID FROM COURSE WHERE C_NAME IN ('DSA','DBMS')
    )
);

-- Nested query with NOT IN: Students NOT enrolled in DSA or DBMS
SELECT S_ID 
FROM STUDENT
WHERE S_ID NOT IN (
    SELECT S_ID 
    FROM STUDENT_COURSE
    WHERE C_ID IN (
        SELECT C_ID FROM COURSE WHERE C_NAME IN ('DSA','DBMS')
    )
);

-- Nested query with ANY: Students older than ANY student in DELHI
SELECT S_NAME 
FROM STUDENT
WHERE S_AGE > ANY (
    SELECT S_AGE FROM STUDENT WHERE S_ADDRESS='DELHI'
);

-- Nested query with ALL: Students older than ALL students in DELHI
SELECT S_NAME 
FROM STUDENT
WHERE S_AGE > ALL (
    SELECT S_AGE FROM STUDENT WHERE S_ADDRESS='DELHI'
);

-- Nested query in FROM clause: Derived table
SELECT S_NAME, S_PHONE
FROM (
    SELECT S_NAME, S_PHONE, S_ADDRESS
    FROM STUDENT
    WHERE S_ADDRESS LIKE 'D%'
) AS subquery_table;

-- Nested query with JOIN
SELECT S.S_NAME, S.S_ADDRESS, SC.C_ID
FROM STUDENT S
INNER JOIN (
    SELECT S_ID, C_ID 
    FROM STUDENT_COURSE 
    WHERE C_ID='C1'
) SC
ON S.S_ID = SC.S_ID;

-- ======================================================
-- ✅ What this file includes:

-- Tables: STUDENT, COURSE, STUDENT_COURSE, EMP.

-- Sample Data: Enough rows for practicing all queries.

-- Queries:

-- Operators (WHERE, IN)

-- Aggregate Functions (COUNT, SUM, AVG, MIN, MAX)

-- GROUP BY & HAVING

-- Subqueries / Nested Queries (IN, NOT IN, ANY, ALL, EXISTS, Derived tables, JOINs)
-- ======================================================
