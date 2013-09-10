//
//  Constants.h
//  SoniScan_2_0
//
//  Created by Hariharan Mohanraj on 12/5/12.
//  Copyright (c) 2012 Hariharan Mohanraj. All rights reserved.
//

#ifndef SoniScan_2_0_Constants_h
#define SoniScan_2_0_Constants_h

// ================================
// Global parameters
// ================================
#ifndef M_PI
#define M_PI  (3.14159265)
#endif

#define DIAGNOSTIC 1

// ===========================
// Portaudio parameters
// ===========================

#define BUFFER_SIZE 4096
#define SAMPLE_RATE 44100
#define PI 3.14159265
typedef float sample;

// =========================
// AudioBlockBase parameters
// =========================

#define MAX_NUM_CHANNELS 10
#define MAX_NUM_SINEGENS 10
#define MAX_NUM_PANNERS  10
#define MAX_NUM_AMPERS   10

// =======================
// File paths
// =======================
#define CSOUND_PATH ""	//"/usr/local/bin/"    //  <---- Change this to the path where you have Csound installed. (usually "/usr/local/bin/")
#define TEST_DATA_PATH "./DataFiles/"
#define CSOUNDFILES_PATH "./CsoundFiles/"  //  <---- Change this to the path where you are storing your CSound files for this project
#define OUTPUT_PATH "./Output/"
// =======================
// ControlBlock parameters
// =======================


#define TEST_DATA_FILENAME_1 "test_a"
#define TEST_DATA_FILENAME_2 "test_b"
#define TEST_DATA_FILENAME_3 "test_c"
#define TEST_DATA_FILENAME_4 "test_d"
#define DATA_BITDEPTH 15
#define TRIM_THRESHOLD 0.45

// =============================
// SonificationEngine parameters
// =============================

#define NUM_MODES 3
#define NUM_SCANS 3
#define TEMPO 60.0



#define CSOUND_FLAGS "-g -d" // <---- Csound flags
#define MAX_ABSSCOREFILE 1024
#define MAX_SCORELINE_LENGTH 256
#define MAX_NOTE_INDEX 36
#define NUM_INSTR 4
#define NUM_BEATS 12
#define NUM_OUTPUTS 2

#endif

