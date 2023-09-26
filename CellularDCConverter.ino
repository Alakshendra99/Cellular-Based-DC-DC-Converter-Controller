/*HHHH Cellular DC DC Converter Controller HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH*/
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*- Header-Files -*/
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <SoftwareSerial.h>
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*- Macros -*/
#define FacoryRestTimer 5000
#define DeveloperTimer 25000
#define OKResponseTimer 1000
#define ResponseStableTimer 100
#define GetTimeout 15000
#define PostTimeout 15000
#define RestartTime 35000
#define ATRetry 2
#define ReconnectTime 60000
#define RelockTime 1200000
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*- Global-Variables-&-Constants -*/
SoftwareSerial GPRS(2,3);
const uint8_tLED = 4;
const uint8_t NET = 5;
char CDuty[3] = {'4','0','P'};
char Duty[3] = {'4','0','P'};
const uint8_t BOOST = 9;
const uint8_t BUCK = 10;
int TOP = 1600;
float DutyCycle = 0.4;
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*- AT-Commands -*/
const char PROGMEM ATCommands[] = {
/*-000-*/'A','T','+','C','I','P','S','H','U','T','\n','#',
/*-012-*/'A','T','\n','#',
/*-016-*/'A','T','+','P','I','N','?','\n','#',
/*-025-*/'A','T','+','C','R','E','G','?','\n','#',
/*-035-*/'A','T','+','C','S','Q','\n','#',
/*-043-*/'A','T','+','C','G','A','T','T','?','\n','#',

/*-054-*/'A','T','+','S','A','P','B','R','=','3',',','1',',','\"','C','O','N','T','Y','P','E','\"',',','\"','G','P','R','S','\"','\n','#',
/*-085-*/'A','T','+','S','A','P','B','R','=','3',',','1',',','\"','A','P','N','\"',',','a','i','r','t','e','l','g','p','r','s','.','c','o','m','\n','#',
/*-120-*/'A','T','+','S','A','P','B','R','=','1',',','1','\n','#',
/*-134-*/'A','T','+','S','A','P','B','R','=','0',',','1','\n','#',

/*-148-*/'A','T','+','H','T','T','P','I','N','I','T','\n','#',
/*-161-*/'A','T','+','H','T','T','P','S','S','L','=','1','\n','#',
/*-175-*/'A','T','+','H','T','T','P','P','A','R','A','=','\"','C','I','D','\"',',','1','\n','#',
/*-196-*/'A','T','+','H','T','T','P','P','A','R','A','=','\"','R','E','D','I','R','\"',',','1','\n','#',
/*-219-*/'A','T','+','H','T','T','P','P','A','R','A','=','\"','C','O','N','T','E','N','T','\"',',','\"','t','e','x','t','/','*','\"','\n','#',
/*-251-*/'A','T','+','H','T','T','P','P','A','R','A','=','\"','C','O','N','T','E','N','T','\"',',',
         '\"','a','p','p','l','i','c','a','t','i','o','n','/','j','s','o','n','\"','\n','#',

/*-293-*/'A','T','+','H','T','T','P','A','C','T','I','O','N','=','0','\n','#',
/*-310-*/'A','T','+','H','T','T','P','A','C','T','I','O','N','=','1','\n','#',
/*-327-*/'A','T','+','H','T','T','P','T','E','R','M','\n','#',

/*-340-*/'A','T','+','H','T','T','P','P','A','R','A','=','\"','U','R','L','\"',',','\"','h','t','t','p','s',':','/','/',
         's','u','a','v','y','-','h','o','m','e','-','a','u','t','o','m','a','t','i','o','n','-','9','1','3','b','1','-','d','e','f','a','u','l','t','-',
         'r','t','d','b','.','f','i','r','e','b','a','s','e','i','o','.','c','o','m','/','p','r','o','d','u','c','t','K','e','y','s','/',
         'L','a','z','y','5','6','7','8','8','9','0','u','i','/','k','e','y','P','o','s','.','j','s','o','n','\"','\n','#',
/*-463-*/'A','T','+','H','T','T','P','P','A','R','A','=','\"','U','R','L','\"',',','\"','h','t','t','p','s',':','/','/',
         's','u','a','v','y','-','h','o','m','e','-','a','u','t','o','m','a','t','i','o','n','-','9','1','3','b','1','-','d','e','f','a','u','l','t','-',
         'r','t','d','b','.','f','i','r','e','b','a','s','e','i','o','.','c','o','m','/','p','r','o','d','u','c','t','K','e','y','s','/',
         'L','a','z','y','5','6','7','8','8','9','0','u','i','/','k','e','y','P','o','s','.','j','s','o','n','?','o','r','d','e','r','B','y','=',
         '%','2','2','$','k','e','y','%','2','2','&','l','i','m','i','t','T','o','L','a','s','t','=','1','\"','\n','#',

/*-619-*/'A','T','+','H','T','T','P','D','A','T','A','=','1','9','2',',','1','0','0','0','0','\n','#',
/*-642-*/'A','T','+','C','P','I','N','?','\n','#',
/*-652-*/'A','T','+','H','T','T','P','R','E','A','D','\n','#',
/*-665-*/'A','T','+','H','T','T','P','D','A','T','A','=','5','0','0',',','4','0','0','0','\n','#',
/*-687-*/'A','T','+','S','A','P','B','R','=','3',',','1',',','\"','A','P','N','\"',',','\"','a','i','r','t','e','l','g','p','r','s','.','c','o','m','\"','\n','#',
/*-724-*/'A','T','+','C','F','U','N','=','0','\n','#',
/*-735-*/'A','T','+','C','F','U','N','=','1','\n','#'
};
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*HHHH Debugging HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH*/
/*- Debugging -*/
class Debugging {
  private:
    bool DevMode = true;  
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------*/
  public:
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------*/
  /*- Developer/Debugger-Controlled-Serial-Monitor -*/
  /*- Overloaded-Functions-To-Print-Stuff-Serially -*/
    void ConsolePrint(uint8_t Reader){
      if(DevMode){Serial.print(Reader);}
    }
    void ConsolePrint(uint16_t Reader){
      if(DevMode){Serial.print(Reader);}
    }
    void ConsolePrint(uint32_t Reader){
      if(DevMode){Serial.print(Reader);}
    }
    void ConsolePrint(char Reader){
      if(DevMode){Serial.write((char)Reader);}
    }
    void ConsolePrint(String Reader){
      if(DevMode){Serial.print(Reader);}
    }
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------*/
  /*- Turning-Signal-LED -*/
  void Signal(bool S){
    digitalWrite(LED,S);  
  }
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------*/
  /*- Turning-Signal-LED -*/
  void Net(bool S){
    digitalWrite(NET,S);
  }
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------*/
  /*- Producing-Delay -*/
  void Delay(unsigned long Time){
    unsigned long Entry = millis();
    unsigned long Exit = millis();
    while(((Exit-Entry)<Time)&&((Exit-Entry)>=0)){
      Exit = millis();
    }
  }
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------*/
  /*- Number-Checker -*/
  bool IsNumber(char C){
    switch(C){
      case '0': N = 0;return true;
      case '1': N = 1;return true;
      case '2': N = 2;return true;
      case '3': N = 3;return true;
      case '4': N = 4;return true;
      case '5': N = 5;return true;
      case '6': N = 6;return true;
      case '7': N = 7;return true;
      case '8': N = 8;return true;
      case '9': N = 9;return true;
      default : return false;
    }
}
void ToNumber(){
  float LoL = 0;
  IsNumber(Duty[0]);
  LoL = N*10;
  IsNumber(Duty[1]);
  LoL = LoL + N;
  LoL = LoL/100;
  if(LoL<0.01){
    LoL = 0.01;
  }else if(LoL>0.99){
    LoL = 0.99;
  }
  DutyCycle = LoL; 
}
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------*/
  /*- Starting-Debugging -*/
  void Start(){
      Serial.begin(9600);
      GPRS.begin(9600);
        pinMode(LED,OUTPUT);
        pinMode(NET,OUTPUT);
  }
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------*/
}; Debugging Debug;
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*HHHH Internet Of Things HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH*/
/*- InternetOfThings -*/
class IOT {
  public:
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------*/
    bool UpFlag = false;
    bool ReUpload = false;
    bool Loading = false;
    void Smartdome();
    void Connect();
    void CompareState();
    void RadioListen();
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------*/
}; IOT IoT;
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*HHHH World Wide Web HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH*/
/*- World-Wide-Web -*/
class WorldWideWeb{
  private:
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------*/
    /*- To-Write-AT-Commands -*/
    void GPRSWrite(uint16_t Reader){
      do{char C = pgm_read_byte_near(ATCommands+Reader);Reader++;
      if(C=='#'){break;}GPRS.write((char)C);
      }while(1);
    }
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------*/
    /*- To-Print-Characters-At-GPRS -*/
    void GPRSPrint(char C){
      GPRS.write((char)C);
    }
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------*/
    /*- To-Flush-Out-Remaining-Data -*/
    void GPRSFlush(){
      while(GPRS.available()){Debug.ConsolePrint((char)GPRS.read());}
    }
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------*/
    /*- To-Flush-Out-Remaining-Data -*/
    void GPRSDelay(unsigned long Timeout){
        delay(ResponseStableTimer);Debug.ConsolePrint('\n');
        unsigned long Entry = millis();
        unsigned long Exit = millis();
        while((((Exit-Entry)<Timeout)&&((Exit-Entry)>=0))){
          if(GPRS.available()){Debug.ConsolePrint((char)GPRS.read());}
          IoT.RadioListen();
          Exit = millis();
        } 
    }
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------*/
    /*- To-Check-For-OK-Response -*/
    bool GPRSCheckOK(unsigned long Timeout=OKResponseTimer,uint16_t StableDelay=ResponseStableTimer){
      char Buffer[2] = {' ',' '};delay(StableDelay);Debug.ConsolePrint('\n');
          unsigned long Entry = millis();
          unsigned long Exit = millis();
        while((((Exit-Entry)<Timeout)&&((Exit-Entry)>=0))){            
            if(GPRS.available()){
              Buffer[0]=Buffer[1];Buffer[1]=(char)GPRS.read();
              Debug.ConsolePrint((char)Buffer[1]);
              if(Buffer[0]=='O'&&Buffer[1]=='K'){return true;}
            } 
            IoT.RadioListen();
            Exit = millis();
        } return false;
    }
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------*/
    /*- To-Check-For-OK-Response -*/
    bool AT200Type(){
        char Buffer[3] = {' ',' ',' '};bool GetFlag = true;
            unsigned long Entry = millis();
            unsigned long Exit = millis();
          
          while(((Exit-Entry)<GetTimeout)&&((Exit-Entry)>=0)){
            if(GPRS.available()){
              Buffer[0]=Buffer[1];Buffer[1]=Buffer[2];Buffer[2]=(char)GPRS.read();
              Debug.ConsolePrint(Buffer[2]);
              if(Buffer[0]=='2'&&Buffer[1]=='0'&&Buffer[2]=='0'){GetFlag=false;break;}
            } 
            IoT.RadioListen();
            Exit = millis();
          } if(GetFlag){GPRSDelay(200);return false;}
          
          GPRSDelay(200);
          return true;
    }
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------*/
    /*- Ensure-OK-Type-AT-Command-Is-Proper -*/
    bool ATOKType(uint16_t R,byte ATRetrying=ATRetry,unsigned long Timeout=OKResponseTimer){
      byte Retry = 0;
      ATStatus = true;
        do{
            GPRSWrite(R);
            bool Report = GPRSCheckOK(Timeout);
            if(Report){return true;} 
            Retry = Retry+1;
        }while(Retry<ATRetrying);
      ATStatus = false;
      return false;
    }
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------*/
    /*- Preparing-For-GET-Method -*/
    void HTTPGet(){
      /*- AT+HTTPPARA="CONTENT","application/json" -*/
      ATOKType(251);
      /*- AT+HTTPPARA="URL",
       *  "https://suavy-home-automation-913b1-default-rtdb.firebaseio.com/productKeys/12345678890ui/keyPos.json?orderBy=%22$key%22&limitToLast=1" -*/
      ATOKType(463);
    }
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------*/
    /*- Preparing-For-POST-Method -*/
    void HTTPPost(){
      /*- AT+HTTPPARA="CONTENT","text/*" -*/
      ATOKType(219);
      /*- AT+HTTPPARA="URL","https://suavy-home-automation-913b1-default-rtdb.firebaseio.com/productKeys/12345678890ui/keyPos.json" -*/
      ATOKType(340);
    }
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------*/
  public:
    bool ATStatus = false;
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------*/
    /*- Connecting-The-GPRS-To-Cloud -*/
    void ConnectToGPRS(){
      /*- AT+CFUN=0 -*/
      ATOKType(724,1);
      GPRSDelay(2500);
      /*- AT+CFUN=1 -*/
      ATOKType(735,2);
      
      GPRSDelay(10000);
      
      /*- AT -*/
      ATOKType(12,2);
      /*- AT+CPIN? -*/
      ATOKType(642,2);
      /*- AT+CREG? -*/
      ATOKType(25,2);
      /*- AT+CSQ -*/
      ATOKType(35,1);
      
      /*- AT+SAPBR=3,1,"CONTYPE","GPRS" -*/
      ATOKType(54,2);
      /*- AT+SAPBR=3,1,"APN","airtelgprs.com" -*/
      ATOKType(687,2);
      
      /*- AT+SAPBR=1,1 -*/
      ATOKType(120,2,10000);
    }
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------*/
    /*- HTTP-Session-Active -*/
    void HTTPConnect(){
      /*- AT+HTTPINIT -*/
      ATOKType(148,1);
      /*- AT+HTTPSSL=1 -*/
      ATOKType(161,1);
      /*- AT+HTTPPARA="CID",1 -*/
      ATOKType(175,1);
      /*- AT+HTTPPARA="REDIR",1 -*/
      ATOKType(196,1);
    }
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------*/
    /*- Downloading-Data-Via-HTTP-Protocol -*/
    bool Download(){
        /*- Requesting-HTTP-GET -*/
        /*- AT+HTTPACTION=0 -*/
        GPRSWrite(293);
        bool Report = AT200Type();
        if(!Report){return false;}
        
        /*- Reading-HTTP-GET-Data -*/
        /*- AT+HTTPREAD -*/
        GPRSWrite(652);
        char Buffer[3] = {' ',' ',' '};
        bool CollectFlag = false;bool Skip = false;byte R = 0;
          unsigned long Entry = millis();
          unsigned long Exit = millis();
          while(((Exit-Entry)<GetTimeout)&&((Exit-Entry)>=0)){
            if(GPRS.available()){
              Buffer[0]=Buffer[1];Buffer[1]=Buffer[2];Buffer[2]=(char)GPRS.read();
              Debug.ConsolePrint(Buffer[2]);
              if(Buffer[0]=='\"'&&Buffer[1]==':'&&Buffer[2]=='\"'){CollectFlag=true;Skip=true;}

              /*- Skipping-Useless-Data -*/
              if(Skip){Skip=false;}
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------*/
              /*- Collecting-Data -*/
              else if(CollectFlag){
                /*- End-of-Data -*/
                if(Buffer[2]=='\"'){break;}
                /*- Load-Data-Collection -*/
                CDuty[R] = Buffer[2];R++;
              }
            }
            IoT.RadioListen();
            Exit = millis();
          }
          
        GPRSDelay(100);
        return CollectFlag;
    }
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------*/
    /*- Uploading-Data-Via-HTTP-Protocol -*/
    void Upload(){
        IoT.Loading = false;
        IoT.ReUpload = false;
        
        /*- Feeding-Parameters-For-HTTP-POST -*/
        HTTPPost();
        
        /*- AT+HTTPDATA -*/
        GPRSWrite(665);GPRSDelay(100);

        IoT.Loading = true;
        /*- Sending-Data -*/
        GPRSPrint('\"');
        for(byte i=0;i<3;i++){
          GPRSPrint((char)Duty[i]);
        } 
        GPRSPrint('\"');GPRSPrint('\n');
        GPRSCheckOK(10000);
        
        /*- AT+HTTPACTION=1 -*/
        GPRSWrite(310);
        bool Report = AT200Type();   
        IoT.Loading = false;

        if(IoT.ReUpload){
          Upload();
          return;
        }
        
        /*- Getting-Back-In-Get-Mode -*/
        HTTPGet();
    }
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------*/
    /*- Manual-Sending-Commands-To-GPRS -*/
    void ManualControl(){
        if(GPRS.available()){
          Serial.write(GPRS.read());
        }
        if(Serial.available()){
          byte a = Serial.read();
          if(a=='#'){
            GPRS.write( 0x1a );
          }else{
            GPRS.write(a);
          }
        }
    }
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------*/
}; WorldWideWeb Internet;
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*HHHH Internet Of Things Function HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH*/
/*- Connecting-The-Central-Server-To-Networks -*/
void IOT::Connect(){
    /*- Connecting-To-GPRS-Network -*/
    Internet.ConnectToGPRS();
    if(!Internet.ATStatus){
      while(!Internet.ATStatus){
        
        unsigned long Entry = millis();
        unsigned long Exit = millis();
        while(((Exit-Entry)<10000)&&((Exit-Entry)>=0)){
          RadioListen();
          Exit = millis();
        }
        /*- Reconnecting -*/
        Internet.ConnectToGPRS();
      }
    }

    /*- Starting-HTTP-Session -*/
    Internet.HTTPConnect();
    /*- Uploading-Lastest-Data -*/
    Internet.Upload();
}
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void IOT::CompareState(){
  Serial.print("\nComparing\n");
  if((Duty[0]!=CDuty[0])||(Duty[1]!=CDuty[1])){
    Duty[0] = CDuty[0];
    Duty[1] = CDuty[1];
    Debug.ToNumber();
    int OCRValue = DutyCycle * TOP;
    OCR1A = OCRValue;
    OCR1B = OCRValue;
  }
  Serial.print(CDuty[0]);Serial.print(CDuty[1]);Serial.print('\n');
  Serial.print(Duty[0]);Serial.print(Duty[1]);Serial.print('\n');
  Serial.print(DutyCycle);Serial.print('\n');
}
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void IOT::RadioListen(){
}
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void IOT::Smartdome(){
  /*- Downloading-Cloud-Load-State -*/
  if((!UpFlag)&&(!Internet.Download())){
    Connect();
  }
  /*- Checking-For-Changes -*/
  if(!UpFlag){
    CompareState();
    /*- For-Failed-Communication -*/
    if(UpFlag){
      Internet.Upload();
      UpFlag = false;
    }
  }
  /*- Uploading-Load-Data -*/
  else{
    Internet.Upload();
    UpFlag = false;
  }
}
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*HHHH Working Code HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH*/
/*- Working Code -*/
void setup() {
  pinMode(BOOST, OUTPUT);      
  pinMode(BUCK, OUTPUT);
  TCCR1A = 0;     
  TCCR1B = 0;
  TCCR1A |= (1 << WGM11) | (1 << COM1A1);
  TCCR1B |= (1 << WGM13) | (1 << CS10) | (1 << WGM12);
  TCCR1A |= (1 << COM1B0) | (1 << COM1B1);
  ICR1 = TOP;
  int OCRValue = DutyCycle * TOP;
  OCR1A = OCRValue;
  OCR1B = OCRValue;
  
  Debug.Start();
  IoT.Connect();
}
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void loop() {
  IoT.Smartdome();
}
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------*/
