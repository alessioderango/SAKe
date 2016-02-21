#include <iostream>
#include <time.h>
#include <string>
#include "../Rain.h"
#include "../Activation.h"
#include "../../timesupport.h"
#include <pqxx/pqxx>

#include "boost/date_time/posix_time/posix_time.hpp"

using namespace std;
using namespace pqxx;
using namespace boost::posix_time;

class DBmanager {
public:
	bool getConnection() {
		C= new connection("dbname=SAKe user=postgres password=alessio hostaddr=127.0.0.1 port=5432");
		if (C->is_open()) {
//			cout << "Opened database successfully: " << C->dbname() << endl;
			return true;
		} else {
//			cout << "Can't open database" << endl;
			return false;
		}
	}

	void disconnect() {
		C->disconnect();
	}

	bool executeQueryRain(Rain *&rain,int &rain_size) {
        string querycount = "select count(*) from rain2 as r where r.\"DATA\" > '1959-09-01' and r.\"DATA\" < '1980-08-31'";
        string query = "select * from rain2 as r where r.\"DATA\" > '1959-09-01' and r.\"DATA\" < '1980-08-31'";

		nontransaction N(*C);
		result RCount(N.exec(querycount.c_str()));
		result::const_iterator ccount = RCount.begin();
		rain_size=ccount[0].as<int>();
        //rain = new Rain[rain_size];
//        cout <<"rain_size "<< rain_size << endl;
        result R(N.exec(query.c_str()));


        rain = new Rain[rain_size];

        int count =0;
        for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
            struct tm tm={0};
            string date1 = c[2].as<string>();
            //strptime(date1.c_str(), "%Y-%m-%d", &tm);
            string a =" 00:00:00.000";
            date1+= a;
            //cout << "raindate Start = " << date1 << endl;
            ptime raindate = time_from_string(date1);
//            std::string ts("1970-01-01");
//            ptime myEpoch(time_from_string(ts)); // Or whatever your epocj is.
//            time_duration myTimeFromEpoch = raindate - myEpoch;
//            boost::int64_t myTimeAsInt = myTimeFromEpoch.ticks();

            //tm = to_tm(raindate);
            //cout << "rain  = " << "    "<<"  "<< tm.tm_hour<< ":" << tm.tm_min << ":"<< tm.tm_sec << "   " <<tm.tm_mday << "-"<< tm.tm_mon << "-"<< 1900+tm.tm_year << endl;

                rain[count] = Rain(to_tm(raindate), c[3].as<double>());
                count++;
        }
//        for (int i = 0; i < count; i++) {
//            std::cout << "count: "
//                         << rain[i].getRainMm() << " s.\n";

//        }



//		cout << "Operation done successfully" << endl;
		return true;
	}

	bool executeQueryActivation(Activation *&activation,int &activation_size) {
		string querycount = "select count(*) from activation";
		string query = "select * from activation";

		nontransaction N(*C);
		result RCount(N.exec(querycount.c_str()));
		result::const_iterator ccount = RCount.begin();
		activation_size=ccount[0].as<int>();
		activation = new Activation[activation_size];
//		cout <<"rain_size "<< activation_size << endl;
		result R(N.exec(query.c_str()));
		int count=0;
		/* List down all the records */
		for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
//			cout << "ID = " << c[0].as<int>() << endl;
//			cout << "Codice SIMI = " << c[1].as<int>() << endl;

			struct tm tmStart={0};
			struct tm tmEnd={0};
            string dateStart = c[1].as<string >();
            string dateEnd = c[2].as<string >();

            //cout << "dateStart = " << dateStart<< endl;
            //cout << "dateEnd = " << dateEnd<< endl;

            ptime start = time_from_string(dateStart);
            ptime end = time_from_string(dateEnd);
            //cout << "tmStart Start = " <<"    "<<"  "<< start << endl;
            //cout << "tmEnd End = " <<"    "<<"  " << end << endl;


            tmStart = to_tm(start);
            tmEnd = to_tm(end);

            //cout << "tmStart Start = " <<"    "<<"  "<< tmStart.tm_hour<< ":" << tmStart.tm_min << ":"<< tmStart.tm_sec << "   " <<tmStart.tm_mday << "-"<< tmStart.tm_mon << "-"<< 1900+tmStart.tm_year << endl;
            //cout << "tmEnd End = " <<"    "<<"  "<< tmEnd.tm_hour<< ":" << tmEnd.tm_min << ":"<< tmEnd.tm_sec << "   " <<tmEnd.tm_mday << "-"<< tmEnd.tm_mon << "-"<< 1900+tmStart.tm_year << endl;

            using boost::posix_time::ptime;
            using namespace boost::gregorian;
            // cout << "milli start = " << (start-ptime(date(1970, Jan, 1))).total_milliseconds() << endl;
            // cout << "milli end = " << (end-ptime(date(1970, Jan, 1))).total_milliseconds() << endl;


            //TODO
            //corregere convervione
            //strptime(dateStart.c_str(), "%Y-%m-%d %H:%M:%S", &tmStart);
            //tmStart.tm_mon+=1;
 //           tmStart = *(gmtime ( &dateStart ));
 //           tmEnd = *(gmtime ( &dateEnd ));
            //strptime(dateEnd.c_str(), "%Y-%m-%d %H:%M:%S", &tmEnd);
            //tmEnd.tm_mon+=1;
			activation[count] = Activation(tmStart, tmEnd);
			count++;
		}
//		cout << "Operation done successfully" << endl;
		return true;
	}

private:
	connection *C;
};

//int main(int argc, char* argv[]) {
//	char * sql;
//	DBmanager db;
//	try {
//		db.getConnection();
//		sql = "select * from rain2";
//		db.executeQuery(sql);
//		db.disconnect();
//
//	} catch (const std::exception &e) {
//		cerr << e.what() << std::endl;
//		return 1;
//	}
//
//}
