#ifndef SERVO_H
#define SERVO_H

enum DetectorState {ACTIVE, INACTIVE};
enum ServoState {CALLIB, IDLE, IN_PROGRESS};

struct Servo{
	enum ServoState eState;
	unsigned int uiCurrentPosition;
	unsigned int uiDesiredPosition;
};
extern struct Servo sServo;

void DetectorInit(void);
enum DetectorState eReadDetector(void);
void Automat(void);
void ServoInit(unsigned int uiServoFrequency);
void ServoCallib(void);
void ServoGoTo(unsigned int uiPosition);

#endif
