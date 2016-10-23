String line;
volatile long rpmcount1=0;
volatile long rpmcount2=0;
volatile unsigned long last_m1=0;
volatile unsigned long last_m2=0;
long debounce_time = 14;

void setup()
{
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(2), rpm_fun1, FALLING);
  attachInterrupt(digitalPinToInterrupt(3), rpm_fun2, FALLING);
  line.reserve(50);
}

String readLine(){
      String s =  "";
      char c;
      while((c = Serial.read()) !='\n'){
          s += c;
      }  
      return s;
}
  
 
void loop()//Measure RPM
{
    /*if (Serial.read() == 'R')
    {
      rpmcount1 = 0;
      rpmcount2 = 0;
    }   
    line = "";
    line+="+";
    line+=rpmcount1;
    line+=",";
    line+=rpmcount2;
    Serial.println(line);*/
    
  if(Serial.available()){    
    if (readLine() == "RESET"){
      rpmcount1 = 0;
      rpmcount2 = 0;
      }
  }
  Serial.println("A:" + String(rpmcount1));
  Serial.println("B:" + String(rpmcount2));
  //Serial.println("-");
  delay(10);
}


void rpm_fun1()
 {
   if( (long)micros() - last_m1 >= debounce_time*1000){
      rpmcount1++;
      last_m1 = micros();
    }
 }
 
 void rpm_fun2()
 {
   if( (long)micros() - last_m2 >= debounce_time*1000){
      rpmcount2++;
      last_m2 = micros();
   }      
 }
