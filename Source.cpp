#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include "Header.h"
#include <ctime>
#include <time.h>
#include <conio.h>
using namespace std;

#pragma region User

#pragma region Base
User::User(string m, string p, string r, string birthday, string tel, string name) {
	this->mail = m;
	this->password = p;
	this->role = r;
	this->birthday = birthday;
	this->tel = tel;
	this->name = name;
}

string User::getMail() {

	mail = mail == "" ? "" : mail;
	return mail;
}

string User::getPassword() {

	password = password == "" ? "" : password;
	return password;
}

string User::getRole() {

	role = role == "" ? "" : role;
	return role;
}

void User::setMail(string val) {
	mail = val;
}

void User::setPassword(string val) {
	password = val;
}

void User::setRole(string val) {
	role = val;
}

string User::getBirthday() {
	return birthday;
}

string User::getTel() {
	return tel;
}

string User::getName() {
	return name;
}

void User::setBirthday(string birthday) {
	this->birthday = birthday;
}

void User::setTel(string tel) {
	this->tel = tel;
}

void User::setName(string name) {
	this->name = name;
}
#pragma endregion

#pragma region Manager
Manager::Manager() {

}

void Manager::addProduct(string pCategory) {

	string pID, pName, pPrice, pSize, pColor;
	cout << "Product ID: ";
	cin >> pID;
	cout << endl;
	cout << "Product Name: ";
	cin >> pName;
	cout << endl;
	cout << "Product Price: ";
	cin >> pPrice;
	cout << endl;
	cout << "Product Size: ";
	cin >> pSize;
	cout << endl;
	cout << "Product Color: ";
	cin >> pColor;
	cout << endl;

	ifstream readProducts("products.txt");
	ofstream writeProduct;
Validity:
	if (!pID.empty() && !pName.empty() && !pPrice.empty() && !pSize.empty() && !pColor.empty()) {

		string line = "";
		while (getline(readProducts, line)) {

			if (pID == line.substr(line.find("id:") + 4, line.find("name") - line.find("id:") - 5)) {
				readProducts.close();
				goto Validity;
			}
		}

		writeProduct.open("products.txt", ios::out | ios::app | ios::in | ios::binary);
		writeProduct << "category: " + pCategory + " id: " + pID + " name: " + pName + 
			" price: " + pPrice + " size: " + pSize + " color: " + pColor + "\n";
		writeProduct.close();
	}
	else {
		cout << "Product already exist." << endl;
		cout << endl;
	}
	readProducts.open("products.txt");

}

void Manager::sendCouponToUser() {

	char letters[] = "abcdefghijklmnopqrstuvwxyz";
	string mail, couponByManager;

	//kupon oluþturma
	for (int i = 0; i < 3; i++)
	{
		char randomChar = letters[rand() % 26];
		string tempChar;
		tempChar = (char)randomChar;

		couponByManager += to_string(rand() % 10);
		couponByManager += tempChar;
	}

	//Kullanýcýya indirim kodu tanýmlamasý							
	cout << "User ID: ";
	cin >> mail;
	cout << endl;

	ifstream readCoupons("coupons.txt");
	ofstream writeCoupon;

	if (!mail.empty() && !couponByManager.empty()) {
		writeCoupon.open("coupons.txt", ios::out | ios::app | ios::in | ios::binary);
		writeCoupon << "mail: " + mail + " coupon: " + couponByManager + "\n";
		writeCoupon.close();
		cout << "Added." << endl;
	}
	else {
		cout << "Error userID or couponByManager" << endl;
	}

	cout << endl;
	mail = "";
	couponByManager = "";
}

