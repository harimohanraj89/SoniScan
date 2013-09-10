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
    
    int parameterInput;
    char charInput[128];
    int batchFlag = 0;
    strcpy(charInput,"test_a");
    
    ControlBlock control;
    SonificationEngine engine;
    
    control.SetEngine(&engine);
    char dataLine[MAX_SCORELINE_LENGTH];
    sprintf(dataLine,TEST_DATA_PATH TEST_DATA_FILENAME_1 ".txt");
    control.ReadFile(TEST_DATA_FILENAME_1);
    
    // ================================
    // TESTING GROUNDS
    // ================================

    std::ifstream configFile;
    configFile.open("config.txt");
    std::string echoText;
    getline(configFile,echoText);
    std::cout << "====================\n" << echoText << "\n====================\n";


    // ================================
    // USER INTERFACE
    // ================================
    
    char userInput;
    
    do
    {
        cout << "SONISCAN\n========\n\n";
        cout << "Current file   : " << charInput          << "\n";
        cout << "Current mode   : " << engine.GetMode()   << "\n";
        cout << "Current scan   : " << engine.GetScan()   << "\n";
        cout << "Current slice  : " << engine.GetSlice()  << "\n";
        cout << "Current instr  : " << engine.GetInstr()  << "\n";
        cout << "Current output : " << engine.GetOutput() << "\n";
        cout << "\n";
        
        for (int i=0; i<NUM_INSTR+1; i++)
        {
            cout << "Instr boundary " << i+1 << " : " << engine.GetInstrBoundary(i) << "\n";
        }
        cout << "\n";
        
        cout << "'a' : Set file\n";
        cout << "'s' : Set mode\n";
        cout << "'d' : Set scan\n";
        cout << "'f' : Set slice\n";
        cout << "'g' : Set instr\n";
        cout << "'h' : Set output\n";
        cout << "'j' : Set boundary\n";
        cout << "'q' : Sonify\n";
        cout << "'x' : Exit\n\n";
        cout << "User input : ";
        
        cin >> userInput;
        
        switch (userInput)
        {
            case 'a' :
                cout << "\n1. " << TEST_DATA_FILENAME_1;
                cout << "\n2. " << TEST_DATA_FILENAME_2;
                cout << "\n3. " << TEST_DATA_FILENAME_3;
                cout << "\n4. " << TEST_DATA_FILENAME_4;
                cout << "\n5. Other";
                cout << "\n";
                cin >> parameterInput;
                switch (parameterInput)
                {
                    case 1:
                        cout << "File: " << TEST_DATA_PATH TEST_DATA_FILENAME_1 << "\n";
                        control.ReadFile(TEST_DATA_FILENAME_1);
                        strcpy(charInput,TEST_DATA_FILENAME_1);
                        break;
                    case 2:
                        cout << "File: " << TEST_DATA_PATH TEST_DATA_FILENAME_2 << "\n";
                        control.ReadFile(TEST_DATA_FILENAME_2);
                        strcpy(charInput,TEST_DATA_FILENAME_2);
                        break;
                    case 3:
                        cout << "File: " << TEST_DATA_PATH TEST_DATA_FILENAME_3 << "\n";
                        control.ReadFile(TEST_DATA_FILENAME_3);
                        strcpy(charInput,TEST_DATA_FILENAME_3);
                        break;
                    case 4:
                        cout << "File: " << TEST_DATA_PATH TEST_DATA_FILENAME_4 << "\n";
                        control.ReadFile(TEST_DATA_FILENAME_4);
                        strcpy(charInput,TEST_DATA_FILENAME_4);
                        break;
                    case 5:
                        char fileInput[MAX_SCORELINE_LENGTH];
                        cout << "Enter filename : ";
                        cin >> fileInput;
                        control.ReadFile(fileInput);
                        strcpy(charInput,fileInput);
                        break;
                    default:
                        cout << "Invalid option.\n";
                        break;
                }
                
                cout << "File read complete.\n";
                
                break;
                
            case 's' :
                cout << "\n1. Averaged score mode";
                cout << "\n2. Intensity to pitch - each voxel";
                cout << "\n3. Intensity to instr - each voxel";
                cout << "\nEnter mode : ";
                cin >> parameterInput;
                engine.SetMode(parameterInput);
                break;

            case 'd' :
                cout << "\n0. Simultaneous\n1. L-R scan";
                cout << "\nEnter scan : ";
                cin >> parameterInput;
                engine.SetScan(parameterInput);
                break;

            case 'f' :
                cout << "\nEnter slice : ";
                cin >> parameterInput;
                engine.SetSlice(parameterInput);
                break;
                
            case 'g' :
                cout << "\nNumber of instruments available : " << NUM_INSTR;
                cout << "\nEnter instr (0 for all instr): ";
                cin >> parameterInput;
                engine.SetInstr(parameterInput);
                break;
            
            case 'h' :
                cout << "\n0. CSound instrument audio file\n";
                cout << "1. MIDI file";
                cout << "\nEnter output: ";
                cin >> parameterInput;
                engine.SetOutput(parameterInput);
                break;
                
            case 'j' :
                float boundaryInput;
                cout << "\nEnter boundary index to change : \n";
                cin >> parameterInput;
                cout << "Enter boundary value for boundary index " << parameterInput << " : ";
                cin >> boundaryInput;
                engine.SetInstrBoundary(boundaryInput,parameterInput-1);
                break;
                
            case 'k' :
                cout << "\nEnter output filename : \n";
                cin >> parameterInput;
                cout << "Enter boundary value for boundary index " << parameterInput << " : ";
                cin >> boundaryInput;
                engine.SetInstrBoundary(boundaryInput,parameterInput-1);
                break;
                
            case 'q' :
                cout << "\nSonifying...\n";
                engine.SonifySelect();
                cout << "\nSonification complete.\n";
                break;
                

            case 'x' :
                cout << "\nThank you for using SoniScan.\n";
                break;
                
            case 'p' :
                batchFlag = 1;
                break;
                
            default :
                break;
        }

    }while (userInput != 'x' && userInput != 'p');
    
    
    if (batchFlag == 1)
    {
        // ================================
        // BATCH PROCESSOR
        // ================================
        
        
        engine.SetInstr(0);
        engine.SetOutput(1);
        for (int mode=3; mode <= 3; mode++)
        {
            for (int scan=0; scan <=1; scan++)
            {
                engine.SetMode(mode);
                engine.SetScan(scan);
                
                std::cout << "\n----------------------------- MILD001 ----------------------\n ";
                control.ReadFile("MILD001");
                engine.SetSlice(39);
                engine.SonifySelect();
                engine.SetSlice(79);
                engine.SonifySelect();
                
                std::cout << "\n----------------------------- NORMAL006 ----------------------\n ";
                control.ReadFile("NORMAL006");
                engine.SetSlice(42);
                engine.SonifySelect();
                engine.SetSlice(77);
                engine.SonifySelect();
                
//                std::cout << "\n----------------------------- Hl_E_J ----------------------\n ";
//                control.ReadFile("Hl_E_J");
//                engine.SetSlice(18);
//                engine.SonifySelect();
//                engine.SetSlice(35);
//                engine.SonifySelect();
//                
//                std::cout << "\n----------------------------- Un_A_L_early ----------------------\n ";
//                control.ReadFile("Un_A_L_early");
//                engine.SetSlice(24);
//                engine.SonifySelect();
//                engine.SetSlice(38);
//                engine.SonifySelect();
//                
//                std::cout << "\n----------------------------- Un_C_T_mod ----------------------\n ";
//                control.ReadFile("Un_C_T_mod");
//                engine.SetSlice(19);
//                engine.SonifySelect();
//                engine.SetSlice(35);
//                engine.SonifySelect();
//                
//                std::cout << "\n----------------------------- Un_R_K_severe ----------------------\n ";
//                control.ReadFile("Un_R_K_severe");
//                engine.SetSlice(16);
//                engine.SonifySelect();
//                engine.SetSlice(37);
//                engine.SonifySelect();
            }
        }
    }

}

