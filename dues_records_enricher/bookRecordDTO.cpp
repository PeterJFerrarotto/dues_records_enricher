#include "bookRecordDTO.h"
#include <algorithm>
#include <ctime>
#include "Constants.h"
using namespace std;

namespace bookRecord{
	bookRecordDTO::bookRecordDTO()
	{
	}

	void bookRecordDTO::setName(const string& name){
		this->name = name;
	}

	void bookRecordDTO::setBookNum(const int bookNum){
		this->bookNum = bookNum;
	}

	void bookRecordDTO::addPaymentDate(excelDate::excelDate* date){
		string key = date->getMMYYYY();
		paymentDates.insert({ key, date });
	}

	void bookRecordDTO::addAssetFine(excelDate::excelDate* date, const string& assetFine){
		if (paidAssetFines.find(date) == paidAssetFines.end()){
			list<string> assetFinesNew = { assetFine };
			paidAssetFines.insert(make_pair(date, assetFinesNew));
		}
		else{
			auto iter = paidAssetFines.find(date);
			iter->second.push_back(assetFine);
		}
	}

	void bookRecordDTO::addUnPaidAssetFine(const string& name, int fine){
		if (unpaidAssetFines.find(name) == unpaidAssetFines.end()){
			list<int> assetFinesNew = { fine };
			unpaidAssetFines.insert(make_pair(name, assetFinesNew));
		}
		else{
			auto iter = unpaidAssetFines.find(name);
			iter->second.push_back(fine);
		}
		this->addToAmountOwed(fine);
	}

	const excelDate::excelDate* const bookRecordDTO::getPaymentDate(const string& mmYYYY){
		if (paymentDates.find(mmYYYY) != paymentDates.end()){
			return paymentDates.find(mmYYYY)->second;
		}
		return nullptr;
	}

	void bookRecordDTO::deletePaymentDate(pair<string, excelDate::excelDate*> paymentDate){
		delete paymentDate.second;
		paymentDate.second = nullptr;
	}

	void bookRecordDTO::deleteAssetFine(pair<excelDate::excelDate*, int> assetFine){
		delete assetFine.first;
		assetFine.first = nullptr;
	}

	bookRecordDTO::~bookRecordDTO()
	{
		/*if (!paymentDates.empty()){
			for_each(paymentDates.begin(), paymentDates.end(), &bookRecordDTO::deletePaymentDate);
			}
			if (!assetFines.empty()){
			for_each(assetFines.begin(), assetFines.end(), &bookRecordDTO::deleteAssetFine);
			}*/
		paymentDates.clear();
		unpaidAssetFines.clear();
	}

	void bookRecordDTO::setMostRecentPaymentDate(int month, int year){
		mostRecentPaymentMonth = month;
		mostRecentPaymentYear = year;
		mostRecentPaymentDate = { 0, 0, 0, 1, month-1, year - 1900 };
	}

	const struct std::tm bookRecordDTO::getMostRecentPaymentDate(){
		return mostRecentPaymentDate;
	}

	void bookRecordDTO::setInitDate(excelDate::excelDate* initDate){
		this->initDate = initDate;
	}

	void bookRecordDTO::setIsRetired(bool isRetired){
		this->isRetired = isRetired;
	}

	const excelDate::excelDate* bookRecordDTO::getInitDate(){
		return initDate;
	}

	const bool bookRecordDTO::getIsRetired(){
		return isRetired;
	}

	void bookRecordDTO::setAmountOwed(int credit){
		if (this->isRetired){
			if (this->mostRecentPaymentMonth > 0 && this->mostRecentPaymentMonth <= 12){
				time_t t = time(NULL);
				tm* timePtr = localtime(&t);
				int month = (timePtr->tm_mon + 1) - this->mostRecentPaymentMonth;
				int year = (timePtr->tm_year + 1900) - this->mostRecentPaymentYear;

				timePtr = nullptr;
				delete timePtr;

				int monthsPassed = month + (year * 12);
				if (monthsPassed > 0){
					this->amountOwed = defaultValues::retiredFee * (monthsPassed)-credit;
				}
				else{
					this->amountOwed = 0;
				}
			}
			else if (this->initDate != nullptr){
				time_t t = time(NULL);
				tm* timePtr = localtime(&t);
				int month = (timePtr->tm_mon + 1) - this->initDate->getMonth();
				int year = (timePtr->tm_year + 1900) - this->initDate->getYear();

				timePtr = nullptr;
				delete timePtr;

				int monthsPassed = month + (year * 12);
				if (monthsPassed > 0){
					this->amountOwed = defaultValues::retiredFee * (monthsPassed)-credit;
				}
				else{
					this->amountOwed = 0;
				}
			}
			else
			{
				this->amountOwed = defaultValues::retiredFee - credit;
			}
		}
		else{
			if (this->mostRecentPaymentMonth > 0 && this->mostRecentPaymentMonth <= 12){
				time_t t = time(NULL);
				tm* timePtr = localtime(&t);
				int month = (timePtr->tm_mon + 1) - this->mostRecentPaymentMonth;
				int year = (timePtr->tm_year + 1900) - this->mostRecentPaymentYear;

				timePtr = nullptr;
				delete timePtr;

				int monthsPassed = month + (year * 12);
				if (monthsPassed > 0){
					this->amountOwed = defaultValues::defaultFee * (monthsPassed)-credit;
				}
				else if (monthsPassed > 60){
					this->amountOwed = 0;
				}
				else{
					this->amountOwed = 0;
				}
			}
			else if (this->initDate != nullptr){
				time_t t = time(NULL);
				tm* timePtr = localtime(&t);
				int month = (timePtr->tm_mon + 1) - this->initDate->getMonth();
				int year = (timePtr->tm_year + 1900) - this->initDate->getYear();

				timePtr = nullptr;
				delete timePtr;

				int monthsPassed = month + (year * 12);
				if (monthsPassed > 0){
					this->amountOwed = defaultValues::defaultFee * (monthsPassed)-credit;
				}
				else{
					this->amountOwed = 0;
				}
			}
			else
			{
				this->amountOwed = defaultValues::defaultFee - credit;
			}
		}
	}

