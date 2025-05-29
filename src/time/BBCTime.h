
/*
 
 Time
 BBCUtils
 
 Utilities for dates and time
 
 Adam Hinshaw 2025
 
 */

#ifndef bbcTime_h
#define bbcTime_h

#include "ofMain.h"

#include <Poco/Timestamp.h>
#include <Poco/DateTime.h>
#include <Poco/DateTimeFormatter.h>
#include <Poco/DateTimeParser.h>
#include <Poco/DateTime.h>

#define bbcSQLDateStampFormat "%Y-%m-%d %H:%M:%S"    // "YYYY-MM-DD HH:MM:SS" : Format SQLite needs to save dates (or could just use  DateTimeFormat::SORTABLE_FORMAT for this..)
#define bbcSQLDayFormat "%Y-%m-%d"                   // "YYYY-MM-DD"
#define bbcSQLTimeFormat "%H:%M:%S"                  // "HH:MM:SS"
#define bbcSQLTimeFormatWithMS "%H:%M:%S:%i"	    //"HH:MM:SS:MSS"
// see: https://pocoproject.org/docs/Poco.DateTimeFormatter.html

namespace bbc {

    namespace utils {
	
		//--------------------------------------------------------------------------------------
		static const string getUpTimeStr(bool show_secs = true) {
            // Return formated string of how long has this app been running.
            
            unsigned long total_up_secs = ofGetElapsedTimeMillis() / 1000;
            
            int dys = (int) floor(total_up_secs / 86400); // 86400 == 60 * 60 * 24, seconds in a day.
            int hrs = (int) floor((total_up_secs % 86400) / 3600); // 3600 == 60 * 60. secopnds in an hour
            int mins = (int) floor(((total_up_secs % 86400) % 3600) / 60);
            int secs = (total_up_secs % 86400) % 3600 % 60;
            
            stringstream out;
            out << "up:" << dys << "d," << hrs << "h," << mins << "m," << secs << "s";
            return out.str();
        }
	
		//--------------------------------------------------------------------------------------
        static float HMSFtoSeconds(const string & input, int frame_rate = 25) {
            // take 0:03:29:17 return (3*60) + 29 + ()
            vector<string> parts = ofSplitString(input, ":", false, true);
            if(parts.size() == 4) {
                int hours = ofToInt(parts[0]);
                int mins = ofToInt(parts[1]);
                int secs = ofToInt(parts[2]);
                float frames = ofToFloat(parts[3]);
                
                return (hours * 3600) + (mins * 60) + secs + (frames / (float)(frame_rate));
            }else{
                ofLogError("HMSFtoSeconds illegal part count. Can't parse") << parts.size() << " 4 expected '" << input << "'";
                return -1.0;
            }
        }
	
		//--------------------------------------------------------------------------------------
        static string secondsToHMS(int totalSeconds) {
            int hours   = floor(totalSeconds / 3600);
            int minutes = floor((totalSeconds - (hours * 3600)) / 60);
            int seconds = round(totalSeconds - (hours * 3600) - (minutes * 60));
            
            return ofToString(hours, 2, '0') + ":" + ofToString(minutes, 2, '0') + ":" + ofToString(seconds, 2, '0');
        }
	
		//--------------------------------------------------------------------------------------
        static string getNowSQLDateStamp() {
            // "2015-02-23 15:39:22"
            Poco::LocalDateTime now;
            return Poco::DateTimeFormatter::format(now, bbcSQLDateStampFormat);
        }
	
		//--------------------------------------------------------------------------------------
        static string getSQLDateStamp(Poco::LocalDateTime & t) {
            return Poco::DateTimeFormatter::format(t, bbcSQLDateStampFormat);
        }
	
		//--------------------------------------------------------------------------------------
        static string getNowSQLDay() {
            // "2015-02-23"
            Poco::LocalDateTime now;
            return Poco::DateTimeFormatter::format(now, bbcSQLDayFormat);
        }
	
