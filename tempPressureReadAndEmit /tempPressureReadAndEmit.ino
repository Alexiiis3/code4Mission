#define kpa2atm 0.00986923267


// pin defs
int pressurePin = 0;

// variables presión
int val;
float pkPa; // pressure in kPa
float pAtm; // pressure in Atm

// variables temperatura
int R1=10000; // the resistor from voltage divider
float Bt=3977.0;// B parameter
float Tc=0;// temperature in celsius

unsigned long time;


void setup()
{
  Serial.begin(9600);
 
}

void loop()
{
  
  /* get the pressure */
  val = analogRead(pressurePin);
  pkPa = ((float)val/(float)1023+0.095)/0.009;
  pAtm = kpa2atm*pkPa;
  
 
  /* send pressure to serial port */
  Serial.print(pkPa);
  Serial.print("kPa ");
  Serial.print(pAtm);
  Serial.println("Atm ");


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


  
  delay(1000);
}







 
