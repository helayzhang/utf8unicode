/*******************************************************************************
 *
 *      @file: utf8unicode.hh
 *
 *      @brief: 
 *
 *      @author: Helay Zhang.
 *               helayzhang@gmail.com
 *
 *      COPYRIGHT (C) 2013.
 *
 ******************************************************************************/
#ifndef UTF8UNICODE_hh_INCLUDED
#define UTF8UNICODE_hh_INCLUDED

#include <string>
#include <vector>

class Utf8Unicode {
public:
    static bool utf8_to_unicode(const std::string &utf8, std::vector<unsigned int> &unicode) {
        unsigned int utf8length = utf8.size();
        unsigned int utf8_cursor = 0;
        unsigned int offset;
        unsigned char* p;
        unsigned int e;
        unicode.clear();
        while (utf8_cursor < utf8length) {
            p = (unsigned char*)&utf8[utf8_cursor];
            if (*p < 0xC0) {
                offset = 0;
                e = p[0];
            }
            else if (*p < 0xE0) {
                /*2:<11000000>*/
                offset = 1;
                if (not check_length(utf8_cursor, offset, utf8length)) return false;
                e = (p[0] & 0x1f) << 6;
                e |= (p[1] & 0x3f);
            }
            else if (*p < 0xF0) {
                /*3:<11100000>*/
                offset = 2;
                if (not check_length(utf8_cursor, offset, utf8length)) return false;
                e = (p[0] & 0x0f) << 12;
                e |= (p[1] & 0x3f) << 6;
                e |= (p[2] & 0x3f);
            }
            else if (*p < 0xF8) {
                /*4:<11110000>*/
                offset = 3;
                if (not check_length(utf8_cursor, offset, utf8length)) return false;
                e = (p[0] & 0x07) << 18;
                e |= (p[1] & 0x3f) << 12;
                e |= (p[2] & 0x3f) << 6;
                e |= (p[3] & 0x3f);
            }
            else if (*p < 0xFC) {
                /*5:<11111000>*/
                offset = 4;
                if (not check_length(utf8_cursor, offset, utf8length)) return false;
                e = (p[0] & 0x03) << 24;
                e |= (p[1] & 0x3f) << 18;
                e |= (p[2] & 0x3f) << 12;
                e |= (p[3] & 0x3f) << 6;
                e |= (p[4] & 0x3f);
            }
            else {
                /*6:<11111100>*/
                offset = 5;
                if (not check_length(utf8_cursor, offset, utf8length)) return false;
                e = (p[0] & 0x01) << 30;
                e |= (p[1] & 0x3f) << 24;
                e |= (p[2] & 0x3f) << 18;
                e |= (p[3] & 0x3f) << 12;
                e |= (p[4] & 0x3f) << 6;
                e |= (p[5] & 0x3f);
            }
            unicode.push_back(e);
            utf8_cursor += offset + 1;
        }
        return true;
    }

    static void unicode_to_utf8(const std::vector<unsigned int> &unicode, std::string &utf8) {
        unsigned int unicodelength = unicode.size();
        unsigned int unicode_cursor = 0;
        unsigned int offset;
        unsigned int u;
        unsigned char* e;
        utf8.clear();
        while (unicode_cursor < unicodelength) {
            u = unicode[unicode_cursor];
            if (u < 0x80) {
                offset = 0;
                utf8.push_back(u);
            }
            else if (u < 0x800) {
                /*<11011111> < 000 0000 0000>*/
                offset = 1;
                utf8.push_back(((u >> 6) & 0x1f)|0xc0);
                utf8.push_back((u & 0x3f)|0x80);
            }
            else if(u < 0x10000) {
                /*<11101111> <0000 0000 0000 0000>*/
                offset = 2;
                utf8.push_back(((u >> 12) & 0x0f)|0xe0);
                utf8.push_back(((u >> 6) & 0x3f)|0x80);
                utf8.push_back((u & 0x3f)|0x80);
            }
            else if(u < 0x200000) {
                /*<11110111> <0 0000 0000 0000 0000 0000>*/
                offset = 3;
                utf8.push_back(((u >> 18) & 0x07)|0xf0);
                utf8.push_back(((u >> 12) & 0x3f)|0x80);
                utf8.push_back(((u >> 6) & 0x3f)|0x80);
                utf8.push_back((u & 0x3f)|0x80);
            }
            else if(u < 0x4000000) {
                /*<11111011> <00 0000 0000 0000 0000 0000 0000>*/
                offset = 4;
                utf8.push_back(((u >> 24) & 0x03)|0xf8);
                utf8.push_back(((u >> 18) & 0x3f)|0x80);
                utf8.push_back(((u >> 12) & 0x3f)|0x80);
                utf8.push_back(((u >> 6) & 0x3f)|0x80);
                utf8.push_back((u & 0x3f)|0x80);
            }
            else {
                /*<11111101> <0000 0000 0000 0000 0000 0000 0000 0000>*/
                offset = 5;
                utf8.push_back(((u >> 30) & 0x01)|0xfc);
                utf8.push_back(((u >> 24) & 0x3f)|0x80);
                utf8.push_back(((u >> 18) & 0x3f)|0x80);
                utf8.push_back(((u >> 12) & 0x3f)|0x80);
                utf8.push_back(((u >> 6) & 0x3f)|0x80);
                utf8.push_back((u & 0x3f)|0x80);
            }
            unicode_cursor++;
        }
    }

private:
    static bool check_length(unsigned int start, unsigned int offset, unsigned int end) {
        if (start + offset >= end) {
            return false;
        }
        return true;
    }
};

#endif