		//--------------------------------------------------------------------------------------
        static string getNowTime() {
            // Time "15:39:22"
            Poco::LocalDateTime now;
            return Poco::DateTimeFormatter::format(now, bbcSQLTimeFormat);
        }
	
		//--------------------------------------------------------------------------------------
		static string getNowTimeWithMS() {
			// time with ms "15:39:22:230"
			Poco::LocalDateTime now;
			return Poco::DateTimeFormatter::format(now, bbcSQLTimeFormatWithMS);
		}
	
		//--------------------------------------------------------------------------------------
        static unsigned int getNowSeconds() {
            return ofGetUnixTime();
        }
	
		//--------------------------------------------------------------------------------------
        static bool isToday(Poco::LocalDateTime & date) {
            Poco::LocalDateTime today;
            
            if(date.day() == today.day() && date.month() == today.month() && date.year() == today.year()) {
                return true;
            }
            
            return false;
        }
	
		//--------------------------------------------------------------------------------------
        static bool isYesterday(Poco::LocalDateTime & date) {
            Poco::LocalDateTime today;
            
            if(date.day() == today.day() && date.month() == today.month() && date.year() == today.year()) {
                return false; // it's today.
            }
            
            Poco::Timespan difference = today - date;
            
          //  int h = difference.totalHours();
          //  int m = difference.totalMinutes();
          //  int s = difference.totalSeconds();
            
            if(difference.totalHours() <= 24) {
                return true;
            }
            
            return false;
        }
	
		//--------------------------------------------------------------------------------------
       /* static string secondsToMS(int totalSeconds) {
            int hours   = floor(totalSeconds / 3600);
            int minutes = floor((totalSeconds - (hours * 3600)) / 60);
            int seconds = round(totalSeconds - (hours * 3600) - (minutes * 60));
            
            return ofToString(minutes) + ":" + ofToString(seconds, 2, '0');
        }
        
        static string minsToHMS(float totalMins) {
            return secondsToHMS((int)(totalMins * 60));
        }
        
        static string minsToMS(float totalMins) {
            return secondsToMS((int)(totalMins * 60));
        }*/
	
		//--------------------------------------------------------------------------------------
        static string msToHMS(int totalMS) {
            
            int totalSeconds = totalMS/1000.0;
          //  int ms = totalMS % 1000;
            
            int hours   = floor(totalSeconds / 3600);
            int minutes = floor((totalSeconds - (hours * 3600)) / 60);
            int seconds = round(totalSeconds - (hours * 3600) - (minutes * 60));
            
            return ofToString(hours, 2, '0') + ":" + ofToString(minutes, 2, '0') + ":" + ofToString(seconds, 2, '0');
        }
	
		//--------------------------------------------------------------------------------------
        static string msToMS(int totalMS, bool show_ms = false, int ms_pad = 3) {
            
            int totalSeconds = totalMS/1000.0;
            
            int ms = totalMS % 1000;
            
            int hours   = floor(totalSeconds / 3600);
            int minutes = floor((totalSeconds - (hours * 3600)) / 60);
            int seconds = round(totalSeconds - (hours * 3600) - (minutes * 60));
            
            string ms_str = show_ms ? "." + ofToString(ms, ms_pad, '0') : "";
            
            /*if(show_ms) {
             ms_str = "." + ms_pad ? ofToString(ms, 3, '0') : ofToString(ms);
             }*/

            return ofToString(minutes) + ":" + ofToString(seconds, 2, '0') + ms_str;
        }
	
		//--------------------------------------------------------------------------------------
        static float msToFrames( const int ms, unsigned int frameRate = 0) {
            
            frameRate = (frameRate == 0) ? ofGetFrameRate() : frameRate;
            
            return frameRate*(ms/1000.0);
        }
	
		//--------------------------------------------------------------------------------------
        static const string getUnixTimeStamp(bool show_ms = false) {
            // get now in format  YYYYMMDDHHMMSSmmm
            std::ostringstream format;
            format << "%Y%m%d%H%M%S" << (show_ms ? "%i" : "");
            
            return ofGetTimestampString(format.str());
        }
        
    
    }

}
#endif /* bbcTime_h */
 
