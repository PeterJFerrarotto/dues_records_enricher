#include "BasicExcel.hpp"
#include <iostream>
#include <string>
#include <dirent.h>
#include <vector>
#include <ctime>
#include <map>
#include <tuple>
#include "Constants.h"
#include "bookRecordDTO.h"
#include "excelDate.h"
using namespace YExcel;
using namespace std;

string& getMonthName(const int monthNum){
	static string dispMonth = "";
	switch (monthNum){
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
		throw exceptions::monthOutOfRange;
		break;
	}
	return dispMonth;
}

string& getMonthNameFull(const int monthNum){
	static string dispMonth = "";
	switch (monthNum){
	case 0:
		throw exceptions::monthIsZero;
		break;
	case 1:
		dispMonth = ColumnConstants::JANf;
		break;
	case 2:
		dispMonth = ColumnConstants::FEBf;
		break;
	case 3:
		dispMonth = ColumnConstants::MARf;
		break;
	case 4:
		dispMonth = ColumnConstants::APRf;
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
		dispMonth = ColumnConstants::AUGf;
		break;
	case 9:
		dispMonth = ColumnConstants::SEPTf;
		break;
	case 10:
		dispMonth = ColumnConstants::OCTf;
		break;
	case 11:
		dispMonth = ColumnConstants::NOVf;
		break;
	case 12:
		dispMonth = ColumnConstants::DECf;
		break;
	default:
		throw exceptions::monthOutOfRange;
		break;
	}
	return dispMonth;
}

int getCredit(const string& month, const string& dispMonth){
	int credit = 0;
	if (dispMonth != month){
		for (size_t i = 0; i < month.size(); i++){
			int y = month[i] - 48;
			if (0 <= y && y <= 9){
				if (credit > 0){
					credit *= 10;
				}
				credit += y;
			}
			else{
				if (credit > 0){
					break;
				}
			}
		}
	}
	else{
		credit = 0;
	}

	return credit;
}

int getNumberFromString(const string& bookNumStr){
	int bookNum = 0;
	for (size_t i = 0; i < bookNumStr.size(); i++){
		int y = bookNumStr[i] - 48;
		if (0 <= y && y <= 9){
			if (bookNum > 0){
				bookNum *= 10;
			}
			bookNum += (bookNumStr[i] - 48);
		}
		else{
			if (bookNum > 0){
				return bookNum;
			}
		}
	}
	return bookNum;
}

string getAssetNameFromAssetString(const string& assetString){
	string name;
	for (size_t i = 0; i < assetString.size(); i++){
		int checkForInt = assetString[i] - 48;
		if (assetString[i] != ' ' && (checkForInt > 9 || checkForInt < 0)){
			name += assetString[i];
		}
	}
	return name;
}

