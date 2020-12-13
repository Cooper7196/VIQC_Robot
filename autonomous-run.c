#pragma config(Sensor, port4,  gyro,           sensorVexIQ_Gyro)
#pragma config(Motor,  motor1,          left,          tmotorVexIQ, PIDControl, encoder)
#pragma config(Motor,  motor2,          right,         tmotorVexIQ, PIDControl, reversed, encoder)
#pragma config(Motor,  motor3,          side,          tmotorVexIQ, PIDControl, encoder)
#pragma config(Motor,  motor5,          rightArmMotor, tmotorVexIQ, PIDControl, encoder)
#pragma config(Motor,  motor6,          leftArmMotor,  tmotorVexIQ, PIDControl, reversed, encoder)
#pragma config(Motor,  motor10,         frontClaw,     tmotorVexIQ, PIDControl, encoder)


void rotate(float angle){
	while(abs(getGyroHeading(gyro) - angle) > 4){
    writeDebugStreamLine("%d", getGyroHeading(gyro));
		float angleDifference = abs(getGyroHeading(gyro) - angle);
		float speed = (angleDifference - 0) / (180 - 0) * (100 - 10) + 10;
		writeDebugStreamLine("%d", angleDifference );
		if(getGyroHeading(gyro) > angle){// && abs(getGyroHeading(gyro) - angle) > 40){
				motor[left] = speed;
				motor[right] = -speed;
		}
		else if(getGyroHeading(gyro) < angle){// && abs(getGyroHeading(gyro) - angle) > 40){
				motor[left] = -speed;
				motor[right] = speed;
		}
	}
	motor[left] = 0;
	motor[right] = 0;
}

void strafe(int amount){
	if(amount > 0){
		motor[side]	= 100;
	}
	else if(amount < 0){
		motor[side] = -100;
	}
	else{
		motor[side] = 0;
	}
	while(abs(getMotorEncoder(side) - amount) > 40){}
	motor[side] = 0;
}

void drive(int amount){
	if(amount > 0){
		motor[left]	= 100;
		motor[right]	= 100;
	}
	else if(amount < 0){
		motor[left]	= -100;
		motor[right]	= -100;
	}
	else{
		motor[left]	= 0;
		motor[right] = 0;
	}
	while(abs((getMotorEncoder(right) + getMotorEncoder(right)) / 2 - amount) > 40){}
	motor[side] = 0;
}

task main()
{
		resetGyro(gyro);

		drive(100);

		rotate(-90);

		strafe(-300);
}
