/*
 * Copyright 2010-2011, Sikuli.org
 * Released under the MIT License.
 *
 */

#ifndef _MYOCR_H_
#define _MYOCR_H_

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>

#include "opencv.hpp"
#include "find-result.h"

class OCRRect {
  
public:
   
   OCRRect();
   
   OCRRect(int x_, int y_, int width_, int height_);
   
   int x;
   int y;
   int height;
   int width;
   
protected:
   
   void addOCRRect(const OCRRect& r);
   
};

class OCRChar : public OCRRect{
   
public:
   
   OCRChar() : ch(0), OCRRect(0,0,0,0){};
   OCRChar(char ch_, int x_, int y_, int width_, int height_)
   : ch(ch_), OCRRect(x_,y_,width_,height_){};
   
   char ch;
};

class OCRWord : public OCRRect {

public:
   void add(const OCRChar& ocr_char);
   
   std::string str();
   
    void clear();
   
    bool empty() { return ocr_chars_.empty();};
   
   bool isValidWord();
   
   std::string getString();
   
   std::vector<OCRChar> getChars();

private:   
   std::vector<OCRChar> ocr_chars_;
};

class OCRLine : public OCRRect{
public:
   
   void addWord(OCRWord& word);

   std::string getString();
   std::vector<OCRWord> getWords();

private:   
   
   std::vector<OCRWord> ocr_words_;
};

class OCRParagraph : public OCRRect{
public:  
   
   void addLine(OCRLine& line);
   std::vector<OCRLine> getLines();
   
private:
   
   std::vector<OCRLine> ocr_lines_;
   
};

class OCRText : public OCRRect{

public:   
   void addParagraph(OCRParagraph& ocr_paragraph);
   
   typedef std::vector<OCRWord>::iterator iterator;
   
   void save(const char* filename);
   void save_with_location(const char* filename);
   
   std::vector<std::string> getLineStrings();
   std::vector<std::string> getWordStrings();

   std::string getString();
   
   std::vector<OCRWord> getWords();
   std::vector<OCRParagraph> getParagraphs();

private:
   
   std::vector<OCRParagraph> ocr_paragraphs_;
   
};

class OCR {

public:
   static std::vector<OCRChar> recognize(const unsigned char* imagedata,
                                    int width, int height, int bpp);
   
   static OCRText recognize(cv::Mat mat);
   static std::string recognize_as_string(const cv::Mat& mat);
   
   static std::vector<FindResult> find_word(const cv::Mat& mat, std::string word, bool is_find_one = true);
   
   static std::vector<FindResult> find_phrase(const cv::Mat& mat, std::vector<std::string> words, bool is_find_one = true);   
   
   static OCRText recognize_screenshot(const char* screenshot_filename);
   
      
   static void init();
   static void init(const char* datapath);
   
   
   static int findEditDistance(const char *s1, const char *s2, 
                                 int max_distance=100);
   
private:
   
   static bool isInitialized;
   
};

#endif // _MYOCR_H_
