
#include "names.h"
#include "ASSP.h"
#include "SSBasicUtilities.h"
#include <EEPROM.h>
//#define DEBUG
#define MESSAGESENDER "Behrooz"
#define PING "ping"
#define NUMBEROFPORTS 4

int ports[] = {1, 2, 3, 4};
int hosts[26];
//int hostsTest[] = {1,1,2,4,2,0,1,3,4,2,0,1,3,4,2,3,1,2,0,2,1,0,2,4,2,3};

void setup(){
    Serial.begin(9600);
    //SerialShield.showASSPmessages = true;
    //task1();
    //task2();
    //task3();
    readEEPROM();
    #ifdef DEBUG
    #endif
    Serial.println("\nEND!");
}
void loop(){

}
void readEEPROM(){
    int a = 699;
    for (int i = 0; i < 30; i++)
    {
        Serial.print(EEPROM.read(a));
        Serial.print(" ");
        a++;
    }
    
    
}
void task1(){
    Serial.println("Host\t\tPort1?");
    for (int i = 0; i < NUMNAMES; i++)
    {
        if (!isHostOnPort(names[i], ports[0]))
        {
            Serial.print(names[i]);
            Serial.println("\t\tNO");
        }
        else
        {
            Serial.print(names[i]);
            Serial.println("\t\tYES");
        }
    }
    Serial.println("End of Task 1");
}
boolean isHostOnPort(const char name[], int port){
    SerialShield.setMessageSender(MESSAGESENDER);
    SerialShield.setMessageContent(PING);
    SerialShield.setMessageDestination(name);
    bool check = false;
    while (!SerialShield.sendASSPMessage(port))
    {
    }
    for (int i = 0; i < 50; i++)
    {
        check = SerialShield.fetchASSPMessage();
        if (check)
        {
            return true;
        }
    }
    return false;
}
void task2(){
    Serial.println("Host\t\tPort3Time");
    for (int i = 0; i < NUMNAMES; i++)
    {
        unsigned long responseTime = getTimeToHost(names[i], ports[2]);
        if ( responseTime == 0)
        {
            Serial.print(names[i]);
            Serial.println("\t\tNC");
        }
        else
        {
            Serial.print(names[i]);
            Serial.print("\t\t");
            Serial.println(responseTime);
        }
    }
    Serial.println("End of Task 2");
}
unsigned long getTimeToHost(const char name[], int port){
    SerialShield.setMessageSender(MESSAGESENDER);
    SerialShield.setMessageContent(PING);
    SerialShield.setMessageDestination(name);
    bool check = false;
    while (!SerialShield.sendASSPMessage(port))
    {
    }
    unsigned long messageSent = millis();
    for (int i = 0; i < 50; i++)
    {
        check = SerialShield.fetchASSPMessage();
        if (check)
        {
            unsigned long messageReceived = millis();
            return messageReceived-messageSent;
        }
    }
    return 0;
}
void task3(){
    Serial.print("Progress Bar:");
    for (int i = 0; i < NUMNAMES; i++)
    {
        hosts[i] = getPortForHost(names[i]);
        Serial.print("|");
    }
    Serial.print("\nPort\t\tHosts");
    for (int j = 0; j < NUMBEROFPORTS; j++)
    {   
        Serial.println();
        Serial.print(ports[j]);
        Serial.print("\t\t");
        printHostOnPorts(ports[j]);
    }
    Serial.print("\nNC\t\t");
    printHostOnPorts(0);
    Serial.println("\n");
    int eeAddress = 700;
    for (int t = 0; t < NUMNAMES; t++)
    {
        EEPROM.put(eeAddress, hosts[t]);
        eeAddress++;
    }
    
    
}
void printHostOnPorts(int portNumber){
    for (int k = 0; k < NUMNAMES; k++)
    {
        if (hosts[k] == portNumber)
        {
            Serial.print(names[k]);
            Serial.print(" ");
        }        
    }
}
int getPortForHost(const char name[]){
    for (int i = 0; i < NUMBEROFPORTS; i++)
    {
        if (isHostOnPort(name, i+1))
        {
            return i+1;
        }
    }
    return 0;
}
void task4(){
    int numberOfHostsOnPorts[] = {}
}
