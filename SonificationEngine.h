//
//  SonificationEngine.h
//  SoniScan_2_0
//
//  Created by Hariharan Mohanraj on 4/15/13.
//  Copyright (c) 2013 Hariharan Mohanraj. All rights reserved.
//

#ifndef __SoniScan_2_0__SonificationEngine__
#define __SoniScan_2_0__SonificationEngine__

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include "Constants.h"

class SonificationEngine
{
    float ***masterData;
    int masterDataSize[3];
    int mode;               // Mode  : 1 = instrument grid mode
    int scan;               // Scan  : 0 = All at once
                            //         1 = Left-to-Right scan
                            //         2 = Center-Outwards scan
    int slice;              // Slice : Current slice number
    int instr;              // Instr : Temp instrument number for score file writing
    int currInstr;
    int output;             // Output: 0 = Csound instrument and audio output
                            //         1 = MIDI file output

    
    float instrBoundaries[NUM_INSTR+1]; // Specifies the boundaries at which the instrument transitions are made
                                        // for Mode 3 sonification
    char outputfile[MAX_SCORELINE_LENGTH];
    char dataFilename[MAX_SCORELINE_LENGTH];
    // Score statement variables
    char scoreLine[MAX_SCORELINE_LENGTH];
    float startTime;
    float duration;
    int noteIndex;
    float panValue;
    float amplitude;
    int midiVelocity;
    int midiPan;
    
    // Slice size variables
    int sliceWidthL;
    int sliceWidthR;
    int sliceHeightU;
    int sliceHeightD;
    int sliceWidth;
    int sliceHeight;
    
public:
    void SetDataFilename(char*);
    
    int GetMode();
    void SetMode(int);
    
    int GetScan();
    void SetScan(int);

    int GetSlice();
    void SetSlice(int);
    
    int GetInstr();
    void SetInstr(int);
    
    int GetOutput();
    void SetOutput(int);

    char* GetOutputFile();
    void SetOutputFile(char*);
    
    float GetInstrBoundary(int);
    void SetInstrBoundary(float,int);
    // -----------------------------------
    void SetMasterData(float***,int[]);
    void SonifySelect();
    
    // Sonification utility functions
    int GetInstrNum(float);
    void UpdateSliceSize();
    void UpdateScoreLine(float,float,float);
    void WriteHeader(std::ofstream&);
    void WriteFooter(std::ofstream&);
    void GenerateLines(char*,char*,char*);
    void DisplayDiagnostics(char*,char*,char*,int[]);
    
    // Mode 1 Sonification
    // Grid-based average, score
    void ModeOneSonify();
    
    // Mode 2 Sonification
    // Individual voxel, score
    void ModeTwoSonify();
    
    // Mode 3 Sonification
    // Individual voxel, intensity to instrument
    void ModeThreeSonify();
    
    // Constructor
    SonificationEngine();
};

#endif /* defined(__SoniScan_2_0__SonificationEngine__) */
