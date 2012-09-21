#include <mogilefs++/mogilefs++>

namespace MogileFS
{
    str_vector splitString(std::string target, std::string token)
    {           
        pcrepp::Pcre regex(token, "g");
        str_vector splitted;
                            
        splitted = regex.split(target);
        return splitted;
    }   

    ClientLib::ClientLib(std::string tracker, int port)
    {
        m_iPort = port;
        m_sTracker = tracker;

        m_bConnected = false;

        m_pCli = new Proto();
        try {
            m_pCli->buf()->connect(m_sTracker.c_str(), m_iPort);

            if(DEBUG > 0)
                std::cout << "Connected: " << std::endl;

            m_bConnected = true;

        } catch(std::exception &e) {

            if (DEBUG > 0)
                std::cout << "Could not Connect, errno: " << errno << std::endl;

        }
    }

    str_vector ClientLib::getPaths(std::string domain, std::string key, std::string extra)
    {
        int subhlp;
        std::string path; 
        std::string auxbuf; 
        str_vector tmpres;
        str_vector result;
        vector_it it;
        
        path = "get_paths domain=" + domain + "&key=" + key;

        if(extra.length() > 0)
            path = path + "&" + extra;

        (*m_pCli) << path + "\r\n" << std::flush;
        std::getline((*m_pCli), auxbuf);

        if(auxbuf.length() > 0) {

            if(DEBUG > 0)
                std::cout << "Received: " << auxbuf << std::endl;

            subhlp = MOGFS_REQ_OK.length();

            if(auxbuf.substr(0, subhlp) == MOGFS_REQ_OK) {

                if(DEBUG > 0)
                    std::cout << "Request OK" << std::endl;
                
                //Let's parse the paths.
                tmpres = splitString(auxbuf.substr(subhlp + 1), "&");

                for(it=tmpres.begin(); it != tmpres.end(); it++)
                {
                    if((*it).substr(0, 6) != "paths=")
                    {
                        result.push_back((*it).substr(6));
                    }
                }
            }
        }
        
        return result;
    }

    int ClientLib::writeData(char *data, size_t size, size_t nmemb,  
                     std::string *buffer)  
    {  
        int result = 0;  

        if (buffer != NULL)  
        {  
            buffer->append(data, size * nmemb);  
            result = size * nmemb;  
        }  
                                         
        return result;  
    }  

    std::string ClientLib::getFile(std::string domain, std::string key)
    {
        vector_it it;
        str_vector paths;
        
        m_sFile = "";
        paths = getPaths(domain, key, "noverify=0");

        CURL *curl;
        CURLcode res;

        curl = curl_easy_init();
        if(curl)
        {
            for(it=paths.begin(); it != paths.end(); it++)
            {
                curl_easy_setopt(curl, CURLOPT_URL, (*it).c_str());
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &ClientLib::writeData);
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, &m_sFile);

                res = curl_easy_perform(curl);

                if(DEBUG > 0)
                    std::cout << "RESULT: " << res << std::endl;

                if(res == CURLE_OK)
                    break;
            }
            
            curl_easy_cleanup(curl);
        }

        return m_sFile;
    }
}
