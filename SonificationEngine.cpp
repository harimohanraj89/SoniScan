//
//  SonificationEngine.cpp
//  SoniScan_2_0
//
//  Created by Hariharan Mohanraj on 4/15/13.
//  Copyright (c) 2013 Hariharan Mohanraj. All rights reserved.
//

#include "SonificationEngine.h"

// ===================================
//      GETTERS AND SETTERS
// ===================================
void SonificationEngine::SetDataFilename(char* argDataFilename)
{
    strcpy(dataFilename, argDataFilename);
}

int SonificationEngine::GetMode()
{
    return mode;
}

void SonificationEngine::SetMode(int argMode)
{
    if (argMode < 1 || argMode > NUM_MODES)
    {
        std::cout << "Invalid mode. SetMode() call ignored.\n";
        return;
    }
    
    mode = argMode;
}

// ----------------------------------

int SonificationEngine::GetScan()
{
    return scan;
}

void SonificationEngine::SetScan(int argScan)
{
    if (argScan < 0 || argScan > NUM_SCANS-1)
    {
        std::cout << "Invalid scan number. SetScan() call ignored.\n";
        return;
    }
    
    scan = argScan;
}

// ----------------------------------

int SonificationEngine::GetSlice()
{
    return slice;
}

void SonificationEngine::SetSlice(int argSlice)
{
    if (argSlice < 0 || argSlice > masterDataSize[2])
    {
        std::cout << "Invalid scan number. SetSlice() call ignored.\n";
        return;
    }
    
    slice = argSlice;
}

// ----------------------------------

int SonificationEngine::GetInstr()
{
    return instr;
}

void SonificationEngine::SetInstr(int argInstr)
{
    if (argInstr < 0 || argInstr > NUM_INSTR)
    {
        std::cout << "Invalid instr number. SetInstr() call ignored.\n";
        return;
    }
    
    instr = argInstr;
}

// ----------------------------------

int SonificationEngine::GetOutput()
{
    return output;
}

void SonificationEngine::SetOutput(int argOutput)
{
    if (argOutput < 0 || argOutput >= NUM_OUTPUTS)
    {
        std::cout << "Invalid output number. SetOutput() call ignored.\n";
        return;
    }
    
    output = argOutput;
}

// ----------------------------------
float SonificationEngine::GetInstrBoundary(int argIndex)
{
    if (argIndex < 0 || argIndex >= NUM_INSTR+1)
    {
        std::cout << "Invalid index. -1 returned by default.\n";
        return -1;
    }
    
    return instrBoundaries[argIndex];
}

void SonificationEngine::SetInstrBoundary(float argValue,int argIndex)
{
    if (argValue < 0 || argValue > 1)
    {
        std::cout << "Invalid value. SetInstrBoundary() call ignored.\n";
        return;
    }
    
    if (argIndex < 0 || argIndex >= NUM_INSTR+1)
    {
        std::cout << "Invalid index. SetInstrBoundary() call ignored.\n";
        return;
    }
    
    instrBoundaries[argIndex] = argValue;
}

// ----------------------------------

void SonificationEngine::SetMasterData(float*** argMasterData, int argMasterDataSize[])
{
    masterData = argMasterData;
    masterDataSize[0] = argMasterDataSize[0];
    masterDataSize[1] = argMasterDataSize[1];
    masterDataSize[2] = argMasterDataSize[2];
}

// ==============================
// SONIFICATION UTILITY FUNCTIONS
// ==============================
bool SonificationEngine::PointUpLine(int x, int y, int x1, int y1, int x2, int y2) {
    return (y > y1 + (x-x1)*(y2-y1)/(x2-x1));
}

bool SonificationEngine::PointRightLine(int x, int y, int x1, int y1, int x2, int y2) {
    return (x > x1 + (y-y1)*(x2-x1)/(y2-y1));   
}

int SonificationEngine::GetInstrNum(float argValue)
{
    for (int i=1; i<NUM_INSTR+1; i++)
    {
        if (argValue < (pow(2,DATA_BITDEPTH) - 1) * instrBoundaries[i])
        {
            return i;
        }
    }
    return NUM_INSTR;
}

