#include <Arduino.h>
#include <utility/imumaths.h>
#include <Adafruit_BNO055.h>


Adafruit_BNO055 bno = Adafruit_BNO055(55);

ISR(TIMER0_COMPA_vect, ISR_NOBLOCK){

  imu::Vector<3> accel = bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
  Serial.print('R');
  Serial.println( accel.x() );

}
 
void setup(void) 
{
  Serial.begin(9600);  
  /* Initialise the sensor */
  if( !bno.begin() )
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  
  delay(1000);

  bno.setExtCrystalUse(true);

  TIMSK |= (1<<OCIE1A); // Enables timer interrupts
  OCR1A = 12499; // Sets the timer to compare match 
  TCCR1A |= (1<<WGM11); // Enables CTC mode (Clear Timer on Compare)
  TCCR1B |= (1<<CS12); // Set pre-scaler of 256
  TCCR1B |= (1<<CS10); // Set pre-scaler of 256


  sei();

  
}
 
void loop(void) 
{

    while(1);
    // OCR0A is what the clock counts up to before triggering the interrupt 
    // Since I used a pre-scaler of 8, every 8 clock cycles the counter goes up by one
    // so it'll take 8*125 = 1000 clock cycles to trigger a compare match event
    // My uC clock speed was at 1000000 cycles/s
    // So 1000 [cycles] / 1000000 [cycles/s] = 0.001 [s] = 1 [ms]
    
    // BUT I might be off by one since it will also have to compare against 0
    // So maybe OCR0A = 124? Section 19.7.2 of the ATmega328_P data sheet says OCRnx is
    // off by one in a formula they have, maybe give that section a read 
    // (if thats your uC)
    
    // Yeah now that I think about it it should be one less cause the counter starts at 0
    // Oh and if you do look at the formula they're using, its to toggle an output every
    // compare match event. Thats why they divided by two, cause it'll take two 
    // compare match events for one periode of their square wave.
    // But you wont't be dividing by two cause one compare match will be the whole 
    // 100 ms
}