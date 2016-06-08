/*
 Usage: ./send <systemCode> <unitCode> <command>
 Command is 0 for OFF and 1 for ON
 */

#include "RCSwitch.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

    /*
     output PIN is hardcoded for testing purposes
     see https://projects.drogon.net/raspberry-pi/wiringpi/pins/
     for pin mapping of the raspberry pi GPIO connector
     */
    int PIN = 0;
    RCSwitch mySwitch = RCSwitch();
    mySwitch.enableTransmit(PIN);

    int protocol = atoi(argv[1]);
    mySwitch.setProtocol(protocol);
    if (wiringPiSetup () == -1) {
        printf("Wiringpi not setup correctly, aborting");
        return 1;
    }
    if (argc < 4) {
        printf("insufficient number of arguments, please give at least 4 arguments");
        return 2;
    }

    switch (protocol) {
        case 1:
        case 2: {
            char* systemCode = argv[2];
            int unitCode = atoi(argv[3]);
            int command  = atoi(argv[4]);

            printf("sending systemCode[%s] unitCode[%i] command[%i]\n", systemCode, unitCode, command);
            switch(command) {
                case 1:
                    mySwitch.switchOn(systemCode, unitCode);
                    break;
                case 0:
                    mySwitch.switchOff(systemCode, unitCode);
                    break;
                default:
                    printf("command[%i] is unsupported\n", command);
                    return -1;
            }
        }
        break;
        case 3: {
            int nDeviceGroup = atoi(argv[2]);
            int nDevice = atoi(argv[3]);
            int nCommand = atoi(argv[4]);
            int nAll = 0;
            if (argc > 4) {
                nAll = atoi(argv[5]);
            }
            boolean bAll = nAll != 0 ? true : false;
            printf("sending systemCode[%s] unitCode[%i] command[%i] all[%i]\n", nDeviceGroup, nDevice, nCommand, nAll);
            switch(nCommand) {
                case 1:
                    mySwitch.switchOn(nDeviceGroup, nDevice, bAll);
                    break;
                case 0:
                    mySwitch.switchOff(nDeviceGroup, nDevice, bAll);
                    break;
                default:
                    printf("command[%i] is unsupported\n", nCommand);
                    return -1;
            }
        }
        break;
    }


	return 0;
}
