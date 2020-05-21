#include <Arduino.h>
#include <Stepper.h>
#include <IRremote.h>

int receiverPin = 12;
Stepper smallStepper(32, 8, 10, 9, 11);
IRrecv IR(receiverPin);
decode_results results;
void setup() 
{
  smallStepper.setSpeed(1000);
  IR.enableIRIn();
}

void loop() 
{
  if(IR.decode(&results))
  {
    switch(results.value)
    {
      case 0xFF02FD:
        smallStepper.step(170);
        delay(500);
        break;
      case 0xFFC23D:
        smallStepper.step(-170);
        delay(500);
        break;
    }
    IR.resume();
  }
}
