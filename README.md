#  Study Recommendation System ("Próximo Exercício")

A CLI (Command Line Interface) application developed in C to manage and recommend programming exercises. The system helps students practice specific topics based on their difficulty level and study history.

> *Note: This project was developed as part of a university course in Brazil, so the source code and user interface are originally in Portuguese.*

##  Features

The system features robust binary data persistence and CSV reporting:

- **Authentication System:**
  - Role-based access (Admin vs. Student).
  - Secure login validation.
- **Smart Recommendation Engine:**
  - Suggests exercises based on **Category** (e.g., Pointers, Structs) and **Difficulty (1-5)**.
  - History tracking to ensure users receive new challenges.
- **Task Management (CRUD):**
  - Admins can Create, Read, Update, and Delete tasks and users.
  - Support for multiple tags per task.
- **Data Persistence & Reporting:**
  - Uses binary files (`.dat`) for the local database (Users, Tasks, History).
  - Exports reports to `.csv` format for external analysis.

##  Tech Stack

- **Language:** C 
- **Architecture:** Modular design (`.c` / `.h` separation).
- **Data Handling:** Binary file manipulation (`fread`/`fwrite`) and text file generation.
- **Build System:** Makefile included for automation.

##  How to Run

Ensure you have a C compiler (like `gcc`) and `make` installed.

1. **Clone the repository:**
   ```bash
   git clone [https://github.com/your-username/study-recommendation-system.git](https://github.com/your-username/study-recommendation-system.git)
   cd study-recommendation-system
