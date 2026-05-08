# Public Transport Simulation System

Production-grade C++ simulation of an urban public transportation ecosystem with support for multiple transport categories, route management, passenger interaction, station systems, and dynamic street-network traversal.

## Overview

This project models a realistic metropolitan transportation environment inspired by the city infrastructure of Izmir. The system simulates:

* Public and private transportation vehicles
* Underground and above-ground stations
* Connected street networks
* Passenger movement and decision-making
* Route pricing and zone-based transportation
* Accessibility-aware transit systems
* Multi-modal transportation support

The architecture is object-oriented and heavily based on inheritance, polymorphism, encapsulation, and graph traversal concepts.

---

## Core Features

### Transportation System

Supports multiple transportation categories:

| Category                     | Types            |
| ---------------------------- | ---------------- |
| Large Public Transport       | Bus, Tram, Metro |
| Small Driver-Based Transport | Taxi, Dolmuş     |
| Self-Service Transport       | Bicycle, Scooter |

### Passenger Simulation

Passengers can:

* Select a current location
* Choose a destination
* Calculate transport eligibility
* Enter and leave vehicles
* Use stations
* Apply discounts based on status
* Spend from a configurable budget

### Street Network Engine

The project models a connected urban graph:

* One-way streets
* Two-way streets
* Underground roads
* Maritime-compatible roads
* Distance calculations
* Shortest reachable station detection

### Route Management

Routes contain:

* Ordered station traversal
* Vehicle assignment
* Ticket pricing
* Route membership validation

### Station Types

#### Above-Ground Stations

* Standard passenger entry
* Connected to surface transportation

#### Underground Stations

* Accessibility-aware design
* Lift/escalator entry support
* Underground transit integration

---

# Architecture

## Project Structure

```text
publicTransportSimulation/
├── build/
│   └── CMakeLists.txt
├── src/
│   ├── enum/
│   ├── prevoz/
│   │   ├── imaVozaca/
│   │   │   ├── veliko/
│   │   │   └── malo/
│   │   └── samousluzno/
│   ├── putnik/
│   ├── ruta/
│   ├── stanica/
│   │   ├── nadzemna/
│   │   └── podzemna/
│   ├── ulica/
│   └── main.cpp
```

---

## Class Hierarchy

### Transportation Layer

```text
Prevoz
├── ImaVozaca
│   ├── Veliko
│   │   ├── Autobus
│   │   ├── Tramvaj
│   │   └── Metro
│   └── Malo
│       ├── Taksi
│       └── Dolmus
└── Samousluzno
    ├── Bicikl
    └── Trotinet
```

### Station Layer

```text
Stanica
├── Nadzemna
└── Podzemna
```

---

# Technical Concepts

## Object-Oriented Programming

The system demonstrates:

* Abstract classes
* Virtual methods
* Runtime polymorphism
* Encapsulation
* Composition
* Inheritance
* Operator overloading
* Dynamic dispatch

## Algorithms and Data Structures

Implemented concepts include:

* Graph traversal
* Shortest-path distance calculations
* Vector-based route storage
* Dynamic adjacency relationships
* Linked street connectivity

## Memory Management

The project uses:

* Raw pointers
* Dynamic object relationships
* Shared entity references
* Centralized simulation ownership

---

# Build Instructions

## Requirements

* C++14 compatible compiler
* CMake >= 3.10

Supported compilers:

* GCC
* Clang
* MSVC

---

## Build

```bash
git clone <repository-url>
cd publicTransportSimulation

mkdir build-output
cd build-output

cmake ../build
cmake --build .
```

---

## Run

```bash
./izmir
```

On Windows:

```powershell
izmir.exe
```

---

# Simulation Flow

The application initializes:

1. Street network
2. Transport vehicles
3. Transportation routes
4. Stations
5. Passenger entities

The user then:

1. Enters personal information
2. Chooses current location
3. Selects a destination
4. Receives available transportation options
5. Uses the transportation system interactively

---

# Example Domain Objects

## Streets

Examples included in the simulation:

* Kordonboyu
* Alsancak
* Konak Meydanı
* Balçova
* Güzelbahçe

## Transport Vehicles

Examples included:

* Metro lines
* Tram systems
* Public buses
* Taxi services
* Shared scooters
* Shared bicycles

---

# Accessibility Support

The system supports accessibility-aware transportation logic.

Examples:

* Passenger disability status
* Underground lift access
* Discount support
* Route compatibility validation

---

# Pricing System

Transportation pricing is zone-aware.

Supported mechanisms:

* Flat route pricing
* Zone-based taxi pricing
* Passenger discounts
* Budget tracking

---

# Design Strengths

## Extensible Architecture

New vehicle types, station types, and routing strategies can be added with minimal modification to existing code.

## Modular Organization

Each domain entity is isolated in its own module:

* Transport
* Passenger
* Route
* Street
* Station

## High Cohesion

Each class owns a clearly defined responsibility.

## Low Coupling

Dependencies are primarily interface-driven through abstract base classes.

---

# Potential Future Improvements

## Recommended Enhancements

* Smart route optimization
* Dijkstra/A* shortest path engine
* Real-time traffic simulation
* Multithreaded simulation engine
* GUI visualization
* JSON configuration loading
* Persistent storage layer
* Unit testing framework
* Event-driven simulation loop
* Logging infrastructure
* Smart ticketing system
* Time-based scheduling
* Fuel and battery simulation

---

# Sample Technologies Used

* C++14
* STL
* CMake
* Object-Oriented Design
* Graph Modeling

---

# Educational Value

This project is suitable for demonstrating:

* Advanced OOP principles
* Simulation architecture
* Transport system modeling
* Graph-based navigation
* C++ project organization
* Polymorphic design

It is appropriate for:

* University projects
* OOP coursework
* Software engineering demonstrations
* System modeling assignments
* C++ portfolio projects

---

# License

This project is intended for educational and academic purposes unless otherwise specified.

---

# Author

Public Transport Simulation System
Built in modern C++ using modular object-oriented architecture.
