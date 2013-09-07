
void moveServo(Servo &servoToMove, int positionToMoveTo )
{
  int currentServoPosition = servoToMove.read();
  int currentServoPositionMicroSeconds = map (currentServoPosition, 0, 180, 700, 2300);
  if (positionToMoveTo > currentServoPosition)
  {
    int amountToMove = positionToMoveTo - currentServoPositionMicroSeconds;
    for (int x = 0; x <= amountToMove; x ++)
    {
      servoToMove.writeMicroseconds(currentServoPositionMicroSeconds + x);
      delayMicroseconds(10);
    }
  }
  else
  {
    int amountToMove = currentServoPositionMicroSeconds - positionToMoveTo;
    for (int x = 0; x <= amountToMove; x ++)
    {
      servoToMove.writeMicroseconds(currentServoPositionMicroSeconds - x);
      delayMicroseconds(10);
    }
  }  
}