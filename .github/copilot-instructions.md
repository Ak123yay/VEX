# VEX Robotics V5 Project - Copilot Instructions

## Repository Overview

This is a **VEX Robotics V5** competition robot project for **team 67**. The repository contains autonomous and operator control code for a VEX V5 robot, built using the **PROS** (Purdue Robotics Operating System) framework with the **EZ-Template** library for simplified robot control.

### Project Type
- **Platform**: VEX V5 Brain
- **Framework**: PROS (Purdue Robotics Operating System) v4.1.1
- **Language**: C++20
- **Build System**: GNU Make with ARM GCC cross-compiler toolchain

### Key Libraries & Dependencies
- **PROS Kernel**: 4.1.1 (core VEX V5 robotics API)
- **EZ-Template**: 3.2.2 (simplified chassis control and autonomous routines)
- **OkapiLib**: 5.0.0 (advanced robotics library with control theory implementations)
- **liblvgl**: 8.3.8 (LVGL graphics library for brain screen UI)
- Pre-compiled firmware libraries in `VEXCode/firmware/` directory

## Project Structure

```
VEX/
└── VEXCode/                    # Main project directory
    ├── src/                    # Source files
    │   ├── main.cpp           # Main robot code (391 lines)
    │   └── autons.cpp         # Autonomous routines (979 lines)
    ├── include/               # Header files
    │   ├── main.h            # Main header with includes
    │   ├── autons.hpp        # Autonomous function declarations
    │   ├── subsystems.hpp    # Robot subsystems (motors, pistons)
    │   ├── EZ-Template/      # EZ-Template library headers
    │   ├── pros/             # PROS API headers
    │   ├── okapi/            # OkapiLib headers
    │   └── liblvgl/          # LVGL UI library headers
    ├── firmware/             # Pre-compiled libraries (.a files)
    ├── Makefile              # Build configuration
    ├── common.mk             # Common make rules
    ├── project.pros          # PROS project metadata
    └── .clang-format         # Code formatting rules
```

## Robot Hardware Configuration

### Drive System
- **Chassis Type**: Tank drive with 3 motors per side (6 motors total)
- **Left Motors**: Ports 4, 2, -3 (negative = reversed)
- **Right Motors**: Ports -10, -9, 8 (negative = reversed)
- **Wheel Diameter**: 3.25 inches
- **Wheel RPM**: 360 (cartridge * motor gear / wheel gear)
- **IMU**: Port 6

### Subsystems
- **Intake Motors**:
  - Motor A: Port 11
  - Motor B: Port -20 (reversed)
- **Pneumatic Pistons** (ADI ports):
  - Middle: Port 'A'
  - Wall: Port 'B'
  - Descore: Port 'C'
  - Aligner: Port 'D'

## Code Architecture

### Main Components

1. **main.cpp** - Contains:
   - `initialize()`: Robot initialization, IMU calibration, autonomous selector setup
   - `autonomous()`: Autonomous mode entry point (calls selected routine)
   - `opcontrol()`: Driver control (tank drive, intake control, piston toggles)
   - `disabled()`: Called when robot is disabled
   - `ez_screen_task()`: Brain screen display task (odometry, temps, battery)

2. **autons.cpp** - Contains:
   - `default_constants()`: PID tuning constants for drive, turn, swing, odometry
   - Competition autonomous routines (left side, right side, skills, etc.)
   - Example/test autonomous routines for debugging
   - Helper functions: `store_start()`, `score_full()`, `match_load_procedure()`, etc.

3. **subsystems.hpp** - Defines:
   - Global robot hardware objects (motors, pistons, controller)
   - State variables for pistons and intake modes
   - Hardware aliases for convenience

### Control Scheme (Driver Control)

**Intake Control** (priority-based):
- **R1**: Toggle intake mode (motor A only, for storing)
- **R2**: Manual intake (both motors forward, for scoring)
- **L1**: Reverse intake (both motors backward)
- **L2**: Eject mode (motor A forward, motor B reverse)

**Piston Control** (toggle):
- **UP**: Middle piston
- **DOWN**: Wall piston (disabled if B pressed to avoid autonomous trigger)
- **LEFT**: Descore piston
- **RIGHT**: Aligner piston

**Debug Controls** (when not connected to competition switch):
- **X**: Toggle PID tuner GUI
- **DOWN + B**: Run selected autonomous in opcontrol

## Building the Project

### Prerequisites

