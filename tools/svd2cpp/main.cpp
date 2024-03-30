// ---------------------------------------------
//           This file is part of
//      _  _   __    _   _    __    __
//     ( \/ ) /__\  ( )_( )  /__\  (  )
//      \  / /(__)\  ) _ (  /(__)\  )(__
//      (__)(__)(__)(_) (_)(__)(__)(____)
//
//     Yet Another HW Abstraction Library
//      Copyright (C) Andreas Terstegge
//      BSD Licensed (see file LICENSE)
//
// ---------------------------------------------
//
// Small program to convert a SVD file into a C++
// structure. Not all features of SVD are yet supported!
//
#include <string>
#include <iostream>
#include <unistd.h>

#include "tinyxml2.h"
#include "svd2cpp.h"

using namespace std;
using namespace tinyxml2;

void usage() {
    cout << "Usage: svd2cpp [-o outfile] <svd-file>"<< endl;
    cout << endl;
    cout << "-o outfile  : The output filename. Default is <file>.h" << endl;
    cout << "<svd-file>  : A valid SVD file" << endl;
    exit(1);
}

int main(int argc, char *argv[]) {
    string infile;
    string outfile;
    int opt;
    while ((opt = getopt(argc, argv, ":o:")) != -1) {
        switch (opt) {
            case 'o': {
                outfile = optarg;
                break;
            }
            case ':': {
                cerr << "Option needs a value!" << endl;
                usage();
                break;
            }
            default:
            case '?': {
                cerr << "Unknown option '" << (char)optopt << "'" << endl;
                usage();
                break;
            }
        }
    }

    if (optind == (argc-1)) {
        infile = argv[optind];
    } else {
        cerr << "No or too many filenames given!" << endl;
        usage();
    }

    // Process the file name
    size_t dot = infile.find_last_of('.');
    string name_we;
    if (dot != string::npos) {
        name_we = infile.substr(0, dot);
    } else {
        name_we = infile;
    }
    if(outfile.empty()) {
        outfile = name_we + ".h";
    }

    // Parse the SVD file
    XMLDocument svd;
    cout << "Reading file " << infile << endl;
    XMLError ret = svd.LoadFile(infile.c_str());
    if (ret != XML_SUCCESS) {
        cerr << "Can not load file " << infile
             << ", Error code: "     << ret
             << endl;
        exit(1);
    }

    // Find the root element
    XMLElement *elem = svd.RootElement();
    if (elem == nullptr) {
        cerr << "Can not find root element in file " << infile
             << endl;
        exit(1);
    }

    // Start the translation process
    svd2cpp::inst.processSvdFile(infile, outfile, elem);
    return 0;
}
