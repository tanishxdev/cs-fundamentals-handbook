# **Object-Oriented Programming (OOP) Interview Questions Sheet**

---

## **I. OOP FUNDAMENTALS**

### **1. Basic Concepts**

1. What is Object-Oriented Programming (OOP)? Explain with real-world examples.
2. What are the advantages of using OOP over procedural programming?
3. What are the disadvantages or limitations of OOP?
4. Differentiate between structured programming and object-oriented programming.
5. What are other programming paradigms besides OOP? (Procedural, Functional, Logical)
6. List popular OOP languages and explain their OOP support.
7. What is the difference between object-based and object-oriented programming?
8. Explain the concept of "everything is an object" in OOP.
9. What is the difference between a class and an object?
10. How does OOP support software reuse and maintenance?

### **2. Classes and Objects**

11. What is a class? Explain with example.
12. What is an object? How is it different from a class?
13. What is instantiation? How are objects created from classes?
14. What are class members? Differentiate between instance members and static members.
15. What is the memory allocation for classes and objects?
16. Can we create a program without creating objects in OOP?
17. What is a class diagram? How is it used in OOP?
18. What are the different types of classes? (Concrete, Abstract, Final, etc.)
19. What is the difference between value types and reference types?
20. What is garbage collection in OOP? How does it work?

---

## **II. FOUR PILLARS OF OOP**

### **3. Encapsulation**

21. What is encapsulation? Explain with real-world example.
22. How is encapsulation implemented in programming languages?
23. What are access modifiers/specifiers? Explain:

- Public
- Private
- Protected
- Default/Internal/Package-private

24. What are getters and setters? Why are they used?
25. What is data hiding? How does encapsulation achieve data hiding?
26. What are the benefits of encapsulation?
27. How does encapsulation differ from abstraction?
28. What is a property? How is it different from a field?
29. What are the different levels of encapsulation? (Class level, package level, etc.)
30. Can we achieve 100% encapsulation? Why or why not?

### **4. Abstraction**

31. What is abstraction? Explain with real-world example.
32. How is abstraction different from encapsulation?
33. What are the different ways to achieve abstraction?
34. What is an abstract class? When should we use it?
35. What are abstract methods? Can abstract class have concrete methods?
36. Can we create an object of an abstract class? Why or why not?
37. What is an interface? How is it different from an abstract class?
38. What are the rules for implementing interfaces?
39. Can an interface have variables? What type of variables?
40. What is multiple inheritance? How do interfaces solve the diamond problem?
41. What is the difference between abstract class and interface?
42. When to use abstract class vs interface?
43. What is a marker interface? Give examples.
44. What is a functional interface?
45. What are default methods in interfaces?
46. What are static methods in interfaces?

### **5. Inheritance**

47. What is inheritance? Explain with real-world example.
48. What are the benefits of using inheritance?
49. Explain different types of inheritance:

- Single Inheritance
- Multiple Inheritance
- Multilevel Inheritance
- Hierarchical Inheritance
- Hybrid Inheritance

50. Which languages support multiple inheritance? How is it implemented?
51. What is the diamond problem? How is it resolved?
52. What are the limitations of inheritance?
53. What is method overriding? How is it different from method overloading?
54. What are the rules for method overriding?
55. What is the `super` keyword? How is it used?
56. What is the `this` keyword? How is it used?
57. What is constructor chaining? Explain with example.
58. What is the order of constructor execution in inheritance?
59. What is composition? How is it different from inheritance?
60. When to use inheritance vs composition?
61. What is aggregation? How is it different from composition?
62. What are the different relationships in OOP? (IS-A, HAS-A, USES-A)
63. What is method hiding/shadowing?

### **6. Polymorphism**

64. What is polymorphism? Explain with real-world example.
65. What are the different types of polymorphism?
66. What is compile-time polymorphism? How is it achieved?
67. What is runtime polymorphism? How is it achieved?
68. What is method overloading? Explain with rules.
69. What is method overriding? Explain with rules.
70. Differentiate between method overloading and method overriding.
71. What is operator overloading? Which languages support it?
72. What is dynamic method dispatch?
73. What is virtual function? How does it enable polymorphism?
74. What is pure virtual function?
75. What are covariant return types?
76. What is upcasting and downcasting?
77. What is the `instanceof` operator? How is it used?
78. How does polymorphism support extensibility?

---

## **III. ADVANCED OOP CONCEPTS**

### **7. Constructors and Destructors**

79. What is a constructor? What is its purpose?
80. What are the characteristics of constructors?
81. Explain different types of constructors:

