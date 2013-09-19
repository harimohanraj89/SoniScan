//
//  ControlBlock.cpp
//  SoniScan_2_0
//
//  Created by Hariharan Mohanraj on 11/30/12.
//  Copyright (c) 2012 Hariharan Mohanraj. All rights reserved.
//

#include "ControlBlock.h"
#include "Constants.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>

// ===========================
// UTILITY FUNCTIONS
// ===========================
int ControlBlock::ArrayMax(int* argArray, int argLength)
{
    if (argLength < 1)
    {
        std::cout << "Empty array argument to ArrayMax(). 0 returned by default.\n";
        return 0;
    }
    
    int max = argArray[0];
    
    for (int i=1; i<argLength; i++)
    {
        if (argArray[i] > max)
        {
            max = argArray[i];
        }
    }
    
    return max;
}

int ControlBlock::ArrayMin(int* argArray, int argLength)
{
    if (argLength < 1)
    {
        std::cout << "Empty array argument to ArrayMin(). 0 returned by default.\n";
        return 0;
    }
    
    int min = argArray[0];
    
    for (int i=1; i<argLength; i++)
    {
        if (argArray[i] < min)
        {
            min = argArray[i];
        }
    }
    
    return min;
}

void ControlBlock::ClearMasterData()
{
    for (int x=0; x<masterDataSize[0]; x++)
    {
        for (int y=0; y<masterDataSize[1]; y++)
        {
            delete[] masterData[x][y];
        }
        
        delete[] masterData[x];
    }
    
    if (masterData != 0)
    {
        delete[] masterData;
    }
}

void ControlBlock::InitMasterData(int argX, int argY, int argZ)
{
    ClearMasterData();
    
    masterData = new float**[argX];
    
    for (int x=0; x<argX; x++)
    {
        masterData[x] = new float*[argY];
        for (int y=0; y<argY; y++)
        {
            masterData[x][y] = new float[argZ];
            for (int z=0; z<argZ; z++)
            {
                masterData[x][y][z] = -1;
            }
        }
    }
    
    masterDataSize[0] = argX;
    masterDataSize[1] = argY;
    masterDataSize[2] = argZ;
}


// ===========================
// PARAMETER FUNCTIONS
// ===========================

// SetSelectionArea() - Overloaded function to define selectionArea
// One name-value pair

void ControlBlock::SetSelectionArea(std::string parameterName1, int parameterValue1)
{
    // Match parameterName1 and assign parameterValue1 accordingly
    
    if(parameterName1.compare("x1") == 0)
    {
        selectionVolume.x1 = parameterValue1;
    }
    if(parameterName1.compare("x2") == 0)
    {
        selectionVolume.x2 = parameterValue1;
    }
    if(parameterName1.compare("y1") == 0)
    {
        selectionVolume.y1 = parameterValue1;
    }
    if(parameterName1.compare("y2") == 0)
    {
        selectionVolume.y2 = parameterValue1;
    }
}

void ControlBlock::SetSelectionArea(std::string parameterName1, int parameterValue1, std::string parameterName2, int parameterValue2)
{
    // Check for duplicate parameter names
    
    if(parameterName1 == parameterName2)
    {
        std::cout << "Duplicate parameter names. SetSelectionArea call ignored.";
        return;
    }
    
    // Match parameterName1 and assign parameterValue1 accordingly
    
    if(parameterName1.compare("x1") == 0)
    {
        selectionVolume.x1 = parameterValue1;
    }
    if(parameterName1.compare("x2") == 0)
    {
        selectionVolume.x2 = parameterValue1;
    }
    if(parameterName1.compare("y1") == 0)
    {
        selectionVolume.y1 = parameterValue1;
    }
    if(parameterName1.compare("y2") == 0)
    {
        selectionVolume.y2 = parameterValue1;
    }
    
    // Match parameterName1 and assign parameterValue1 accordingly
    
    if(parameterName2.compare("x1") == 0)
    {
        selectionVolume.x1 = parameterValue2;
    }
    if(parameterName2.compare("x2") == 0)
    {
        selectionVolume.x2 = parameterValue2;
    }
    if(parameterName2.compare("y1") == 0)
    {
        selectionVolume.y1 = parameterValue2;
    }
    if(parameterName2.compare("y2") == 0)
    {
        selectionVolume.y2 = parameterValue2;
    }
}

