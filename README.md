libmogfs++
==================================

This is a C++ library that allows to query and fetch files from 
a MogileFS cluster. 

This is an alpha version yet.

==================================
Usage:

It is as simple as:

// Test file
//MogFS
#include <mogilefs++/mogilefs++>

[...]

std::string key;
std::string domain;
std::string picFile;

//MogileFS namespace
MogileFS::ClientLib *client;

[...]

client = new MogileFS::ClientLib("mogile.server.com", 6001);
picFile = client->getFile(domain, key);

[...]

Done!.
==================================
Requirements:

This library uses:

cURL
pcre++
socket++

==================================
Compiling and installing:

./configure
make
sudo make install

Then, link your code to libmogfs++
