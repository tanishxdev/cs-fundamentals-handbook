# **Computer Networks Interview Questions Sheet**

---

## **I. NETWORK FUNDAMENTALS**

### **1. Basic Concepts**

1. What is a computer network? Explain its purpose and importance.
2. Differentiate between network and internet.
3. What are the components of a computer network? (Nodes, Links, Media, Protocols)
4. Explain the terms: node, host, server, client, and peer.
5. What is network topology? Why is it important?
6. Explain different types of network topologies:
   - Bus Topology
   - Star Topology
   - Ring Topology
   - Mesh Topology (Full, Partial)
   - Tree Topology
   - Hybrid Topology
7. What is bandwidth? How is it measured?
8. What is throughput? Differentiate between bandwidth and throughput.
9. What is latency? Explain types of delays in networks.
10. What is jitter? Why is it important?

### **2. Network Types**

11. Explain different types of networks based on geographical area:

- PAN (Personal Area Network)
- LAN (Local Area Network)
- MAN (Metropolitan Area Network)
- WAN (Wide Area Network)
- GAN (Global Area Network)

12. What is LAN? Explain its characteristics and uses.
13. What is WAN? How is it different from LAN?
14. What is wireless network? Explain its types.
15. What is VPN (Virtual Private Network)? Explain its types and advantages.
16. What is intranet and extranet?
17. What is the Internet? How does it differ from the World Wide Web?

### **3. Network Devices**

18. Explain different network devices:

- Hub
- Switch
- Router
- Bridge
- Gateway
- Repeater
- Modem
- NIC (Network Interface Card)
- Access Point

19. Differentiate between hub and switch.
20. Differentiate between router and gateway.
21. Differentiate between router and switch.
22. Differentiate between bridge and switch.
23. What is a load balancer? How does it work?
24. What is a firewall? Explain its types and working.
25. What is a proxy server?

---

## **II. NETWORK MODELS**

### **4. OSI Model**

26. What is the OSI model? Why was it created?
27. Explain all 7 layers of the OSI model:

- Layer 7: Application Layer
- Layer 6: Presentation Layer
- Layer 5: Session Layer
- Layer 4: Transport Layer
- Layer 3: Network Layer
- Layer 2: Data Link Layer
- Layer 1: Physical Layer

28. What is the function of each OSI layer?
29. What protocols operate at each OSI layer?
30. What is encapsulation and de-capsulation in OSI model?
31. What are PDUs (Protocol Data Units) at each layer?

- Application Layer: Data
- Presentation Layer: Data
- Session Layer: Data
- Transport Layer: Segment (TCP) / Datagram (UDP)
- Network Layer: Packet
- Data Link Layer: Frame
- Physical Layer: Bits

### **5. TCP/IP Model**

32. What is the TCP/IP model? Explain its layers.
33. Differentiate between OSI model and TCP/IP model.
34. Explain the four layers of TCP/IP model:

- Application Layer
- Transport Layer
- Internet Layer
- Network Access/Link Layer

35. How does TCP/IP model map to OSI model?
36. What is the hybrid model (5-layer model)?

---

## **III. PHYSICAL LAYER**

### **6. Transmission Media**

37. What is transmission media? Explain its types.
38. Differentiate between guided and unguided media.
39. Explain guided media:

- Twisted Pair Cable (UTP, STP)
- Coaxial Cable
- Fiber Optic Cable

40. Explain unguided/wireless media:

- Radio Waves
- Microwaves
- Infrared
- Satellite Communication

41. What are the advantages of fiber optic cable?
42. What is Ethernet cable? Explain categories (Cat5, Cat6, etc.)

### **7. Physical Layer Concepts**

43. What is signaling? Explain analog and digital signals.
44. What is modulation and demodulation?
45. Explain different modulation techniques.
46. What is multiplexing? Explain its types:

- FDM (Frequency Division Multiplexing)
- TDM (Time Division Multiplexing)
- WDM (Wavelength Division Multiplexing)
- CDM (Code Division Multiplexing)

47. What is switching? Explain circuit switching and packet switching.
48. Differentiate between circuit switching and packet switching.
49. What is message switching?
50. What is DSL (Digital Subscriber Line)?
51. What is ISDN (Integrated Services Digital Network)?

---

