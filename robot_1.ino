#define mot_ena 9 //пин ШИМа левого мотора
#define mot_in1 8 //пин левого мотора
#define mot_in2 7 //пин левого мотора
#define mot_in3 6 //пин правого мотора
#define mot_in4 4 //пин правого мотора
#define mot_enb 10 //пин ШИМа правого мотора

#define ir_1 A0 //пин 1 ИК-датчика
#define ir_2 A1 //пин 2 ИК-датчика
#define ir_3 A2 //пин 3 ИК-датчика
#define ir_4 A3 //пин 4 ИК-датчика
#define ir_5 A4 //пин 5 ИК-датчика
#define ir_6 A5 //пин 6 ИК-датчика

#define lev_vik 11 //пин левого выключателя
#define pra_vik 12 //пин правого выключателя

//для выравнивания скорости колес
byte max_skor_lev = 128;
byte max_skor_prav = 128;
//---------------------------------

byte min_skor = 0;
byte left_c=0; //count of left ps
byte right_c=0; //count of rigth ps
unsigned long last_l=0;
unsigned long last_r=0;
unsigned long interval=5000;


void setup() {

randomSeed(analogRead(A7));
// пины энкодеров на вход
//pinMode(13, OUTPUT);
pinMode(3, INPUT); // пин левого энкодера на вход
pinMode(2, INPUT); // пин правого энкодера на вход
//-------------------------
// пины для левого и правого моторов на выход
pinMode(mot_ena, OUTPUT);
pinMode(mot_in1, OUTPUT);
pinMode(mot_in2, OUTPUT);
pinMode(mot_in3, OUTPUT);
pinMode(mot_in4, OUTPUT);
pinMode(mot_enb, OUTPUT);
//-------------------------------------------
// пины ИК-датчиков на вход
pinMode(ir_1, INPUT);
pinMode(ir_2, INPUT);
pinMode(ir_3, INPUT);
pinMode(ir_4, INPUT);
pinMode(ir_5, INPUT);
pinMode(ir_6, INPUT);
//-------------------------
// пины левого и правого выключателей на вход
pinMode(lev_vik, INPUT_PULLUP);
pinMode(pra_vik, INPUT_PULLUP);
//---------------------------
Serial.begin(9600);
  Serial.println("Hello world");
delay(2000);
//digitalWrite(13,HIGH);
ROB_VPERED();
}


void loop() {
//Serial.println("1");
// если срабатывает левый выключатель на бампере
if (digitalRead(lev_vik) == LOW)
{
  unsigned long cur_l = millis();
  Serial.println(cur_l-last_l);
  if(cur_l-last_l > interval) {
// save the last time you blinked the LED
last_l=cur_l; 
left_c=0;
  }
  
  left_c=left_c+1;
  byte c=1;
  if (left_c>2){ 
      c=2;
  }
  for(byte i=1;i<=c;i++){
 Serial.println("Left loop begin ");
 Serial.println(left_c);
Serial.println(c);
  ROB_STOP();
delay(200);
ROB_NAZAD();
delay(150);
ROB_STOP();
delay(200);
ROB_PRAV();
delay(random(400, 1500));
ROB_STOP();
delay(200);
ROB_VPERED();
Serial.println("Left loop done ");
 }
}
//-----------------------------------------------
// если срабатывает правый выключатель на бампере
if (digitalRead(pra_vik) == LOW)
{
  unsigned long cur_r = millis();
  if(cur_r-last_r > interval) {
// save the last time you blinked the LED
last_r=cur_r; 
right_c=0;
  }

  right_c=right_c+1;
  byte c=1;
  if (right_c>2){c=2;};
  for(byte i=1;i<=c;i++){

  Serial.println("Right loop done");

ROB_STOP();
delay(200);
ROB_NAZAD();
delay(150);
ROB_STOP();
delay(200);
ROB_LEV();
delay(random(400, 1500));
ROB_STOP();
delay(200);
ROB_VPERED();
  }
}
//-----------------------------------------------
// если срабатывает 2 ИК-датчик
/*
if (digitalRead(ir_2) == LOW)
{
ROB_STOP();
delay(200);
ROB_PRAV();
delay(random(200, 1100));
ROB_STOP();
delay(200);
ROB_VPERED();
}
//-----------------------------------------------
// если срабатывает 3 ИК-датчик
if (digitalRead(ir_3) == LOW)
{
ROB_STOP();
delay(200);
ROB_PRAV();
delay(random(200, 1100));
ROB_STOP();
delay(200);
ROB_VPERED();
}
//-----------------------------------------------
// если срабатывает 4 ИК-датчик
if (digitalRead(ir_4) == LOW)
{
ROB_STOP();
delay(200);
ROB_LEV();
delay(random(200, 1100));
ROB_STOP();
delay(200);
ROB_VPERED();
}
//-----------------------------------------------
// если срабатывает 5 ИК-датчик
if (digitalRead(ir_5) == LOW)
{
ROB_STOP();
delay(200);
ROB_LEV();
delay(random(200, 1100));
ROB_STOP();
delay(200);
ROB_VPERED();
}
//-----------------------------------------------
// если срабатывает 1 ИК-датчик
if (digitalRead(ir_1) == LOW)
{
ROB_PRAV();
delay(10);
ROB_VPERED();
}
//-----------------------------------------------
// если срабатывает 6 ИК-датчик
if (digitalRead(ir_6) == LOW)
{
ROB_LEV();
delay(10);
ROB_VPERED();
}
//-----------------------------------------------
*/

}

// поворот направо на месте
void ROB_PRAV()
{
// левый мотор вперед
digitalWrite(mot_in1, LOW);
digitalWrite(mot_in2, HIGH);
analogWrite(mot_ena, max_skor_lev);
// правый мотор назад
digitalWrite(mot_in3, LOW);
digitalWrite(mot_in4, HIGH);
analogWrite(mot_enb, max_skor_prav);
}
//-----------------
// поворот налево на месте
void ROB_LEV()
{
// правый мотор вперед
digitalWrite(mot_in3, HIGH);
digitalWrite(mot_in4, LOW);
analogWrite(mot_enb, max_skor_prav);
// левый мотор назад
digitalWrite(mot_in1, HIGH);
digitalWrite(mot_in2, LOW);
analogWrite(mot_ena, max_skor_lev);
}
//---------------------
// езда вперед
void ROB_VPERED()
{
// левый мотор вперед
digitalWrite(mot_in1, LOW);
digitalWrite(mot_in2, HIGH);
analogWrite(mot_ena, max_skor_lev);
// правый мотор вперед
digitalWrite(mot_in3, HIGH);
digitalWrite(mot_in4, LOW);
analogWrite(mot_enb, max_skor_prav);
}
//-------------------------------------
// езда назад
void ROB_NAZAD()
{
// левый мотор назад
digitalWrite(mot_in1, HIGH);
digitalWrite(mot_in2, LOW);
analogWrite(mot_ena, max_skor_lev);
// правый мотор назад
digitalWrite(mot_in3, LOW);
digitalWrite(mot_in4, HIGH);
analogWrite(mot_enb, max_skor_prav);
}
//------------------------------------
// стоп
void ROB_STOP()
{
// левый мотор стоп
digitalWrite(mot_in1, LOW);
digitalWrite(mot_in2, LOW);
analogWrite(mot_ena, min_skor);
// правый мотор стоп
digitalWrite(mot_in3, LOW);
digitalWrite(mot_in4, LOW);
analogWrite(mot_enb, min_skor);
}
//--------------------------------
