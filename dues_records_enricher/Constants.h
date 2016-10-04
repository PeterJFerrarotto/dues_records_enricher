#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <string>
#include <vector>

using namespace std;

namespace ColumnConstants {
	static char* NAME = "NAME:";
	static const size_t NAMER = 0;
	static const size_t NAMEC = 0;

	static char* BOOKNUM = "NO.";
	static const size_t BOOKNUMR = 4;
	static const size_t BOOKNUMC = 0;

	static char* INITDATE = "DATE OF INIT";
	static const size_t INITDATER = 4;
	static const size_t INITDATEC = 2;

	static char* MONTH = "MONTH";
	static const size_t MONTHR = 6;

	static char* YEAR = "YEAR";
	static const size_t YEARR = 6;


	static char* JAN = "JAN";
	static const size_t JANR = 8;

	static char* FEB = "FEB";
	static const size_t FEBR = 9;

	static char* MAR = "MAR";
	static const size_t MARR = 10;

	static char* APR = "APR";
	static const size_t APRR = 11;

	static char* MAY = "MAY";
	static const size_t MAYR = 12;

	static char* JUNE = "JUNE";
	static const size_t JUNER = 13;

	static char* JULY = "JULY";
	static const size_t JULYR = 14;

	static char* AUG = "AUG";
	static const size_t AUGR = 15;

	static char* SEPT = "SEPT";
	static const size_t SEPTR = 16;

	static char* OCT = "OCT";
	static const size_t OCTR = 17;

	static char* NOV = "NOV";
	static const size_t NOVR = 18;

	static char* DEC = "DEC";
	static const size_t DECR = 19;

	//Full Month Names:

	static char* JANf = "January";

	static char* FEBf = "February";

	static char* MARf = "March";

	static char* APRf = "April";

	static char* AUGf = "August";

	static char* SEPTf = "September";

	static char* OCTf = "October";
	
	static char* NOVf = "November";

	static char* DECf = "December";

	//Year/Month Columns:

	static char* YEAR_2010 = "2010";
	static const size_t YEAR_2010C = 1;

	static char* YEAR_2011 = "2011";
	static const size_t YEAR_2011C = 3;

	static char* YEAR_2012 = "2012";
	static const size_t YEAR_2012C = 5;

	static char* YEAR_2013 = "2013";
	static const size_t YEAR_2013C = 7;

	static char* YEAR_2014 = "2014";
	static const size_t YEAR_2014C = 9;

	static char* YEAR_2015 = "2015";
	static const size_t YEAR_2015C = 11;

	static char* YEAR_2016 = "2016";
	static const size_t YEAR_2016C = 13;

	static char* ASSESSMENTS = "ASSESSMENTS-FINES-ETC";
	static const size_t ASSESSMENTSR = 37;
	static const size_t ASSESSMENTSC = 0;

	static char* ASSESSDATE = "DATE";
	static const size_t ASSESSDATER = 38;
	static const size_t ASSESSDATEC = 0;

	static char* ASSESSITEM = "ITEM";
	static const size_t ASSESSITEMR = 38;
	static const size_t ASSESSITEMC = 1;

	static char* ASSESSREMARKS = "REMARKS";
	static const size_t ASSESSREMARKSR = 38;
	static const size_t ASSESSREMARKSC = 2;

	static const size_t YEARNUMR = 7;

	//Address location:
	static char* ADDRESSTEXT = "ADDRESS";
	static const size_t ADDRESSR = 2;
	static const size_t ADDRESSC = 1;
}

namespace fileDirecs{
	//static char const direc[360] = "C:/Users/Peter/Documents/Dues Records/Book Men/";
	//static char const addrDirec[360] = "C:/Users/Peter/Documents/Dues Records/Book Men/addresses.xls";
	//static char const direc[360] = "C:/Users/Home-PC/Desktop/Dues Records/Book Men/";
	//static char const addrDirec[360] = "C:/Users/Home-PC/Desktop/Dues Records/Book Men/addresses.xls";
	static char const direc[360] = "C:/Users/peter/My Documents/Dues Records/Book Men/";
	//static char const addrDirec[360] = "C:/Users/Peter/Desktop/Dues Records/Book Men/addresses.xls";

	//static const char* saveDirec = "C:/Users/Peter/Documents/Dues Records/Book Men/enrichedBookRecords.xls";

	//static const char* saveDirec = "C:/Users/Home-PC/Desktop/Dues Records/Book Men/enrichedBookRecords.xls";

	static const char* saveDirec = "C:/Users/peter/My Documents/Dues Records/Book Men/enrichedBookRecords.xls";
	static const vector<char*> dirLetters = { "A/", "B/", "C/", "D/", "E/", "F/", "G/", "H/", "I/", "J/", "K/", "L/", "M/", "N/", "O/", "P/", "Q/", "R/", "S/", "T/", "U/", "V/", "W/", "XYZ/" };
	
	static const char* workSheetName = "2010-2014";

	static const char* saveWorkSheetName = "Book Men";
	static const char* saveWorkSheetDetailsName = "Book Men Details";
}

namespace exceptions{
	static const string direcNotFound = "Directory not found: ";
	static const string monthIsZero = "Month is zero!";
	static const string monthOutOfRange = "Month is outside of range!";
	static const string worksheetNotFound = "Worksheet 2010-2014 not found!";
	static const string undefinedMonth = "Error: Undefined cell found in Month column!";
}

namespace defaultValues{
	static const int defaultFee = 39;
	static const int retiredFee = 3;
}

#endif