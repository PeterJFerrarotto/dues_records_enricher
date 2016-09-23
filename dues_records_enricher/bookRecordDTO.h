#ifndef BOOK_RECORD_DTO_H
#define BOOK_RECORD_DTO_H

#include <string>
#include <map>
#include <list>
#include "excelDate.h"
#include <ctime>

namespace bookRecord{
	class bookRecordDTO
	{
	public:
		bookRecordDTO();
		
		void setFirstName(const std::string& firstName);
		void setBookNum(const int bookNum);
		void addPaymentDate(excelDate::excelDate* date);
		void addAssetFine(excelDate::excelDate* date, const std::string& assetFine);
		void setInitDate(excelDate::excelDate* initDate);
		void setIsRetired(bool isRetired);
		void setMostRecentPaymentDate(const int month, const int year);
		void setAmountOwed(int credit = 0);
		void addToAmountOwed(int amount);
		void subtractFromAmountOwed(int amount);
		void addPaidAssetFine(const std::string& name, int fine);
		void addUnPaidAssetFine(const std::string& name, int fine);
		void setIsStale();
		void setAddress1(const std::string& a1);
		void setAddress2(const std::string& a2);
		void setAddress3(const std::string& a3);
		void setLastName(const std::string& lastName);
		void setMidInit(const std::string& midInit);
		void setSuffix(const std::string& suffix);

		const std::string& getFirstName();
		const int getBookNum();
		const excelDate::excelDate* const getPaymentDate(const std::string& mmYYYY);
		const struct std::tm getMostRecentPaymentDate();
		const excelDate::excelDate* getInitDate();
		const double getInitDateVal();
		const bool getIsRetired();
		const int getAmountOwed();
		const std::map<std::string, excelDate::excelDate*>& getPaymentDates();
		const std::map<excelDate::excelDate*, std::list<std::string>>& getPaidAssetFines();
		const std::map<std::string, std::list<int>>& getUnpaidAssetFines();
		const int getUniqueIdentifier();
		void setUniqueId(size_t id);
		const bool getIsStale();
		const std::string& getAddress1();
		const std::string& getAddress2();
		const std::string& getAddress3();
		const int getMonthsSincePayment();
		const std::string& getLastName();
		const std::string& getMidInit();
		const std::string& getSuffix();
		const std::string& getFullName();

		void clearData();

		~bookRecordDTO();
	private:
		std::map<std::string, excelDate::excelDate*> paymentDates;
		std::map<excelDate::excelDate*,std::list<std::string>> paidAssetFines;
		std::map<std::string, std::list<int>> unpaidAssetFines;
		std::string firstName;
		std::string midInit;
		std::string lastName;
		std::string suffix;
		std::string address1;
		std::string address2;
		std::string address3;
		struct std::tm mostRecentPaymentDate;
		excelDate::excelDate* initDate;
		int uniqueId;
		bool isRetired;
		bool isStale;
		int bookNum;
		int amountOwed;
		int mostRecentPaymentMonth;
		int mostRecentPaymentYear;

		void deletePaymentDate(std::pair<std::string, excelDate::excelDate*> paymentDate);

		void deleteAssetFine(std::pair<excelDate::excelDate*, int> assetFine);
	};
}

#endif