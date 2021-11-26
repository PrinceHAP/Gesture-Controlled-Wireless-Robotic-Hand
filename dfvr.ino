#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


//Create a voltage divider circuit combining a flex sensor with a 47k resistor.
//- The resistor should connect from A0 to GND.
//- The flex sensor should connect from A0 to 3.3V
//As the resistance of the flex sensor increases (meaning it's being bent), the
//voltage at A0 should decrease.


const int FLEX_PIN_1 = A1;  //start from left to right
const int FLEX_PIN_2 = A2;
const int FLEX_PIN_3 = A3;
const int FLEX_PIN_4 = A4;
const int FLEX_PIN_5 = A5;// Pin connected to voltage divider output

// Measure the voltage at 5V and the actual resistance of your
// 47k resistor, and enter them below:
//have to calibrated finally--using multimeter

const float VCC_1 = 4.98; // Measured voltage of Ardunio 5V line
const float R_DIV_1 = 47500.0; // Measured resistance of 3.3k resistor
const float VCC_2 = 4.98;
const float R_DIV_2 = 47500.0; 
const float VCC_3 = 4.98;
const float R_DIV_3 = 47500.0;  
const float VCC_4 = 4.98;
const float R_DIV_4 = 47500.0; 
const float VCC_5 = 4.98;
const float R_DIV_5 = 47500.0; 

// Upload the code, then try to adjust these values to more
// accurately calculate bend degree.

const float STRAIGHT_RESISTANCE_1 = 59762.0; // resistance when straight
const float BEND_RESISTANCE_1 = 116666.0; // resistance at 90 deg
const float STRAIGHT_RESISTANCE_2 = 59762.0; // resistance when straight
const float BEND_RESISTANCE_2 = 116666.0; // resistance at 90 deg
const float STRAIGHT_RESISTANCE_3 = 59762.0; // resistance when straight
const float BEND_RESISTANCE_3 = 116666.0; // resistance at 90 deg
const float STRAIGHT_RESISTANCE_4 = 59762.0; // resistance when straight
const float BEND_RESISTANCE_4 = 116666.0; // resistance at 90 deg
const float STRAIGHT_RESISTANCE_5 = 59762.0; // resistance when straight
const float BEND_RESISTANCE_5 = 116666.0; // resistance at 90 deg

float sensor_data_angle[5];



//radio link
RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";


void setup() 
{
  Serial.begin(9600);
  pinMode(FLEX_PIN_1, INPUT);
  pinMode(FLEX_PIN_2, INPUT);
  pinMode(FLEX_PIN_3, INPUT);
  pinMode(FLEX_PIN_4, INPUT);
  pinMode(FLEX_PIN_5, INPUT);

  //radio link
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() 
{
  // Read the ADC, and calculate voltage and resistance from it
  int flexADC_1 = analogRead(FLEX_PIN_1);
  float flexV_1 = flexADC_1 * VCC_1 / 1023.0;
  float flexR_1 = R_DIV_1 * (VCC_1 / flexV_1 - 1.0);
  Serial.println("1------Resistance: " + String(flexR_1) + " ohms\n");

  int flexADC_2 = analogRead(FLEX_PIN_2);
  float flexV_2 = flexADC_2 * VCC_2 / 1023.0;
  float flexR_2 = R_DIV_2 * (VCC_2 / flexV_2 - 1.0);
  Serial.println("2------Resistance: " + String(flexR_2) + " ohms\n");

  int flexADC_3 = analogRead(FLEX_PIN_3);
  float flexV_3 = flexADC_2 * VCC_3 / 1023.0;
  float flexR_3 = R_DIV_3 * (VCC_3 / flexV_3 - 1.0);
  Serial.println("3------Resistance: " + String(flexR_3) + " ohms\n");



  int flexADC_4 = analogRead(FLEX_PIN_4);
  float flexV_4 = flexADC_4 * VCC_4 / 1023.0;
  float flexR_4 = R_DIV_4 * (VCC_4 / flexV_4 - 1.0);
  Serial.println("4------Resistance: " + String(flexR_4) + " ohms\n");

  int flexADC_5 = analogRead(FLEX_PIN_5);
  float flexV_5 = flexADC_5 * VCC_5 / 1023.0;
  float flexR_5 = R_DIV_5 * (VCC_5 / flexV_5 - 1.0);
  Serial.println("5------Resistance: " + String(flexR_5) + " ohms\n");



  // Use the calculated resistance to estimate the sensor's
  // bend angle:
  
  sensor_data_angle[0] = map(flexR_1, STRAIGHT_RESISTANCE_1, BEND_RESISTANCE_1,0, 90.0);
  Serial.println("1-----Bend: " + String(sensor_data_angle[0]) + " degrees");
  Serial.println();
  sensor_data_angle[1] = map(flexR_2, STRAIGHT_RESISTANCE_2, BEND_RESISTANCE_2,0, 90.0);
  Serial.println("2-----Bend: " + String(sensor_data_angle[1]) + " degrees");
  Serial.println();
  sensor_data_angle[2] = map(flexR_3, STRAIGHT_RESISTANCE_3, BEND_RESISTANCE_3,0, 90.0);
  Serial.println("3-----Bend: " + String(sensor_data_angle[2]) + " degrees");
  Serial.println();
  sensor_data_angle[3] = map(flexR_4, STRAIGHT_RESISTANCE_4, BEND_RESISTANCE_4,0, 90.0);
  Serial.println("4-----Bend: " + String(sensor_data_angle[3]) + " degrees");
  Serial.println();
  sensor_data_angle[4] = map(flexR_5, STRAIGHT_RESISTANCE_5, BEND_RESISTANCE_5,0, 90.0);
  Serial.println("5-----Bend: " + String(sensor_data_angle[4]) + " degrees");
  Serial.println();



 //radio link
 radio.write(&sensor_data_angle, sizeof(sensor_data_angle));







  
  delay(1000);
}

