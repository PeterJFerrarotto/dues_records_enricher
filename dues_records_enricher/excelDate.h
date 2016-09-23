#ifndef EXCEL_DATE_H
#define EXCEL_DATE_H

#include <string>
#include <ctime>

namespace excelDate{
	class excelDate
	{
	public:
		excelDate();
		excelDate(const std::string& month, const int monthNum, const int year, const double date);
		excelDate(const double date);
		~excelDate();

		const int getDay();
		const int getYear();
		const int getMonth();
		const int getAmntOwed();
		const double getDispVal();
		const std::string& getDispMonth();
		const int getYearPaidFor();
		const int getMonthPaidFor();

		std::string getMMYYYY();

		const bool before(int month, int date);

		const bool after(int month, int year);

		const std::time_t getDatePaidFor();
	private:
		int month;
		int day;
		int year;
		int amntOwed;
		double dateDispVal;
		std::string dispMonth;
		int yearPaidFor;
		int monthPaidFor;
		struct std::tm datePaidFor;

		void parseData(const std::string& month, const double date);
		void parseData(const double date);
		void setDispMonth();
	};
}
#endif