- Default Constructor
- Parameterized Constructor
- Copy Constructor
- Private Constructor
- Static Constructor

82. Can constructors be overloaded? Give example.
83. Can constructors be inherited?
84. What is constructor chaining? Explain with example.
85. What is the order of constructor execution in inheritance?
86. What is a destructor? When is it called?
87. Can destructors be overloaded?
88. What is the difference between finalize() and destructor?
89. What is object initialization order?
90. What are initializer blocks? (Static and instance)

### **8. Static Concepts**

91. What are static members? (Variables, methods, blocks)
92. What is the difference between static and instance members?
93. When to use static vs instance members?
94. Can we override static methods? Why or why not?
95. What is static binding and dynamic binding?
96. What are static classes? When are they used?
97. Can we create an object of a static class?
98. What is the memory allocation for static members?
99. What are static imports?

### **9. Advanced Inheritance Concepts**

100. What is the final keyword? How is it used with:


    - Variables
    - Methods
    - Classes

101. What is a sealed class?
102. What is a nested class? Explain types:


    - Static nested class
    - Inner class
    - Local inner class
    - Anonymous inner class

103. What are the access rules for nested classes?
104. What is a singleton class? How to implement it?
105. What is a factory class? How to implement it?
106. What is a wrapper class? Why is it used?

### **10. Exception Handling in OOP**

107. What is exception handling in OOP?
108. What is the difference between checked and unchecked exceptions?
109. What is the exception hierarchy in OOP languages?
110. How is exception handling done in constructors?
111. Can we throw exceptions from destructors?

---

## **IV. DESIGN PRINCIPLES AND PATTERNS**

### **11. SOLID Principles**

112. What are SOLID principles? Explain each:


    - S: Single Responsibility Principle (SRP)
    - O: Open/Closed Principle (OCP)
    - L: Liskov Substitution Principle (LSP)
    - I: Interface Segregation Principle (ISP)
    - D: Dependency Inversion Principle (DIP)

113. Give examples of each SOLID principle violation and fix.
114. How do SOLID principles improve code quality?

### **12. Design Patterns**

115. What are design patterns? Why are they used?
116. Explain different categories of design patterns:


    - Creational Patterns
    - Structural Patterns
    - Behavioral Patterns

117. Explain important design patterns with examples:


    - Singleton Pattern
    - Factory Pattern
    - Abstract Factory Pattern
    - Builder Pattern
    - Prototype Pattern
    - Adapter Pattern
    - Decorator Pattern
    - Observer Pattern
    - Strategy Pattern
    - Template Method Pattern

### **13. Other Principles**

