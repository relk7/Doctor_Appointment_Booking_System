#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <algorithm>

using namespace std;

const int MAX_UPCOMING_APPOINTMENTS = 3;

struct Doctor {
    string id;
    string name;
    vector<string> slots;
};

struct Appointment {
    int id;
    string patientId;
    string patientName;
    string doctorId;
    string dateTime;
    string status;
};

vector<Doctor> doctors = {
    {"1", "Dr. Ahmed", {}},
    {"2", "Dr. Sara", {}}
};

// Stores appointments while the program is running
vector<Appointment> appointments;
int nextAppointmentId = 1;

// Converts a timestamp into a readable date and time
string formatDateTime(time_t timestamp) {
    tm* local = localtime(&timestamp);
    stringstream output;
    output << put_time(local, "%Y-%m-%d %H:%M");
    return output.str();
}

// Returns the current date and time in the same format
string currentDateTime() {
    return formatDateTime(time(nullptr));
}

// Generates sample appointment slots for the next seven days
void generateSlots() {
    const vector<string> times = {
        "09:00", "10:00", "11:00", "13:00", "14:00"
    };

    time_t now = time(nullptr);

    for (int day = 1; day <= 7; day++) {
        time_t futureDay = now + static_cast<time_t>(day) * 24 * 60 * 60;
        tm date = *localtime(&futureDay);

        for (const string& time : times) {
            stringstream slot;
            slot << put_time(&date, "%Y-%m-%d") << " " << time;

            for (Doctor& doctor : doctors) {
                doctor.slots.push_back(slot.str());
            }
        }
    }
}

// Displays the doctors and returns the selected doctor
Doctor* chooseDoctor() {
    cout << "\nAvailable doctors:\n";

    for (const Doctor& doctor : doctors) {
        cout << doctor.id << ". " << doctor.name << '\n';
    }

    cout << "Enter doctor number: ";
    string id;
    cin >> id;

    for (Doctor& doctor : doctors) {
        if (doctor.id == id) {
            return &doctor;
        }
    }

    cout << "Invalid doctor number.\n";
    return nullptr;
}

// Checks whether a slot is free from pending or accepted appointments
bool isSlotAvailable(const string& doctorId, const string& dateTime) {
    for (const Appointment& appointment : appointments) {
        if (appointment.doctorId == doctorId &&
            appointment.dateTime == dateTime &&
            (appointment.status == "Pending" ||
             appointment.status == "Accepted")) {
            return false;
        }
    }

    return true;
}

// Counts a patient's future pending and accepted appointments
int countUpcomingAppointments(const string& patientId) {
    int count = 0;
    string now = currentDateTime();

    for (const Appointment& appointment : appointments) {
        if (appointment.patientId == patientId &&
            appointment.dateTime > now &&
            (appointment.status == "Pending" ||
             appointment.status == "Accepted")) {
            count++;
        }
    }

    return count;
}

// Displays the selected doctor's available future slots
void viewAvailability() {
    Doctor* doctor = chooseDoctor();

    if (doctor == nullptr) {
        return;
    }

    cout << "\nAvailable slots for " << doctor->name << ":\n";
    bool found = false;

    for (const string& slot : doctor->slots) {
        if (slot > currentDateTime() &&
            isSlotAvailable(doctor->id, slot)) {
            cout << slot << '\n';
            found = true;
        }
    }

    if (!found) {
        cout << "No available slots.\n";
    }
}