	void bookRecordDTO::addToAmountOwed(int amount){
		amountOwed += amount;
	}

	void bookRecordDTO::subtractFromAmountOwed(int amount){
		amountOwed -= amount;
	}

	const int bookRecordDTO::getAmountOwed(){
		return amountOwed;
	}

	const map<string, excelDate::excelDate*>& bookRecordDTO::getPaymentDates(){
		return paymentDates;
	}
	const map<excelDate::excelDate*, list<string>>& bookRecordDTO::getPaidAssetFines(){
		return paidAssetFines;
	}
	const map<string, list<int>>& bookRecordDTO::getUnpaidAssetFines(){
		return unpaidAssetFines;
	}

	void bookRecordDTO::setUniqueId(size_t id){
		uniqueId = id;
	}

	const int bookRecordDTO::getUniqueIdentifier(){
		return uniqueId;
	}

	const double bookRecordDTO::getInitDateVal(){
		if (initDate != nullptr){
			return (initDate->getDispVal());
		}
		return 0;
	}

	const string& bookRecordDTO::getName(){
		return name;
	}

	const int bookRecordDTO::getBookNum(){
		return bookNum;
	}

	void bookRecordDTO::setIsStale(){
		time_t t = time(NULL);
		tm* timePtr = localtime(&t);
		int month = timePtr->tm_mon + 1;
		int year = timePtr->tm_year + 1900;

		isStale = mostRecentPaymentYear < year || (mostRecentPaymentYear == year && mostRecentPaymentMonth <= month - 2);
	}

	const bool bookRecordDTO::getIsStale(){
		return isStale;
	}

	const string& bookRecordDTO::getAddress(){
		return address;
	}

	const int bookRecordDTO::getMonthsSincePayment(){
		if (this->mostRecentPaymentMonth > 0 && this->mostRecentPaymentMonth <= 12){
			time_t t = time(NULL);
			tm* timePtr = localtime(&t);
			int month = (timePtr->tm_mon + 1) - this->mostRecentPaymentMonth;
			int year = (timePtr->tm_year + 1900) - this->mostRecentPaymentYear;

			timePtr = nullptr;
			delete timePtr;

			return month + (year * 12) > 0 ? month + (year * 12) : 0 ;
		}
		else if (this->initDate != nullptr){
			time_t t = time(NULL);
			tm* timePtr = localtime(&t);
			int month = (timePtr->tm_mon + 1) - this->initDate->getMonth();
			int year = (timePtr->tm_year + 1900) - this->initDate->getYear();

			timePtr = nullptr;
			delete timePtr;

			return month + (year * 12) > 0 ? month + (year * 12) : 0;
		}
	}

	void bookRecordDTO::clearData(){
		excelDate::excelDate* toDelete;
		if (!paymentDates.empty()){
			for (map<string, excelDate::excelDate*>::iterator itr = paymentDates.begin(); itr != paymentDates.end(); itr++){
				toDelete = itr->second;
				delete toDelete;
			}
			paymentDates.clear();
		}

		if (!paidAssetFines.empty()){
			for (map<excelDate::excelDate*, list<string>>::iterator itr = paidAssetFines.begin(); itr != paidAssetFines.end(); itr++){
				toDelete = itr->first;
				delete toDelete;
			}
			paidAssetFines.clear();
		}

		unpaidAssetFines.clear();

		if (initDate != nullptr){
			delete initDate;
			initDate = nullptr;
		}
	}

	void bookRecordDTO::setAddress(const string& address){
		this->address = address;
	}
}
