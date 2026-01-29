# **Database Management System (DBMS) Interview Questions Sheet**

---

## **I. DATABASE FUNDAMENTALS**

### **1. Basic Concepts**

1. What is Data? Differentiate between data and information.
2. What is a Database? Explain with real-world examples.
3. What is a Database Management System (DBMS)? What are its main objectives?
4. What are the advantages of DBMS over traditional file-based systems?
5. What are the disadvantages of DBMS?
6. Differentiate between DBMS and RDBMS.
7. What is a Database System? Explain its components.
8. What are the different types of DBMS? (Hierarchical, Network, Relational, Object-oriented, NoSQL)
9. What is a database schema? Differentiate between schema and instance.
10. Explain the terms: intension and extension of a database.

### **2. Database Architecture**

11. What is data abstraction in DBMS? Explain the three levels of data abstraction.
12. Explain the three-schema architecture of DBMS.
13. What is data independence? Explain logical and physical data independence.
14. Differentiate between 2-tier and 3-tier architecture in DBMS.
15. What is a database instance? How does it differ from database schema?
16. What is a data dictionary? What information does it contain?

---

## **II. DATA MODELS**

### **3. Entity-Relationship Model**

17. What is an Entity-Relationship (E-R) Model?
18. Explain the following terms with examples:

- Entity
- Entity Type
- Entity Set
- Attributes (Simple, Composite, Derived, Single-valued, Multi-valued)
- Relationships

19. What is a weak entity? Explain with example.
20. What are participation constraints? (Total vs Partial participation)
21. What are cardinality constraints? (1:1, 1:N, M:N)
22. What are the different symbols used in ER diagrams?
23. What is generalization and specialization in ER model?
24. What is aggregation in ER model?
25. What is an Extended ER Model (EER)?

### **4. Relational Model**

26. What is a Relational Model? Explain its basic structure.
27. What is a relation? Differentiate between relation and relationship.
28. Explain the terms: tuple, attribute, domain, degree, cardinality.
29. What is a relational schema?
30. What are relational algebra operations? (Select, Project, Union, Set Difference, Cartesian Product, Rename)
31. What are additional relational algebra operations? (Join, Division)
32. What is relational calculus? Differentiate between tuple and domain relational calculus.

---

## **III. DATABASE DESIGN**

### **5. Keys in DBMS**

33. What is a Super Key?
34. What is a Candidate Key?
35. What is a Primary Key? What are its properties?
36. What is an Alternate Key?
37. What is a Foreign Key? How does it maintain referential integrity?
38. What is a Composite Key?
39. What is a Unique Key? Differentiate between Primary Key and Unique Key.
40. What is a Surrogate Key? When is it used?
41. What is a Natural Key?

### **6. Functional Dependencies**

42. What is Functional Dependency? Explain with examples.
43. What are Armstrong's Axioms? (Reflexivity, Augmentation, Transitivity)
44. What is closure of a set of functional dependencies?
45. What is a minimal cover/canonical cover?
46. What is normalization? Why is it important?

### **7. Normalization**

47. What is 1NF (First Normal Form)? Explain with example.
48. What is 2NF (Second Normal Form)? Explain with example.
49. What is 3NF (Third Normal Form)? Explain with example.
50. What is BCNF (Boyce-Codd Normal Form)? Explain with example.
51. What is 4NF (Fourth Normal Form)? Explain with multi-valued dependencies.
52. What is 5NF (Fifth Normal Form)? Explain with join dependencies.
53. What is denormalization? When and why is it used?
54. Differentiate between normalization and denormalization.
55. What are anomalies in database? (Insertion, Update, Deletion)

---

## **IV. STRUCTURED QUERY LANGUAGE (SQL)**

### **8. SQL Basics**

56. What is SQL? What are its characteristics?
57. Differentiate between SQL and NoSQL databases.
58. What are the different categories of SQL commands?
59. What is DDL (Data Definition Language)? Give examples.
60. What is DML (Data Manipulation Language)? Give examples.
61. What is DCL (Data Control Language)? Give examples.
62. What is TCL (Transaction Control Language)? Give examples.

### **9. SQL Operations**