void Manager::addCourier() {
	ifstream readCourier("courier.txt");
	ofstream writeCourier;

MenuCourier:
	string Cno, line, name;
	cout << "Courier's no? ";
	cin >> Cno;
	cout << endl;

	if (readCourier.is_open())
	{
		while (getline(readCourier, line))
		{
			string tempNo = line.substr(line.find("no:") + 4, line.find("name") - line.find("no:") - 5);
			string tempName= line.substr(line.find("tempName:") + 13, line.length());
			//string deliveryTimes= line.substr(line.find("deliveryTimes:") + 15, line.find("orderNumbers") - line.find("deliveryTimes:") - 16);
			//string orderNumbers = line.substr(line.find("orderNumbers:") + 14, line.length());
			//cout << "X" + tempNo + "X" + tempName + "X" + deliveryTimes + "X" + orderNumbers + "X" << endl;
			//deliveryTimes: 13:00, 14:00 orderNumbers: 3, 5

			if (Cno == tempNo) {
				cout << "Courier already exist." << endl << endl;
				readCourier.close();
				readCourier.open("courier.txt");
				goto MenuCourier;
			}
		}

		cout << "Courier's name? ";
		cin >> name;
		cout << endl;

		string Clocation;
		cout << "Location?";
		cin >> Clocation;
		cout << endl;
		writeCourier.open("courier.txt", ios::out | ios::app | ios::in | ios::binary);
		writeCourier << "no: " + Cno + " name: " + name + " status: " + "ok" + " location: " + Clocation + "\n";
		writeCourier.close();
		cout << "Added." << endl << endl;
		Cno = "";
	}
	else {
		cout << "File cant open. Try again" << endl << endl;
		readCourier.open("courier.txt");
		goto MenuCourier;
	}
	readCourier.close();
	readCourier.open("courier.txt");
}

void Manager::readComments() {

	ifstream readComments("comments.txt");
	string line;
	if (readComments.is_open())
	{
		while (getline(readComments, line))
		{
			cout << line << endl;
		}
	}

	readComments.close();
	readComments.open("comments.txt");
	cout << endl;
}

void Manager::showBills() {
	ifstream readBill("bills.txt");
	string line;
	readBill.close();
	readBill.open("bills.txt");

	while (getline(readBill, line)) {
		cout << line << endl;
		
	}
	readBill.close();
}

#pragma endregion

#pragma region Member

Member::Member(string mail, string password, string role, string birthday, string tel, string name, string addressMember, string coupon)
	:User(mail, password, role, birthday, tel, name)   {
	address= addressMember;
}

string Member::getCoupon() {
	return coupon;
}

string Member::getAddress() {
	return address;
}

void Member::setAddress(string address) {
	this->address = address;
}

void Member::showProducts(string pName) {

	ifstream readProducts("products.txt");
	string line;
	readProducts.close();
	readProducts.open("products.txt");

	if (readProducts.is_open()) {
		
		while (getline(readProducts, line)) {
			
			if (pName== line.substr(line.find("category:") + 10, line.find("id:") - line.find("category:") - 11)) {
				cout << line << endl;
			}			
		}
	}
	else {
		cout << "File error." << endl;
		cout << endl;
	}
	readProducts.close();
	readProducts.open("products.txt");

}

void Member::addItemToCart(list<list<string>>*items) {
	
	string selected, itemSize, itemColor;
	cout << "Select id: ";
	cin >> selected;
	cout << endl;

	list<string> productFeatures;
	cout << "Size: ";
	cin >> itemSize;
	cout << endl;

	cout << "Color: ";
	cin >> itemColor;
	cout << endl;
	
	//productFeatures.push_front(selected);
	//productFeatures.push_front(itemSize);
	//productFeatures.push_front(itemColor);

	bool controlItem = false;

	ifstream readProducts("products.txt");
	string line;
	int price=0;
	readProducts.close();
	readProducts.open("products.txt");

	if (readProducts.is_open()) {

		while (getline(readProducts, line)) 
		{
			string itemId = line.substr(line.find("id:") + 4, line.find("name") - line.find("id") - 5);
			string itemPrice = line.substr(line.find("price:") + 7, line.find("size") - line.find("price") - 8);
			string itemS= line.substr(line.find("size:") + 6, line.find("color") - line.find("size") - 7);
			string itemC= line.substr(line.find("color:") + 7, line.length());
			
			if (selected== itemId && itemSize== itemS && itemColor== itemC) {
				//cout << "X" << itemId << "X" << itemPrice << "X" << endl;
				controlItem = true;				
				price += stoi(itemPrice);
				//cout << price << endl;
				cout << "Added: " << selected << endl;
			}			
		}
	}
	else {
		cout << "File error." << endl;
		cout << endl;
	}
	readProducts.close();
	readProducts.open("products.txt");
	productFeatures.push_front(to_string(price));
	if (controlItem==true) {
		items->push_front(productFeatures);
		//cout << items->front().front() << endl;
		//cout << items->front().back() << endl;
	}
	else {
		cout << "Product not found or try to select product..." << endl;
	}
	
}