⚠️ **CRITICAL BUILD REQUIREMENT**: This project requires the **ARM GCC embedded toolchain** which is **not pre-installed** in standard CI/GitHub Actions environments and requires explicit installation.

Required tools:
- `arm-none-eabi-gcc` (ARM cross-compiler)
- `arm-none-eabi-g++` (ARM C++ cross-compiler)
- `arm-none-eabi-ar`, `arm-none-eabi-objcopy`, etc.
- GNU Make 4.x+
- PROS CLI (optional, for managing dependencies and uploading to robot)

### Build Commands

```bash
cd VEXCode
make              # Build the project (default target: quick)
make clean        # Clean build artifacts
make all          # Full build
```

### Build Outputs
- `bin/monolith.bin` - Full program binary
- `bin/cold.package.bin` - Cold image (libraries)
- `bin/hot.package.bin` - Hot image (user code)

### Known Build Issues & Workarounds

#### Issue 1: ARM Toolchain Not Found
**Error**: `arm-none-eabi-g++: not found`

**Cause**: The ARM GCC embedded toolchain is not installed in the environment.

**Workaround**: 
1. For local development, install the ARM toolchain:
   - **Linux**: `sudo apt-get install gcc-arm-none-eabi`
   - **macOS**: `brew install arm-none-eabi-gcc`
   - **Windows**: Download from [ARM Developer](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm)
   
2. For CI/CD: Install the ARM toolchain in your CI workflow. Example for GitHub Actions:
   ```yaml
   - name: Install ARM toolchain
     run: sudo apt-get update && sudo apt-get install -y gcc-arm-none-eabi
   ```
   Or use a pre-configured Docker container with the toolchain included.

**Note**: Building for VEX V5 is primarily done locally and uploaded directly to the robot hardware. Continuous integration is **not typically used** for VEX robotics projects, but can be configured if desired.

## Code Style & Conventions

### Formatting
- **Style Guide**: Based on Google C++ Style Guide
- **Column Limit**: None (unlimited line length)
- **Indentation**: 2 spaces
- **Tab Width**: 2 spaces
- **Formatter**: `.clang-format` file is provided

### C++ Standard
- **C Standard**: `gnu11`
- **C++ Standard**: `gnu++20`
- **Extra Flags**: `-Wno-deprecated-enum-enum-conversion`

### Naming Conventions
- **Functions**: `snake_case` (e.g., `drive_example()`, `match_load_procedure()`)
- **Variables**: `snake_case` (e.g., `p1_state`, `intake_motor_a`)
- **Constants**: `UPPER_SNAKE_CASE` (e.g., `DRIVE_SPEED`, `INTAKE_SPEED`)
- **Classes**: Not extensively used (EZ-Template uses `ez::Drive` class)

### Code Organization
- Keep autonomous routines in `autons.cpp`
- Keep robot hardware definitions in `subsystems.hpp`
- Keep main control logic in `main.cpp`
- Use inline helper functions for repeated operations (e.g., `store_start()`, `score_full()`)

## Common Development Tasks

### Adding a New Autonomous Routine

1. **Declare** the function in `include/autons.hpp`:
   ```cpp
   void my_new_auton();
   ```

2. **Implement** the function in `src/autons.cpp`:
   ```cpp
   void my_new_auton() {
     chassis.pid_targets_reset();
     chassis.drive_imu_reset();
     chassis.drive_sensor_reset();
     
     // Your autonomous code here
     chassis.pid_drive_set(24_in, 110);  // Drive 24 inches at speed 110
     chassis.pid_wait();
   }
   ```

3. **Add to selector** in `src/main.cpp` `initialize()`:
   ```cpp
   ez::as::auton_selector.autons_add({
     {"My Auton\n\nDescription here", my_new_auton},
     // ... other autons
   });
   ```

### Tuning PID Constants

1. Enable PID tuner by pressing **X** on controller (when not connected to competition switch)
2. Use arrow keys to navigate constants
3. Use **A** and **Y** buttons to increment/decrement values
4. Once satisfied, update `default_constants()` in `autons.cpp` with the tuned values

### Adding a New Motor/Sensor

1. **Define hardware** in `include/subsystems.hpp`:
   ```cpp
   inline pros::Motor my_motor(PORT_NUMBER);  // positive or negative for direction
   ```

2. **Use in code** (motors are globally accessible):
   ```cpp
   my_motor.move(127);  // Full speed forward
   my_motor.move(-127); // Full speed reverse
   my_motor.move(0);    // Stop
   ```

### Debugging Tips