63. Explain the SELECT statement with its clauses.
64. What is WHERE clause? What operators can be used with it?
65. What is ORDER BY clause?
66. What is GROUP BY clause? Explain with HAVING clause.
67. What are aggregate functions? (COUNT, SUM, AVG, MAX, MIN)
68. What are scalar functions? Give examples.
69. Differentiate between DELETE, TRUNCATE, and DROP commands.
70. What is ALTER command? What operations can be performed using it?
71. What is UPDATE command? How is it different from ALTER?

### **10. SQL Joins**

72. What is JOIN in SQL? Why is it used?
73. Explain different types of JOINS:

- INNER JOIN
- LEFT JOIN (LEFT OUTER JOIN)
- RIGHT JOIN (RIGHT OUTER JOIN)
- FULL JOIN (FULL OUTER JOIN)
- CROSS JOIN (Cartesian Product)
- SELF JOIN
- NATURAL JOIN
- EQUI JOIN

74. What is the difference between INNER JOIN and OUTER JOIN?
75. What is the difference between LEFT JOIN and RIGHT JOIN?

### **11. Advanced SQL**

76. What are subqueries/nested queries? Explain with types.
77. What are correlated subqueries?
78. What is a view? What are its advantages and disadvantages?
79. What is materialized view? How is it different from view?
80. What are indexes? Why are they used?
81. What are stored procedures? What are their advantages?
82. What are functions in SQL? Differentiate between stored procedure and function.
83. What are triggers? What are their types? (BEFORE, AFTER, INSTEAD OF)
84. What is a cursor? Why is it used?
85. What is the difference between UNION and UNION ALL?
86. What is the difference between INTERSECT and EXCEPT/MINUS?
87. What is the WITH CHECK OPTION in views?
88. What are transactions in SQL?

---

## **V. TRANSACTION MANAGEMENT**

### **12. Transactions**

89. What is a transaction? Give real-world examples.
90. What are ACID properties? Explain each with examples.

- Atomicity
- Consistency
- Isolation
- Durability

91. What is transaction state? Explain different states.
92. What is a schedule? What are serial and concurrent schedules?
93. What is serializability? Why is it important?
94. What is conflict serializability?
95. What is view serializability?
96. What are precedence graphs?

### **13. Concurrency Control**

97. What is concurrency control? Why is it needed?
98. What are concurrency problems? (Lost Update, Dirty Read, Non-repeatable Read, Phantom Read)
99. What are locks? Explain different types of locks.

- Shared Lock (Read Lock)
- Exclusive Lock (Write Lock)
- Intention Locks

100. What is two-phase locking (2PL)? Explain its phases.
101. What is strict two-phase locking?
102. What is timestamp-based protocol?
103. What is multiversion concurrency control (MVCC)?
104. What is optimistic concurrency control?
105. What are isolation levels? Explain each:

- Read Uncommitted
- Read Committed
- Repeatable Read
- Serializable

106. What is deadlock? How does it occur?
107. What are deadlock prevention techniques?
108. What are deadlock detection and recovery techniques?
109. What is wait-die and wound-wait scheme?
110. What is the Banker's Algorithm?

### **14. Recovery System**

111. What is a log-based recovery?
112. What is write-ahead logging (WAL)?
113. What are checkpoints? Why are they used?
114. What is deferred update protocol?
115. What is immediate update protocol?
116. What is shadow paging?

---

## **VI. ADVANCED DATABASE CONCEPTS**

### **15. Indexing**

117. What is indexing? Why is it important?
118. What are the types of indexes?

- Clustered Index
- Non-clustered Index
- Unique Index
- Composite Index
- Covering Index
- Bitmap Index
- Hash Index

119. Differentiate between clustered and non-clustered index.
120. What is B-tree? Explain its structure.
121. What is B+ tree? How is it different from B-tree?
122. What is the difference between primary index and secondary index?
123. What is dense index and sparse index?
124. What is multi-level indexing?

### **16. File Organization**

125. What are different file organization methods?

- Sequential File Organization
- Heap/Pile File Organization
- Hash File Organization
- B+ Tree File Organization
- Indexed Sequential Access Method (ISAM)

126. What is hashing? Explain different hashing techniques.
127. What is static hashing?
128. What is dynamic hashing? (Extendible, Linear)
129. What are collisions in hashing? How are they resolved?

### **17. Query Processing and Optimization**