void ControlBlock::SetSelectionArea(std::string parameterName1, int parameterValue1, std::string parameterName2, int parameterValue2, std::string parameterName3, int parameterValue3)
{
    // Check for duplicate parameter names
    
    if(parameterName1 == parameterName2 || parameterName1 == parameterName3 || parameterName2 == parameterName3)
    {
        std::cout << "Duplicate parameter names. SetSelectionArea call ignored.";
        return;
    }
    
    // Match parameterName1 and assign parameterValue1 accordingly
    
    if(parameterName1.compare("x1") == 0)
    {
        selectionVolume.x1 = parameterValue1;
    }
    if(parameterName1.compare("x2") == 0)
    {
        selectionVolume.x2 = parameterValue1;
    }
    if(parameterName1.compare("y1") == 0)
    {
        selectionVolume.y1 = parameterValue1;
    }
    if(parameterName1.compare("y2") == 0)
    {
        selectionVolume.y2 = parameterValue1;
    }
    
    // Match parameterName2 and assign parameterValue2 accordingly
    
    if(parameterName2.compare("x1") == 0)
    {
        selectionVolume.x1 = parameterValue2;
    }
    if(parameterName2.compare("x2") == 0)
    {
        selectionVolume.x2 = parameterValue2;
    }
    if(parameterName2.compare("y1") == 0)
    {
        selectionVolume.y1 = parameterValue2;
    }
    if(parameterName2.compare("y2") == 0)
    {
        selectionVolume.y2 = parameterValue2;
    }
    
    // Match parameterName3 and assign parameterValue3 accordingly
    
    if(parameterName3.compare("x1") == 0)
    {
        selectionVolume.x1 = parameterValue1;
    }
    if(parameterName3.compare("x2") == 0)
    {
        selectionVolume.x2 = parameterValue1;
    }
    if(parameterName3.compare("y1") == 0)
    {
        selectionVolume.y1 = parameterValue1;
    }
    if(parameterName3.compare("y2") == 0)
    {
        selectionVolume.y2 = parameterValue1;
    }
}

void ControlBlock::SetSelectionArea(std::string parameterName1, int parameterValue1, std::string parameterName2, int parameterValue2, std::string parameterName3, int parameterValue3, std::string parameterName4, int parameterValue4)
{
    // Check for duplicate parameter names
    
    if(parameterName1 == parameterName2 || parameterName1 == parameterName3 || parameterName1 == parameterName4 || parameterName2 == parameterName3 || parameterName2 == parameterName4 || parameterName3 == parameterName4)
    {
        std::cout << "Duplicate parameter names. SetSelectionArea call ignored.";
        return;
    }
    
    // Match parameterName1 and assign parameterValue1 accordingly
    
    if(parameterName1.compare("x1") == 0)
    {
        selectionVolume.x1 = parameterValue1;
    }
    if(parameterName1.compare("x2") == 0)
    {
        selectionVolume.x2 = parameterValue1;
    }
    if(parameterName1.compare("y1") == 0)
    {
        selectionVolume.y1 = parameterValue1;
    }
    if(parameterName1.compare("y2") == 0)
    {
        selectionVolume.y2 = parameterValue1;
    }
    
    // Match parameterName2 and assign parameterValue2 accordingly
    
    if(parameterName2.compare("x1") == 0)
    {
        selectionVolume.x1 = parameterValue2;
    }
    if(parameterName2.compare("x2") == 0)
    {
        selectionVolume.x2 = parameterValue2;
    }
    if(parameterName2.compare("y1") == 0)
    {
        selectionVolume.y1 = parameterValue2;
    }
    if(parameterName2.compare("y2") == 0)
    {
        selectionVolume.y2 = parameterValue2;
    }
    
    // Match parameterName3 and assign parameterValue3 accordingly
    
    if(parameterName3.compare("x1") == 0)
    {
        selectionVolume.x1 = parameterValue1;
    }
    if(parameterName3.compare("x2") == 0)
    {
        selectionVolume.x2 = parameterValue1;
    }
    if(parameterName3.compare("y1") == 0)
    {
        selectionVolume.y1 = parameterValue1;
    }
    if(parameterName3.compare("y2") == 0)
    {
        selectionVolume.y2 = parameterValue1;
    }
    
    // Match parameterName4 and assign parameterValue4 accordingly
    
    if(parameterName4.compare("x1") == 0)
    {
        selectionVolume.x1 = parameterValue4;
    }
    if(parameterName4.compare("x2") == 0)
    {
        selectionVolume.x2 = parameterValue4;
    }
    if(parameterName4.compare("y1") == 0)
    {
        selectionVolume.y1 = parameterValue4;
    }
    if(parameterName4.compare("y2") == 0)
    {
        selectionVolume.y2 = parameterValue4;
    }
}