int SonificationEngine::GetLobe(int x, int y) {
    if (std::abs(FPSLICE-slice) < std::abs(TOSLICE-slice)) {    // Frontal Parietal slice

        // Frontal lobe
        if (!PointUpLine(x,y,AX,AX,BX,BY) && !PointUpLine(x,y,BX,BY,HX,HY) && !PointUpLine(x,y,HX,HY,EX,EY)) {
            return 1;
        }

        // Sensory Motor Cortex
        if ( (PointUpLine(x,y,AX,AX,BX,BY) && !PointUpLine(x,y,DX,DY,CX,CY) && !PointRightLine(x,y,BX,BY,CX,CY) ) ||
             (PointUpLine(x,y,HX,HY,EX,EY) && !PointUpLine(x,y,GX,GY,FX,FY) && PointRightLine(x,y,HX,HY,GX,GY) ) ) {
            return 2;
        }

        // Parietal Lobe
        if  (PointUpLine(x,y,DX,DX,CX,CY) || PointUpLine(x,y,CX,CY,GX,GY) || PointUpLine(x,y,GX,GY,FX,FY)) {
            return 3;
        }
    }
    else {  // Temporal Occipital slice

        // Occipital Lobe
        if (PointUpLine(x,y,IX,IY,JX,JY) && PointUpLine(x,y,LX,LY,MX,MY) && 
            ! (!PointUpLine(x,y,JX,JY,KX,KY) && !PointUpLine(x,y,KX,KY,LX,LY)) ) {
            return 5;
        }

        // Temporal Lobe
        if ( ( !PointUpLine(x,y,IX,IY,JX,JY) && !PointRightLine(x,y,JX,JY,JX,JY+1) ) ||
            (!PointUpLine(x,y,LX,LY,MX,MY) && PointRightLine(x,y,LX,LY,LX,LY+1)) ) {
            return 4;
        }
    }

    return 0;
}

void SonificationEngine::UpdateSliceSize()
{
    
    int flag;
    // -------------------
    // Find width of slice
    // -------------------
    
    // Starting from left, find first column with valid datapoints
    
    flag = 0;
    for (int x=0; x<masterDataSize[0] && flag==0; x++)
    {
        for (int y=0; y<masterDataSize[1]; y++)
            if (masterData[x][y][slice] != -1)
            {
                sliceWidthL = x;
                flag = 1;
                break;
            }
        
        if (x == masterDataSize[0]-1) // If you've reached the end without
        {                             // finding valid datapoints...
            sliceWidthL = x;
        }
        
    }
    
    // Starting from left, find first column with valid datapoints
    
    flag = 0;
    for (int x=masterDataSize[0]-1; x>=0 && flag==0; x--)
    {
        for (int y=0; y<masterDataSize[1]; y++)
            if (masterData[x][y][slice] != -1)
            {
                sliceWidthR = x;
                flag = 1;
                break;
            }
        
        if (x == 0)                 // If you've reached the beginning without
        {                           // finding valid datapoints...
            sliceWidthR = 0;
        }
        
    }
    
    // From left and right limits, calculate slice width
    
    sliceWidth = sliceWidthR - sliceWidthL + 1;
    
    
    // --------------------
    // Find height of slice
    // --------------------
    
    // Starting from bottom, look for first row with valid datapoints
    
    flag=0;
    for (int y=0; y<masterDataSize[1] && flag==0; y++)
    {
        for (int x=0; x<masterDataSize[0]; x++)
            if (masterData[x][y][slice] != -1)
            {
                sliceHeightD = y;
                flag=1;
                break;
            }
        
        if (y == masterDataSize[1])     // If you've reached the top without
        {                               // finding valid datapoints...
            sliceHeightD = y;
        }
    }
    
    // Starting from top, look for first row with valid datapoints
    
    flag = 0;
    for (int y=masterDataSize[1]-1; y>=0 && flag==0; y--)
    {
        for (int x=0; x<masterDataSize[0]; x++)
            if (masterData[x][y][slice] != -1)
            {
                sliceHeightU = y;
                flag=1;
                break;
            }
        
        if (y == 0)                     // If you've reached the bottom without
        {                               // finding valid datapoints...
            sliceHeightU = y;
        }
    }
    
    // From upper and lower limits, calculate slice height
    
    sliceHeight = sliceHeightU - sliceHeightD + 1;
}


