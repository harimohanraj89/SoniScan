//
//  main.cpp
//  SoniScan_2_0
//
//  Created by Hariharan Mohanraj on 11/30/12.
//  Copyright (c) 2012 Hariharan Mohanraj. All rights reserved.
//

#include <iostream>
#include <fstream>

#include <stdio.h>
#include <math.h>
#include <vector>
#include <string>

#include "ControlBlock.h"
#include "SonificationEngine.h"

using namespace std;

int main(void);
int main(void)
{   
    
//================================================================================
    
    // ================================
    // FILE AND STRING TESTING GROUNDS
    // ================================

    float parameterInput;
    char charInput[128];
    strcpy(charInput,"gen_BB01_perspec");
    
    ControlBlock control;
    SonificationEngine engine;
    
    control.SetEngine(&engine);
    char dataLine[MAX_SCORELINE_LENGTH];
    sprintf(dataLine,TEST_DATA_PATH TEST_DATA_FILENAME_1 ".txt");
    control.ReadFile(charInput);

    engine.SetInstrBoundary(0.5,0);
    engine.SetInstrBoundary(0.75,1);
    engine.SetInstrBoundary(0.87,2);
    engine.SetInstrBoundary(0.92,3);
    engine.SetInstrBoundary(1,4);
    

    // ================================
    // BATCH PROCESSOR PARAMETERS
    // ================================

    char fileBase[50][MAX_SCORELINE_LENGTH];
    char batchFileName[MAX_SCORELINE_LENGTH];
    ofstream numLog;

    strcpy(fileBase[0], "gen_AA01");
    strcpy(fileBase[1], "nor_BB01");
    strcpy(fileBase[2], "mil_JA01");
    strcpy(fileBase[3], "gen_JN01");
    strcpy(fileBase[4], "gen_LB01");
    strcpy(fileBase[5], "mil_LS01");
    strcpy(fileBase[6], "gen_ND01");
    strcpy(fileBase[7], "gen_NR01");
    strcpy(fileBase[8], "mil_SF01");
    strcpy(fileBase[9], "mod_SG01");
    strcpy(fileBase[10], "mil_DO01");
    strcpy(fileBase[11], "mod_PM01");
    strcpy(fileBase[12], "nor_DG01");
    strcpy(fileBase[13], "nor_DG02");
    strcpy(fileBase[14], "nor_KF01");
    strcpy(fileBase[15], "nor_LF01");
    strcpy(fileBase[16], "nor_RS01");
    strcpy(fileBase[17], "sev_HB01");
    strcpy(fileBase[18], "sev_RC01");
    strcpy(fileBase[19], "nor_RF01");
    strcpy(fileBase[20], "nor_YA01");
    strcpy(fileBase[21], "sev_HB02");

    int numBase = 22;
    // ================================
    // TESTING GROUNDS
    // ================================

    // ================================
    // USER INTERFACE
    // ================================
    
    char userInput;
    
    do
    {
        // system("clear");

        cout << "SONISCAN\n========\n\n";
        cout << "Current center freq   : " << engine.GetCenterFreq()   << "\n";
        cout << "Current detune factor : " << engine.GetDetuneFactor()   << "\n";
        cout << "\n";
        
        for (int i=0; i<NUM_INSTR+1; i++)
        {
            cout << "Instr boundary " << i+1 << " : " << engine.GetInstrBoundary(i) << "\n";
        }
        cout << "\n";
        cout << "'s' : Set Center Frequency\n";
        cout << "'d' : Set Detune Factor\n";
        cout << "'p' : Batch Sonify\n";
        cout << "'x' : Exit\n\n";
        cout << "User input : ";
        
        cin >> userInput;
        
        switch (userInput)
        {
            case 's' :
                cout << "\nEnter center frequency : ";
                cin >> parameterInput;
                engine.SetCenterFreq(parameterInput);
                break;
                
            case 'd' :
                cout << "\nEnter detune factor : ";
                cin >> parameterInput;
                engine.SetDetuneFactor(parameterInput);
                break;
                
            case 'p' :
                // ================================
                // BATCH PROCESSOR
                // ================================

                numLog.open(OUTPUT_PATH NUMBERS_LOG, std::ios::trunc);
                numLog << "Brain, L Frontal, L SMC, L Parietal, R Frontal, R SMC, R Parietal\n";
                numLog.close();

                for (int baseNum=0; baseNum<numBase; baseNum++) {

                    strcpy(batchFileName, fileBase[baseNum]);
                    strcat(batchFileName, "_orthogl");
                    cout << batchFileName << "\n";
                    control.ReadFile(batchFileName);
                    engine.SetSlice(29);
                    engine.SonifySelect();

                    strcpy(batchFileName, fileBase[baseNum]);
                    strcat(batchFileName, "_perspec");
                    cout << batchFileName << "\n";
                    control.ReadFile(batchFileName);
                    engine.SetSlice(0);
                    engine.SonifySelect();
                }
                break;

            case 'x' :
                cout << "\nThank you for using SoniScan.\n";
                break;
                
            default :
                break;
        }

    }while (userInput != 'x');

}