bookRecord::bookRecordDTO* enrichBookData(const char* filePath, size_t num){
	bookRecord::bookRecordDTO* bookRecord = new bookRecord::bookRecordDTO();
	BasicExcel bookDataFile;
	bookDataFile.Load(filePath);
	if (bookDataFile.worksheets_.empty()){
		return nullptr;
	}
	BasicExcelWorksheet* worksheet = bookDataFile.GetWorksheet(fileDirecs::workSheetName);
	if (worksheet == NULL){
		throw "Worksheet 2010-2014 not found!";
	}
	BasicExcelCell* cell;
	string name;
	string address;
	string socialSecurity;
	string month;
	int assetFine;
	string assetFineString;
	string dateOfBirth;
	string phoneNumber;
	bool isRetired;
	bool consecUnpaid = false;
	string tmp;
	excelDate::excelDate* date = nullptr;
	int bookNum;
	int credit = 0;
	int year;
	int monthNum;
	int tempYear;
	double dateVal;

	size_t dateCol;
	size_t dateRow;

	size_t assetCol;
	size_t assetRow;

	string assetName;

	cell = worksheet->Cell(ColumnConstants::NAMER, ColumnConstants::NAMEC + 1);
	if (cell->Type() == BasicExcelCell::UNDEFINED){
		std::cout << "No name!\t";
	}
	else{
		name = cell->GetString();
		std::cout << num << ": " <<  name << endl << endl << '\t';
		bookRecord->setName(name);
	}

	cell = worksheet->Cell(ColumnConstants::ADDRESSR, ColumnConstants::ADDRESSC);
	if (cell->Type() != BasicExcelCell::UNDEFINED){
		address = cell->GetString();
		bookRecord->setAddress(name);
	}

	cell = worksheet->Cell(ColumnConstants::BOOKNUMR, ColumnConstants::BOOKNUMC + 1);
	if (cell->Type() == BasicExcelCell::UNDEFINED){
		cell = worksheet->Cell(ColumnConstants::BOOKNUMR, ColumnConstants::BOOKNUMC);
		tmp = cell->GetString();
		bookNum = getNumberFromString(tmp);
		if (bookNum > 0){
			bookRecord->setBookNum(bookNum);
			isRetired = (tmp[tmp.size() - 1] == 'r');
			bookRecord->setIsRetired(isRetired);
			std::cout << bookNum << '\t';
		}
		else{
			std::cout << "No book number!" << '\t';
		}
	}
	else if (cell->Type() == BasicExcelCell::INT || cell->Type() == BasicExcelCell::DOUBLE) {
		bookNum = cell->GetInteger();
		bookRecord->setBookNum(bookNum);
		std::cout << bookNum << '\t';
	}
	else if (cell->Type() == BasicExcelCell::STRING){
		tmp = cell->GetString();
		bookNum = getNumberFromString(tmp);
		if (bookNum > 0){
			bookRecord->setBookNum(bookNum);
			isRetired = (tmp[tmp.size() - 1] == 'r');
			bookRecord->setIsRetired(isRetired);
			std::cout << bookNum << '\t';
		}
		else{
			std::cout << "No book Number!" << '\t';
		}
	}
	else{
		std::cout << "No book number!" << '\t';
	}

	cell = worksheet->Cell(ColumnConstants::INITDATER, ColumnConstants::INITDATEC + 1);
	if (cell->Type() == BasicExcelCell::DOUBLE){
		dateVal = cell->GetDouble();
		date = new excelDate::excelDate(dateVal);
		bookRecord->setInitDate(date);
	}

	dateCol = ColumnConstants::YEAR_2010C;
	dateRow = ColumnConstants::JANR;
	monthNum = dateRow - 7;
	cell = worksheet->Cell(dateRow - 1, dateCol);
	if (cell->Type() == BasicExcelCell::INT || cell->Type() == BasicExcelCell::DOUBLE){
		year = cell->GetInteger();
	}

	while (true){
		if (dateRow > ColumnConstants::DECR){
			dateRow = ColumnConstants::YEARR;
			dateCol += 2;
			cell = worksheet->Cell(dateRow, dateCol);
			if (cell->Type() == BasicExcelCell::UNDEFINED){
				break;
			}
			dateRow = ColumnConstants::JANR;
			cell = worksheet->Cell(dateRow - 1, dateCol);
			if (cell->Type() == BasicExcelCell::UNDEFINED){
				break;
			}
		}
		cell = worksheet->Cell(ColumnConstants::YEARNUMR, dateCol);
		tempYear = cell->GetInteger();
		cell = worksheet->Cell(dateRow, dateCol - 1);
		if (cell->Type() == BasicExcelCell::UNDEFINED){
			throw exceptions::undefinedMonth;
		}
		else {
			month = cell->GetString();
		}

		cell = worksheet->Cell(dateRow, dateCol);
		if (cell->Type() == BasicExcelCell::UNDEFINED){
			string monthName = getMonthName(dateRow - 7);
			if (month != monthName && month.size() != monthName.size() + 1){
				if (credit == 0 && !consecUnpaid){
					credit = getCredit(month, monthName);
				}
				bookRecord->setMostRecentPaymentDate(monthNum, year);
				bookRecord->setAmountOwed(credit);
			}
			consecUnpaid = true;
		}
		else if (cell->Type() == BasicExcelCell::DOUBLE) {
			dateVal = cell->GetDouble();
			year = tempYear;
			monthNum = dateRow - 7;
			date = new excelDate::excelDate(month, monthNum, year, dateVal);
			bookRecord->addPaymentDate(date);
			bookRecord->setMostRecentPaymentDate(monthNum, year);
			bookRecord->setAmountOwed();
			consecUnpaid = false;
		}
		else if (cell->Type() == BasicExcelCell::STRING){
			if (cell->GetString() == "X" || cell->GetString() == "x" || cell->GetString() == "W" || cell->GetString() == "w"){
				year = tempYear;
				monthNum = dateRow - 7;
				bookRecord->setMostRecentPaymentDate(monthNum, year);
				bookRecord->setAmountOwed();
				consecUnpaid = false;
			}
		}
		dateRow++;
	}

	if (date != nullptr && monthNum != 0 && year != 0){
		bookRecord->setMostRecentPaymentDate(monthNum, year);
		bookRecord->setIsStale();
	}

	dateCol = ColumnConstants::ASSESSDATEC;
	dateRow = ColumnConstants::ASSESSDATER + 1;
	assetCol = ColumnConstants::ASSESSITEMC;
	assetRow = ColumnConstants::ASSESSITEMR + 1;
		
	while (true){
		cell = worksheet->Cell(assetRow, assetCol);
		if (cell->Type() == BasicExcelCell::UNDEFINED){
			break;
		}
		if (cell->Type() == BasicExcelCell::INT || cell->Type() == BasicExcelCell::DOUBLE){
			assetFine = cell->GetInteger();
			assetName = "No Name";
			assetFineString = to_string(assetFine);
		}
		else if (cell->Type() == BasicExcelCell::STRING){
			assetFineString = cell->GetString();
			assetName = getAssetNameFromAssetString(assetFineString);
			assetFine = getNumberFromString(assetFineString);
		}

		cell = worksheet->Cell(dateRow, dateCol);
		if (cell->Type() == BasicExcelCell::UNDEFINED){
			bookRecord->addUnPaidAssetFine(assetName, assetFine);
		}
		else if (cell->Type() == BasicExcelCell::DOUBLE){
			dateVal = cell->GetDouble();
			date = new excelDate::excelDate(dateVal);
			bookRecord->addAssetFine(date, assetFineString);
		}
		assetRow++;
		dateRow++;
	}

	std::cout << endl << endl;
	if (bookRecord->getAmountOwed() <= 0)
		bookRecord->setAmountOwed();
	bookRecord->setUniqueId(num);
	return bookRecord;
}

