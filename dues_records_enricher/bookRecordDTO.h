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
		
		void setName(const std::string& name);
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
		void setAddress(const std::string& address);

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
		const std::string& getAddress();
		const int getMonthsSincePayment();
		const std::string& getName();
		const std::string& getAddress1();
		const std::string& getAddress2();

		void clearData();

		~bookRecordDTO();

		void setIsFrozen(bool isFrozen){ this->isFrozen = isFrozen; }
		bool getIsFrozen(){ return isFrozen; }
	private:
		std::map<std::string, excelDate::excelDate*> paymentDates;
		std::map<excelDate::excelDate*,std::list<std::string>> paidAssetFines;
		std::map<std::string, std::list<int>> unpaidAssetFines;
		std::string name;
		std::string address;
		std::string address1, address2;
		struct std::tm mostRecentPaymentDate;
		excelDate::excelDate* initDate;
		int uniqueId;
		bool isRetired;
		bool isStale;
		bool isFrozen;
		int bookNum;
		int amountOwed;
		int mostRecentPaymentMonth;
		int mostRecentPaymentYear;

		void deletePaymentDate(std::pair<std::string, excelDate::excelDate*> paymentDate);

		void deleteAssetFine(std::pair<excelDate::excelDate*, int> assetFine);

		void populateAddresses12();
	};
}

#endif