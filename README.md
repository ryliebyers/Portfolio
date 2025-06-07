# GitHub Portfolio

A collection of personal and collaborative projects showcasing experience in mobile development, backend systems, UI frameworks, and security protocols.

---

## 📱 AndroidDrawingApp

A basic Android drawing app built with **Kotlin** and **Jetpack Compose**.

**Features:**
- Pen customization: choose pen type, color, and size  
- "Marble" mode: a ball rolls around the screen in ink, creating randomized strokes  
- Firebase Authentication  
- HTTP server integration for sharing and viewing community drawings  
- Built using Kotlin, Jetpack Compose, and HTML  

**Collaborators:** Mina Akbari, Ray Ding

---

## 🎮 DropcatcherQTGame

A falling-object catching game developed using **C++**, **C**, and **qmake**.  
Demonstrates use of the Qt framework for interactive GUI programming.

**Collaborators:** Mina Akbari, Ray Ding

---

## 🧙 Flutter RPG App

A cross-platform character sheet manager for tabletop role-playing games.

**Tech Stack:**
- Built with **Flutter** and **Dart**  
- Uses **Firebase** for secure data storage and authentication  

Players can create, update, and store character profiles across multiple campaigns.

---

## 🧮 FunctionParser

A custom interpreter for a mini C++-like scripting language.

**Language:** C++  
Parses and evaluates arithmetic expressions and basic control structures.

---

## 🎓 LMS (Learning Management System)

A full-stack web application for managing academic users and coursework, built with **ASP.NET Core** and **Entity Framework**.

**Key Features:**
- 🔐 **Authentication:** ASP.NET Identity with a dedicated user database (`TeamXLMSUsers`)  
- 🗂️ **Data Models:** Courses, departments, and classes scaffolded from `TeamXLMS` database  
- 👥 **User Roles:** Admin, Professor, and Student dashboards with role-based access  
- 🧮 **Grading System:** Automatic final grade calculation based on assignment weights  
- 🧪 **Testing:** Includes unit test setup and manual data entry for development  

**Setup Instructions:**
1. Configure both databases using user secrets  
2. Scaffold LMS models from the `TeamXLMS` database  
3. Run Entity Framework migrations and updates  
4. Implement required controller methods (`AdministratorController`, `ProfessorController`, etc.)

**Collaborator:** Ray Ding

---

## 🔐 TLSlite

A simplified implementation of the **TLS** protocol using **C**, **RSA encryption**, and **Diffie-Hellman key exchange**.

**Components:**
- Certificate Authority  
- Server and Client with mutual authentication  
- OpenSSL-generated public/private key pairs and X.509 certificates  

**TLS Handshake Flow:**
1. **Client** sends a nonce  
2. **Server** responds with:
   - Server certificate  
   - Server's Diffie-Hellman public key  
   - Encrypted signature: `Enc(serverRSAPriv, serverDHPub)`  
3. **Client** replies with:
   - Client certificate  
   - Client's Diffie-Hellman public key  
   - Encrypted signature: `Enc(clientRSAPriv, clientDHPub)`  

---