void loadBookData(vector<bookRecord::bookRecordDTO*>& bookRecords){
	DIR *dirp;
	struct dirent *dp;
	bookRecord::bookRecordDTO* bookRecord;

	char directory[360];
	strcpy(directory, fileDirecs::direc);

	char fileDirec[360];
	char fileName[360];
	if ((dirp = opendir(fileDirecs::direc)) == NULL){
		throw exceptions::direcNotFound + " " + fileDirecs::direc;
	}
	closedir(dirp);
	for (size_t i = 0; i < fileDirecs::dirLetters.size(); i++){
		//if (bookRecords.size() >= 5) break;
		strcpy(directory, fileDirecs::direc);
		strcat(directory, fileDirecs::dirLetters[i]);
		if ((dirp = opendir(directory)) == NULL){
			throw exceptions::direcNotFound + " " + directory;
		}
		while ((dp = readdir(dirp)) != NULL) {
			//if (bookRecords.size() >= 5) break;
			std::cout << ".";
			strcpy(fileName, dp->d_name);
			if (fileName[0] != '.' && fileName[1] != '.'){
				strcpy(fileDirec, directory);
				strcat(fileDirec, fileName);
				bookRecord = enrichBookData(fileDirec, bookRecords.size());
				if (bookRecord != nullptr){
					bookRecords.push_back(bookRecord);
				}
			}
		}
	}
}

void prepareEnrichedBook(BasicExcelWorksheet* worksheet){
	BasicExcelCell* cell;
	size_t row = 0;
	size_t col = 0;
	vector<const char*> columnNames = { "UniqueID", "Name", "BookNum", "RetiredInd", "Address", "InitDate", "AmountOwed", "MostRecentPaymentMonth", "MostRecentPaymentYear", "MonthsSincePayment", "StaleInd"};
	for (; col < columnNames.size(); col++){
		cell = worksheet->Cell(row, col);
		cell->SetString(columnNames[col]);
	}
}

void prepareDetailsBook(BasicExcelWorksheet* worksheet){
	BasicExcelCell* cell;
	size_t row = 0;
	size_t col = 0;
	vector<const char*> columnNames = { "UniqueID", "Type", "PaymentDate", "Name", "MonthYear", "Month", "Year", "DatePaidFor", "Fine" };
	for (; col < columnNames.size(); col++){
		cell = worksheet->Cell(row, col);
		cell->SetString(columnNames[col]);
	}
}

