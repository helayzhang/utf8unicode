###Utf8 <-> Unicode Utility for C++

####HOW TO USE:
The key is using `std::string` to store utf8 data, and `std::vector<unsigned int>` to store unicode data.

You can refer to the header to get more informations:

    Utf8Unicode::utf8_to_unicode(src_string, dst_buffer);
    Utf8Unicode::unicode_to_utf8(src_buffer, dst_string);
