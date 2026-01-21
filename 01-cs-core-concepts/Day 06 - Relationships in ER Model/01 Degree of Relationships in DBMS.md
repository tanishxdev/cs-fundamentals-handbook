# Day 6 – Relationships in ER Model

---

## Article 1: Degree of Relationships in DBMS

### **1. Overview**

In a database, entities interact with one another through relationships. The **degree of a relationship** defines the number of entity types involved in that relationship. Understanding relationship degrees is essential for designing accurate ER diagrams and converting them into relational tables.

---

### **2. Types of Relationship Degrees**

#### **Unary (Degree 1)**

* Involves **one entity set** interacting with itself.
* Also called a **recursive relationship**.

**Example:**

* Class monitors are also students. The relationship “is a monitor of” involves only the `Student` entity.

**Representation:** Only one entity set participates.

![](https://media.geeksforgeeks.org/wp-content/uploads/20231030173427/unary.jpg)

---

#### **Binary (Degree 2)**

* Involves **two entity sets**.
* Most common relationship type; easy to convert into relational tables.

**Examples:**

1. `Student` and `ID` – each student has one ID.
2. `Father` and `Daughter` – one father can have many daughters; each daughter belongs to only one father (one-to-many relationship).

**Representation:** Two entities connected via a relationship.

![](https://media.geeksforgeeks.org/wp-content/uploads/20231030173529/binary.jpg)
---

#### **Ternary (Degree 3)**

* Involves **three entity sets**.
* More complex to convert into relational tables than binary relationships.

**Example:**

* Entities: `Teacher`, `Course`, `Class`
* Relationship: A teacher teaches a particular course in a particular class.

**Representation:** Three entities connected via a single relationship.

![](https://media.geeksforgeeks.org/wp-content/uploads/20231030173612/tarnary.jpg)
---

#### **N-ary (Degree n)**

* Involves **n entity sets**.
* Rarely used due to complexity in converting into relational tables.

**Example:**

* Entities: `Teacher`, `Class`, `Location`, `Salary`, `Course`
* Relationship: All five entities are associated in one complex relationship.

**Representation:** n entities connected in a single relationship.

![](https://media.geeksforgeeks.org/wp-content/uploads/20231030173925/nary.jpg)
---

### **3. Summary**

* The **degree of relationship** reflects the complexity of interactions between entities.
* **Unary and binary relationships** are common and simpler to implement.
* **Ternary and n-ary relationships** are used for complex scenarios requiring multiple entity associations.
* Choosing the right degree depends on the **specific data requirements and application needs**.