void ControlBlock::SetSelectionVolume(int argX1, int argX2, int argY1, int argY2, int argZ1, int argZ2)
{
    int temp;
    int localArgX1 = argX1;
    int localArgX2 = argX2;
    int localArgY1 = argY1;
    int localArgY2 = argY2;
    int localArgZ1 = argZ1;
    int localArgZ2 = argZ2;
    
    // Ensure that arg 1 is less than arg 2
    if (localArgX1 > localArgX2)
    {
        temp = localArgX1;
        localArgX1 = localArgX2;
        localArgX2 = temp;
    }
    
    if (localArgY1 > localArgY2)
    {
        temp = localArgY1;
        localArgY1 = localArgY2;
        localArgY2 = temp;
    }
    
    if (localArgZ1 > localArgZ2)
    {
        temp = localArgZ1;
        localArgZ1 = localArgZ2;
        localArgZ2 = temp;
    }
    
    // Clip all arg values to between 0 and masterDataSize[i]-1
    if (localArgX1 < 0)
        localArgX1 = 0;
    if (localArgX1 > masterDataSize[0]-1)
        localArgX1 = masterDataSize[0]-1;
    
    if (localArgX2 < 0)
        localArgX2 = 0;
    if (localArgX2 > masterDataSize[0]-1)
        localArgX2 = masterDataSize[0]-1;
    
    if (localArgY1 < 0)
        localArgY1 = 0;
    if (localArgY1 > masterDataSize[0]-1)
        localArgY1 = masterDataSize[0]-1;
    
    if (localArgY2 < 0)
        localArgY2 = 0;
    if (localArgY2 > masterDataSize[0]-1)
        localArgY2 = masterDataSize[0]-1;
    
    if (localArgZ1 < 0)
        localArgZ1 = 0;
    if (localArgZ1 > masterDataSize[0]-1)
        localArgZ1 = masterDataSize[0]-1;
    
    if (localArgZ2 < 0)
        localArgZ2 = 0;
    if (localArgZ2 > masterDataSize[0]-1)
        localArgZ2 = masterDataSize[0]-1;
    
    // Assign all args to selectionVolume
    selectionVolume.x1 = localArgX1;
    selectionVolume.x2 = localArgX2;
    selectionVolume.y1 = localArgY1;
    selectionVolume.y2 = localArgY2;
    selectionVolume.z1 = localArgZ1;
    selectionVolume.z2 = localArgZ2;
    
}


void ControlBlock::SetRangeMin(float value)
{
    rangeMin = value;
}

void ControlBlock::SetRangeMax(float value)
{
    rangeMax = value;
}

void ControlBlock::SetShift(float value)
{
    shift = value;
}

void ControlBlock::SetVolume(float value)
{
    if(volume < 0)
        std::cout << "Negative volume parameter. SetVolume call ignored";
    else
        volume = value;
}


// =================================
// SONIFICATION ENGINE CONNECTORS
// =================================

void ControlBlock::SetEngine(SonificationEngine* argEngine)
{
    if (argEngine == 0)
    {
        std::cout << "Null argument received in SetEngine(). Setting engine to null.\n";
    }
    engine = argEngine;
}

SonificationEngine* ControlBlock::GetEngine()
{
    return engine;
}

// ===========================
// DATA INPUT/OUTPUT FUNCTIONS
// ===========================


// Function to read file into masterData
// -------------------------------------