void SonificationEngine::UpdateScoreLine(float xFraction, float yFraction, float argValue)
{
    // Start time (sec) is a function of x-position and scan number
    // Duration (sec) for all notes is one beat, or NUM_BEATS beats
    // ------------------
    switch (scan)
    {
        case 0: // SIMULTANEOUS PLAY
            startTime = 0;
            duration = NUM_BEATS;
            break;
            
        case 1: // L-R SCAN
            startTime = xFraction * sliceWidth * 0.25;
            duration = 0.25;
            break;

        case 2: // C-OUT SCAN
            startTime = fabs(0.5 - xFraction) * sliceWidth * 0.25;
            duration = 0.25;
            break;
            
        default:
            startTime = 0;
            break;
    }
    
    
    // Pan value (1-0 = L-R) depends on x-position of voxel and pan
    // ------------------
    panValue = (1 - xFraction);
    midiPan  = (int)(64); // <-- TODO: Things are very mono
    midiPan  = (int)(xFraction*127.99);

    
    switch (mode)
    {
        case 1: // MODE ONE SONIFY
            
            
            // Current instrument is a function y-value
            // ------------------
            if (instr == 0)
            {
                currInstr = (int)((float)NUM_INSTR*yFraction) + 1;
            }
            
            
            // Zero to max is split up into MAX_NOTE_INDEX+1 bins
            // Compute which bin argAvg falls into
            // ------------------
            noteIndex = argValue * (MAX_NOTE_INDEX+1) / pow(2,DATA_BITDEPTH);
            
            // AMPLITUDE and MIDIVELOCITY
            // Amplitude is a function of scan
            // ------------------
            amplitude = scan * 1.0/(float)(NUM_INSTR) + (1-scan) * 1.0/(float)(NUM_BEATS*NUM_INSTR);
            midiVelocity = 1;
            
            /*midiVelocity = (int)(127*amplitude);
            if (midiVelocity == 0)
            {
                midiVelocity++;
            }*/
            
            break;
            
        case 2: // MODE TWO SONIFY
            
            
            // CURRENT INSTRUMENT
            // Current instrument is a function y-value
            // ------------------
            if (instr == 0)
            {
                currInstr = GetLobe(xFraction*sliceWidth + sliceWidthL, yFraction*sliceHeight + sliceHeightD);
                if (currInstr > 3) {
                    currInstr -= 3;
                }
            }
            
            // NOTE INDEX
            // Zero to max is split up into MAX_NOTE_INDEX+1 bins
            // Compute which bin argAvg falls into
            // ------------------
            noteIndex = argValue * (MAX_NOTE_INDEX+1) / (pow(2,DATA_BITDEPTH)+1);
            
            
            // AMPLITUDE
            // Amplitude is a function of scan
            // ------------------
            amplitude = scan * 1.0/(float)(sliceHeight*5) + (1-scan) * 1.0/(float)(sliceWidth*sliceHeight);
            midiVelocity = 1;
            
            /*midiVelocity = (int)(127*amplitude);
            if (midiVelocity == 0)
            {
                midiVelocity++;
            }*/
             
            break;
            
        case 3: // MODE THREE SONIFY
            
            
            // CURRENT INSTRUMENT
            // Current instrument is a function of value
            // ------------------
            if (instr == 0)
            {
                currInstr = GetInstrNum(argValue);
            }
            
            // NOTE INDEX
            // Note index is mapped to y-axis position
            // ------------------
            noteIndex = (int)(yFraction*MAX_NOTE_INDEX + 1);
            
            
            // AMPLITUDE
            // Amplitude is a function of scan
            // ------------------
            amplitude = scan * 1.0/(float)(sliceHeight*5) + (1-scan) * 1.0/(float)(sliceWidth*sliceHeight);
            midiVelocity = 1;
            
            /*midiVelocity = (int)(127*amplitude);
            if (midiVelocity == 0)
            {
                midiVelocity++;
            }*/
            
            break;
            
        default:
            break;
    }
}


