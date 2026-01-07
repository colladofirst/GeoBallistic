# Geodesic Distance & Idealized Projectile Model (C++)

C++ program that computes the geodesic distance between two points on Earth
using the Haversine formula and explores an idealized classical physics model
to estimate velocities, forces and energies.

  ⚠️⚠️⚠️ **Disclaimer**  ⚠️⚠️⚠️

This project is purely theoretical and educational.  
It relies on highly simplified classical models and does **not** represent
real-world ballistic, aerospace or physical systems.

---

## Description

This personal learning project combines basic geodesy and classical mechanics.
First, the geodesic distance between two points on Earth is calculated using the
Haversine formula. Then, this distance is used in a **simplified** classical model
to estimate initial velocities, launch forces and mechanical energy.

The objective of the project is to explore orders of magnitude, model limitations
and the importance of physical assumptions, rather than to simulate real systems.

---

## Features

- Geodesic distance computation on a spherical Earth (Haversine formula)
- Input validation for coordinate format `(x, y)`
- Conversion between degrees and radians
- Idealized decomposition of velocity and force vectors
- Classical validity checks (non-relativistic regime)
- Estimation of:
  - Initial velocity components
  - Launch force vector
  - Mechanical energy (kinetic + potential)

---

## Physical Model and Assumptions

This project uses a **highly idealized classical model**:

- No air resistance
- No gravity during motion
- No guidance or control systems
- No real ballistic trajectory simulation
- Constant acceleration during launch
- Flat classical (Newtonian) framework

As a result, the numerical values obtained for short travel times can become
extremely large. This behavior is **expected** and highlights the limitations
of simplified models.

---

## What I Learned

- Implementation of mathematical formulas that imply elemental functions (sin, cos, sqrt...)
- Handling user input and validation in C++
- Structuring code using functions and data structures
- Vector decomposition in classical mechanics
- Identifying the limits of applicability of physical models
- Writing clearer and more maintainable code through refactoring

---

## Possible Improvements

- Refactor input handling for greater robustness
- Use `std::string` instead of raw character input
- Support UTF-8 paths and international input
- Introduce gravity and trajectory simulation
- Improve numerical stability and unit handling
- Introduce air resistance and less idealized mechanism
- Implement a Relativity work model for v>≈90%c
- Computation of other physics variables such as W,P,etc
- Implement a more realistic launch mechanism
- Implement mathematical|visual functions to represent the movement beetween the Earth.

---