void ControlBlock::ReadFile(char* argFilename)
{
    char dataLine[MAX_SCORELINE_LENGTH];
    sprintf(dataLine,TEST_DATA_PATH "%s.txt", argFilename);
    
    std::string str;
    int curr;
    
    int nums[4] = {0,0,0,0};
    int exp = 0;
    int pos;
    int index = 4;
    int lineCount = 0;
    int currLine;

    std::cout << "Reading file...\n";
    
    std::ifstream inputFile;

    
    // Calculate line count
    // --------------------
    inputFile.open(dataLine);
    
    if(!inputFile.good())
    {
        std::cout << "Error opening file!\n";
        return;
    }
    
    
    while (getline(inputFile, str))
    {
        lineCount++;
    }
    
    // Check for empty file
    // --------------------
    if (lineCount < 1)
    {
        std::cout << "Empty file! FileRead() call ignored.\n";
        return;
    }
    
    inputFile.close();
    
    
    // Initialize arrays to hold data
    // ------------------------------
    int* X    = new int[lineCount];
    int* Y    = new int[lineCount];
    int* Z    = new int[lineCount];
    int* vals = new int[lineCount];
    
    
    inputFile.open(dataLine);
    
    if(!inputFile.good())
    {
        std::cout << "Error opening file!";
        return;
    }
    
    // Populate arrays with data from file
    // -----------------------------------
    currLine = 0;
    while(getline(inputFile, str))
    {
        pos = str.size() - 1;
        index = 3;
        exp = 0;
        nums[0] = 0;
        nums[1] = 0;
        nums[2] = 0;
        nums[3] = 0;
        
        while (index >= 0 && pos >= 0)
        {
            curr = int(str[pos]);
            if ( curr >= 48 && curr <= 57)   // If curr is a number character
            {
                nums[index] += (curr-48) * pow(10,exp);
                exp++;
            }
            
            if (curr == 44)
            {
                index--;
                exp = 0;
            }
            pos--;
        }

        X[currLine]    = nums[0];
        Y[currLine]    = nums[1];
        Z[currLine]    = nums[2];
        vals[currLine] = nums[3];
        currLine++;
    }
    
    int xMin;
    int xMax;
    int yMin;
    int yMax;
    int zMin;
    int zMax;
    
    xMin = ArrayMin(X,lineCount);
    xMax = ArrayMax(X,lineCount);
    yMin = ArrayMin(Y,lineCount);
    yMax = ArrayMax(Y,lineCount);
    zMin = ArrayMin(Z,lineCount);
    zMax = ArrayMax(Z,lineCount);
    
    InitMasterData(xMax-xMin+1, yMax-yMin+1, zMax-zMin+1);
    
    for (int i=0; i<lineCount; i++)
    {
        masterData[X[i]-1][Y[i]-1][Z[i]-1] = vals[i];
    }
    
    TrimMasterData();
    engine->SetMasterData(masterData,masterDataSize);
    
    delete[] X;
    delete[] Y;
    delete[] Z;
    delete[] vals;
    
    std::strcpy(dataFilename, argFilename);
    engine->SetDataFilename(dataFilename);   
}

// Function to trim away all external data
// ---------------------------------------
void ControlBlock::TrimMasterData()
{
    int absThreshold = TRIM_THRESHOLD * pow(2,DATA_BITDEPTH);
    int x;
    bool trimFlag;
    
    // Check whether data exists
    if (masterData == 0)
    {
        std::cout << "Dataset does not exist. TrimData() call ignored.\n";
        return;
    }
    
    // Iterate through each slice of data
    
    for (int z=0; z<masterDataSize[2]; z++)
    {
        // Iterate through each row of slice
        for (int y=0; y<masterDataSize[1]; y++)
        {
            // Trim data from left
            trimFlag = true;
            x=0;
            while(trimFlag)
            {
                if (x >= masterDataSize[0])
                {
                    trimFlag = false;
                } else if (masterData[x][y][z] > absThreshold)
                {
                    trimFlag = false;
                } else
                {
                    masterData[x][y][z] = -1;
                }

                x++;
            }
            
            // Trim data from right
            trimFlag = true;
            x = masterDataSize[0] - 1;
            while(trimFlag)
            {
                if (x < 0)
                {
                    trimFlag = false;
                    
                } else if (masterData[x][y][z] > absThreshold)
                {
                    trimFlag = false;
                    
                } else
                {
                    masterData[x][y][z] = -1;
                }
                
                x--;
            }
            
        }
        
    }
}

// Function to output current masterData
// -------------------------------------
void ControlBlock::OutputData()
{
    std::cout << "Current master data:\n";
    
    for (int z=0; z<masterDataSize[2]; z++)
    {
        std::cout << "z = " << z+1 << "\n";
        for (int y=0; y<masterDataSize[1]; y++)
        {
            for (int x=0; x<masterDataSize[0]; x++)
            {
                std::cout << masterData[x][y][z] << "\t";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }
}


// ===========
// Const/Destr
// ===========

ControlBlock::ControlBlock()
{
    masterDataSize[0] = 0;
    masterDataSize[1] = 0;
    masterDataSize[2] = 0;
    masterData = 0;
}

ControlBlock::~ControlBlock()
{
    ClearMasterData();
}