1. **Brain Screen Output**: Use `ez::screen_print()` in `ez_screen_task()` to display debug info
2. **Controller Rumble**: `master.rumble(".")` for success, `master.rumble("---")` for error
3. **LLEMU Auton Selector**: Shows currently selected autonomous on brain screen
4. **Test Autonomous in Driver Control**: Press DOWN + B when not connected to competition switch

## EZ-Template Specifics

### Movement Functions
- `chassis.pid_drive_set(distance, speed, slew)` - Drive forward/backward
- `chassis.pid_turn_set(angle, speed)` - Turn in place
- `chassis.pid_swing_set(angle, direction, speed)` - Swing turn
- `chassis.pid_wait()` - Wait for movement to complete
- `chassis.pid_wait_until(distance)` - Wait until robot reaches distance

### Odometry Functions
- `chassis.odom_xyt_set(x, y, theta)` - Set current position
- `chassis.odom_drive_set(x, y, speed)` - Drive to point
- `chassis.odom_turn_set(angle, speed)` - Turn to angle
- `chassis.pid_odom_set({{x1, y1}, {x2, y2}, ...}, speed)` - Pure pursuit path

### Units (from OkapiLib)
Use `_in`, `_deg` literals for chassis movements (OkapiLib provides these):
```cpp
chassis.pid_drive_set(24_in, 110);     // 24 inches
chassis.pid_turn_set(90_deg, 90);      // 90 degrees
```

Note: For delays, use plain integers (milliseconds):
```cpp
pros::delay(500);  // 500 milliseconds
```

## Testing

This project **does not have automated tests**. Testing is done by:
1. **Uploading to robot** and running autonomous/driver control
2. **Using test autonomous routines** (e.g., `drive_example()`, `turn_example()`)
3. **Competition testing** in practice matches

To test changes:
- Build the project: `make`
- Upload to robot: Use PROS CLI (`pros upload`) or VEX Brain Utility
- Select test autonomous on brain screen
- Run and observe robot behavior

## Important Notes for AI Coding Agents

### What NOT to Do
1. ❌ **Do NOT try to build this project in CI without installing ARM toolchain first** - it will fail with `arm-none-eabi-g++: not found`
2. ❌ **Do NOT add automated testing infrastructure** - VEX projects are tested on physical hardware
3. ❌ **Do NOT modify firmware libraries** - these are pre-compiled and project-specific
4. ❌ **Do NOT change the C++ standard** - VEX V5 requires C++20
5. ❌ **Do NOT remove or significantly modify PID constants** without understanding their purpose

### What TO Do
1. ✅ **Maintain code style** as defined in `.clang-format`
2. ✅ **Keep autonomous routines modular** and well-commented
3. ✅ **Document hardware changes** if motor/sensor ports are modified
4. ✅ **Test critical changes** by describing the expected robot behavior
5. ✅ **Preserve existing autonomous routines** - they are competition-critical
6. ✅ **Use helper functions** to avoid code duplication
7. ✅ **Follow EZ-Template patterns** for consistency

### Common Code Patterns
- **PID Drive**: Always reset sensors before autonomous
  ```cpp
  chassis.pid_targets_reset();
  chassis.drive_imu_reset();
  chassis.drive_sensor_reset();
  ```
- **Wait for movement**: Use `chassis.pid_wait()` after movement commands
- **Delays**: Use `pros::delay()` with milliseconds
- **Motor control**: Use `.move()` with values -127 to 127

## External Resources

- [EZ-Template Documentation](https://ez-robotics.github.io/EZ-Template/)
- [PROS Documentation](https://pros.cs.purdue.edu/)
- [OkapiLib Documentation](https://okapilib.github.io/OkapiLib/)
- [VEX V5 API](https://api.vex.com/)

## Competition Context

This robot participates in VEX V5 robotics competitions. Key considerations:
- **Autonomous period**: 15 seconds at start of match
- **Driver control period**: 1 minute 45 seconds after autonomous
- **Skills challenge**: 1 minute to score maximum points
- **Robot must be competition-ready**: Code should be reliable and well-tested

## Summary

When working on this repository, remember:
- This is embedded robotics code for VEX V5 hardware
- Building requires ARM GCC toolchain (must be installed explicitly in CI environments)
- Code is tested on physical robot hardware, not through automated tests
- EZ-Template provides high-level control abstractions
- PID constants are carefully tuned for this specific robot configuration
- Competition reliability is paramount - avoid breaking changes to working code
