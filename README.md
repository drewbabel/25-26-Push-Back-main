# VEX V5 Arcade Drive Robot

A simple arcade drive robot program for VEX V5 using the PROS development environment.

## Motor Configuration

The robot uses a 4-motor drivetrain with the following port assignments:

- **Port 1**: Top Right Motor
- **Port 2**: Bottom Right Motor  
- **Port 3**: Top Left Motor
- **Port 4**: Bottom Left Motor

## Controls

The robot uses arcade drive control scheme:

- **Left Joystick (Y-axis)**: Forward/Backward movement
  - Push up = Move forward
  - Push down = Move backward
  
- **Right Joystick (X-axis)**: Turning
  - Push right = Turn right
  - Push left = Turn left

## Features

- **Simultaneous Movement**: You can move forward/backward and turn at the same time
  - Example: Push left joystick forward and right joystick right = Move in a clockwise circle
  - Example: Push left joystick forward and right joystick left = Move in a counter-clockwise circle

- **LCD Display**: Shows real-time joystick values and calculated motor speeds for debugging

## Building and Running

1. Make sure you have the ARM GCC toolchain installed for VEX V5
2. Connect your VEX V5 brain to your computer
3. Run the following commands:

```bash
# Build the project
pros make

# Upload to robot
pros upload

# Or build and upload in one step
pros mu
```

## Development

This project uses PROS 4 with the V5 kernel. The main logic is in `src/main.cpp` in the `opcontrol()` function which handles the operator control period.

## Motor Direction Notes

The motor groups are configured with appropriate reversals to ensure:
- Both left motors spin in the same direction
- Both right motors spin in the same direction  
- Forward joystick input makes the robot move forward
- Right turn input makes the robot turn right

If your robot moves in unexpected directions, you may need to adjust the motor reversals in the code by adding or removing the minus signs in the MotorGroup constructors. 