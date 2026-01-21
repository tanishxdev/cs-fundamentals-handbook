-- ============================================
-- SQL Practice
-- Topics: SQL Views, Indexes, Cursors, Triggers
-- ============================================

-- ============================================
-- 1. SQL VIEWS
-- ============================================

-- Create table
CREATE TABLE Students (
    student_id INT PRIMARY KEY,
    name VARCHAR(50),
    grade INT,
    class VARCHAR(10)
);

-- Insert sample data
INSERT INTO Students (student_id, name, grade, class) VALUES
(1, 'Alice', 85, 'A'),
(2, 'Bob', 90, 'B'),
(3, 'Charlie', 78, 'A'),
(4, 'David', 88, 'B');

-- Create a simple view for students in class A
CREATE VIEW ClassA_Students AS
SELECT student_id, name, grade
FROM Students
WHERE class = 'A';

-- Query the view
SELECT * FROM ClassA_Students;

-- Drop the view
-- DROP VIEW ClassA_Students;

-- ============================================
-- 2. SQL INDEXES
-- ============================================

-- Single Column Index
CREATE INDEX idx_grade ON Students(grade);

-- Multi-Column Index
CREATE INDEX idx_class_grade ON Students(class, grade);

-- Unique Index
CREATE UNIQUE INDEX idx_unique_student_name ON Students(name);

-- Drop an index
-- DROP INDEX idx_class_grade;

-- Show indexes (MySQL example)
-- SHOW INDEXES FROM Students;

-- ============================================
-- 3. SQL CURSORS
-- ============================================

-- Explicit Cursor Example (T-SQL)
-- Make sure to run in SQL Server
DECLARE @StudentName VARCHAR(50), @StudentGrade INT;

DECLARE student_cursor CURSOR FOR
SELECT name, grade FROM Students;

OPEN student_cursor;

FETCH NEXT FROM student_cursor INTO @StudentName, @StudentGrade;
WHILE @@FETCH_STATUS = 0
BEGIN
    PRINT 'Student: ' + @StudentName + ', Grade: ' + CAST(@StudentGrade AS VARCHAR);
    FETCH NEXT FROM student_cursor INTO @StudentName, @StudentGrade;
END

CLOSE student_cursor;
DEALLOCATE student_cursor;

-- Implicit Cursor Example (PL/SQL)
-- BEGIN
--   FOR stu_rec IN (SELECT * FROM Students) LOOP
--       DBMS_OUTPUT.PUT_LINE('Student: ' || stu_rec.name || ', Grade: ' || stu_rec.grade);
--   END LOOP;
-- END;
-- /

-- ============================================
-- 4. SQL TRIGGERS
-- ============================================

-- Example: BEFORE INSERT Trigger (MySQL)
-- This trigger calculates total marks before inserting
CREATE TABLE Student_Marks (
    student_id INT PRIMARY KEY,
    sub1 INT,
    sub2 INT,
    sub3 INT,
    total INT,
    percentage DECIMAL(5,2)
);

DELIMITER $$
CREATE TRIGGER calculate_total
BEFORE INSERT ON Student_Marks
FOR EACH ROW
BEGIN
    SET NEW.total = NEW.sub1 + NEW.sub2 + NEW.sub3;
    SET NEW.percentage = NEW.total / 3;
END$$
DELIMITER ;

-- Insert sample data
INSERT INTO Student_Marks (student_id, sub1, sub2, sub3) VALUES
(1, 80, 90, 85),
(2, 70, 75, 80);

-- Verify trigger execution
SELECT * FROM Student_Marks;

-- DML Trigger Example: Prevent updates on Students table
CREATE TRIGGER prevent_update
BEFORE UPDATE ON Students
FOR EACH ROW
BEGIN
    SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = 'Updates not allowed on Students table';
END;
