# 🚨 Emergency Management System

A comprehensive **Data Structures project in C++** designed to simulate a smart city emergency response system. This project demonstrates practical implementation of core data structures by managing emergencies, users, vehicles, dispatch operations, and reporting in a modular real-world scenario.

---

## 📌 Project Overview

The Emergency Management System is built to efficiently handle:

- Emergency registration and tracking
- User and citizen management
- Vehicle dispatch and allocation
- Resource monitoring
- Incident response history
- Daily operational reports

This project applies theoretical **Data Structures and Algorithms (DSA)** concepts to solve practical emergency management challenges for **Islamabad Smart City**.

---

## 🧠 Data Structures Used

This project showcases the implementation and use of:

| Data Structure | Purpose | Real-world Application |
|----------------|---------|------------------------|
| **Graph** | City road network & shortest paths | Finding fastest route to emergency |
| **Queue** | Emergency request processing | Handling emergencies in FIFO order |
| **Stack** | Response history tracking | Viewing most recent actions first |
| **Hash Table** | Citizen registration & lookup | Fast user ID search (O(1) average) |
| **Linked List** | Vehicle fleet management | Dynamic vehicle allocation |

---

## ✨ Key Features

### 👤 User Management
- Register new citizens with unique IDs
- Store user records persistently
- Search users efficiently using hash table
- Generate citizen reports

### 🚑 Emergency Handling
- Report 5 types of emergencies (Medical, Fire, Police, Accident, Rescue)
- Log emergencies with unique IDs
- Process active emergencies via queue
- Track emergency status (Pending → Assigned → Resolved)

### 🚓 Vehicle Management
- Add emergency vehicles (Ambulance, Fire Truck, Police Car, Rescue Van, Patrol Bike)
- Dispatch nearest available vehicles
- Track vehicle availability and assignment history

### 🗺️ Smart City Mapping
- 20 mapped locations across Islamabad
- Shortest path calculation using Floyd-Warshall algorithm
- Route display using Dijkstra's algorithm
- Find nearest emergency service (hospital, police, fire station)

### 📊 Reporting System
- Dispatch logs with timestamps
- Emergency history tracking
- Daily activity reports
- Fleet management reports
- Citizen registration reports

---

## 📁 Project Structure

```
DataStructures_Project/
│
├── src/                      # Source code directory
│   ├── main.cpp              # Program entry point
│   ├── CityMap.h             # Graph implementation
│   ├── Colors.h              # Terminal color codes
│   ├── EmergencyManager.h    # Emergency handling logic
│   ├── Graph.h               # Basic graph structure
│   ├── HashTable.h           # Hash table for citizens
│   ├── LinkedList.h          # Linked list for vehicles
│   ├── menu.h                # Menu display functions
│   ├── Queue.h               # Queue for emergencies
│   ├── ResponseStack.h       # Stack for history
│   ├── UserManager.h         # User management
│   └── VehicleManager.h      # Vehicle management
│
├── data/                     # Data storage directory
│   ├── users_data.txt        # Registered citizens
│   ├── vehicles.txt          # Vehicle fleet
│   ├── emergencies.txt       # Active emergencies
│   ├── dispatch_log.txt      # Dispatch records
│   └── response_history.txt  # Response logs
│
├── README.md                 # Documentation
├── .gitignore               # Git ignore rules
└── LICENSE                  # MIT License
```

---

## ⚙️ Technologies Used

| Category | Technology |
|----------|-----------|
| **Language** | C++17 |
| **Programming Paradigm** | Object-Oriented + Procedural |
| **Data Storage** | File handling (text-based persistence) |
| **Algorithms** | Floyd-Warshall, Dijkstra, Linear Probing |
| **Platform** | Cross-platform console application |

---

## 🚀 How to Run the Project

### Prerequisites
- C++17 compatible compiler (g++, clang++, MSVC)
- Terminal / Command Prompt

### Step 1: Clone the repository
```bash
git clone https://github.com/MoeedRaza/Data-Structures-Emergency-Management-System.git
```

### Step 2: Navigate into the project folder
```bash
cd Data-Structures-Emergency-Management-System
```

### Step 3: Compile the project
```bash
g++ src/main.cpp -o emergency_system
```

### Step 4: Run the program

**On Linux/Mac:**
```bash
./emergency_system
```

**On Windows:**
```bash
emergency_system.exe
```

### Default Admin PIN
```
1234
```

---

## 🎯 Educational Objectives

This repository is ideal for:

- 📚 **Data Structures students** - See real implementations of Graphs, Queues, Stacks, Hash Tables, Linked Lists
- 💻 **C++ beginners** - Learn OOP, file handling, and modular design
- 🏫 **University project demonstrations** - Complete working system with documentation
- 🔬 **DSA practical implementation learning** - Connect theory to practice
- 📁 **Portfolio building** - Showcase a complete project with multiple data structures

---

## 📊 Sample Output

```
╔══════════════════════════════════════════════════════════╗
║       ISLAMABAD SMART CITY EMERGENCY DISPATCH            ║
║                   MANAGEMENT SYSTEM                      ║
╚══════════════════════════════════════════════════════════╝

=== SHORTEST ROUTE ===
From: F-10 Police Station (Police)
To: I-8 Sector (Residential)
Total Distance: 6 km
Estimated Time: 12 minutes
Route: F-10 Police → G-9 Fire → I-8 Sector

=== EMERGENCY RESPONSE ===
Emergency ID: E1004
Emergency Type: Medical
Caller Location: F-7 Sector
Emergency Location: E-7 Sector
Nearest Hospital: Polyclinic Hospital (3 km)
Estimated arrival: 6 minutes
```

---

## 🔮 Future Improvements

Potential upgrades to enhance the system:

- GUI integration
- Database support (SQL/MySQL)
- GPS/live route optimization
- Web-based dashboard
- Authentication system
- Real-time notifications

---

## 🛡️ Best Practices Implemented

- **Modular code structure** - Each data structure has its own header file
- **Header-based design** - Clean separation of declarations and implementations
- **Separation of concerns** - User, Vehicle, Emergency managers work independently
- **Reusable components** - Data structures can be used in other projects
- **Persistent data storage** - All data saved to text files between runs
- **Organized project architecture** - Clear src/ and data/ folders
- **Colored terminal output** - Enhanced user experience with color coding
- **Error handling** - Input validation and graceful error messages

---

## 🤝 Contribution

Contributions are welcome.

To contribute:

1. Fork the repository
2. Create a new branch
3. Commit your changes
4. Push your branch
5. Open a Pull Request

---

## 📄 License

This project is licensed under the **MIT License** - see the [LICENSE](LICENSE) file for details.

```
MIT License

Copyright (c) 2024 Abdul Moeed Raza

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files...
```

---

## 👨‍💻 Author

Abdul Moeed Raza
Computer Science Student | Web Developer | DSA Enthusiast

---

## ⭐ Show Your Support

If you found this project helpful or educational, please consider:

- ⭐ Starring this repository on GitHub
- 🍴 Forking it for your own learning
- 📢 Sharing it with fellow students
- 🐛 Reporting issues or suggesting improvements

---

**Built with ❤️ for Islamabad Smart City Initiative | Data Structures & Algorithms Final Project**

---

## 🎉 Thank You for Visiting!

This project demonstrates the power of data structures in solving real-world problems. Feel free to explore, learn, and contribute!