void saveEnrichedBookData(vector<bookRecord::bookRecordDTO*> bookRecords){
	BasicExcel bookDataFile;
	bookDataFile.New(2);
	bookDataFile.RenameWorksheet("Sheet1", fileDirecs::saveWorkSheetName);
	bookDataFile.RenameWorksheet("Sheet2", fileDirecs::saveWorkSheetDetailsName);
	if (bookDataFile.worksheets_.empty()){
		bookDataFile.SaveAs(fileDirecs::saveDirec);
	}
	BasicExcelWorksheet* worksheet = bookDataFile.GetWorksheet(fileDirecs::saveWorkSheetName);
	if (worksheet == NULL){
		bookDataFile.AddWorksheet(fileDirecs::saveWorkSheetName);
		bookDataFile.Save();
		BasicExcelWorksheet* worksheet = bookDataFile.GetWorksheet(fileDirecs::saveWorkSheetName);
	}
	BasicExcelWorksheet* detailsWorksheet = bookDataFile.GetWorksheet(fileDirecs::saveWorkSheetDetailsName);
	if (detailsWorksheet == NULL){
		bookDataFile.AddWorksheet(fileDirecs::saveWorkSheetDetailsName);
		bookDataFile.Save();
		BasicExcelWorksheet* detailsWorksheet = bookDataFile.GetWorksheet(fileDirecs::saveWorkSheetDetailsName);
	}
	prepareEnrichedBook(worksheet);
	prepareDetailsBook(detailsWorksheet);
	BasicExcelCell* cell;
	BasicExcelCell* detailCell;
	time_t dayDiff;
	int retiredStatus;
	int staleStatus;
	int monthsSincePayment;
	int mostRecentMonth;
	int mostRecentYear;
	string mostRecentMonthName;
	
	size_t destCol = 0;
	size_t destRow = 1;
	size_t detailCol = 0;
	size_t detailRow = 1;
	for (size_t i = 0; i < bookRecords.size(); i++){
		bookRecord::bookRecordDTO* tmp = bookRecords[i];
		destCol = 0;
		cell = worksheet->Cell(destRow, destCol++);
		cell->SetInteger(tmp->getUniqueIdentifier());

		cell = worksheet->Cell(destRow, destCol++);
		cell->SetString(tmp->getName().c_str());

		cell = worksheet->Cell(destRow, destCol++);
		if (tmp->getBookNum() != 0){
			cell->SetInteger(tmp->getBookNum());
		}

		cell = worksheet->Cell(destRow, destCol++);
		retiredStatus = (tmp->getIsRetired() ? -1 : 0);
		cell->SetInteger(retiredStatus);

		cell = worksheet->Cell(destRow, destCol++);
		cell->SetString(tmp->getAddress().c_str());

		cell = worksheet->Cell(destRow, destCol++);
		if (tmp->getInitDate() != nullptr){
			cell->SetDouble(tmp->getInitDateVal());
		}

		cell = worksheet->Cell(destRow, destCol++);

		cell->SetInteger(tmp->getAmountOwed());

		cell = worksheet->Cell(destRow, destCol++);
		mostRecentMonth = tmp->getMostRecentPaymentDate().tm_mon + 1;
		if (mostRecentMonth > 0 && mostRecentMonth <= 12){
			mostRecentMonthName = getMonthNameFull(mostRecentMonth);
			cell->SetString(mostRecentMonthName.c_str());
		}

		cell = worksheet->Cell(destRow, destCol++);
		mostRecentYear = tmp->getMostRecentPaymentDate().tm_year + 1900;
		if (mostRecentYear != 1900){
			cell->SetInteger(mostRecentYear);
		}
		
		cell = worksheet->Cell(destRow, destCol++);
		monthsSincePayment = tmp->getMonthsSincePayment();
		cell->SetInteger(monthsSincePayment);

		cell = worksheet->Cell(destRow++, destCol);
		staleStatus = (tmp->getIsStale() ? -1 : 0);
		cell->SetInteger(staleStatus);

		cout << "Done with " << tmp->getName() << " information..." << endl;

		if (tmp->getPaymentDates().size() != 0)
		{
			for (pair<string, excelDate::excelDate*> dateStringPair : tmp->getPaymentDates()){
				detailCol = 0;
				detailCell = detailsWorksheet->Cell(detailRow, detailCol++);
				detailCell->SetInteger(tmp->getUniqueIdentifier());

				detailCell = detailsWorksheet->Cell(detailRow, detailCol++);
				detailCell->SetString("Monthly Fee");

				detailCell = detailsWorksheet->Cell(detailRow, detailCol++);
				detailCell->SetDouble(dateStringPair.second->getDispVal());

				detailCell = detailsWorksheet->Cell(detailRow, detailCol++);
				detailCell->SetString("");

				detailCell = detailsWorksheet->Cell(detailRow, detailCol++);
				detailCell->SetString(dateStringPair.first.c_str());

				detailCell = detailsWorksheet->Cell(detailRow, detailCol++);
				detailCell->SetInteger(dateStringPair.second->getMonthPaidFor());

				detailCell = detailsWorksheet->Cell(detailRow, detailCol++);
				detailCell->SetInteger(dateStringPair.second->getYearPaidFor());

				detailCell = detailsWorksheet->Cell(detailRow++, detailCol);
				dayDiff = ((dateStringPair.second->getDatePaidFor() + 2208988800) / (60 * 60 * 24)) + 2;
				detailCell->SetDouble(dayDiff);
			}
			cout << "Done with " << tmp->getName() << " monthly fees..." << endl;
		}

		if (tmp->getPaidAssetFines().size() != 0){
			for (pair<excelDate::excelDate*, list<string>> paidAssetFine : tmp->getPaidAssetFines()){
				for (string name : paidAssetFine.second){
					detailCol = 0;
					detailCell = detailsWorksheet->Cell(detailRow, detailCol++);
					detailCell->SetInteger(tmp->getUniqueIdentifier());
					
					detailCell = detailsWorksheet->Cell(detailRow, detailCol++);
					detailCell->SetString("Paid Asset Fine");
					
					detailCell = detailsWorksheet->Cell(detailRow, detailCol++);
					detailCell->SetDouble(paidAssetFine.first->getDispVal());

					detailCell = detailsWorksheet->Cell(detailRow++, detailCol);
					detailCell->SetString(name.c_str());
				}
			}
			cout << "Done with " << tmp->getName() << " paid assessments..." << endl;
		}

		if (tmp->getUnpaidAssetFines().size() != 0){
			for (pair<string, list<int>> unpaidAssetFine : tmp->getUnpaidAssetFines()){
				for (int fine : unpaidAssetFine.second){
					detailCol = 0;
					detailCell = detailsWorksheet->Cell(detailRow, detailCol++);
					detailCell->SetInteger(tmp->getUniqueIdentifier());
					
					detailCell = detailsWorksheet->Cell(detailRow, detailCol++);
					detailCell->SetString("Unpaid Asset Fine");
					
					detailCell = detailsWorksheet->Cell(detailRow, detailCol++);
					detailCell->EraseContents();
					
					detailCell = detailsWorksheet->Cell(detailRow, detailCol++);
					detailCell->SetString(unpaidAssetFine.first.c_str());
					
					detailCell = detailsWorksheet->Cell(detailRow, detailCol++);
					detailCell->SetString("");
					
					detailCell = detailsWorksheet->Cell(detailRow, detailCol++);
					detailCell->EraseContents();
					
					detailCell = detailsWorksheet->Cell(detailRow, detailCol++);
					detailCell->EraseContents();
					
					detailCell = detailsWorksheet->Cell(detailRow, detailCol++);
					detailCell->EraseContents();
					
					detailCell = detailsWorksheet->Cell(detailRow++, detailCol);
					detailCell->SetInteger(fine);
				}
			}
			cout << "Done with " << tmp->getName() << " unpaid assessments..." << endl;
		}
		cout << "Done with " << tmp->getName() << "!" << endl << endl;
		tmp->clearData();
		delete tmp;
	}
	bookRecords.clear();
	bookDataFile.SaveAs(fileDirecs::saveDirec);
}

int main()
{
	string exitString;
	vector<bookRecord::bookRecordDTO*> bookRecords;
	try{
		loadBookData(bookRecords);
		saveEnrichedBookData(bookRecords);
	}
	catch (const string& e){
		std::cout << e << endl;
	}
	std::cout << "Complete!" << endl;
	getline(cin, exitString);
}