void Member::writeComment(string mail) {
	ifstream readComments("comments.txt");
	ofstream writeComments;
MenuComment:

	if (readComments.is_open())
	{
		int counter = 0, action;
		string line;
		for (int i = 0; getline(readComments, line); i++)
		{
			++counter;
		}

		readComments.close();

		string tempCommentNo = to_string(counter);
		string tempComment;
		cout << "Your comment: ";
		cin >> tempComment;
		cout << "1) Product" << endl;
		cout << "2) Propasal" << endl;
		cin >> action;
		cout << endl;

		writeComments.open("comments.txt", ios::out | ios::app | ios::in | ios::binary);

		if (action == 1) {

		TryID:
			string productNo;
			cout << "Product ID: ";
			cin >> productNo;
			cout << endl;

			if (!productNo.empty()) {
				writeComments << "commentNo: " + tempCommentNo + " comment: " + tempComment + " productNo: " + productNo + " customer: " + mail + "\n";
				CommentProduct commentProduct(tempCommentNo, tempComment, productNo);
			}
			else {
				goto TryID;
			}

		}
		else if (action == 2) {
			string propasalNo = tempCommentNo;
			writeComments << "commentNo: " + tempCommentNo + " comment: " + tempComment + " propasalNo: " + propasalNo + " customer: " + mail + "\n";
			CommentPropasal commentPropasal(tempCommentNo, tempComment, propasalNo);
		}
		else {
			writeComments.close();
			goto MenuComment;
		}

		writeComments.close();
	}
	else {
		cout << "File is close. Try again." << endl;
		readComments.open("comments.txt");
		goto MenuComment;
	}
	readComments.open("comments.txt");
}

void Member::showOrders(User* user) {
	ifstream readOrder("orders.txt");
	string line;
	readOrder.close();
	readOrder.open("orders.txt");

	while (getline(readOrder, line)) {
		string userNo = line.substr(line.find("user:")+6, line.find("price")- line.find("user")-7);
		if (userNo==user->getMail()) {
			cout << line << endl;
		}
	}
	readOrder.close();
}

void Member::changePassword(User *user) {

	string line, newPassword;
	cout << "Your new password: ";
	cin >> newPassword;
	ifstream readUsers("users.txt");
	readUsers.close();
	readUsers.open("users.txt");

ControlFile:
	if (readUsers.is_open())
	{
		ofstream tempFile("tempFile.txt");
		tempFile.open("tempFile.txt", ios::out | ios::app | ios::in | ios::binary);
		tempFile << "";
		tempFile.close();
		
		while (getline(readUsers, line))
		{
			if (!line.find("mail: " + user->getMail() + " " + "password: " + user->getPassword())) {
				string part1 = line.substr(0, line.find("password:") + 9);
				string part2 = line.substr(line.find("role:"), line.length());
				line = part1 + " " + newPassword + " " + part2;
				user->setPassword(newPassword);
				cout << line << endl;
			}
			cout << user->getPassword() << endl;
			tempFile.open("tempFile.txt", ios::out | ios::app | ios::in | ios::binary);
			tempFile << line + "\n";
			tempFile.close();
			line = "";
		}
		tempFile.close();
		readUsers.close();
		remove("users.txt");
		rename("tempFile.txt", "users.txt");
	}
	else {
		readUsers.open("users.txt");
		cout << "Error!" << endl;
		goto ControlFile;
	}				
	
	cout << endl;
}
#pragma endregion

