# 📒 Student Address Book in C

A console-based Student Address Book application developed in C that stores and manages contact details with strong validation and uniqueness checks.
This project was built as part of my Embedded Systems learning journey and focuses on practical C programming and data validation techniques.

---

## 🚀 Project Overview

This project maintains an address book of student records (up to ~100 entries) containing:

* Name
* Mobile Number
* Email ID

The system ensures that every mobile number and email ID is **valid and unique** across the entire list.

---

## ✅ Key Features

* Add new student contacts
* Store and manage multiple records
* Mobile number validation
* Email format validation
* Duplicate mobile number prevention
* Duplicate email ID prevention
* File-based data storage
* Modular C program structure
* Menu-driven execution

---

## 🔍 Validations Implemented

### 📱 Mobile Number Validation

* Accepts only numeric digits
* Fixed length check
* Rejects invalid characters
* Ensures number is unique in records

### 📧 Email Validation

* Checks proper format with `@` and domain
* Rejects invalid patterns
* Ensures email ID is unique

---

## 🛠 Technical Concepts Used

* Structures in C
* Arrays of structures
* Header and source file separation
* String handling functions
* File handling
* Input validation logic
* Modular programming

---

## 📂 Project Structure

```
student-address-book-c/
│
├── src/
│   ├── main.c
│   ├── contact.c
│   ├── file.c
│   └── populate.c
│
├── include/
│   ├── contact.h
│   ├── file.h
│   └── populate.h
│
├── data/
│   ├── addressbook.csv
│   └── contacts.txt
│
├── README.md
├── Makefile
└── .gitignore
```

---

## ▶️ How to Compile and Run

```
gcc src/*.c -Iinclude -o addressbook
./addressbook
```

---

## 🎯 Learning Outcome

Through this project I improved my skills in:

* C programming fundamentals
* Real-world input validation
* Data integrity enforcement
* Modular code organization
* File-based record handling

---

## 🔧 Future Improvements (Planned)

* Search by name/number/email
* Edit and delete records
* Sorting contacts
* Better UI flow
* Dynamic memory version

---

## 🤝 Feedback

Suggestions and improvements are welcome. This project is part of my continuous learning journey in C and Embedded Systems.