## **IV. DATA LINK LAYER**

### **8. Data Link Layer Basics**

52. What is the function of Data Link Layer?
53. Explain the sublayers of Data Link Layer (LLC and MAC).
54. What is framing? Explain different framing methods.
55. What is error detection? Explain methods:

- Parity Check (Even, Odd)
- Checksum
- CRC (Cyclic Redundancy Check)

56. What is error correction? Explain Hamming code.
57. What is flow control? Explain methods:

- Stop and Wait
- Sliding Window Protocol

58. What is ARQ (Automatic Repeat Request)? Explain types.

### **9. MAC (Media Access Control)**

59. What is MAC address? Explain its format.
60. How is MAC address different from IP address?
61. What are different MAC protocols?
62. Explain random access protocols:

- ALOHA (Pure, Slotted)
- CSMA (Carrier Sense Multiple Access)
- CSMA/CD (Collision Detection)
- CSMA/CA (Collision Avoidance)

63. What are controlled access protocols?
64. What are channelization protocols?
65. What is Ethernet? Explain its frame format.
66. What is Wi-Fi? Explain IEEE 802.11 standards.

### **10. Switching**

67. What is a bridge? How does it work?
68. What is a switch? How does it work?
69. Explain different switching techniques in switches.
70. What is VLAN (Virtual LAN)?
71. What is STP (Spanning Tree Protocol)?

---

## **V. NETWORK LAYER**

### **11. Network Layer Basics**

72. What is the function of Network Layer?
73. What is logical addressing?
74. What is routing? Explain routing algorithms.
75. What is IP addressing? Explain IPv4 address structure.
76. What are different classes of IPv4 addresses?

- Class A (1-126)
- Class B (128-191)
- Class C (192-223)
- Class D (224-239) - Multicast
- Class E (240-255) - Experimental

77. What is subnet mask? How is it used?
78. What is subnetting? Why is it needed?
79. What is supernetting (CIDR)?
80. What is VLSM (Variable Length Subnet Masking)?

### **12. IPv4 and IPv6**

81. What is IPv4? Explain its header format.
82. What is IPv6? Explain its header format.
83. Differentiate between IPv4 and IPv6.
84. What are private IP addresses? (RFC 1918)
85. What are special IP addresses?

- Loopback (127.0.0.0/8)
- APIPA (169.254.0.0/16)
- Broadcast addresses

86. What is NAT (Network Address Translation)? Explain its types.
87. What is ICMP (Internet Control Message Protocol)?
88. What is ARP (Address Resolution Protocol)?
89. What is RARP (Reverse ARP)?
90. What is BOOTP/DHCP?
91. What is DNS (Domain Name System)? How does it work?

### **13. Routing Protocols**

92. What are routing protocols? Explain types:

- Static Routing
- Dynamic Routing

93. Differentiate between distance vector and link state routing.
94. Explain RIP (Routing Information Protocol).
95. Explain OSPF (Open Shortest Path First).
96. Explain BGP (Border Gateway Protocol).
97. What is default gateway?
98. What is routing table? What information does it contain?

---

## **VI. TRANSPORT LAYER**

### **14. Transport Layer Basics**

99. What is the function of Transport Layer?
100. What is port number? Explain well-known ports.
101. What is socket? Explain socket programming.
102. What is multiplexing and demultiplexing at transport layer?

### **15. TCP (Transmission Control Protocol)**

103. What is TCP? Explain its characteristics.
104. Explain TCP header format.
105. What is TCP 3-way handshake?
106. What is TCP 4-way termination?
107. What are TCP flags? (SYN, ACK, FIN, RST, PSH, URG)
108. What is TCP congestion control?
109. Explain TCP flow control mechanisms.
110. What is TCP sliding window?
111. What is Nagle's algorithm?
112. What is TCP keep-alive?
113. What is TCP timeout and retransmission?

### **16. UDP (User Datagram Protocol)**

114. What is UDP? Explain its characteristics.
115. Explain UDP header format.
116. Differentiate between TCP and UDP.
117. When to use TCP vs UDP?

### **17. Transport Layer Services**

118. What are different QoS (Quality of Service) parameters?
119. What is SCTP (Stream Control Transmission Protocol)?
120. What is QUIC protocol?

---