Courier::Courier(string mail, string password, string role, string birthday,
	string tel, string name, list<string> orderNumbers)
	:User(mail, password, role, birthday, tel, name) {
	this->orderNumbers = orderNumbers;
}

list<string> Courier::getOrderNumbers() {
	return orderNumbers;
}

void Courier::addOrderNumbers(string orderNumber) {
	/*if(this->orderNumbers.size()>0) { this->orderNumbers.push_front( ", " + orderNumber); }
	else{ this->orderNumbers.push_front( orderNumber); }*/
	this->orderNumbers.push_front(orderNumber);
}

string Courier::getLocation() {
	return location;
}

void Courier::setLocation(string location) {
	this->location = location;
}

void Courier::setStatus(string status) {
	this->status = status;
}

#pragma endregion

#pragma region Clothes

Clothe::Clothe(string category, string name, string price, string size, string color) {
	setCategory(category);
	setName(category);
	setPrice(category);
	setSize(category);
	setColor(category);
}

void Clothe::setCategory(string category) {
	this->category = category;
}

void Clothe::setName(string name) {
	this->name = name;
}

void Clothe::setPrice(string price) {
	this->price = price;
}

void Clothe::setSize(string size) {
	this->size = size;
}

void Clothe::setColor(string color) {
	this->color = color;
}

#pragma endregion

#pragma region Comments
Comments::Comments(string commentNo, string comment)
	:commentNo(commentNo),
	comment(comment) {

}

void Comments::setComment(string comment) {
	this->comment = comment;
}

string Comments::getComment() {
	return comment;
}

void Comments::setCommentNo(string commentNo) {
	this->commentNo = commentNo;
}

string Comments::getCommentNo() {
	return commentNo;
}

CommentProduct::CommentProduct(string commentNo, string comment, string productNo)
:Comments(commentNo, comment) {
	setProductNo(productNo);
}

void CommentProduct::setProductNo(string productNo) {
	this->productNo = productNo;
}

string CommentProduct::getProductNo() {
	return productNo;
}

CommentPropasal::CommentPropasal(string commentNo, string comment, string proposalNo)
:Comments(commentNo, comment) {
	setProposalNo(proposalNo);
}

void CommentPropasal::setProposalNo(string propasalNo) {
	this->proposalNo = propasalNo;
}

string CommentPropasal::getProposalNo() {
	return proposalNo;
}
#pragma endregion

#pragma region Time

MyTimes::MyTimes() {

}

string MyTimes::getCurrentHour() {
	/*const time_t now = time(nullptr);
	const tm calendar_time = *localtime(addressof(now));*/
	/*std::tm* t = std::localtime(nullptr);
	int hour = t->tm_hour;*/
	/*time_t now;
	struct tm* tm= localtime(nullptr);
	now = time(0);*/
	struct tm newtime;
	time_t now = time(0);
	localtime_s(&newtime, &now);
	//int Month = 1 + newtime.tm_mon;
	return to_string(newtime.tm_hour) + ":" + to_string(newtime.tm_min);
}

string MyTimes::calculateTime(string time, string min){
	int firstHour= stoi(time.substr(0, time.find(":")));
	int firstMin = stoi(time.substr(time.find(":")+1, time.length()));
	//cout << firstHour <<" " << firstMin << endl;

	int secondMin = stoi(min);
	int tempFirstMin = (secondMin + firstMin) % 60;
	
	while (secondMin + firstMin >= 60) {
		secondMin -= 60;
		firstHour += 1;
	}
	if (firstHour >=24) {
		firstHour = firstHour - 24;
	}
	string tempVal= to_string(tempFirstMin);
	if (tempFirstMin<10) {
		tempVal = "0" + to_string(tempFirstMin);
	}
	//cout << firstHour << " " << tempFirstMin << endl;
	string tempVar = to_string(firstHour) + ":" + to_string(tempFirstMin);
	//cout << tempVar << endl;
	return tempVar;
}

