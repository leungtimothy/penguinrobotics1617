#ifndef AUTO_FUNCTIONS_H
#define AUTO_FUNCTIONS_H

enum Turn_Directions { LEFT, RIGHT };

/**
 * Use this function command the robot to rotate about its Z axis using the data
 * obtained via the gyroscope.
 *
 * @param turnDirection Choose LEFT or RIGHT for direction of turn.
 * @param targetDegrees the amount of degrees the robot will rotate relative to
 * its original bearing.
 *
 */
void driveGyroTurn(enum Turn_Directions turnDirection, int targetDegrees);
void driveHolo(int distance, int power);
void driveHoloTest(int bearing, int distance, int power);

#endif
