#pragma once

void default_constants();

void drive_example();
void turn_example();
void drive_and_turn();
void wait_until_change_speed();
void swing_example();
void motion_chaining();
void combining_movements();
void interfered_example();
void odom_drive_example();
void odom_pure_pursuit_example();
void odom_pure_pursuit_wait_until_example();
void odom_boomerang_example();
void odom_boomerang_injected_pure_pursuit_example();
void measure_offsets();

// ========== COMPETITION AUTONOMOUS ROUTINES ==========
void autonomous_left_side();   // Left side scoring routine
void autonomous_left_side_full();
void autonomous_right_side_full();
void autonomous_right_side();  // Right side scoring routine
void autonomous_safe();        // Safe fallback routine
void autonomous_skills();      // Skills challenge routine