string MyTimes::newDeliveryTime(string time, string address) {
	//cout << "TT: " << time << endl;
	ifstream readTimes("times.txt");
	readTimes.close();
	readTimes.open("times.txt");
	string line;
	string tempTime;
	while (getline(readTimes, line)) {
		string tempAddres = line.substr(line.find("location:") + 10, line.find("time") - line.find("location") - 11);
		if (address == tempAddres) {
			tempTime = line.substr(line.find("time:") + 6, line.length());
			//cout << tempTime<<endl;
		}

	}
	readTimes.close();
	readTimes.open("times.txt");
	string newTime=calculateTime(time, tempTime);

	return newTime;
}

string MyTimes::getDeliveryTime(string OAddress) {
	ifstream readTimes("times.txt");
	readTimes.close();
	readTimes.open("times.txt");
	string line;
	string tempTime;
	while (getline(readTimes, line)) {
		string tempAddres= line.substr(line.find("location:") + 10, line.find("time")- line.find("location")-11);
		if (OAddress== tempAddres) {
			tempTime = line.substr(line.find("time:") + 6, line.length());
			//cout << tempTime<<endl;
		}
		
	}
	readTimes.close();
	readTimes.open("times.txt");
	string tempCurrentHour = getCurrentHour();
	return calculateTime(tempCurrentHour, tempTime);
}

MyTimes::MyTimes(string hour, string minute) {
	this->hour = hour;
	this->minute = minute;
}

string MyTimes::getHour() {
	return hour;
}

string MyTimes::getMinute() {
	return minute;
}

void MyTimes::setHour(string hour) {
	this->hour = hour;
}

void MyTimes::setMinute(string minute) {
	this->minute = minute;
}

#pragma endregion

#pragma region Order

Order::Order() {

}

