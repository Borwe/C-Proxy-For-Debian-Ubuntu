#include <iostream>
#include "proxier.h"

using namespace std;

int main()
{
    cout<<"starting.... proxy changer"<<endl;
    Proxify p;

    if(p.created()==false){
		return -1;
    }

    error:
    cout<<"Okay, now please choose one of the following options bellow"<<endl;
    cout<<"1, remove proxy\t"<<endl<<"2, use tor proxy\t"<<endl;
    cout<<"3, enter manual proxy"<<endl;

    int opt;


    if(cin>>opt && (opt==1 || opt==2 || opt==3)){
		if(opt==1){
			p.removeProxy(cout);
		}else if(opt==2){
			p.torProxy(cout);
		}else if(opt==3){
			string proxy;
			string port;
			cout<<"Please input Proxy bellow:"<<endl;
			cin>>proxy;
			cout<<"Please input port bellow:"<<endl;
			cin>>port;
			p.manualProxy(cout,proxy,port);
		}
    }else{
		cout<<"You did not choose a valid option"<<endl;
		cin.clear();
		goto error;
    }

    return 0;
}
