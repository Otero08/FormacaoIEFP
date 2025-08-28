int A = 1;
int B = 2;
int C = 3;
int a= 0;
int b= 0;
int c= 0;

void setup() {
  Serial.begin(9600);
Serial.println(A);
Serial.println(B);
Serial.println(C);

c = C;
a = A ;
b = B;

A=b;
B=c;
C=a;

Serial.println(A);
Serial.println(B);
Serial.println(C);



  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
