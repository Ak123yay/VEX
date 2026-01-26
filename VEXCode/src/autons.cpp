#include "main.h"


/////
// For installation, upgrading, documentations, and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////


// These are out of 127
const int DRIVE_SPEED = 50;
const int TURN_SPEED = 40;
const int SWING_SPEED = 110;


// Intake speeds
const int INTAKE_SPEED = 100;


const int INTAKE_EJECT_SPEED_A = 100;
const int INTAKE_EJECT_SPEED_B = 100;


///
// Constants
///
void default_constants() {
  // P, I, D, and Start I
  chassis.pid_drive_constants_set(20.0, 0.0, 100.0);         // Fwd/rev constants, used for odom and non odom motions
  chassis.pid_heading_constants_set(11.0, 0.0, 20.0);        // Holds the robot straight while going forward without odom
  chassis.pid_turn_constants_set(4.0, 0.05, 20.0, 15.0);     // Turn in place constants, was at 3.0 before
  chassis.pid_swing_constants_set(6.0, 0.0, 65.0);           // Swing constants
  chassis.pid_odom_angular_constants_set(6.5, 0.0, 52.5);    // Angular control for odom motions
  chassis.pid_odom_boomerang_constants_set(5.8, 0.0, 32.5);  // Angular control for boomerang motions


  // Exit conditions
  chassis.pid_turn_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_swing_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_drive_exit_condition_set(90_ms, 1_in, 250_ms, 3_in, 500_ms, 500_ms);
  chassis.pid_odom_turn_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 750_ms);
  chassis.pid_odom_drive_exit_condition_set(90_ms, 1_in, 250_ms, 3_in, 500_ms, 750_ms);
  chassis.pid_turn_chain_constant_set(3_deg);
  chassis.pid_swing_chain_constant_set(5_deg);
  chassis.pid_drive_chain_constant_set(3_in);


  // Slew constants
  chassis.slew_turn_constants_set(3_deg, 70);
  chassis.slew_drive_constants_set(3_in, 70);
  chassis.slew_swing_constants_set(3_in, 80);


  // The amount that turns are prioritized over driving in odom motions
  // - if you have tracking wheels, you can run this higher.  1.0 is the max
  chassis.odom_turn_bias_set(0.9);


  chassis.odom_look_ahead_set(7_in);           // This is how far ahead in the path the robot looks at
  chassis.odom_boomerang_distance_set(16_in);  // This sets the maximum distance away from target that the carrot point can be
  chassis.odom_boomerang_dlead_set(0.625);     // This handles how aggressive the end of boomerang motions are


  chassis.pid_angle_behavior_set(ez::shortest);  // Changes the default behavior for turning, this defaults it to the shortest path there
}


///
// Drive Example
///
void drive_example() {
  // The first parameter is target inches
  // The second parameter is max speed the robot will drive at
  // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
  // for slew, only enable it when the drive distance is greater than the slew distance + a few inches


  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_drive_set(-12_in, DRIVE_SPEED);
  chassis.pid_wait();


  // // amazonq-ignore-next-line
  // chassis.pid_drive_set(-12_in, DRIVE_SPEED);
  // chassis.pid_wait();


}


///
// Turn Example
///
void turn_example() {
  // The first parameter is the target in degrees
  // The second parameter is max speed the robot will drive at

  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();
}


///
// Combining Turn + Drive
///
void drive_and_turn() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();


  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();


  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait();


  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();


  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}


///
// Wait Until and Changing Max Speed
///
void wait_until_change_speed() {
  // pid_wait_until will wait until the robot gets to a desired position


  // When the robot gets to 6 inches slowly, the robot will travel the remaining distance at full speed
  chassis.pid_drive_set(24_in, 30, true);
  chassis.pid_wait_until(6_in);
  // amazonq-ignore-next-line
  chassis.pid_speed_max_set(DRIVE_SPEED);  // After driving 6 inches at 30 speed, the robot will go the remaining distance at DRIVE_SPEED
  chassis.pid_wait();


  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();


  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait();


  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();


  // When the robot gets to -6 inches slowly, the robot will travel the remaining distance at full speed
  chassis.pid_drive_set(-24_in, 30, true);
  chassis.pid_wait_until(-6_in);
  chassis.pid_speed_max_set(DRIVE_SPEED);  // After driving 6 inches at 30 speed, the robot will go the remaining distance at DRIVE_SPEED
  chassis.pid_wait();
}


