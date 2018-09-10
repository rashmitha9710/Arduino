int num = 0;

void setup()
{
  Serial.begin(9600);
}

void loop()
{ 
  Serial.print("Dette programmet har kjørt ");
  num++;
  String txt = write(String(num));
  Serial.println(txt);
  delay(50);
}

String write(String text)
{
  return text + " ganger!";
}
