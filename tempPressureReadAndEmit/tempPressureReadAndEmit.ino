/****
 * Reading from a Vishay NTCLE100E3 Thermistor
 * TEMPERATURE 
 * Code for thermistor readings taken from 
 * https://www.eprojectszone.com/measuring-temperature-with-an-arduino-and-a-thermistor/
 * Thermistor spec https://www.mouser.es/datasheet/2/427/VISH_S_A0012091193_1-2572478.pdf
 *
 * PRESSURE
 * MPX1145a sensor
 *
 * EMIT/RECEIVE
 * APC220
 *
 * CANSAT SINESTUDIOS TEAM - IES Villaverde
 */
#define kpa2atm 0.00986923267


int R1=10000; // the resistor from voltage divider
float Bt=3977.0;// B parameter
float Tc=0;// temperature in celsius

// pin defs
int pressurePin = 0;

// variables
int val;
float pkPa; // pressure in kPa
float pAtm; // pressure in Atm



void setup(void) {
 Serial.begin(9600);
}
void loop(void) { 
  updatetemp();
  updatePression();
}   
void updatetemp()// function which generates temperature
{
  int x=analogRead(A1);//reading the value from Analog pin 1
  float Vout=x*(5/1023.0);// transform it in voltage
  float Rt=R1*Vout/(5.0-Vout);// the resistance of thermistor from the voltage divider
                              //this value cance with temperature
  float a1=1/298.15;//298.155 represent 25 degrees celsius in kelvin
                     //and 1/298.15 represent 1/To in equation
  float b1=1/Bt;// 1/Btsecond parameter in equation
  float c1=log(Rt/10000.0);//third parameter, 50000 ohms are Ro at zero degrees celsius
  float y1=a1+b1*c1;// the result of equation
  float  T=1/y1;// temperature in kelvin
        Tc=T-273.15;//temperature in celsius
        Serial.println(Tc);// display temperature in serial monitor
}
void updatePression() //To read pression from mpx
{
   /* get and print current time */
  time = millis()/1000;
  Serial.print(time);
  Serial.print(": ");

  /* get the pressure */
  val = analogRead(pressurePin);
  pkPa = ((float)val/(float)1023+0.095)/0.009;
  pAtm = kpa2atm*pkPa;
   
  /* send pressure to serial port */
  Serial.print(pkPa);
  Serial.print("kPa ");
  Serial.print(pAtm);
  Serial.print("Atm \n");
  
   
  delay(1000);
}