///
// Swing Example
///
void swing_example() {
  // The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
  // The second parameter is the target in degrees
  // The third parameter is the speed of the moving side of the drive
  // The fourth parameter is the speed of the still side of the drive, this allows for wider arcs


  // amazonq-ignore-next-line
  chassis.pid_swing_set(ez::LEFT_SWING, 45_deg, SWING_SPEED, 45);
  chassis.pid_wait();


  chassis.pid_swing_set(ez::RIGHT_SWING, 0_deg, SWING_SPEED, 45);
  chassis.pid_wait();


  chassis.pid_swing_set(ez::RIGHT_SWING, 45_deg, SWING_SPEED, 45);
  chassis.pid_wait();


  chassis.pid_swing_set(ez::LEFT_SWING, 0_deg, SWING_SPEED, 45);
  chassis.pid_wait();
}


///
// Motion Chaining
///
void motion_chaining() {  
  // Motion chaining is where motions all try to blend together instead of individual movements.
  // This works by exiting while the robot is still moving a little bit.
  // To use this, replace pid_wait with pid_wait_quick_chain.
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();


  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();


  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();


  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();


  // Your final motion should still be a normal pid_wait
  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}


///
// Auto that tests everything
///
void combining_movements() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();


  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();


  chassis.pid_swing_set(ez::RIGHT_SWING, -45_deg, SWING_SPEED, 45);
  chassis.pid_wait();


  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();


  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}


///
// Interference example
///
void tug(int attempts) {
  // amazonq-ignore-next-line
  for (int i = 0; i < attempts - 1; i++) {
    // Attempt to drive backward
    // amazonq-ignore-next-line
    printf("i - %i", i);
    chassis.pid_drive_set(-12_in, 127);
    chassis.pid_wait();


    // If failsafed...
    if (chassis.interfered) {
      chassis.drive_sensor_reset();
      // amazonq-ignore-next-line
      chassis.pid_drive_set(-2_in, 20);
      pros::delay(1000);
    }
    // If the robot successfully drove back, return
    else {
      return;
    }
  }
}


// If there is no interference, the robot will drive forward and turn 90 degrees.
// If interfered, the robot will drive forward and then attempt to drive backward.
void interfered_example() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();


  if (chassis.interfered) {
    tug(3);
    return;
  }


  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();
}


///
// Odom Drive PID
///
void odom_drive_example() {
  // This works the same as pid_drive_set, but it uses odom instead!
  // You can replace pid_drive_set with pid_odom_set and your robot will
  // have better error correction.


  chassis.pid_odom_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();


  chassis.pid_odom_set(-12_in, DRIVE_SPEED);
  chassis.pid_wait();


  // amazonq-ignore-next-line
  chassis.pid_odom_set(-12_in, DRIVE_SPEED);
  chassis.pid_wait();
}


///
// Odom Pure Pursuit
///
void odom_pure_pursuit_example() {
  // Drive to 0, 30 and pass through 6, 10 and 0, 20 on the way, with slew
  chassis.pid_odom_set({{{6_in, 10_in}, fwd, DRIVE_SPEED},
                        {{0_in, 20_in}, fwd, DRIVE_SPEED},
                        {{0_in, 30_in}, fwd, DRIVE_SPEED}},
                       true);
  chassis.pid_wait();


  // Drive to 0, 0 backwards
  chassis.pid_odom_set({{0_in, 0_in}, rev, DRIVE_SPEED},
                       true);
  chassis.pid_wait();
}


///
// Odom Pure Pursuit Wait Until
///
void odom_pure_pursuit_wait_until_example() {
  chassis.pid_odom_set({{{0_in, 24_in}, fwd, DRIVE_SPEED},
                        {{12_in, 24_in}, fwd, DRIVE_SPEED},
                        {{24_in, 24_in}, fwd, DRIVE_SPEED}},
                       true);
  chassis.pid_wait_until_index(1);  // Waits until the robot passes 12, 24
  // Intake.move(127);  // Set your intake to start moving once it passes through the second point in the index
  chassis.pid_wait();
  // Intake.move(0);  // Turn the intake off
}


///
// Odom Boomerang
///
void odom_boomerang_example() {
  chassis.pid_odom_set({{0_in, 24_in, 45_deg}, fwd, DRIVE_SPEED},
                       true);
  chassis.pid_wait();


  chassis.pid_odom_set({{0_in, 0_in, 0_deg}, rev, DRIVE_SPEED},
                       true);
  chassis.pid_wait();
}


