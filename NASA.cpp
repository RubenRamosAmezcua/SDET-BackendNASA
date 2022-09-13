#include <iostream>
#include "curl/curl.h"
#include "json/json.h"
#include <string>
#include <cstdint>
#include <memory>

#pragma comment (lib, "Normaliz.lib")
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Wldap32.lib")
#pragma comment (lib, "advapi32.lib")
#pragma comment (lib, "crypt32.lib")

namespace
{
    std::size_t callback(
        const char* in,
        std::size_t size,
        std::size_t num,
        std::string* out)
    {
        const std::size_t totalBytes(size * num);
        out->append(in, totalBytes);
        return totalBytes;
    }
}
const std::string url = "https://api.nasa.gov/mars-photos/api/v1/rovers/curiosity/photos?sol=1000&api_key=pXI0cr8DdRgEmMHuWQz8WxitLjegXkSW9HSZldyx";
const std::string My_KEY = "pXI0cr8DdRgEmMHuWQz8WxitLjegXkSW9HSZldyx";
const std::string NASA_1000thMarssol = "https://api.nasa.gov/mars-photos/api/v1/rovers/curiosity/photos?sol=1000&api_key=pXI0cr8DdRgEmMHuWQz8WxitLjegXkSW9HSZldyx";
const std::string NASA_Earth = "https://api.nasa.gov/mars-photos/api/v1/rovers/curiosity/photos?earth_date=";
const std::string NASA_1000_Opportunity = "https://api.nasa.gov/mars-photos/api/v1/rovers/opportunity/photos?sol=1000&api_key=";
const std::string NASA_Spirit = "https://api.nasa.gov/mars-photos/api/v1/rovers/spirit/photos?sol=1000&api_key=";
const std::string NASA_1000cameras = "https://api.nasa.gov/mars-photos/api/v1/rovers/curiosity/photos?sol=1000&camera=";
 

int main()
{

  //  auto etriesArray = {""};
    auto earthday = "";
    int i = 0;
    std::string earthdate = "2015-05-30";

    CURL* curl;


    curl = curl_easy_init();

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    
    //Timeout 10sec
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);
    
    // Response information.
    long httpCode(0);
    std::unique_ptr<std::string> httpData(new std::string());
    // Hook up data handling function.
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);

    // Hook up data container (will be passed as the last parameter to the
    // callback handling function). 
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, httpData.get());

    // Run our HTTP GET command, capture the HTTP response code, and clean up.
    curl_easy_perform(curl);
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
 

    if (httpCode == 200)
    {
        std::cout << "\nGot successful response from " << url << std::endl;

        // Response looks good - done using Curl now.  Try to parse the results
        // and print them out.
        Json::Value jsonData;
        Json::Reader jsonReader;
       
        //get all the data to the JsonReader and parse it so it could be analyzed 
        if (jsonReader.parse(*httpData.get(), jsonData))
        {
          
            std::cout << "Successfully parsed JSON data" << std::endl;
            std::cout << "\nJSON data received:" << std::endl;
           
            
            auto etriesArray = jsonData["photos"];

           
            
            do
            {
                //Print the 10  first pictures.
                auto firstelement = etriesArray[i];
                std::cout << "Picture number" << i +1<< firstelement << "\n";
                i++;
            } while (i <= 9);
        
        ///////////////////////////////////////////////////////////////Get the Earth date //////////////////////////////////////////////////////////
           
            auto earthday = etriesArray[0]["earth_date"];
            std::cout << "date" << 1 << earthday << "\n";

            Json::StreamWriterBuilder builder;
            builder["earth_date"] = "";
            //earthdate = Json::writeString(builder, earthday);

            std::cout << "date11111111111111" << 1 << earthdate << "\n";


        }
        else
        {
            //Error messages
            std::cout << "Could not parse HTTP data as JSON" << std::endl;
            std::cout << "HTTP data was:\n" << *httpData.get() << std::endl;
            return 1;
        }
        
    }
    else
    {
        //URL not correct.
        std::cout << "Couldn't GET from " << url << " - exiting" << std::endl;
        return 1;
    }   

 
  
    /*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

    curl_global_init(0);
    curl = curl_easy_init();

    std :: string url2 = NASA_Earth.c_str() + earthdate + "&api_key=" + My_KEY;

    curl_easy_setopt(curl, CURLOPT_URL, url2);

    //Timeout 10sec
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);

    // Response information.
    long httpCode2(0);
    std::unique_ptr<std::string> httpData2(new std::string());
    // Hook up data handling function.
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);

    // Hook up data container (will be passed as the last parameter to the
    // callback handling function). 
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, httpData2.get());

    // Run our HTTP GET command, capture the HTTP response code, and clean up.
    curl_easy_perform(curl);
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode2);
    curl_easy_cleanup(curl);
    curl_global_cleanup();

    if (httpCode2 == 200)
    {
        std::cout << "\nGot successful response from " << url2 << std::endl;

        // Response looks good - done using Curl now.  Try to parse the results
        // and print them out.
        Json::Value jsonData;
        Json::Reader jsonReader;

        //get all the data to the JsonReader and parse it so it could be analyzed 
        if (jsonReader.parse(*httpData2.get(), jsonData))
        {

            std::cout << "Successfully parsed JSON data" << std::endl;
            std::cout << "\nJSON data received:" << std::endl;
            auto etriesArray = jsonData["photos"];

            do
            {
                //Print the 10  first pictures of the date earth
                auto firstelement = etriesArray[i];
                std::cout << "Picture number" << i + 1 << firstelement << "\n";
                i++;
            } while (i <= 9);
        }
        else
        {
            //Error messages
            std::cout << "Could not parse HTTP data as JSON" << std::endl;
            std::cout << "HTTP data was:\n" << *httpData2.get() << std::endl;
            return 1;
        }

    }
    else
    {
        //URL not correct.
        std::cout << "Couldn't GET from " << url2 << " - exiting" << std::endl;
        std::cout << "HTTP data was:\n" << *httpData2.get() << std::endl;
        std::cout << "HTTP data was:\n" << httpCode2  << std::endl;
        return 1;
    }
    return 0;


  }