void Order::startSimulation() {
	ifstream readOrder("orders.txt");
	 
	readOrder.close();
	readOrder.open("orders.txt");

	int tHour=23, tMin=59;

	string lineOrder;
	//en küçük saat alýndý
	while (getline(readOrder, lineOrder)) {

		string status = lineOrder.substr(lineOrder.find("status:")+8, 
			lineOrder.find("courierNo")- lineOrder.find("status")-9);

		if (status=="online") {
			string tempOrderDelivery = lineOrder.substr(lineOrder.find("orderDelivery:") + 15,
				lineOrder.find("courierStatus") - lineOrder.find("orderDelivery") - 16);
			string tH = tempOrderDelivery.substr(0, tempOrderDelivery.find(":"));
			string tM = tempOrderDelivery.substr(tempOrderDelivery.find(":") + 1, tempOrderDelivery.length());
			int tempHour = stoi(tH.substr(0, 1)) == 0 ? 0 : stoi(tH);
			int tempMin = stoi(tM.substr(0, 1)) == 0 ? stoi(tM.substr(1, 1)) : stoi(tM);
			//cout << "1: " << tempHour << endl;
			//cout << "1: " << tempMin << endl;
			
			if (tempHour < tHour ) {				 		
				tHour = tempHour;
				tMin = tempMin;
			}
			else if (tempHour <= tHour && tempMin <= tMin) {
				tHour = tempHour;
				tMin = tempMin;
			}
			
			//cout << "2: " << tHour << endl;
			//cout << "2: " << tMin << endl;
		}	
		//cout << "2: " << tHour << endl;
		//cout << "2: " << tMin << endl;
		//cout << endl;
	}
	
	readOrder.close();
	readOrder.open("orders.txt");


	//en küçük saatin orderNo'su ve Address'i alýndý
	string tempOrderNo, tempAddress, tempDeliveryTime;
	while (getline(readOrder, lineOrder)) {
		
		string status = lineOrder.substr(lineOrder.find("status:") + 8,
			lineOrder.find("courierNo") - lineOrder.find("status") - 9);
		
		if (status == "online") {
			string tempTime = lineOrder.substr(lineOrder.find("orderDelivery:") + 15,
				lineOrder.find("courierStatus") - lineOrder.find("orderDelivery") - 16);
			string tempMinTime = to_string(tHour) + ":" + to_string(tMin);
			//cout << tempTime << endl;
			//cout << tempMinTime << endl;
			if (tempTime == tempMinTime) {
				tempAddress = lineOrder.substr(lineOrder.find("address:")+9, lineOrder.find("status")- lineOrder.find("address") -10);
				tempOrderNo = lineOrder.substr(lineOrder.find("orderNo:")+9, 
					lineOrder.find("user")- lineOrder.find("orderNo")-10);
				tempDeliveryTime = tempMinTime;
				//cout << lineOrder << endl;
				//cout << tempOrderNo << endl;
			}
		}		
	}
	readOrder.close();
	readOrder.open("orders.txt");

	ofstream tempFile("tempFile3.txt");
	tempFile.open("tempFile3.txt", ios::out | ios::app | ios::in | ios::binary);
	tempFile << "";
	tempFile.close();

	//Courier'ýn yeni delivery time'ý
	string newDeliveryTime;
	if (!tempDeliveryTime.empty()) {
		newDeliveryTime = orderDelivery.newDeliveryTime(tempDeliveryTime, tempAddress);
	}
	else {
		newDeliveryTime = "ok";
	}
		
	//önce bitecek olan orderNo alýndýktan sonra status'u offline olur,	
	string tempCourierNo;
	while (getline(readOrder, lineOrder)) {

		string status = lineOrder.substr(lineOrder.find("status:") + 8,
			lineOrder.find("courierNo") - lineOrder.find("status") - 9);

		string minOrderNo = lineOrder.substr(lineOrder.find("orderNo:") + 9,
			lineOrder.find("user") - lineOrder.find("orderNo") - 10);

		if (status == "online" && tempOrderNo == minOrderNo) {

			string part1 = lineOrder.substr(0, lineOrder.find("status:") + 8);
			string part2 = lineOrder.substr(lineOrder.find("courierNo:"), lineOrder.length());
			tempCourierNo = lineOrder.substr(lineOrder.find("courierNo:") + 11,
				lineOrder.find("location:") - lineOrder.find("courierNo:") - 12);

			lineOrder = part1 + "offline " + part2;
			_getch();
		}
		tempFile.open("tempFile3.txt", ios::out | ios::app | ios::in | ios::binary);
		tempFile << lineOrder + "\n";
		tempFile.close();
	}

	readOrder.close();
	readOrder.open("orders.txt");

	//courier status'u ok olur 
	ifstream readCourier("courier.txt");

	readCourier.close();
	readCourier.open("courier.txt");

	ofstream tempF("tempF3.txt");
	tempF.open("tempF3.txt", ios::out | ios::app | ios::in | ios::binary);
	tempF << "";
	tempF.close();
	string lineCourier;
	while (getline(readCourier, lineCourier)) {
		string tempCNo = lineCourier.substr(lineCourier.find("no:") + 4,
			lineCourier.find("name") - lineCourier.find("no") - 5);

		if (tempCNo == tempCourierNo) {
			string part1 = lineCourier.substr(0, lineCourier.find("status:") + 8);
			//string part2= lineCourier.substr(lineCourier.find("location:"), lineCourier.length());
			//lineCourier = part1 + "ok " + part2;
			lineCourier = part1 + "ok " + "location: " + tempAddress;
			_getch();
		}
		tempF.open("tempF3.txt", ios::out | ios::app | ios::in | ios::binary);
		tempF << lineCourier + "\n";
		tempF.close();

	}
	readCourier.close();
	readCourier.open("courier.txt");

	readOrder.close();
	readCourier.close();

	//courier bir dahakine atlar yani setOrder() çaðrýlarak
	remove("orders.txt");
	rename("tempFile3.txt", "orders.txt");
	remove("courier.txt");
	rename("tempF3.txt", "courier.txt");
	setOrder(newDeliveryTime);
	remove("orders.txt");
	rename("tempFile2.txt", "orders.txt");
	remove("courier.txt");
	rename("tempF2.txt", "courier.txt");
	readOrder.close();
	
}