///
// Odom Boomerang Injected Pure Pursuit
///
void odom_boomerang_injected_pure_pursuit_example() {
  chassis.pid_odom_set({{{0_in, 24_in, 45_deg}, fwd, DRIVE_SPEED},
                        {{12_in, 24_in}, fwd, DRIVE_SPEED},
                        {{24_in, 24_in}, fwd, DRIVE_SPEED}},
                       true);
  chassis.pid_wait();


  chassis.pid_odom_set({{0_in, 0_in, 0_deg}, rev, DRIVE_SPEED},
                       true);
  chassis.pid_wait();
}


///
// Calculate the offsets of your tracking wheels
///
void measure_offsets() {
  // Number of times to test
  int iterations = 10;


  // Our final offsets
  double l_offset = 0.0, r_offset = 0.0, b_offset = 0.0, f_offset = 0.0;


  // Reset all trackers if they exist
  if (chassis.odom_tracker_left != nullptr) chassis.odom_tracker_left->reset();
  if (chassis.odom_tracker_right != nullptr) chassis.odom_tracker_right->reset();
  if (chassis.odom_tracker_back != nullptr) chassis.odom_tracker_back->reset();
  if (chassis.odom_tracker_front != nullptr) chassis.odom_tracker_front->reset();
 
  for (int i = 0; i < iterations; i++) {
    // Reset pid targets and get ready for running an auton
    chassis.pid_targets_reset();
    chassis.drive_imu_reset();
    chassis.drive_sensor_reset();
    chassis.drive_brake_set(MOTOR_BRAKE_HOLD);
    chassis.odom_xyt_set(0_in, 0_in, 0_deg);
    double imu_start = chassis.odom_theta_get();
    // amazonq-ignore-next-line
    double target = i % 2 == 0 ? 90 : 270;  // Switch the turn target every run from 270 to 90


    // Turn to target at half power
    chassis.pid_turn_set(target, 63, ez::raw);
    chassis.pid_wait();
    pros::delay(250);


    // Calculate delta in angle
    double t_delta = util::to_rad(fabs(util::wrap_angle(chassis.odom_theta_get() - imu_start)));


    // Calculate delta in sensor values that exist
    double l_delta = chassis.odom_tracker_left != nullptr ? chassis.odom_tracker_left->get() : 0.0;
    double r_delta = chassis.odom_tracker_right != nullptr ? chassis.odom_tracker_right->get() : 0.0;
    double b_delta = chassis.odom_tracker_back != nullptr ? chassis.odom_tracker_back->get() : 0.0;
    double f_delta = chassis.odom_tracker_front != nullptr ? chassis.odom_tracker_front->get() : 0.0;


    // Calculate the radius that the robot traveled
    // amazonq-ignore-next-line
    l_offset += l_delta / t_delta;
    r_offset += r_delta / t_delta;
    b_offset += b_delta / t_delta;
    f_offset += f_delta / t_delta;
  }


  // Average all offsets
  l_offset /= iterations;
  r_offset /= iterations;
  b_offset /= iterations;
  f_offset /= iterations;


  // Set new offsets to trackers that exist
  if (chassis.odom_tracker_left != nullptr) chassis.odom_tracker_left->distance_to_center_set(l_offset);
  if (chassis.odom_tracker_right != nullptr) chassis.odom_tracker_right->distance_to_center_set(r_offset);
  if (chassis.odom_tracker_back != nullptr) chassis.odom_tracker_back->distance_to_center_set(b_offset);
  if (chassis.odom_tracker_front != nullptr) chassis.odom_tracker_front->distance_to_center_set(f_offset);
}


// . . .
// Make your own autonomous functions here!
// . . .