void SonificationEngine::WriteHeader(std::ofstream &file)
{
    std::ifstream headerFile;
    std::string headerLine;
    
    if (mode == 1) {
        headerFile.open(CSOUNDFILES_PATH "scd_header.txt");
        while (headerFile.good())
        {
            getline(headerFile,headerLine);
            file << "\n" << headerLine;
        }
        
        headerFile.close();
    }

    else {
        switch (output)
        {
            case 0: // CSOUND INSTR FILE HEADER
                
                headerFile.open(CSOUNDFILES_PATH "csd_instr_header.txt");
                
                while (headerFile.good())
                {
                    getline(headerFile,headerLine);
                    file << headerLine << "\n";
                }
                
                headerFile.close();
                
                break;
                
            case 1: // MIDI FILE HEADER

                headerFile.open(CSOUNDFILES_PATH "csd_midi_header.txt");
                
                while (headerFile.good())
                {
                    getline(headerFile,headerLine);
                    file << headerLine << "\n";
                }
                
                headerFile.close();
                
                break;
                
            default:
                std::cout << "Invalid output value!\n";
                break;
        }
    }
}

void SonificationEngine::GenerateLines(char* fileLine, char* flagLine, char* commandLine)
{
    char localFileLine[2*MAX_SCORELINE_LENGTH];
    char localFlagLine[2*MAX_SCORELINE_LENGTH];
    char localCommandLine[2*MAX_SCORELINE_LENGTH];
    char localoutputfile[2*MAX_SCORELINE_LENGTH];
    if (strcmp(outputfile,"default"))
    {
        std::sprintf(localoutputfile, "%s_sl%d_m%d_s%d", dataFilename, slice, mode, scan);
        
    } else
    {
        std::sprintf(localoutputfile,"%s",outputfile);
    }
    
    std::sprintf(localFileLine, OUTPUT_PATH "%s_out%d.txt", localoutputfile, output);
    if (output == 0)
    {
        std::sprintf(localFlagLine, "-o" OUTPUT_PATH "%s.wav", localoutputfile);
        
    } else if (output == 1)
    {
        std::sprintf(localFlagLine, " --midioutfile=" OUTPUT_PATH "%s_sl%d_m%d_s%d.mid", dataFilename, slice, mode, scan);
        
    } else
    {
        std::sprintf(localFlagLine, "");
    }
    std::sprintf(localCommandLine, CSOUND_PATH "csound %s %s " CSOUND_FLAGS, localFileLine, localFlagLine);
    
    strcpy(fileLine, localFileLine);
    strcpy(flagLine, localFlagLine);
    strcpy(commandLine,localCommandLine);
}

void SonificationEngine::DisplayDiagnostics(char* fileLine, char* flagLine, char* commandLine, int instrCount[])
{
    std::cout << "SONIFICATION MAPPING DIAGNOSTICS\n";
    std::cout << "-----------------------------------------\n";
    std::cout << "Mode  : " << mode << "\n";
    std::cout << "Scan  : " << scan << "\n";
    std::cout << "Slice : " << slice << "\n";
    std::cout << "Instr : " << instr << "\n";
    std::cout << "\n";
    std::cout << "Instrument note totals\n";
    std::cout << "----------------------\n";
    int sum = 0;
    for (int i=0; i<NUM_INSTR; i++)
    {
        std::cout << "Instr " << i+1 << " : " << instrCount[i] << " notes\n";
        sum += instrCount[i];
    }
    std::cout << "Total   : " << sum << " notes\n";
    std::cout << "\n";
    
    std::cout << "\n\nSLICE DIAGNOSTICS\n";
    std::cout << "-----------------------------------------\n";
    std::cout << "Slice total size    : " << masterDataSize[0] << "\t" << masterDataSize[1] << "\n";
    std::cout << "Slice width         : " << sliceWidthL << " to " << sliceWidthR << " : " << sliceWidth << " voxels\n";
    std::cout << "Slice height        : " << sliceHeightD << " to " << sliceHeightU << " : " << sliceHeight << " voxels\n";
    std::cout << "\n";
    
    std::cout << "FILE AND COMMAND DIAGNOSTICS\n";
    std::cout << "-----------------------------------------\n";
    std::cout << "Csound file name  : " << fileLine << "\n";
    std::cout << "Audio output flag : " << flagLine << "\n";
    std::cout << "System command    : " << commandLine << "\n";
    
}