118. What is DRY principle? (Don't Repeat Yourself)
119. What is KISS principle? (Keep It Simple, Stupid)
120. What is YAGNI? (You Aren't Gonna Need It)
121. What is Law of Demeter? (Principle of Least Knowledge)

---

## **V. LANGUAGE-SPECIFIC OOP CONCEPTS**

### **14. Java OOP Specific**

122. What is the Object class in Java? What methods does it provide?
123. What is the difference between == and equals() method?
124. What is hashCode() method? What is its contract with equals()?
125. What is clone() method? Explain deep vs shallow copy.
126. What are wrapper classes in Java? Explain autoboxing and unboxing.
127. What are enum types in Java?
128. What are annotations in Java?
129. What are generics in Java? How do they support type safety?
130. What is reflection in Java?

### **15. C++ OOP Specific**

131. What are friend functions and friend classes?
132. What are virtual functions and virtual destructors?
133. What are pure virtual functions and abstract classes?
134. What are templates in C++? How are they different from generics?
135. What is the difference between struct and class in C++?
136. What are namespaces in C++?
137. What is RAII (Resource Acquisition Is Initialization)?
138. What are smart pointers? Explain unique_ptr, shared_ptr, weak_ptr.

### **16. Python OOP Specific**

139. How does Python implement OOP differently?
140. What are dunder/magic methods in Python?
141. What is method resolution order (MRO) in Python?
142. What are properties and descriptors in Python?
143. What are decorators in Python? How are they used in OOP?
144. What are metaclasses in Python?

---

## **VI. MEMORY MANAGEMENT**

### **17. Object Lifecycle**

145. What is the lifecycle of an object?
146. What is object creation and initialization process?
147. What is object destruction and cleanup process?
148. What is object serialization and deserialization?
149. What is object pooling? When is it used?

### **18. Memory Models**

150. What is stack vs heap memory?
151. How are objects stored in memory?
152. What is memory fragmentation?
153. What are memory leaks? How to prevent them?
154. What is garbage collection? Explain different algorithms.

---

## **VII. REAL-WORLD APPLICATIONS**

### **19. OOP in System Design**

155. How to design a library management system using OOP?
156. How to design an e-commerce system using OOP?
157. How to design a banking system using OOP?
158. How to design a social media application using OOP?
159. How to design a game using OOP?

### **20. Best Practices**

160. When to use inheritance vs composition?
161. How to decide between abstract class and interface?
162. What is the rule of three/five/zero in C++?
163. How to achieve loose coupling in OOP?
164. What are anti-patterns in OOP? (God class, Anemic domain model, etc.)

### **21. Testing in OOP**

165. What is unit testing in OOP?
166. What is mocking in OOP testing?
167. How to test private methods?
168. What is dependency injection? How does it help testing?

---

## **VIII. COMPARISON QUESTIONS**

1. **Class vs Object**
2. **Abstraction vs Encapsulation**
3. **Inheritance vs Composition**
4. **Method Overloading vs Method Overriding**
5. **Compile-time vs Runtime Polymorphism**
6. **Abstract Class vs Interface**
7. **Static vs Instance Members**
8. **Stack vs Heap Memory**
9. **Shallow Copy vs Deep Copy**
10. **Early Binding vs Late Binding**
11. **Has-a vs Is-a Relationship**
12. **Aggregation vs Composition**
13. **Final vs Finally vs Finalize**
14. **== vs equals() method**
15. **C++ vs Java OOP implementation**

---

## **IX. CODE ANALYSIS QUESTIONS**

### **22. Predict Output**

169. What is the output of inheritance hierarchy code?
170. What is the output of polymorphism example?
171. What is the output of static vs instance method calls?
172. What is the output of constructor chaining?
173. What is the output of exception handling in constructors?

### **23. Identify Issues**

174. Identify SOLID principle violations in given code.
175. Identify design flaws in inheritance hierarchy.
176. Identify memory leak issues.
177. Identify thread safety issues in singleton implementation.
178. Identify issues with equals() and hashCode() implementation.

### **24. Design Implementation**

179. Implement singleton pattern with thread safety.
180. Implement factory pattern for shape objects.
181. Implement observer pattern for weather station.
182. Implement decorator pattern for coffee shop.
183. Implement strategy pattern for payment processing.

---

## **X. THEORETICAL QUESTIONS**

### **25. Fundamental Concepts**

184. What is the difference between message passing and method invocation?
185. What is dynamic binding? How is it achieved?
186. What is the difference between early and late binding?
187. What are the characteristics of good OOP design?
188. What is the difference between OOP and component-based programming?

### **26. Evolution of OOP**

189. How has OOP evolved over time?
190. What are the criticisms of OOP?
191. What are the alternatives to OOP? (Functional programming, etc.)
192. What is the future of OOP?

---

## **IMPORTANT CONCEPTS SUMMARY**

### **Four Pillars of OOP:**

1. **Encapsulation** - Binding data and methods, data hiding
2. **Abstraction** - Hiding complexity, showing only essentials
3. **Inheritance** - IS-A relationship, code reuse
4. **Polymorphism** - Many forms, method overloading/overriding

### **Key Relationships:**

- **IS-A** - Inheritance (Car IS-A Vehicle)
- **HAS-A** - Composition/Association (Car HAS-A Engine)
- **USES-A** - Dependency (Driver USES-A Car)

### **Access Modifiers:**

- **Public** - Accessible from anywhere
- **Private** - Accessible only within class
- **Protected** - Accessible within class and subclasses
- **Default** - Accessible within package

### **Important Keywords:**

- `this` - Reference to current object
- `super` - Reference to parent class
- `static` - Class-level members
- `final` - Cannot be changed/overridden/extended
- `abstract` - Cannot be instantiated, must be extended
- `interface` - Contract for implementation

---

## **COMMON INTERVIEW SCENARIOS**

### **1. Design Problems (30-45 minutes)**

- Design a parking lot system
- Design a chess game
- Design a vending machine
- Design a file system
- Design an elevator system

### **2. Code Review (20-30 minutes)**

- Review given OOP code for best practices
- Identify design flaws
- Suggest improvements
- Refactor code

### **3. Theory Discussion (20-30 minutes)**

- Explain OOP concepts with examples
- Discuss SOLID principles
- Compare different approaches
- Explain design patterns

### **4. Implementation (30-45 minutes)**

- Implement specific design pattern
- Fix given broken code
- Add new feature to existing design
- Optimize existing implementation

---

**Total Questions: 190+ (covering all aspects of Object-Oriented Programming)**