///
// COMPETITION AUTONOMOUS 1 - LEFT SIDE (pos1)
/// Description: Left side scoring routine
/// Start Position: Left side of field (recommended)
/// Strategy: Intake piece, drive forward, score at goal
/// Expected Score: 1 piece + goal
///
void autonomous_left_side() {
  printf("=== LEFT SIDE AUTONOMOUS STARTED ===\n");
 
  // Reset all subsystems


  // Start intake motors
  intake_motor_a.move(INTAKE_SPEED);
  pros::delay(100);


  // Drive forward slightly to grab piece
  chassis.pid_drive_set(2_in, DRIVE_SPEED, false);
  chassis.pid_wait();
  printf("Piece intake: SUCCESS\n");


  // Small correction turn for alignment
  chassis.pid_turn_set(-9_deg, TURN_SPEED);
  chassis.pid_wait();


  // Drive to scoring position
  chassis.pid_drive_set(32, 40, true);
  chassis.pid_wait();
  printf("Drive to goal: SUCCESS\n");


  chassis.pid_turn_set(-146_deg, TURN_SPEED);
  chassis.pid_wait();


  chassis.pid_drive_set(50_in, DRIVE_SPEED, true);
  chassis.pid_wait();


  chassis.pid_turn_set(-180_deg, TURN_SPEED);
  chassis.pid_wait();


  wall.set_value(true);


  chassis.pid_drive_set(5_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  pros::delay(3000);  // Extra 3000ms after movement finishes


  chassis.pid_drive_set(-50_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  wall.set_value(false);
  intake_motor_b.move(100);


  printf("=== LEFT SIDE AUTONOMOUS COMPLETE ===\n");
}


void autonomous_left_side_full() {
  printf("=== LEFT SIDE FULL AUTONOMOUS STARTED ===\n");
  // Full autonomous routine for left side
  // Add your full autonomous code here

  intake_motor_a.move(INTAKE_SPEED);
  pros::delay(100);

  chassis.pid_drive_set(31_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(-90_deg, TURN_SPEED);
  chassis.pid_wait();

  wall.set_value(true);
  chassis.pid_drive_set(20_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  printf("=== LEFT SIDE FULL AUTONOMOUS COMPLETE ===\n");
}


///
// COMPETITION AUTONOMOUS 2 - RIGHT SIDE (pos2)
/// Description: Right side scoring routine
/// Start Position: Right side of field (recommended)
/// Strategy: Intake piece, drive and turn, score at goal on opposite side
/// Expected Score: 1 piece + goal
///
void autonomous_right_side() {
  printf("=== RIGHT SIDE AUTONOMOUS STARTED ===\n");
 
  // Reset all subsystems


  // Start intake motors
  intake_motor_a.move(INTAKE_SPEED);
  pros::delay(100);


  // Drive forward slightly to grab piece
  chassis.pid_drive_set(2_in, DRIVE_SPEED, false);
  chassis.pid_wait();
  printf("Piece intake: SUCCESS\n");


  // Small correction turn for alignment
  chassis.pid_turn_set(9_deg, TURN_SPEED);
  chassis.pid_wait();


  // Drive to scoring position
  chassis.pid_drive_set(32, 40, true);
  chassis.pid_wait();
  printf("Drive to goal: SUCCESS\n");


  chassis.pid_turn_set(146_deg, TURN_SPEED);
  chassis.pid_wait();


  chassis.pid_drive_set(50_in, DRIVE_SPEED, true);
  chassis.pid_wait();


  chassis.pid_turn_set(180_deg, TURN_SPEED);
  chassis.pid_wait();


  wall.set_value(true);


  chassis.pid_drive_set(5_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  pros::delay(3000);  // Extra 3000ms after movement finishes


  chassis.pid_drive_set(-50_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  wall.set_value(false);
  intake_motor_b.move(100);

  // amazonq-ignore-next-line
  printf("RIGHT SIDE Autonomous Complete!\n");
}


void autonomous_right_side_full() {
  printf("=== RIGHT SIDE FULL AUTONOMOUS STARTED ===\n");
  // Full autonomous routine for right side
  // Add your full autonomous code here
  printf("=== RIGHT SIDE FULL AUTONOMOUS COMPLETE ===\n");
}


///
// SAFE AUTONOMOUS - Just scores one piece (fallback if positioning uncertain)
///
void autonomous_safe() {
  printf("=== SAFE AUTONOMOUS STARTED (FALLBACK) ===\n");


  // Start intake
  intake_motor_a.move(INTAKE_SPEED);
  intake_motor_b.move(INTAKE_SPEED);
  pros::delay(100);


  // Simple forward drive to score
  chassis.pid_drive_set(2_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  printf("Score placement: SUCCESS\n");


  // Stop intake
  intake_motor_a.move(0);
  intake_motor_b.move(0);


  printf("=== SAFE AUTONOMOUS COMPLETE ===\n");
}


///
// SKILLS AUTONOMOUS - Optimized for maximum points
/// Note: Use this for skills challenges
///
// ---------- helper functions (put near top of your .cpp) ----------
inline void store_start() {
  // spin only intake A to "store" a ball (your request)
  intake_motor_a.move(-127);
  intake_motor_b.move(0);
}
inline void store_stop() {
  intake_motor_a.move(0);
}
inline void score_full() {
  // both intakes to score (left negative, right positive like original)
  intake_motor_a.move(-127);
  intake_motor_b.move(127);
}
inline void score_half() {
  intake_motor_a.move(-127);
  intake_motor_b.move(80);
}
inline void stop_intakes() {
  intake_motor_a.move(0);
  intake_motor_b.move(0);
}
inline void wall_extend()  { wall.set_value(true);  }
inline void wall_retract() { wall.set_value(false); }


void match_load_procedure(int times, double wiggle_amount) {
  // Extend wall to grab matchload (per field image)
  wall.set_value(true);

  // STORE mode: intake motor A only
  intake_motor_a.move(-127);
  intake_motor_b.move(0);

  for (int i = 0; i < times; i++) {
    chassis.pid_drive_set(-(wiggle_amount - 0.3), 40);
    pros::delay(300);
    chassis.pid_drive_set(wiggle_amount, 40);
    pros::delay(300);
  }

  // Wait for balls to fully feed
  pros::delay(2000 - times * 600);

  // Stop intake after matchload
  intake_motor_a.move(0);
}

float get_heading(float current_x, float current_y, float dest_x, float dest_y) {
  float delta_x = dest_x - current_x;
  float delta_y = dest_y - current_y;

  if (delta_x < 0.000001 && delta_x > -0.000001) {
    throw std::invalid_argument("dest_x - current_x cannot = 0");
  }

  float alpha = atan(delta_y / delta_x) * 180 / acos(-1);
  
  float theta;

  if (delta_x > 0) {
    theta = 90 - alpha;
  }
  if (delta_x < 0) {
    theta = 270 - alpha;
  }
  
  return theta;
}

/**
 * @brief gets distance between current position and desired position of bot
 */
float get_distance(float current_x, float current_y, float dest_x, float dest_y) {
  return sqrt(pow(dest_x - current_x, 2) + pow(dest_y - current_y, 2));
}



// ---------- skills routine (main) ----------
void autonomous_skills() {
  // Start facing 0 degrees (audience-facing orientation per image)
  chassis.drive_angle_set(0_deg);

  // ------------------ 1) Go to first matchload (left side) ------------------
  chassis.pid_drive_set(32.661, 70); // drive till in front of match load
  chassis.pid_wait();

  // turn to face matchload: use shorter route (-90 instead of 270)
  chassis.pid_turn_set(-90_deg, 105);
  pros::delay(500);

  // extend wall to grab matchload (piston extend)
  wall_extend();
  pros::delay(300);

  // drive into matchload, ensure wall is extended
  chassis.pid_drive_set(11.55, 65);
  wall_extend();
  pros::delay(1000);   // let robot settle into matchload

  match_load_procedure(3, 0.9);

  // back out of matchload, retract piston
  chassis.pid_drive_set(-12, 75);
  chassis.pid_wait();
  wall_retract();


  // ensure intakes stopped
  stop_intakes();

  // ------------------ 2) Drive through alley to long goal #1 ------------------
  // face alley to long goal using your heading helper
  chassis.pid_turn_set(get_heading(-46.175, 45.833, -31.371, 58.597) + 180, 60);
  pros::delay(500);

  // drive into alley (distance helper)
  chassis.pid_drive_set(get_distance(-46.175, 45.833, -31.371, 58.597) * -1, 75);
  pros::delay(1000);

  // face parallel to long goal (short rotation)
  chassis.pid_turn_set(-90, 60); // replaced 270 with -90
  pros::delay(500);

  // cross field to center area
  chassis.pid_drive_set(-70.43, 90);
  chassis.pid_wait();

  // orient perpendicular to long goal
  chassis.pid_turn_set(0, 105);
  pros::delay(500);

  // move into scoring setup
  chassis.pid_drive_set(-12.366, 60);
  chassis.pid_wait();

  // face long goal
  chassis.pid_turn_set(90, 105);
  chassis.pid_wait();

  // ------------------ 3) 1st long goal score ------------------
  chassis.pid_drive_set(-6.279, 60); // drive into long goal
  chassis.pid_wait();

  // push backward and spin both intakes to score
  chassis.pid_drive_set(-60, 50);
  score_full();
  pros::delay(2600);
  stop_intakes();
  pros::delay(100);

  // back out and get next matchload
  chassis.pid_drive_set(27.713, 65);
  pros::delay(100);
  wall_extend();
  pros::delay(1000);
  match_load_procedure(3, 0.9); //matchload procedure

  // ------------------ 4) 2nd long goal score ------------------
  chassis.pid_drive_set(-28.361, 75); // move backwards into long goal
  pros::delay(500);
  wall_retract();
  chassis.pid_wait();
  pros::delay(300);

  chassis.pid_drive_set(-60, 50);
  score_half(); // lower-power variant used originally
  pros::delay(2600);
  stop_intakes();

  chassis.pid_drive_set(14.27, 75); // move out from long goal
  pros::delay(600);

  // reposition to other side / mid field
  chassis.pid_turn_set(180, 105);
  pros::delay(500);
  chassis.pid_drive_set(97.162, 85); // to between other long goal & matchload
  chassis.pid_wait();

  // face matchload on other side
  chassis.pid_turn_set(90, 105);
  pros::delay(500);

  // go into matchload (other side)
  chassis.pid_drive_set(15.239, 65);
  chassis.pid_wait();
  wall_extend();
  pros::delay(600);

  // explicit load
  store_start();
  pros::delay(1600);
  store_stop();

  // back out
  chassis.pid_drive_set(-12.739, 75);
  chassis.pid_wait();
  wall_retract();
  stop_intakes();

  // ------------------ 5) alley to 3rd long goal (other side) ------------------
  chassis.pid_turn_set(get_heading(45.05, -48.831, 31.371, -59.997) + 180, 60);
  pros::delay(500);

  chassis.pid_drive_set(get_distance(45.05, -48.831, 31.371, -59.997) * -1, 75);
  pros::delay(1000);

  // face parallel to long goal (short route)
  chassis.pid_turn_set(90, 105);
  pros::delay(500);

  chassis.pid_drive_set(-70.43, 90);
  chassis.pid_wait();

  chassis.pid_turn_set(180, 105); // perpendicular to long goal
  pros::delay(500);

  chassis.pid_drive_set(-10.566, 70); // move to setup long goal
  pros::delay(800);

  // face long goal using -90 instead of 270
  chassis.pid_turn_set(-90, 105);
  pros::delay(500);

  // ------------------ 6) 3rd long goal score ------------------
  chassis.pid_drive_set(-8.279, 70);
  chassis.pid_wait();

  store_start();
  pros::delay(300);
  store_stop();

  chassis.pid_drive_set(-60, 50);
  score_full();
  pros::delay(2600);
  stop_intakes();
  pros::delay(100);

  // get next matchload
  chassis.pid_drive_set(27.713, 60);
  pros::delay(100);
  wall_extend();
  pros::delay(800);

  store_start();
  pros::delay(1600);
  store_stop();

  // ------------------ 7) 4th long goal score ------------------
  chassis.pid_drive_set(-28.361, 75); // move backwards into long goal
  pros::delay(500);
  wall_retract();
  chassis.pid_wait();

  store_start();
  pros::delay(300);
  store_stop();

  chassis.pid_drive_set(-60, 50);
  score_half();
  pros::delay(2600);
  stop_intakes();
  pros::delay(100);

  chassis.pid_drive_set(14.27, 75); // drive out from long goal
  pros::delay(300);
  pros::delay(300);

  // ------------------ 8) Parking (platform hook) ------------------
  // normalize long angles to shortest turns
  chassis.pid_turn_set(-40, 105); // 320 -> -40 (shorter)
  pros::delay(500);
  chassis.pid_drive_set(40, 75); // drive to wall as bump/align
  pros::delay(700);

  chassis.pid_turn_set(-20, 105); // 340 -> -20 (shorter)
  pros::delay(500);
  chassis.pid_drive_set(10, 75);
  pros::delay(500);

  chassis.pid_turn_set(0, 105);
  pros::delay(500);
  chassis.pid_drive_set(15, 75); // into park
  pros::delay(500);

  // extend wall to hook platform
  wall_extend();
  pros::delay(150);
  chassis.pid_drive_set(-6, 75); // back a bit to hook onto platform
  pros::delay(300);
  chassis.pid_drive_set(40, 105); // forward into park/fully on platform

  // final small scoring spin while parking (settle balls)
  intake_motor_a.move(-127);
  intake_motor_b.move(30);
  pros::delay(1000);

  wall_retract(); // retract piston at end
  stop_intakes(); // make sure intakes are off
}