void SonificationEngine::WriteFooter(std::ofstream &file)
{
    std::ifstream footerFile;
    std::string footerLine;
    
    if (mode == 1) {
        footerFile.open(CSOUNDFILES_PATH "scd_footer.txt");
    }
    else {
        footerFile.open(CSOUNDFILES_PATH "csd_footer.txt");
    }

    while (footerFile.good())
    {
        getline(footerFile,footerLine);
        file << footerLine << "\n";
    }
                    
    footerFile.close();
}

// ======================
// SONIFICATION FUNCTIONS
// ======================

void SonificationEngine::SonifySelect()
{
    switch (mode)
    {
        case 1:
            
            if (scan < 0 || scan > NUM_SCANS-1)
            {
                std::cout << "Error. Current scan value is invalid. SonifySelect() call ignored.\n";
                break;
            }
            
            if (slice < 0 || slice > masterDataSize[2])
            {
                std::cout << "Error. Current slice value is invalid. SonifySelect() call ignored.\n";
                break;
            }
            ModeOneSonify();
            break;
            
            
        case 2:
            
            if (scan < 0 || scan > NUM_SCANS-1)
            {
                std::cout << "Error. Current scan value is invalid. SonifySelect() call ignored.\n";
                break;
            }
            
            if (slice < 0 || slice > masterDataSize[2])
            {
                std::cout << "Error. Current slice value is invalid. SonifySelect() call ignored.\n";
                break;
            }
            
            ModeTwoSonify();
            break;
            
        case 3:
            
            if (scan < 0 || scan > NUM_SCANS-1)
            {
                std::cout << "Error. Current scan value is invalid. SonifySelect() call ignored.\n";
                break;
            }
            
            if (slice < 0 || slice > masterDataSize[2])
            {
                std::cout << "Error. Current slice value is invalid. SonifySelect() call ignored.\n";
                break;
            }
            
            ModeThreeSonify();
            break;
            
        default:
            std::cout << "Error. Current mode value is invalid. SonifySelect() call ignored.\n";
            break;
    }
}


// =========================================================================
//
//                              MODE ONE SONIFY
//
// =========================================================================

void SonificationEngine::ModeOneSonify()
{   
    float average;
    int count;
    int maxValue = pow(2,DATA_BITDEPTH) - 1;
    int instrCount[NUM_INSTR];
    for (int i=0; i<NUM_INSTR; i++)
    {
        instrCount[i] = 0;
    }
    
    // -----------------------------
    // Update slice size variables
    // -----------------------------
    UpdateSliceSize();

    // -----------------------------------------------
    // Divide selected rectangle into even grid spaces
    // -----------------------------------------------
    
    float xRatio = float(sliceWidth)/float(NUM_BEATS);
    float yRatio = float(sliceHeight)/float(NUM_INSTR);
    
    float averageArray[3];
    int countArray [3];
    int averageArrayInt[3];
    int localInstr;

    for (int i=0; i<3; i++) {
        averageArray[i] = 0;
        averageArrayInt[i]=0;
        countArray[i] = 0;
    }
    
    for (int row=sliceHeightD; row <= sliceHeightU; row++) {
        for (int col=sliceWidthL; col <= sliceWidthR; col++) {
            localInstr = GetLobe(col,row);
            if (localInstr != 0 && masterData[row][col][slice] > TRIM_THRESHOLD) {
                localInstr = (localInstr-1)%3;
                averageArray[localInstr] += masterData[row][col][slice];
                countArray[localInstr]++;
            }
        }
    }

    for (int i=0; i<3; i++) {
        averageArray[i] /= countArray[i];
        std::cout << averageArray[i] << "\t";
    }

    // -----------------------------
    // Generate lines
    // -----------------------------
    char fileLine[MAX_SCORELINE_LENGTH];
    char flagLine[MAX_SCORELINE_LENGTH];
    char commandLine[2*MAX_SCORELINE_LENGTH];
    
    GenerateLines(fileLine,flagLine,commandLine);
    
    // -----------------------------
    // Open score file pointer
    // -----------------------------
    std::cout << "Opening : " << fileLine << "\n";
    std::ofstream scoreFile;
    scoreFile.open(fileLine, std::ios::trunc);
    
    WriteHeader(scoreFile);

    std::ifstream scdOsc;
    std::string scdOscStr;
    for (int i=0; i<3; i++) {
        averageArrayInt[i] = (int)(MODE_ONE_FREQ*(1 - DETUNE_FACTOR*(averageArray[1] - averageArray[i])/averageArray[1]));
        std::cout << "Calculated freq " << i << " : " << averageArrayInt[i] << "\n";
    }

    sprintf(scoreLine,"%d, %d, %d],[%d, %d, %d", averageArrayInt[0],averageArrayInt[1],averageArrayInt[2],averageArrayInt[0],averageArrayInt[1],averageArrayInt[2]);
    scoreFile << scoreLine;
    
    WriteFooter(scoreFile);
    scoreFile.close();
    
    DisplayDiagnostics(fileLine, flagLine, commandLine, instrCount);
}


