#include "main.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "VEX V5 Arcade Drive Robot");

	pros::lcd::register_btn1_cb(on_center_button);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	
	// Motor configuration based on your specifications:
	// Left Motor Group : Ports 1, 2, 3
	// Right Motor Group: Ports 4, 5, 6
	
	// Create left side motor group (ports 1 and 2 and 3)
	// pros::MotorGroup left_mg({1, 2, 3});
	pros::MotorGroup left_mg({-1, -2, -3});
	
	
	// Create right side motor group (ports 4 and 5 and 6)  
	// pros::MotorGroup right_mg({4, 5, -6});
	pros::MotorGroup right_mg({4, 5, +6});

	pros::Motor intake(7);

	

	while (true) {
		pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);

		// Arcade control scheme
		// Left joystick up/down (Y-axis) controls forward/backward movement
		int forward = master.get_analog(ANALOG_LEFT_Y);  
		
		// Right joystick left/right (X-axis) controls turning
		int turn = master.get_analog(ANALOG_RIGHT_X);    
		
		int intake_forward = master.get_digital(pros::E_CONTROLLER_DIGITAL_L1);
		int intake_backward = master.get_digital(pros::E_CONTROLLER_DIGITAL_L2);

		// Calculate motor speeds for arcade drive
		// Left side: forward - turn (subtract turn to turn right when joystick pushed right)
		// Right side: forward + turn (add turn to turn right when joystick pushed right)
		int left_speed = forward - turn;
		int right_speed = forward + turn;

		// Set motor speeds
		left_mg.move(left_speed);
		right_mg.move(right_speed);

		// Move intake 
		if (intake_forward){
			intake.move(-127);
		}
		else if(intake_backward){
			intake.move(127);
		}
		else{
			intake.move(0);
		}
		
		// Display current joystick values and motor speeds on LCD for debugging
		pros::lcd::print(1, "Forward: %d, Turn: %d", forward, turn);
		pros::lcd::print(2, "Left: %d, Right: %d", left_speed, right_speed);
		
		// Run for 20 ms then update
		pros::delay(20);
	}
}