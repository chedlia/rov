/*
manipulator.c
Intended to control the motion of the manipulator arm(s) attached to the ROV.
 */

/* 
 NOTES: 
 Please place any general notes here. What is a general note? A note that may be needed to further explain why you chose to do something
 and to keep the rest of the code organized and concise. you may also offer ideas.
 Please place your name and time stamp by any contributed note.
 
 Arm location tracker. - Joel Lonbeck February 15, 2009	9:36 PM	
 After some thought it seems nessesary to keep track of the manipulator's location as it moves. 
 unless there is some reading we can take from the hardware that would allow us to determine it's current location.
 Tracking the manipulator location would have several benefits:
 1. use macros - ie. return to default position, extend arm full length.
 2. visualization of current arm position - ie. a display on the controller that might state or display the current arm position.
 The tracker may be needed to calculate the movement nessesary to place the manipulator in the desired posture. 
 I've placed a proposed skeleton function below.
 
 Standard representation of movement.  - Joel Lonbeck February 15, 2009	9:54 PM	
 I think we need to decide on a standard representation of movement for the manipulators (and everything else).
 for example: "1" equals 1 unit of positive movement, 
 and -5 equals 5 units of negative movement. We will also need to decide which way will be positive/negative.
 */	

/*
 Global vars
 */
#define ON 1
#define FORWARD 1
#define OFF 0
#define CLOSED 0
#define REVERSE -1

/*
 This struct is used to keep track of the manipulators position.
 */
struct manip {
	int joint1 = 0;
	int joint2 = 0;
	int joint3 = 0;
	int joint4 = 0;
	int joint5 = 0;
	int gripper = CLOSED;
}

/*
 MOVEJOINT
 a unversal function telling each motor how to move
 @param motor; 1,2,3 etc.
 @param direction; FORWARD, REVERSE
 @param step; how many steps it should make?
 */
function movejoint(int motor, int direction, int step) {
}

/*
 GRIPPER
 controls the gripper's (at the end of the arm) on/off state
 @param state; OFF, ON
 */
function gripper(int state) {	
}

/*
 RESET
 returns the manipulator to the default position.
 */
function reset(){
}

/*
 TRACK
 tracks the movement of the manipulator. This function may be called by movement functions in order to keep the current location of the
 manipulator up to date. The input of the parameters are still unclear. They will need to convey the proposed movement of the manipulator.
 We will need to decide on a standard repesentation of movement.
 @param joint1
 @param joint2
 @param joint3
 @param joint4
 @param joint5
 @param gripper
 */
function track(int joint1, int joint2, int joint3, int joint4, int joint5, int gripper){
}

/*
 STATE
 returns the current state of the manipulator. ie. motor1 is at position 3, motor2 is at position 5, motor3 is at position 1, etc
 @return manip; returns the manip struct
 */
function state(){
	return manip;
}