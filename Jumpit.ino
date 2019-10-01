#define VIB_1_PIN 5
#define VIB_2_PIN 6
#define SENS_1_PIN 8
// Create a class for the vibration motors
class Vib {
  // pin attribute is not publicly accessible
  private:
    // Communication pin
    byte pin;
    // Intensity percentage
    int percentage = 255;
    // Boolean for state tracking
    bool turnedOn = false;
  // Main class methodes are defined here
  public:
    Vib(byte pin){
      // Store pin passed to the object during construction to the private attribute
      this->pin = pin;
      init();
    }

    // Standard pin setup
    void init(){
      pinMode(pin, OUTPUT);
      off();
      this->turnedOn = false;
    }
    // Set the PWM signal to the percentage stored in 
    void on(){
      analogWrite(pin, percentage);
      this->turnedOn = true;
    }
    // Turn off pin
    void off(){
      digitalWrite(pin, LOW);
      this->turnedOn = false;
    }
    // Toggle the state of the pin (on -> off ; off -> on)
    void toggle(){
      if (this->turnedOn){
        off();
      }
      else{
        on();
      }
    }

    void setPercentage(int n){
      // Transform 0-100 scale that the user inputs to 0-255 scale that the PWM pin requires
      n = n * 255;
      n = n / 100;
      this->percentage = n;
      // Refresh the state of the pin so that the output is updated to the new percentage
      if (this->turnedOn){
        on();
      }
    }
    
  
};


class Sensor {
  private:
    byte pin;
  public:
    Sensor(byte pin) {
      // Store pin passed to the object during construction to the private attribute
      this->pin = pin;
      init();
    }
    // Will be changed when I can test the UART things with the sensor
    void init(){
      pinMode(pin, INPUT);
    }

    // Return current distance in centimeters to object
    int getDistance() {
      // I haven't been able to program with the sensor yet, so this is just placeholder
      return 0;
    }
};
Vib Vib1(VIB_1_PIN);
Vib Vib2(VIB_2_PIN);
Sensor Sensor1(SENS_1_PIN);

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  // If the distance is less than 200
  if (Sensor1.getDistance() < 200){
    Vib1.on();
    Vib1.setPercentage(100);
    Vib2.on();
    Vib2.setPercentage(100);
  }
  // If the distance is between 200 and 300
  else if (Sensor1.getDistance() < 300){
    Vib1.on();
    Vib1.setPercentage(75);
    Vib2.on();
    Vib2.setPercentage(75);
  }
  // If the distance is between 300 and 400
  else if (Sensor1.getDistance() < 400){
    Vib1.on();
    Vib1.setPercentage(50);
    Vib2.on();
    Vib2.setPercentage(50);
  }
  // If the distance is more than 400
  else{
    Vib1.off();
    Vib2.off();
  }
}
