
# TASK 1 – Understand the Problem and Identify the Objects

## 1. Problem Statement

The objective of this assignment is to design a Metro Smart-Card Fare System using C++ and Object-Oriented Programming (OOP) concepts.

The system allows passengers to use a smart card for metro travel. It maintains the card balance, calculates journey fares based on the destination zone and travel time, applies eligible passenger concessions, checks peak-hour surcharges, and deducts the fare from the available balance.

The system should be designed to make fare calculation simple, accurate, reliable, and easy to maintain.

## 2. Objectives

- To understand the requirements of a metro smart-card fare system.
- To identify the main objects involved in the system.
- To identify the attributes and behaviours of each object.
- To apply encapsulation, abstraction, inheritance, and polymorphism where appropriate.
- To design a modular and reusable system using C++ classes and objects.

## 3. Identification of Objects

The following objects are identified for the Metro Smart-Card Fare System.

### A. Passenger

**Description:** Represents a person who uses the metro service.

**Attributes:**
- passengerId
- passengerName
- passengerCategory

**Behaviours:**
- Register passenger details.
- Select passenger category.
- Access the metro service.

### B. SmartCard

**Description:** Represents the travel card used by passengers to pay for metro journeys.

**Attributes:**
- cardId
- balance

**Behaviours:**
- Recharge the smart card.
- Check available balance.
- Deduct journey fare.
- Display current balance.

### C. Journey

**Description:** Represents a passenger's metro journey.

**Attributes:**
- sourceZone
- destinationZone
- journeyHour
- journeyMinute

**Behaviours:**
- Select destination zone.
- Enter journey time.
- Validate journey details.

### D. FarePolicy

**Description:** Responsible for calculating the fare based on journey details and applicable fare rules.

**Attributes:**
- baseFare
- peakSurcharge
- concessionPercentage

**Behaviours:**
- Calculate base fare.
- Check peak-hour conditions.
- Apply eligible concessions.
- Calculate final fare.

## 4. Object Relationships

1. A Passenger owns a SmartCard.
2. A Passenger makes a Journey.
3. A Journey is used to request fare calculation.
4. FarePolicy calculates the fare based on journey details and passenger category.
5. SmartCard deducts the calculated fare from its balance.

## 5. Object-Oriented Programming Concepts

### Encapsulation
Encapsulation combines data and functions inside a class. For example, the SmartCard class stores the balance and provides functions to recharge, check, and deduct money.

### Abstraction
Abstraction hides internal implementation details and exposes only the required operations. For example, the passenger can use a fare calculation function without knowing the complete calculation process.

### Inheritance
Inheritance allows a derived class to reuse the properties and behaviours of a base class. Different passenger categories can be represented using suitable derived classes if required by the implementation.

### Polymorphism
Polymorphism allows the same function or interface to perform different operations depending on the object. For example, fare calculation can be customised for different passenger categories.

## 6. Basic System Workflow

1. The passenger selects the destination zone.
2. The system receives the journey time.
3. The system identifies the passenger category.
4. The FarePolicy calculates the base fare.
5. Applicable concession and peak-hour rules are checked.
6. The system verifies whether the smart card has sufficient balance.
7. If the balance is sufficient, the fare is deducted.
8. The updated balance is displayed.

## 7. Conclusion

The Metro Smart-Card Fare System can be designed effectively using C++ Object-Oriented Programming concepts. Identifying the main objects, their attributes, behaviours, and relationships provides a clear foundation for developing a modular, reusable, and maintainable application.