// =========================================================================
//
//                              MODE TWO SONIFY
//
// =========================================================================


void SonificationEngine::ModeTwoSonify()
{
    float value;
    int maxValue = pow(2,DATA_BITDEPTH) - 1;
    int instrCount[NUM_INSTR];
    for (int i=0; i<NUM_INSTR; i++)
    {
        instrCount[i] = 0;
    }
    
    // -----------------------------
    // Update slice size variables
    // -----------------------------
    UpdateSliceSize();
    
    // -----------------------------
    // Generate lines
    // -----------------------------
    char fileLine[MAX_SCORELINE_LENGTH];
    char flagLine[MAX_SCORELINE_LENGTH];
    char commandLine[2*MAX_SCORELINE_LENGTH];
    
    GenerateLines(fileLine,flagLine,commandLine);
    
    // -----------------------------
    // Open score file pointer
    // -----------------------------
    std::cout << "Opening : " << fileLine << "\n";
    std::ofstream scoreFile;
    scoreFile.open(fileLine, std::ios::trunc);
    
    WriteHeader(scoreFile);
    
    // -----------------------------------------------
    // Iterate through entire brain column-wise
    // -----------------------------------------------
    
    // currInstr is instr. If instr == 0, another condition inside loop will update currInstr.
    currInstr = instr;
    
    for (int x=sliceWidthL; x<=sliceWidthR; x++)
    {
        for (int y=sliceHeightD; y<=sliceHeightU; y++)
        {   
            
            if (masterData[x][y][slice] != -1)
            {
                value = masterData[x][y][slice];
                UpdateScoreLine((float)(x - sliceWidthL)/(float)sliceWidth, (float)(y - sliceHeightD)/(float)sliceHeight, value);
                
                switch (output)
                {
                    case 0:
                        std::sprintf(scoreLine, "i%d %f %f %d %f %d %f\n", currInstr, startTime, duration, noteIndex, amplitude, currInstr, panValue);
                        scoreFile << scoreLine;
                        break;
                    case 1:
                        std::sprintf(scoreLine, "i%d %f %f %d %d %d %d\n", currInstr, startTime, duration, noteIndex, midiVelocity, currInstr, midiPan);
                        scoreFile << scoreLine;
                        break;
                        
                    default:
                        break;
                }
                
                instrCount[currInstr-1]++;
            }
            
        }
    }
    
    WriteFooter(scoreFile);
    scoreFile.close();
    
    // -------------------------
    // Csound file execution
    // -------------------------
    system(commandLine);
    
    DisplayDiagnostics(fileLine, flagLine, commandLine, instrCount);
}


// =========================================================================
//
//                             MODE THREE SONIFY
//
// =========================================================================


