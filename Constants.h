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
#define NUMBERS_LOG "numbers_log.csv"
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
#define MODE_ONE_FREQ 440
#define DETUNE_FACTOR 0.1

// =============================
// Brain Lobes parameters
// =============================

#define PERSPSLICE 0
#define FPSLICE 30
#define TOSLICE 68

#define AX 14
#define AY 37

#define BX 28
#define BY 45

#define CX 26
#define CY 57

#define DX 7
#define DY 50

#define EX 72
#define EY 37

#define FX 75
#define FY 54

#define GX 58
#define GY 59

#define HX 52
#define HY 44

#define IX 11
#define IY 65

#define JX 32
#define JY 59

#define KX 43
#define KY 70

#define LX 53
#define LY 56

#define MX 0
#define MY 67

#define NX 149
#define NY 0

#define OX 193
#define OY 0

#define PX 148
#define PY 132

#define QX 111
#define QY 147

#define ORTHOGL_MIDLINE 43
#define PERSPEC_MIDLINE 321.5
#endif

