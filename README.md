####Utf8 convert to Unicode, Unicode convert to Utf8. Writtern by Cplusplus.

To convert utf8 into unicode, you should prepare your input(utf8 string) in a std::string variable, and prepare a std::vector<unsigned int> for output use. Then call like: 

####Utf8Unicode::utf8_to_unicode(src_string, dst_buffer);

To convert unicode into utf8, you should prepare you input(unicode buffer) in a std::vector<unsigned int> variable, and prepare a std::string for output use. Then call like: 

####Utf8Unicode::unicode_to_utf8(src_buffer, dst_string);
