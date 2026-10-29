# Doctor Appointment Booking System

A small console application written in C++.
It was built for the Advanced Software Engineering team assignment (2026 / 2027).

## Team

| Student ID | Full name | Assigned task | Branch | PR Link
|------------|-----------|---------------|--------|--------|
| 20240189 | Rahma Ahmed Ahmed | Use Cases & Class Diagram | Rahma & Rahma_class_diagram |https://github.com/relk7/Doctor_Appointment_Booking_System/pull/1 & https://github.com/relk7/Doctor_Appointment_Booking_System/pull/2 |
| 2024023 | Roaa Abdelfatah Salah | Sequence Diagram | Roaa_Sequence_diagram |https://github.com/relk7/Doctor_Appointment_Booking_System/pull/3|
| 20240571 | Maryam Ahmed Adel | Implementation | Mayram_Implementation | https://github.com/relk7/Doctor_Appointment_Booking_System/pull/4|

## Project files

| File | Purpose |
|------|---------|
| `requirements.txt` | System requirements R1 to R7 |
| `use_cases.md` | Patient and doctor use cases |
| `use_case_diagram.md` | Use case diagram (Mermaid) |
| `class_diagram.md` | Class diagram (Mermaid) |
| `sequence_diagram.md` | Booking sequence diagram (Mermaid) |
| `main.cpp` | The C++ application |

## How to run

### What you need

- A C++ compiler with C++17 support (g++ 9 or newer).
- Git.
- No extra libraries are needed.

### Steps (Linux / macOS)

```bash
git clone <your-repo-url>
cd <your-repo-folder>
g++ -std=c++17 -Wall -o booking src/main.cpp
./booking
```

### Steps (Windows, MinGW or MSYS2)

```bash
git clone <your-repo-url>
cd <your-repo-folder>
g++ -std=c++17 -Wall -o booking.exe src/main.cpp
booking.exe
```

## How to use the app

The app shows a menu in the console.

1. View a doctor's available days and times (R1).
2. Book an appointment in a free slot (R2).
3. Doctor: accept or decline a pending request (R3).
4. View my appointments.
5. Exit.

## Booking limit (R4)

**N = 3.**

A patient can have at most 3 upcoming appointments.

- Future **Pending** and **Accepted** appointments count.
- **Declined**, **Cancelled** and past appointments do not count.

## Functional requirements (R1 to R4)

| ID | Requirement | Where it is implemented |
|----|-------------|-------------------------|
| R1 | View doctor availability | Menu option 1 |
| R2 | Book an appointment | Menu option 2 |
| R3 | Doctor accepts or declines | Menu option 3 |
| R4 | Limit of N upcoming appointments | Checked before every booking |

## Non-functional requirements (R5 to R7)

These are explained here only. They are not implemented or tested.

**R5: Patient data is only for authorized staff.**
- Add a login with roles (patient, doctor, admin).
- Check the role before showing any medical data.
- Store passwords as hashes, never as plain text.
- Use HTTPS if the app becomes a web app.

**R6: Available times show within 2 seconds.**
- Keep slots in memory, sorted by date.
- Filter by doctor and date only.
- In a real system, use a database index on doctor and date.

**R7: Usable on mobile screens.**
- Use a responsive web interface (for example, CSS media queries).
- Use large buttons and short forms.
- Test on a small screen size, such as 360 px wide.

## Diagrams

- [Use case diagram](use_case_diagram.md)
- [Class diagram](class_diagram.md)
- [Sequence diagram](sequence_diagram.md)
