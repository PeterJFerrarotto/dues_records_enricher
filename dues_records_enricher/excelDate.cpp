#include "excelDate.h"
#include <string>
#include <ctime>
#include <stdio.h>
#include <algorithm>
#include "Constants.h"
using namespace std;

namespace excelDate{
	excelDate::excelDate()
	{
	}

	excelDate::excelDate(const string& month, const int monthNum, const int year, const double date){
		try{
			dispMonth = month;
			monthPaidFor = monthNum;
			parseData(month, date);
			yearPaidFor = year;
			dateDispVal = date;
		}
		catch (const string& e){
			throw e;
		}
	}
	
	excelDate::excelDate(const double date){
		parseData(date);
	}

	excelDate::~excelDate()
	{
	}

	const int excelDate::getDay(){
		return day;
	}

	const int excelDate::getYear(){
		return year;
	}

	const int excelDate::getMonth(){
		return month;
	}

	const int excelDate::getAmntOwed(){
		return amntOwed;
	}

	const double excelDate::getDispVal(){
		return dateDispVal;
	}

	const string& excelDate::getDispMonth(){
		return dispMonth;
	}

	void excelDate::setDispMonth(){
		switch (monthPaidFor){
		case 0:
			throw exceptions::monthIsZero;
			break;
		case 1:
			dispMonth = ColumnConstants::JAN;
			break;
		case 2:
			dispMonth = ColumnConstants::FEB;
			break;
		case 3:
			dispMonth = ColumnConstants::MAR;
			break;
		case 4:
			dispMonth = ColumnConstants::APR;
			break;
		case 5:
			dispMonth = ColumnConstants::MAY;
			break;
		case 6:
			dispMonth = ColumnConstants::JUNE;
			break;
		case 7:
			dispMonth = ColumnConstants::JULY;
			break;
		case 8:
			dispMonth = ColumnConstants::AUG;
			break;
		case 9:
			dispMonth = ColumnConstants::SEPT;
			break;
		case 10:
			dispMonth = ColumnConstants::OCT;
			break;
		case 11:
			dispMonth = ColumnConstants::NOV;
			break;
		case 12:
			dispMonth = ColumnConstants::DEC;
			break;
		default:
			throw "Month number is outside of range!";
			break;
		}
	}

	void excelDate::parseData(const string& month, const double date){
		day = 0;
		this->month = 0;
		year = 0;
		int position = 0;
		amntOwed = 0;
		int leapDays = (int)((date + 1400) / 1461);
		this->year = (int)((date - leapDays - 1) / 365);
		int janFirst = this->year * 365 + (int)((this->year + 7) / 4);
		int wholeDays = (int)date - janFirst;
		if (this->year % 4 != 0 && wholeDays > 58)
			++wholeDays;
		static int firstOfMonth[12] = { 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335 };
		this->month = upper_bound(&firstOfMonth[0], &firstOfMonth[12], wholeDays) - &firstOfMonth[0];
		this->day = wholeDays - firstOfMonth[this->month - 1] + 1;
		this->year += 1900;
		this->dateDispVal = date;
		try{
			if (dispMonth != month){
				for (size_t i = 0; i < month.size(); i++){
					int y = month[i] - 48;
					if (0 <= y && y <= 9){
						if (amntOwed > 0){
							amntOwed *= 10;
						}
						amntOwed += y;
					}
					else{
						if (amntOwed > 0){
							break;
						}
					}
				}
			}
			if (amntOwed == 0){
				amntOwed = 0;
			}
			setDispMonth();
		}
		catch (const string& e){
			throw e;
		}
	}

	void excelDate::parseData(const double date){
		day = 0;
		this->month = 0;
		year = 0;
		int position = 0;
		amntOwed = 0;
		int leapDays = (int)((date + 1400) / 1461);
		this->year = (int)((date - leapDays - 1) / 365);
		int janFirst = this->year * 365 + (int)((this->year + 7) / 4);
		int wholeDays = (int)date - janFirst;
		if (this->year % 4 != 0 && wholeDays > 58)
			++wholeDays;
		static int firstOfMonth[12] = { 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335 };
		this->month = upper_bound(&firstOfMonth[0], &firstOfMonth[12], wholeDays) - &firstOfMonth[0];
		this->day = wholeDays - firstOfMonth[this->month - 1] + 1;
		this->year += 1900;
		this->dateDispVal = date;
	}

	string excelDate::getMMYYYY(){
		string mm = dispMonth;
		string yyyy = to_string(yearPaidFor);
		string mmyyyy = mm + '.' + yyyy;
		return (mmyyyy);
	}

	const bool excelDate::before(int month, int year){
		return ((year > this->year) || (year == this->year && month > this->month));
	}

	const bool excelDate::after(int month, int year){
		return ((year < this->year) || (year == this->year && month < this->month));
	}

	const int excelDate::getYearPaidFor(){
		return yearPaidFor;
	}

	const int excelDate::getMonthPaidFor(){
		return monthPaidFor;
	}

	const time_t excelDate::getDatePaidFor(){
		struct tm tmp = { 0, 0, 0, 1, monthPaidFor - 1, yearPaidFor - 1900 };
		return mktime(&tmp);
	}
}