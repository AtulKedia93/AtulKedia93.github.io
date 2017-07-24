int op1=9,op2=10;//Constants,pins.
double lt1=0,t1=0,t2;//check data type
int lt0=0,t0;
int B;
void setup()
{
  pinMode(op1,OUTPUT);
  pinMode(op2,OUTPUT);
  for(int i=1;i<=5;i++) pinMode(i,INPUT);
  Serial.begin(9600);
}
void loop()
{
  delay(15000);
  int a_ip1[5]={0,0,0,0,0},a_ip2[5]={0,1,2,3,4},a[5]={0,0,0,0,0},n=0;
  for(int j=0;j<5;j++)
  {
    for(int i=0;i<5;i++)
    {
      a_ip1[i]+=analogRead(i+1);                  //Reading photodiodes
    }
  }
  for(int i=0;i<5;i++)
  {
    Serial.print(" ");
    Serial.print(a_ip1[i]);
    if(a_ip1[i]<580)
    {
      a[i]=1;n++; //Comparing if shadow present.
    }
  }
  if(n==1) t1 = (0*36*a[0]+1*36*a[1]+2*36*a[2]+3*36*a[3]+4*36*a[4])/5;
  else if(n==2 && a[4]==1 && a[0]==1) t1 = 162;
  else t1 = (0*36*a[0]+1*36*a[1]+2*36*a[2]+3*36*a[3]+4*36*a[4])/10;
  Serial.print(" ");
  if(lt1!=t1)
  {
    analogWrite(op2,128);
    analogWrite(op1,255);//Arbit addition
    delay(15000);
    int b[5]={0,0,0,0,0},m=0;
    for(int j=0;j<5;j++)
    {
      for(int i=0;i<5;i++)
      {
        a_ip2[i]+=analogRead(i+1);                  //Reading photodiodes
      }
    }
    for(int i=0;i<5;i++)
    {
      Serial.print(" ");
      Serial.print(a_ip2[i]);
      if(a_ip2[i]<580)
      {
        b[i]=1;m++; //Comparing if shadow present.
      }
    }
    if(m==1) t2 = (0*36*b[0]+1*36*b[1]+2*36*b[2]+3*36*b[3]+4*36*b[4])/5;
    else if(m==2 && b[5]==1 && b[1]==1) t2 = 162;
    else t2 = (0*36*b[0]+1*36*b[1]+2*36*b[2]+3*36*b[3]+4*36*b[4])/10;
    t1=t1*3.14/180;t2=t2*3.14/180;
    B=1/(sin(t1)*(1/tan(t1)-1/tan(t2)));//Full value of B=2*3.14*26700*0.09176*0.01
    if(abs(B)>255) Serial.println("Naa ho payega");
    if(B>0)
    {
      int x = B*cos(t1);
      analogWrite(op2,x);
      analogWrite(op1,0);
    }
    else
    {
      int x = B*cos(t1);
      analogWrite(op1,x);
      analogWrite(op2,0);
    }
    Serial.println(" ");
    Serial.println(lt1);
    Serial.println(" ");
    Serial.println(t1);
  }
  lt1=t1;
  Serial.println(" ");
}
