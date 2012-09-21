#ifndef _MOGILEFS_H
#define _MOGILEFS_H

#include <errno.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <pcre++.h>
#include <curl/curl.h>
#include <curl/easy.h>
#include <linux/types.h>
#include <socket++/protocol.h>

#define MAX_MSG_LENGTH  1024
#ifndef DEBUG
#define DEBUG 1
#else
#define DEBUG 0
#endif

namespace MogileFS 
{
    typedef protocol iProto;
    typedef std::vector<std::string> str_vector;
    typedef std::vector<std::string>::iterator vector_it;

    std::string const MOGFS_REQ_OK = "OK";
    str_vector splitString(std::string target, std::string token);

    class Proto : public iProto
    {
        public: 
            class iProtoBuf : public iProto::protocolbuf
            {
                public:
                    iProtoBuf(): iProto::protocolbuf(protocol::tcp){}
                    void serve_clients (int portno =-1){}
                    const char * rfc_name() const { return "mogilefs"; } 
                    const char * rfc_doc() const { return ""; }
            };

        public:
            Proto(): std::ios(0) { m_pBuf = new iProtoBuf(); std::ios::init(m_pBuf); }
            iProtoBuf* buf() { return (iProtoBuf *) protocol::rdbuf(); }
            iProtoBuf *m_pBuf;

    };

    class ClientLib
    {
        public:
            ClientLib(std::string tracker, int port);
            ~ClientLib() {}

            str_vector getPaths(std::string domain, std::string key, std::string extra);
            std::string getFile(std::string domain, std::string key);

        private:
            //This has to be static as cURL likes it that way
            static int writeData(char *ptr, size_t size, size_t nmemb, std::string *buffer);
            std::string sFILE;

            int m_iPort;
            Proto *m_pCli;
            bool m_bConnected;
            std::string m_sFile;
            std::string m_sTracker;
    };
}


#endif //define _MOGILEFS++_H
