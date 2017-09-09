#include "server.h"
#include <iostream>

using namespace std;

int main()
{
    try{
        WheelHttp http;
        cout<<"Port : "<<http.port()<<endl;
        http.startup();
    } catch(const server_error & err){
        cout<<err.what()<<endl;
    }

    cout << "Hello World!" << endl;
    exit(0);
}