// Allows a patient to request an appointment
void requestAppointment() {
    string patientId, patientName;

    cout << "Enter patient ID: ";
    cin >> patientId;

    cout << "Enter patient name (one word): ";
    cin >> patientName;

    // Reject the request if the patient has reached the limit
    if (countUpcomingAppointments(patientId) >=
        MAX_UPCOMING_APPOINTMENTS) {
        cout << "Booking rejected: maximum of "
             << MAX_UPCOMING_APPOINTMENTS
             << " upcoming appointments reached.\n";
        return;
    }

    Doctor* doctor = chooseDoctor();

    if (doctor == nullptr) {
        return;
    }
  
    // Collect the doctor's currently available future slots
    vector<string> availableSlots;

    for (const string& slot : doctor->slots) {
        if (slot > currentDateTime() &&
            isSlotAvailable(doctor->id, slot)) {
            availableSlots.push_back(slot);
        }
    }

    if (availableSlots.empty()) {
        cout << "No available slots for this doctor.\n";
        return;
    }

    cout << "\nAvailable slots:\n";

    for (size_t i = 0; i < availableSlots.size(); i++) {
        cout << i + 1 << ". " << availableSlots[i] << '\n';
    }

    cout << "Choose a slot number: ";
    int choice;

    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input.\n";
        return;
    }

    if (choice < 1 ||
        choice > static_cast<int>(availableSlots.size())) {
        cout << "Invalid slot number.\n";
        return;
    }

    string selectedSlot = availableSlots[choice - 1];

    if (!isSlotAvailable(doctor->id, selectedSlot)) {
        cout << "This slot is no longer available.\n";
        return;
    }

    appointments.push_back({
        nextAppointmentId,
        patientId,
        patientName,
        doctor->id,
        selectedSlot,
        "Pending"
    });

    cout << "Appointment request created.\n";
    cout << "Appointment ID: " << nextAppointmentId << '\n';
    cout << "Status: Pending\n";

    nextAppointmentId++;
}

void reviewAppointments() {
    Doctor* doctor = chooseDoctor();

    if (doctor == nullptr) {
        return;
    }

    vector<int> pendingIndexes;

    cout << "\nPending requests for " << doctor->name << ":\n";

    for (size_t i = 0; i < appointments.size(); i++) {
        const Appointment& appointment = appointments[i];

        if (appointment.doctorId == doctor->id &&
            appointment.status == "Pending" &&
            appointment.dateTime > currentDateTime()) {
            cout << "ID: " << appointment.id
                 << " | Patient: " << appointment.patientName
                 << " | Date: " << appointment.dateTime << '\n';

            pendingIndexes.push_back(static_cast<int>(i));
        }
    }

    if (pendingIndexes.empty()) {
        cout << "No pending requests.\n";
        return;
    }

    cout << "Enter appointment ID to review: ";
    int id;

    if (!(cin >> id)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input.\n";
        return;
    }

    int selectedIndex = -1;

    for (int index : pendingIndexes) {
        if (appointments[index].id == id) {
            selectedIndex = index;
            break;
        }
    }

    if (selectedIndex == -1) {
        cout << "Invalid appointment ID.\n";
        return;
    }

    cout << "Accept or decline? (A/D): ";
    char decision;
    cin >> decision;
    decision = static_cast<char>(toupper(decision));

    if (decision == 'A') {
        appointments[selectedIndex].status = "Accepted";
        cout << "Appointment accepted.\n";
    } else if (decision == 'D') {
        appointments[selectedIndex].status = "Declined";
        cout << "Appointment declined. The slot is available again.\n";
    } else {
        cout << "Invalid decision. Enter A or D.\n";
    }
}

void viewPatientAppointments() {
    string patientId;

    cout << "Enter patient ID: ";
    cin >> patientId;

    bool found = false;

    for (const Appointment& appointment : appointments) {
        if (appointment.patientId == patientId) {
            cout << "ID: " << appointment.id
                 << " | Doctor: ";

            for (const Doctor& doctor : doctors) {
                if (doctor.id == appointment.doctorId) {
                    cout << doctor.name;
                    break;
                }
            }

            cout << " | Date: " << appointment.dateTime
                 << " | Status: " << appointment.status << '\n';

            found = true;
        }
    }

    if (!found) {
        cout << "No appointments found.\n";
    }
}

int main() {
    generateSlots();

    while (true) {
        cout << "\n=== Doctor Appointment Booking System ===\n";
        cout << "1. View doctor availability\n";
        cout << "2. Request an appointment\n";
        cout << "3. Accept or decline appointment requests\n";
        cout << "4. View patient appointments\n";
        cout << "5. Exit\n";
        cout << "Choose an option: ";

        int choice;

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Please enter a number from 1 to 5.\n";
            continue;
        }

        switch (choice) {
            case 1:
                viewAvailability();
                break;
            case 2:
                requestAppointment();
                break;
            case 3:
                reviewAppointments();
                break;
            case 4:
                viewPatientAppointments();
                break;
            case 5:
                cout << "Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice. Please choose 1 to 5.\n";
        }
    }
}
