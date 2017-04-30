#ifndef PROXIER_H_INCLUDED
#define PROXIER_H_INCLUDED

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

class Proxify{
private:
	string env="/etc/environment";
    string apt="/etc/apt/apt.conf.d/apt.conf";
    ofstream fenv;
    ofstream fapt;
    vector<string> firstfour;
    vector<string> envlist;
    vector<string> aptlist;
    vector<string> gtksettings;

public:
	string proxy;
	string port;
	Proxify():fenv(env),fapt(apt){
        firstfour.push_back("PATH=\"/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games\"");
        firstfour.push_back("");
        firstfour.push_back("no_proxy=localhost,127.0.0.0/8,*.local");
        firstfour.push_back("NO_PROXY=localhost,127.0.0.0/8,*.local");

        envlist.push_back("all_proxy=socks://");
        envlist.push_back("ALL_PROXY=socks://");
        envlist.push_back("http_proxy=http://");
        envlist.push_back("HTTP_PROXY=http://");
        envlist.push_back("ftp_proxy=http://");
        envlist.push_back("FTP_PROXY=http://");
        envlist.push_back("https_proxy=http://");
        envlist.push_back("HTTPS_PROXY=http://");

        aptlist.push_back("Acquire::http::proxy \"http://");
        aptlist.push_back("Acquire::ftp::proxy \"ftp://");
        aptlist.push_back("Acquire::https::proxy \"https://");

        gtksettings.push_back("gsettings set org.gnome.system.proxy mode 'none'");
	};
	bool created(){
		if(fenv.is_open()==true && fapt.is_open()==true){
			cout<<"Gained access to proxy files"<<endl;
			return true;
		}
		else{
			cout<<"Please run mint_proxy_on then restart this application"<<endl;
			return false;
		}
	};

	void removeProxy(ostream &os){
		fapt.app;
		fapt<<"";

		const char *gtk=gtksettings.at(0).c_str();
		system(gtk);

		fenv.app;
		fenv<<"";

		os<<"okay, done removing proxy, application exiting\n";
	};

	void torProxy(ostream &os){
		proxy="127.0.0.1";
		port="8118";

		//gtk settings
		gtksettings.push_back("gsettings set org.gnome.system.proxy mode 'manual'");
		gtksettings.push_back("gsettings set org.gnome.system.proxy.http host '"+proxy+"'");
		gtksettings.push_back("gsettings set org.gnome.system.proxy.http port "+port);

        for(string &s:gtksettings){
			system(s.c_str());
        }

        //for apt.conf
        string aptproxy=proxy+":"+port+"/\";";
        for(string &s:aptlist){
			fapt.app;
			string t=s+aptproxy+"\n";
			fapt<<t;
        }

        //for env
        string envproxy=proxy+":"+port;
        for(string &s:firstfour){
			fenv.app;
			string t=s+"\n";
			fenv<<t;
        }
        int i=0;
        for(string &s:envlist){
			if(i<2){
				fenv<<s+envproxy+"/\n";
				++i;
			}else{
				fenv<<s+envproxy+"\n";
			}
        }

        os<<"Done, now please make sure you have privoxy and tor already running, thank you."<<endl;
	};

	void manualProxy(ostream &os,string &pr,string &po){

		proxy=pr;
		port=po;

		//gtk settings
		gtksettings.push_back("gsettings set org.gnome.system.proxy mode 'manual'");
		gtksettings.push_back("gsettings set org.gnome.system.proxy.http host '"+proxy+"'");
		gtksettings.push_back("gsettings set org.gnome.system.proxy.http port "+port);

        for(string &s:gtksettings){
			system(s.c_str());
        }

        //for apt.conf
        string aptproxy=proxy+":"+port+"/\";";
        for(string &s:aptlist){
			fapt.app;
			string t=s+aptproxy+"\n";
			fapt<<t;
        }

        //for env
        string envproxy=proxy+":"+port;
        for(string &s:firstfour){
			fenv.app;
			string t=s+"\n";
			fenv<<t;
        }
        int i=0;
        for(string &s:envlist){
			if(i<2){
				fenv<<s+envproxy+"/\n";
				++i;
			}else{
				fenv<<s+envproxy+"\n";
			}
        }

        os<<"Done, you can now use your new proxy"<<proxy<<":"<<port<<"\nENJOY!!!";

	};
};


#endif // PROXIER_H_INCLUDED