void Order::setOrder(string deliveryTimeBegin) {

	MyTimes tempTime;
	if (deliveryTimeBegin=="ok") {
		deliveryTimeBegin = tempTime.getCurrentHour();
	}
	ifstream readOrder("orders.txt");

	readOrder.close();
	readOrder.open("orders.txt");

	ifstream readCourier("courier.txt");
	readCourier.close();
	readCourier.open("courier.txt");

	ofstream tempFile("tempFile2.txt");
	tempFile.open("tempFile2.txt", ios::out | ios::app | ios::in | ios::binary);
	tempFile << "";
	tempFile.close();

	ofstream tempF("tempF2.txt");
	tempF.open("tempF2.txt", ios::out | ios::app | ios::in | ios::binary);
	tempF << "";
	tempF.close();



	string lineOrder, lineCourier;

	string tempCno, tempClocation;
	int buffer = 0;

	//courier'a order atanýyor
	while (getline(readCourier, lineCourier)) {
		//cout << lineCourier << endl;
		string Cno = lineCourier.substr(lineCourier.find("no:") + 4, lineCourier.find("name") - lineCourier.find("no") - 5);
		string Cstatus = lineCourier.substr(lineCourier.find("status:") + 8, lineCourier.find("location") - lineCourier.find("status") - 9);
		string Clocation = lineCourier.substr(lineCourier.find("location:") + 10, lineCourier.length());
		string Cname = lineCourier.substr(lineCourier.find("name:") + 6, lineCourier.find("status") - lineCourier.find("name") - 7);
		//cout << "X" + Cno + "X" + Cstatus + "X" + Clocation + "X" + Cname + "X"<<endl;

		if (Cstatus == "ok" && buffer == 0) {
			Cstatus = "busy";
			/*readCourier.close();
			readCourier.open("courier.txt");
			break;*/
			tempCno = Cno;
			tempClocation = Clocation;
			buffer = 1;
			_getch();
		}

		tempF.open("tempF2.txt", ios::out | ios::app | ios::in | ios::binary);
		tempF << "no: " + Cno + " name: " + Cname + " status: " + Cstatus + " location: " + Clocation + "\n";
		tempF.close();

	}
	readCourier.close();
	readCourier.open("courier.txt");

	//courier'a order atandýktan sonra order güncelleniyor
	if (buffer == 1) {

		while (getline(readOrder, lineOrder)) {
			//cout << lineOrder << endl;

			//string Ostatus = lineOrder.substr(lineOrder.find("status:")+8,lineOrder.find("courierNo")- lineOrder.find("status")-9);
			string Ostatus = lineOrder.substr(lineOrder.find("status:") + 8, lineOrder.length());

			string OAddress = lineOrder.substr(lineOrder.find("address:") + 9, lineOrder.find("status:") - lineOrder.find("address:") - 10);

			if (Ostatus == "offline" && buffer == 1) {
				//cout << Ostatus << endl;
				string part1 = lineOrder.substr(0, lineOrder.find("status:") - 1);
				string part2 = part1 + " status: online" + " courierNo: " + tempCno + " location: " + tempClocation +
					" orderBegin: " + deliveryTimeBegin + " orderDelivery: " + orderDelivery.newDeliveryTime(deliveryTimeBegin, OAddress)
					+ " courierStatus: busy";

				lineOrder = part2;
				buffer = 2;
				_getch();
			}

			tempFile.open("tempFile2.txt", ios::out | ios::app | ios::in | ios::binary);
			tempFile << lineOrder + "\n";
			tempFile.close();
			//break;
		}
	}
	else {
		while (getline(readOrder, lineOrder)) {
			tempFile.open("tempFile2.txt", ios::out | ios::app | ios::in | ios::binary);
			tempFile << lineOrder + "\n";
			tempFile.close();
		}
	}

	if (buffer==1) {
		//tempCno
		readCourier.close();
		tempF.close();

		remove("tempF2.txt");
		tempF.open("tempF2.txt", ios::out | ios::app | ios::in | ios::binary);
		tempF << "";
		tempF.close();

		readCourier.open("courier.txt");

		while (getline(readCourier, lineCourier)) {
			//cout << lineCourier << endl;
			string Cno = lineCourier.substr(lineCourier.find("no:") + 4, lineCourier.find("name") - lineCourier.find("no") - 5);
			string Cstatus = lineCourier.substr(lineCourier.find("status:") + 8, lineCourier.find("location") - lineCourier.find("status") - 9);
			string Clocation = lineCourier.substr(lineCourier.find("location:") + 10, lineCourier.length());
			string Cname = lineCourier.substr(lineCourier.find("name:") + 6, lineCourier.find("status") - lineCourier.find("name") - 7);
			//cout << "X" + Cno + "X" + Cstatus + "X" + Clocation + "X" + Cname + "X"<<endl;

			if (Cstatus == "busy" && tempCno==Cno && buffer == 1) {
				Cstatus = "ok";
				 
				buffer = 0;
				_getch();
			}

			tempF.open("tempF2.txt", ios::out | ios::app | ios::in | ios::binary);
			tempF << "no: " + Cno + " name: " + Cname + " status: " + Cstatus + " location: " + Clocation + "\n";
			tempF.close();

		}
		readCourier.close();
	}

	tempFile.close();
	readOrder.close();
	readCourier.close();

	//readCourier.open("courier.txt");
	//readOrder.open("orders.txt");

}