void SonificationEngine::ModeThreeSonify()
{
    float value;
    int maxValue = pow(2,DATA_BITDEPTH) - 1;
    int instrCount[NUM_INSTR];
    for (int i=0; i<NUM_INSTR; i++)
    {
        instrCount[i] = 0;
    }
    
    // -----------------------------
    // Update slice slize variables
    // -----------------------------
    UpdateSliceSize();
    
    // -----------------------------
    // Generate lines
    // -----------------------------
    char fileLine[MAX_SCORELINE_LENGTH];
    char flagLine[MAX_SCORELINE_LENGTH];
    char commandLine[2*MAX_SCORELINE_LENGTH];
    
    GenerateLines(fileLine,flagLine,commandLine);
    
    // -----------------------------
    // Open score file pointer
    // -----------------------------
    std::cout << "Opening : " << fileLine << "\n";
    std::ofstream scoreFile;
    scoreFile.open(fileLine, std::ios::trunc);
    
    WriteHeader(scoreFile);

    // -----------------------------------------------
    // Iterate through entire brain column-wise
    // -----------------------------------------------
    
    // currInstr is instr. If isntr == 0, another condition inside loop will update currInstr.
    currInstr = instr;
    
    for (int x=sliceWidthL; x<=sliceWidthR; x++)
    {
        for (int y=sliceHeightD; y<=sliceHeightU; y++)
        {
            if (masterData[x][y][slice] > (pow(2,DATA_BITDEPTH) - 1) * instrBoundaries[0] && masterData[x][y][slice] < (pow(2,DATA_BITDEPTH) - 1) * instrBoundaries[NUM_INSTR])
            {
                
                value = masterData[x][y][slice];
                currInstr = GetInstrNum(value);
                UpdateScoreLine((float)(x - sliceWidthL)/(float)sliceWidth, (float)(y - sliceHeightD)/(float)sliceHeight, value);

                switch (output)
                {
                    case 0:
                        std::sprintf(scoreLine, "i%d %f %f %d %f %d %f\n", currInstr, startTime, duration, noteIndex, amplitude, currInstr, panValue);
                        scoreFile << scoreLine;
                        break;
                    case 1:
                        std::sprintf(scoreLine, "i%d %f %f %d %d %d %d\n", currInstr, startTime, duration, noteIndex, midiVelocity, currInstr, midiPan);
                        scoreFile << scoreLine;
                        break;
                        
                    default:
                        break;
                }
                
                instrCount[currInstr-1]++;
                // ---------------------------------------------------
                // TEMPO/DURATION VARIATION NEEDS TO BE INCLUDED HERE.
                // ---------------------------------------------------
                
                // duration *= pow(2,NUM_INSTR) / pow(2,currInstr-1);
                // 
                // for (int i=0; i<pow(2,currInstr-1); i++)
                // {
                //     std::sprintf(scoreLine, "i%d %f %f %d %f %f\n", currInstr, startTime + i*duration, duration, noteIndex, panValue, amplitude);
                //     scoreFile << scoreLine;
                // }
            }
            
        }
    }
    
    WriteFooter(scoreFile);
    scoreFile.close();
    
    // -------------------------
    // Csound file execution
    // -------------------------
    system(commandLine);
    
    DisplayDiagnostics(fileLine, flagLine, commandLine, instrCount);
}


// =========================
// CONSTRUCTORS/DESTRUCTORS
// =========================
SonificationEngine::SonificationEngine()
{
    masterData = 0;
    masterDataSize[0] = 0;
    masterDataSize[1] = 0;
    masterDataSize[2] = 0;
    
    mode = 3;
    scan = 1;
    slice = 0;
    instr = 0;
    output = 1;
    strcpy(outputfile,"");
    
//    for (int i=0; i<NUM_INSTR+1; i++)
//    {
//        instrBoundaries[i] = float(maxValue * (i)) / (float)NUM_INSTR;
//    }
    
    // SPECIFIC CASE
    // -------------
    
//    // Non Linear Boundaries
//    instrBoundaries[0] = 0.45;
//    instrBoundaries[1] = 0.55;
//    instrBoundaries[2] = 0.65;
//    instrBoundaries[3] = 0.75;
//    instrBoundaries[4] = 1;

    // Linear Boundaries
    instrBoundaries[0] = 0.50;
    instrBoundaries[1] = 0.625;
    instrBoundaries[2] = 0.75;
    instrBoundaries[3] = 0.875;
    instrBoundaries[4] = 1;
    
}