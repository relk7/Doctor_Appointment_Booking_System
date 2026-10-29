#Sequence Diagram — Appointment Booking
```mermaid
sequenceDiagram
    actor Patient
    participant System as AppointmentService
    participant Doctor
    participant Appointment

    Patient->>System: viewAvailability(doctorId)
    System->>Doctor: getAvailableSlots()
    Doctor-->>System: availableSlots
    System-->>Patient: displayAvailableSlots

    Patient->>System: requestAppointment(doctorId, dateTime)
    System->>System: checkSlotAvailability()
    System->>System: countUpcomingAppointments()

    alt Slot available AND count less than N
        System->>Appointment: create Pending appointment
        Appointment-->>System: appointmentCreated
        System-->>Patient: booking request pending
    else Slot unavailable OR count reached N
        System-->>Patient: reject request with reason
    end

    Doctor->>System: reviewRequest(appointmentId, decision)
    System->>Appointment: update status
    Note over System,Appointment: Decision is Accept or Decline
    Appointment-->>System: updated status
    System-->>Patient: notify appointment outcome
    ```
