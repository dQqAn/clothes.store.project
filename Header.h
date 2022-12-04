#pragma once
#include <iostream>
#include <list>
using namespace std;

#pragma region User
class User {

public:
	User(string mail, string password, string role, string birthday, string tel, string name);
	string getMail();
	string getPassword();
	string getRole();
	string getBirthday();
	string getTel();
	string getName();

	void setMail(string);
	void setPassword(string);
	void setRole(string);
	void setBirthday(string);
	void setTel(string);
	void setName(string);

private:
	string mail;	
	string password;
	string role;
	string birthday;
	string tel;
	string name;
};

class Manager {

public:
	Manager();
	void addProduct(string pCategory);
	void addCourier();
	void readComments();
	void sendCouponToUser();
	void showBills();

private:

};

#pragma region Time

class MyTimes {
public:
	MyTimes();
	MyTimes(string hour, string minute);

	string getHour();
	string getMinute();
	string getCurrentHour();
	string getDeliveryTime(string OAddress);

	void setHour(string);
	void setMinute(string);

	string calculateTime(string first, string second);
	
private:
	string hour;
	string minute;
};

#pragma endregion

class Member:public User{

public:
	Member(string mail, string password, string role, string birthday, string tel, string name, string adress, string coupon);
	void showProducts(string pName);
	void showOrders();
	void writeComment(string mail);
	void changePassword(User *user);
	void addItemToCart(list<list<string>> *items);
	
	string getCoupon();
	string getAddress();

	void setAddress(string);

private:
	string coupon;
	string address;	
};

class Courier: public User{
	
public:
	Courier(string mail, string password, string role, string birthday, 
		string tel, string name, list<string> orderNumbers);
	
	list<string> getOrderNumbers();
	
	void addOrderNumbers(string orderNumber);

	string getLocation();

	void setLocation(string location);

	

	void setStatus(string status);
private:
	list<string> deliveryTimes;
	MyTimes TdeliveryTimes;

	list<string> orderNumbers;	

	string location;
	string status;
};

#pragma endregion

#pragma region Clothes

class Clothe {
public:
	Clothe(string category, string name, string price, string size, string color);

	string getCategory();
	string getName();
	string getPrice();
	string getSize();
	string getColor();

	void setCategory(string);
	void setName(string);
	void setPrice(string);
	void setSize(string);
	void setColor(string);
private:
	string category;
	string name;
	string price;
	string size;
	string color;
};

#pragma endregion

#pragma region Order

class Order {
public:
	Order();
	void buyItems(User* user, list<list<string>>* items, Member* member);
	void setOrder();

	void startSimulation();
private:
	int orderNo=0;
	int price=0;
	MyTimes orderBegin;
	MyTimes orderDelivery;
};

#pragma endregion

#pragma region Comments
class Comments {
public:
	Comments(string commentNo, string comment);
	void setCommentNo(string);
	string getCommentNo();

	void setComment(string);
	string getComment();

private:
	string comment; //yorum içeriði
	string commentNo; // yorum id
};

class CommentProduct: public Comments {
public:
	CommentProduct(string, string, string);

	void setProductNo(string);
	string getProductNo();

private:
	string productNo; // ürün id
};

class CommentPropasal : public Comments {
public:
	CommentPropasal(string, string, string);

	void setProposalNo(string);
	string getProposalNo();

private:
	string proposalNo; //öneri id
};
#pragma endregion

