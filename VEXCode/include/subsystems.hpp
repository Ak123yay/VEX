#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"

extern Drive chassis;
//vex me gusta
// Controller
inline pros::Controller master(pros::E_CONTROLLER_MASTER);

// Global variables for piston and intake states
inline bool p1_state, p2_state, p3_state, p4_state;
inline bool r1_intake_state = false;

// Intake motors
inline pros::Motor intake_motor_a(20);
inline pros::Motor intake_motor_b(-11);

// Pneumatic pistons
inline pros::adi::DigitalOut Middle('A');
inline pros::adi::DigitalOut Wall('B');
inline pros::adi::DigitalOut Descore('C');
inline pros::adi::DigitalOut Aligner('D');

// Piston aliases for lowercase usage
inline auto& middle = Middle;
inline auto& wall = Wall;
inline auto& descore = Descore;
inline auto& aligner = Aligner;