## **VII. APPLICATION LAYER**

### **18. Application Layer Protocols**

121. What is the function of Application Layer?
122. Explain client-server architecture.
123. Explain peer-to-peer architecture.
124. What is HTTP? Explain HTTP methods.
125. What is HTTPS? How does SSL/TLS work?
126. What is FTP? Explain active and passive modes.
127. What is SMTP? How does email work?
128. What is POP3 and IMAP?
129. What is DNS? Explain DNS hierarchy and record types.
130. What is DHCP? Explain DORA process.
131. What is SNMP (Simple Network Management Protocol)?
132. What is Telnet and SSH?
133. What is NTP (Network Time Protocol)?
134. What is VoIP (Voice over IP)?

### **19. Web Technologies**

135. What is URL? Explain its components.
136. What is cookie? How does it work?
137. What is session? How is it different from cookie?
138. What is REST API?
139. What is WebSocket?
140. What is CDN (Content Delivery Network)?

---

## **VIII. NETWORK SECURITY**

### **20. Security Basics**

141. What is network security? Why is it important?
142. Explain CIA triad (Confidentiality, Integrity, Availability).
143. What are different types of network attacks?

- DoS/DDoS attacks
- Man-in-the-middle attack
- Phishing
- SQL injection
- XSS (Cross-site scripting)
- CSRF (Cross-site request forgery)

144. What is malware? Explain types.

### **21. Security Protocols**

145. What is encryption? Explain symmetric and asymmetric encryption.
146. What is SSL/TLS? How does handshake work?
147. What is IPsec? Explain its modes.
148. What is VPN? Explain types.
149. What is firewall? Explain types.
150. What is IDS/IPS (Intrusion Detection/Prevention System)?
151. What is DMZ (Demilitarized Zone)?
152. What is honeypot?

### **22. Cryptography**

153. Explain RSA algorithm.
154. Explain Diffie-Hellman key exchange.
155. What is digital signature?
156. What is digital certificate?
157. What is PKI (Public Key Infrastructure)?
158. What is hashing? Explain MD5, SHA algorithms.

---

## **IX. WIRELESS NETWORKS**

### **23. Wireless Technologies**

159. What is Wi-Fi? Explain IEEE 802.11 standards.
160. What is Bluetooth? Explain its architecture.
161. What is NFC (Near Field Communication)?
162. What is RFID (Radio Frequency Identification)?
163. What is Zigbee?
164. What is Li-Fi?

### **24. Mobile Networks**

165. Explain cellular network generations (1G to 5G).
166. What is GSM? Explain its architecture.
167. What is CDMA?
168. What is LTE?
169. What is mobile IP?

---

## **X. ADVANCED TOPICS**

### **25. Network Management**

170. What is network management? Explain FCAPS model.
171. What is SNMP? Explain its components.
172. What is network monitoring?
173. What is packet sniffing?
174. What is bandwidth management?
175. What is traffic shaping?

### **26. Quality of Service**

176. What is QoS? Why is it important?
177. Explain QoS parameters (bandwidth, delay, jitter, loss).
178. What is traffic policing and shaping?
179. What is DiffServ and IntServ?

### **27. Multimedia Networking**

180. What is streaming? Explain live and on-demand.
181. What is RTP/RTCP?
182. What is RTSP?
183. What is SIP (Session Initiation Protocol)?

### **28. Emerging Technologies**

184. What is SDN (Software Defined Networking)?
185. What is NFV (Network Function Virtualization)?
186. What is IoT (Internet of Things)?
187. What is cloud computing? Explain types (IaaS, PaaS, SaaS).
188. What is edge computing?
189. What is 5G? What are its features?

---

## **XI. NETWORK TROUBLESHOOTING**

### **29. Troubleshooting Tools**

190. What is ping command? How does it work?
191. What is traceroute/tracert? How does it work?
192. What is netstat command?
193. What is nslookup/dig command?
194. What is ipconfig/ifconfig command?
195. What is Wireshark? How is it used?
196. What is tcpdump?
197. What is iperf?

### **30. Troubleshooting Scenarios**

198. What happens when you type "google.com" in browser?
199. How to troubleshoot "no internet connection"?
200. How to troubleshoot slow network?
201. How to troubleshoot DNS issues?
202. How to troubleshoot IP address conflicts?
203. How to troubleshoot port connectivity?
204. How to troubleshoot wireless connection issues?
205. How to troubleshoot routing issues?