void Order::buyItems(User* user, list<list<string>>* items, Member* member) {
	ifstream readOrders("orders.txt");
	ofstream writeOrders;
	/*writeOrders.open("orders.txt", ios::out | ios::app | ios::in | ios::binary);
	writeOrders << "";
	writeOrders.close();*/
	writeOrders.open("orders.txt", ios::out | ios::app | ios::in | ios::binary);
	string ShipControl;
	cout << "Will you buy? " << endl;
	cout << "Y/N: ";
	cin >> ShipControl;
	cout << endl;

	string line;
	int counter = 1;

	int tempPrice = 0;

	if (ShipControl == "Y") {

		list<list<string>>::iterator myListIt;
		for (myListIt = items->begin(); myListIt != items->end(); ++myListIt) {

			list<string>::iterator single_it;
			list<string>& single_list_pointer = *myListIt;
			//int tempCounter = 0;
			for (single_it = single_list_pointer.begin(); single_it != single_list_pointer.end(); single_it++)
			{
				/*++tempCounter;
				if (tempCounter==1) {
					tempPrice = *single_it;
					cout << tempPrice << endl;
				}*/
				tempPrice += stoi(*single_it);
				//cout << tempPrice << endl;
			}
		}

		readOrders.close();
		readOrders.open("orders.txt");
		for (int i = 0; getline(readOrders, line); i++)
		{
			++counter;
		}
		this->orderNo = counter;
		this->price = tempPrice;
		writeOrders << "orderNo: " + to_string(counter) + " user: " + user->getMail() 
			+ " price: " + to_string(tempPrice) + " address: " + member->getAddress() + " status: " + "offline" + "\n";
		writeOrders.close();
		writeOrders.open("orders.txt", ios::out | ios::app | ios::in | ios::binary);
		
		ofstream writeBill;		
		writeBill.open("bills.txt", ios::out | ios::app | ios::in | ios::binary);
		writeBill << "";
		writeBill.close();
		writeBill.open("bills.txt", ios::out | ios::app | ios::in | ios::binary);
		string orderTime = orderBegin.getCurrentHour();
		writeBill << "name: "+member->getName() + " orderTime: "+ orderTime + 
			" orderNo: " + to_string(counter) + " price: " + to_string(tempPrice) + "\n";
		writeBill.close();
		cout<< "name: " + member->getName() + " orderTime: " + orderTime +
			" orderNo: " + to_string(counter) + " price: " + to_string(tempPrice) + "\n";
		counter = 1;
	}
	readOrders.close();
	//readOrders.open("orders.txt");
	writeOrders.close();
	//writeOrders.open("orders.txt", ios::out | ios::app | ios::in | ios::binary);
	items->clear();

	//setOrder();
}

#pragma endregion

