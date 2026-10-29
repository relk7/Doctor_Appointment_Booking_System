# Use Cases — Doctor Appointment Booking System

## Actors

- **Patient:** Views doctors' available appointment slots and requests appointments.
- **Doctor:** Reviews appointment requests and accepts or declines them.

## UC1 — View Doctor Availability

**Primary actor:** Patient

**Preconditions:** The system has doctor availability information.

**Main flow:**
1. The patient requests the available appointment slots for a doctor.
2. The system retrieves the doctor's available days and times.
3. The system displays the available slots to the patient.

**Alternative flow:**
1. If no slots are available, the system informs the patient that no appointments are currently available.

## UC2 — Request an Appointment

**Primary actor:** Patient

**Preconditions:** The patient and doctor exist, and the patient can access the booking function.

**Main flow:**
1. The patient views the doctor's available slots.
2. The patient selects a slot and requests an appointment.
3. The system checks whether the selected slot is still available.
4. The system counts the patient's future Pending and Accepted appointments.
5. If the slot is available and the patient has fewer than N upcoming appointments, the system creates a Pending appointment.
6. The system informs the patient that the request is pending the doctor's decision.

**Alternative flow:**
1. If the slot is no longer available, the system rejects the request and informs the patient.
2. If the patient has already reached N upcoming appointments, the system rejects the request and explains the appointment limit.

## UC3 — Review Appointment Request

**Primary actor:** Doctor

**Preconditions:** A Pending appointment request exists for the doctor.

**Main flow:**
1. The doctor views pending appointment requests.
2. The doctor selects a request.
3. The doctor accepts or declines the request.
4. The system updates the appointment status.
5. The system records the updated status.

**Alternative flow:**
1. If the request is no longer Pending, the system informs the doctor that it cannot be processed again.

## Business Rules

- The chosen value is N = 3 upcoming appointments per patient.
- Only future Pending and Accepted appointments count toward N.
- Declined, Cancelled, and past appointments do not count.
- A time slot cannot be booked by more than one appointment.
- A newly requested appointment starts with Pending status.

## Non-functional Requirements

- Patient medical data must be accessible only to authorized staff.
- Available appointment times should be displayed within 2 seconds.
- The application should be usable on mobile phone screens.