130. What is query processing?
131. Explain the steps in query processing.
132. What is query optimization? Why is it important?
133. What are query optimization techniques?
134. What is cost-based optimization?
135. What is heuristic optimization?
136. What is a query execution plan?
137. What are selection operations? (Linear search, Binary search, Using index)
138. What are join operations? (Nested loop, Block nested loop, Indexed nested loop, Merge join, Hash join)

### **18. Distributed Databases**

139. What is a distributed database?
140. What are the advantages and disadvantages of distributed databases?
141. What is data fragmentation? (Horizontal, Vertical, Hybrid)
142. What is data replication?
143. What is distributed transaction management?
144. What is two-phase commit protocol (2PC)?
145. What is three-phase commit protocol (3PC)?

### **19. NoSQL Databases**

146. What is NoSQL? When is it used?
147. What are the types of NoSQL databases?

- Document-based (MongoDB)
- Key-value store (Redis)
- Column-based (Cassandra)
- Graph-based (Neo4j)

148. Differentiate between SQL and NoSQL databases.
149. What is CAP theorem? Explain Consistency, Availability, Partition Tolerance.
150. What is BASE property? (Basically Available, Soft state, Eventually consistent)

---

## **VII. DATABASE SECURITY & ADMINISTRATION**

### **20. Database Security**

151. What is database security? Why is it important?
152. What are different types of database security threats?
153. What is authentication? What are authentication methods?
154. What is authorization? What are authorization models?
155. What is Role-Based Access Control (RBAC)?
156. What is Discretionary Access Control (DAC)?
157. What is Mandatory Access Control (MAC)?
158. What are privileges in SQL? (GRANT, REVOKE)
159. What is encryption? How is it used in databases?
160. What is data masking?
161. What is SQL injection? How to prevent it?
162. What is auditing in databases?

### **21. Database Administration**

163. What is a Database Administrator (DBA)? What are their responsibilities?
164. What are different types of DBA? (System DBA, Application DBA, etc.)
165. What is database tuning?
166. What is capacity planning?
167. What are backup and recovery strategies?
168. What are different types of backups? (Full, Differential, Incremental)
169. What is database migration?
170. What is data warehousing?
171. What is data mining?
172. What is OLAP vs OLTP?
173. What is ETL process? (Extract, Transform, Load)

---

## **VIII. SCALABILITY & PERFORMANCE**

### **22. Scaling Techniques**

174. What is vertical scaling? What are its advantages and disadvantages?
175. What is horizontal scaling? What are its advantages and disadvantages?
176. What is sharding? How does it work?
177. What is replication? What are its types? (Master-slave, Master-master)
178. What is load balancing in databases?
179. What is caching? How does it improve performance?
180. What is database partitioning? (Range, Hash, List)
181. What is connection pooling?

### **23. Performance Optimization**

182. How do you optimize SQL queries?
183. What are query execution plans? How to read them?
184. What is database indexing strategy?
185. How to handle slow queries?
186. What is database monitoring?
187. What are performance counters in databases?
188. What is database profiling?

---

## **IX. REAL-WORLD SCENARIOS**

### **24. Design Questions**

189. Design a database for an e-commerce website.
190. Design a database for a social media platform.
191. Design a database for a hospital management system.
192. Design a database for a library management system.
193. Design a database for a university management system.
194. How would you design a database for high-read vs high-write applications?
195. How would you design a database for real-time applications?

### **25. Problem-Solving Questions**

196. How would you handle a database that has grown too large?
197. How would you improve database performance under heavy load?
198. How would you migrate data from one database to another?
199. How would you handle database corruption?
200. How would you design a disaster recovery plan?

---

## **X. COMPARISON QUESTIONS**

1. **DBMS vs RDBMS**
2. **SQL vs NoSQL**
3. **Primary Key vs Unique Key**
4. **Clustered Index vs Non-clustered Index**
5. **DELETE vs TRUNCATE vs DROP**
6. **WHERE vs HAVING**
7. **INNER JOIN vs OUTER JOIN**
8. **UNION vs UNION ALL**
9. **Stored Procedure vs Function**
10. **View vs Materialized View**
11. **Vertical Scaling vs Horizontal Scaling**
12. **Normalization vs Denormalization**
13. **OLTP vs OLAP**
14. **2-tier vs 3-tier Architecture**
15. **Shared Lock vs Exclusive Lock**

---

> Total Questions: 200+ (covering all aspects of DBMS)