---

## **XII. PRACTICAL CONCEPTS**

### **31. Network Design**

206. How to design a network for a small office?
207. How to design a network for a campus?
208. What factors to consider in network design?
209. What is network documentation?

### **32. Performance Optimization**

210. How to optimize network performance?
211. What is bandwidth throttling?
212. What is compression? Explain types.
213. What is caching? How does it help?

### **33. Real-world Scenarios**

214. Explain load balancing in web servers.
215. How does CDN work?
216. How does video streaming work?
217. How does online gaming work?
218. How does VoIP work?
219. How does video conferencing work?

---

## **XIII. COMPARISON QUESTIONS**

1. **TCP vs UDP**
2. **IPv4 vs IPv6**
3. **Hub vs Switch vs Router**
4. **Circuit Switching vs Packet Switching**
5. **OSI Model vs TCP/IP Model**
6. **Static Routing vs Dynamic Routing**
7. **Distance Vector vs Link State Routing**
8. **HTTP vs HTTPS**
9. **Symmetric vs Asymmetric Encryption**
10. **Wi-Fi vs Bluetooth**
11. **LAN vs WAN**
12. **Firewall vs IDS/IPS**
13. **NAT vs PAT**
14. **POP3 vs IMAP**
15. **SSL vs TLS**

---

## **IMPORTANT PROTOCOLS SUMMARY**

### **Application Layer:**

- HTTP/HTTPS (80/443)
- FTP (20/21)
- SMTP (25)
- DNS (53)
- DHCP (67/68)
- SSH (22)
- Telnet (23)
- SNMP (161)

### **Transport Layer:**

- TCP (Connection-oriented)
- UDP (Connectionless)
- SCTP

### **Network Layer:**

- IP (IPv4, IPv6)
- ICMP
- IGMP
- ARP/RARP
- OSPF, RIP, BGP

### **Data Link Layer:**

- Ethernet (IEEE 802.3)
- Wi-Fi (IEEE 802.11)
- PPP
- HDLC

---

## **KEY CONCEPTS TO REMEMBER**

### **Must Know:**

- OSI Model layers and functions
- TCP/IP Model
- TCP vs UDP differences
- IP addressing and subnetting
- HTTP/HTTPS working
- DNS resolution process
- Network devices and their functions
- Basic troubleshooting commands

### **Should Know:**

- Routing protocols (RIP, OSPF, BGP)
- Network security concepts
- Wireless networking
- Network troubleshooting scenarios
- Performance optimization techniques

### **Good to Know:**

- Advanced routing concepts
- Network design principles
- Emerging technologies (SDN, IoT, 5G)
- Cloud networking
- Network virtualization

---

## **COMMON INTERVIEW SCENARIOS**

### **1. "What happens when you type google.com in browser?"**

This comprehensive question tests understanding of:

- DNS resolution
- TCP connection establishment
- HTTP request/response
- Rendering process
- Caching mechanisms

### **2. Network Troubleshooting**

- Ping works but browser doesn't
- Slow network performance
- Intermittent connectivity
- DNS resolution failures
- Port connectivity issues

### **3. Network Design**

- Design network for specific requirements
- Choose appropriate devices
- IP addressing scheme
- Security considerations
- Scalability planning

### **4. Protocol Analysis**

- Analyze packet captures
- Identify protocol issues
- Suggest optimizations
- Security vulnerability assessment

---

## **IMPORTANT NUMBERS TO REMEMBER**

### **Port Numbers:**

- HTTP: 80
- HTTPS: 443
- DNS: 53
- SSH: 22
- FTP: 20/21
- SMTP: 25
- DHCP: 67/68
- Telnet: 23

### **IP Address Ranges:**

- Private IPs: 10.0.0.0/8, 172.16.0.0/12, 192.168.0.0/16
- Loopback: 127.0.0.0/8
- APIPA: 169.254.0.0/16

### **MTU Sizes:**

- Ethernet: 1500 bytes
- PPPoE: 1492 bytes
- Jumbo frames: 9000 bytes

---

**Total Questions: 220+ (covering all aspects of Computer Networks)**
