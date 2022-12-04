#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include "Header.h"
#include <conio.h>
using namespace std;

void setTempInfos(string line, string& mail, string& password, string& role, string& birthday,
	string& tel, string& name, string& address, string& coupon) {
	mail = line.substr(line.find("mail:") + 6, line.find("password") - 7);
	password = line.substr(line.find("password:") + 10, line.find("role") - line.find("password") - 11);
	role = line.substr(line.find("role:") + 6, line.find("birthday") - line.find("role") - 7);
	birthday = line.substr(line.find("birthday:") + 10, line.find("tel") - line.find("birthday") - 11);
	tel = line.substr(line.find("tel:") + 5, line.find("name") - line.find("tel") - 6);
	name = line.substr(line.find("name:") + 6, line.find("address:") - line.find("name") - 7);
	address= line.substr(line.find("address:") + 9, line.find("coupon:") - line.find("address") - 10);
	coupon= line.substr(line.find("coupon:") + 8, line.length());
	//cout << "X" + name + "X" + address + "X" + coupon + "X" << endl;
}

// Enumerator
enum IN {

	// 13 is ASCII for carriage
	// return
	IN_BACK = 8,
	IN_RET = 13

};

string takePasswdFromUser(
	char sp = '*')
{
	// Stores the password
	string passwd = "";
	char ch_ipt;

	// Until condition is true
	while (true) {

		ch_ipt = _getch();

		// if the ch_ipt
		if (ch_ipt == IN::IN_RET) {
			cout << endl;
			return passwd;
		}
		else if (ch_ipt == IN::IN_BACK
			&& passwd.length() != 0) {
			passwd.pop_back();

			// Cout statement is very
			// important as it will erase
			// previously printed character
			cout << "\b \b";

			continue;
		}

		// Without using this, program
		// will crash as \b can't be
		// print in beginning of line
		else if (ch_ipt == IN::IN_BACK
			&& passwd.length() == 0) {
			continue;
		}

		passwd.push_back(ch_ipt);
		cout << sp;
	}
}

void showCart(list<list<string>> myList)
{
	list<list<string>>::iterator myListIt;
	for (myListIt = myList.begin(); myListIt != myList.end(); ++myListIt) {

		list<string>::iterator single_it;
		list<string>& single_list_pointer = *myListIt;

		for (single_it = single_list_pointer.begin(); single_it != single_list_pointer.end(); single_it++)
		{
			//cout << *single_it << " x " << endl;
		}
	}		
}

int main()
{
	/*MyTimes x;
	x.calculateTime("17:50", "100");
	x.getDeliveryTime("arakli");*/
	string line, tempMail, tempPassword, tempRole, tempBirthday, tempTel, tempName; //geçici bilgiler
	int action = 0;

	Manager manager;	

	ifstream readUsers("users.txt");
	ofstream writeUsers;

	string mail, password, role, birthday, tel, name, address, coupon; // member or manager

	srand((unsigned)time(0)); //random için

	list<list<string>> cartItems;
	
	Order order;
	order.setOrder();
	remove("orders.txt");
	rename("tempFile2.txt", "orders.txt");
	remove("courier.txt");
	rename("tempF2.txt", "courier.txt");
	
	/*order.startSimulation();
	remove("orders.txt");
	rename("tempFile3.txt", "orders.txt");
	remove("courier.txt");
	rename("tempF3.txt", "courier.txt");*/

Menu:

	cout << "1) Sign in: " << endl;
	cout << "2) Sign up:" << endl;
	cin >> action;
	cout << endl;

	if (action == 1) {

	MenuInit:

		cout << "1) Manager Login: " << endl;
		cout << "2) Member Login:" << endl;
		cout << "3) Back:" << endl;
		cin >> action;
		cout << endl;

		switch (action)
		{
#pragma region Manager
		case 1:

			cout << "Your mail? ";
			cin >> mail;
			cout << "Your password? " << endl;
			password = takePasswdFromUser();
			cout << endl;

			readUsers.close();
			readUsers.open("users.txt");
			if (readUsers.is_open())
			{
				while (getline(readUsers, line))
				{

					setTempInfos(line, tempMail, tempPassword, tempRole, tempBirthday, tel, name, address, coupon);

					if (mail == tempMail && password == tempPassword && "manager" == tempRole) {

						User user(mail, password, "manager", birthday, tel, name);
						Member member(mail, password, "manager", birthday, tel, name, address, coupon);
						readUsers.close();
						readUsers.open("users.txt");

					MenuManager:

						cout << "1) Add product: " << endl;
						cout << "2) Add courier:" << endl;
						cout << "3) Reading complaints and suggestions:" << endl;
						cout << "4) Create coupon:" << endl;
						cout << "5) See bills:" << endl;
						cout << "6) Back:" << endl;
						cin >> action;
						cout << endl;

						switch (action)
						{

						case 1:

							//Kýyafet kategorilerinin yer aldýðý dosyalara ürün giriþinin yaptýrýlmasý

						MenuItems:
							cout << "1) Add Dress" << endl;
							cout << "2) Add Tshirt" << endl;
							cout << "3) Add Pants" << endl;
							cout << "4) Add Shirt" << endl;
							cout << "5) Add Skirt" << endl;
							cout << "6) Add Shoe" << endl;
							cout << "7) Back" << endl;
							cin >> action;
							cout << endl;

							switch (action)
							{

							case 1:
								manager.addProduct("Dress");
								goto MenuItems;

							case 2:
								manager.addProduct("Tshirt");
								goto MenuItems;

							case 3:
								manager.addProduct("Pants");
								goto MenuItems;

							case 4:
								manager.addProduct("Shirt");
								goto MenuItems;

							case 5:
								manager.addProduct("Skirt");
								goto MenuItems;

							case 6:
								manager.addProduct("Shoe");
								goto MenuItems;

							case 7:
								goto MenuManager;

							default:
								readUsers.close();
								readUsers.open("users.txt");
								goto MenuItems;

							}

						case 2:

							//Sisteme kurye eklenmesi						
							manager.addCourier();
							goto MenuManager;

						case 3:

							//Þikâyet ve öneri okunmasý
							manager.readComments();
							goto MenuManager;

						case 4:

							manager.sendCouponToUser();
							goto MenuManager;

						case 5: //TODO: Yapýlan sipariþlerin faturalarýnýn görüntülemesi

							//Yapýlan sipariþlerin faturalarýnýn görüntülemesi
							break;

						case 6:

							system("CLS");
							user.setMail("");
							user.setPassword("");
							user.setRole("");
							readUsers.close();
							readUsers.open("users.txt");
							goto MenuInit;

						default:
							readUsers.close();
							readUsers.open("users.txt");
							goto MenuManager;

						}
					}
				}
			}
			else {
				cout << "File is close. Try again." << endl;
				readUsers.open("users.txt");
				goto MenuInit;
			}

			readUsers.close();
			readUsers.open("users.txt");
			goto MenuInit;

#pragma endregion

#pragma region Member

		case 2:

			cout << "Your mail? ";
			cin >> mail;
			cout << "Your password? " << endl;
			password = takePasswdFromUser();
			cout << endl;

			readUsers.close();
			readUsers.open("users.txt");
			if (readUsers.is_open())
			{
				while (getline(readUsers, line))
				{

					setTempInfos(line, tempMail, tempPassword, tempRole, tempBirthday, tel, name, address, coupon);

					if (mail == tempMail && password == tempPassword && "member" == tempRole) {

						User user(mail, password, "member", birthday, tel, name);
						Member member(mail, password, "member", birthday, tel, name, address, coupon);
						readUsers.close();
						readUsers.open("users.txt");

					MenuMember:

						cout << "1) Products: " << endl;
						cout << "2) Orders:" << endl;
						cout << "3) Write complaints or suggestions:" << endl;
						cout << "4) Change Password:" << endl;
						cout << "5) Back:" << endl;
						cin >> action;
						cout << endl;

						switch (action)
						{
						case 1:
							//Kýyafet kategorilerinin gösterimi ve ürün seçimi

						ShowItems:
							cout << "1) Dress" << endl;
							cout << "2) Tshirt" << endl;
							cout << "3) Pants" << endl;
							cout << "4) Shirt" << endl;
							cout << "5) Skirt" << endl;
							cout << "6) Shoe" << endl;
							cout << "7) Back" << endl;
							cout << "8) Cart" << endl;							
							cin >> action;
							cout << endl;

							switch (action)
							{

							case 1:	

								member.showProducts("Dress");		
								member.addItemToCart(&cartItems);								
								//cout << cartItems.front().front() << endl;
								//cout << cartItems.front().back() << endl;
								goto ShowItems;

							case 2:
								member.showProducts("Tshirt");
								member.addItemToCart(&cartItems);
								goto ShowItems;

							case 3:
								member.showProducts("Pants");
								member.addItemToCart(&cartItems);
								goto ShowItems;

							case 4:
								member.showProducts("Shirt");
								member.addItemToCart(&cartItems);
								goto ShowItems;

							case 5:
								member.showProducts("Skirt");
								member.addItemToCart(&cartItems);
								goto ShowItems;

							case 6:
								member.showProducts("Shoe");
								member.addItemToCart(&cartItems);
								goto ShowItems;

							case 7:
								goto MenuMember;

							case 8:
								readUsers.close();								
								showCart(cartItems);															
								order.buyItems(&user, &cartItems, &member);
								remove("orders.txt");
								rename("tempFile.txt", "orders.txt");
								remove("courier.txt");
								rename("tempF.txt", "courier.txt");
								readUsers.open("users.txt");
								goto MenuMember;

							default:
								readUsers.close();
								readUsers.open("users.txt");
								goto ShowItems;
							}

						case 2:
							//TODO: Sipariþ Takip
							//Sipariþ Takip

							break;

						case 3:

							//Þikayet/Öneriler(Geri bildirimler)
							member.writeComment(user.getMail());
							goto MenuMember;

						case 4:

							//Þifre Deðiþtir	
							readUsers.close();
							member.changePassword(&user);
							readUsers.open("users.txt");
							goto MenuMember;

						case 5:
							system("CLS");
							user.setMail("");
							user.setPassword("");
							user.setRole("");
							readUsers.close();
							readUsers.open("users.txt");
							goto MenuInit;

						default:
							readUsers.close();
							readUsers.open("users.txt");
							goto MenuMember;
						}
					}
				}

			}
			else {
				cout << "File is close. Try again." << endl;
				readUsers.open("users.txt");
				goto MenuInit;
			}
			readUsers.close();
			readUsers.open("users.txt");
			goto MenuInit;

		case 3:
			goto Menu;

		default:
			readUsers.close();
			readUsers.open("users.txt");
			goto MenuInit;

#pragma endregion

		}


	}

	else if (action == 2) {

		//Sign up
	MailControl:
		cout << "Your mail? ";
		cin >> mail;
		
		if (mail.substr(mail.find("@")+1, mail.length()) != ("gmail.com")) {
			cout << "Mail format error..." << endl;
			goto MailControl;
		}

	PasswordControl:
		cout << "Your password? " << endl;
		password = takePasswdFromUser();
		cout << password << endl;
		if (password.length()<3) {
			cout << "Your password is weak..." << endl;
			goto PasswordControl;
		}

		cout << "Your role? ";
		cin >> role;

	DateControl:
		string tempYear, tempDay, tempMonth;
		cout << "Your birthday's day? " <<endl;
		cin >> tempDay;
		cout << endl;
		cout << "Your birthday's month? " << endl;
		cin >> tempMonth;
		cout << endl;
		cout << "Your birthday's year? " << endl;
		cin >> tempYear;
		cout << endl;		
		if (stoi(tempDay) < 1 || stoi(tempDay) > 31 || stoi(tempMonth) <1 || stoi(tempMonth) >12
			|| stoi(tempYear) > 2015 || stoi(tempYear) < 1900){
			cout << "Date format error..." << endl;
			goto DateControl;
		}
		birthday = tempDay + "/" + tempMonth + "/" + tempYear;

		cout << "Your tel? ";
		cin >> tel;
		cout << "Your name? ";
		cin >> name;
		cout << "Your address? ";
		cin >> address;
		cout << endl;

		writeUsers.open("users.txt", ios::out | ios::app | ios::in | ios::binary);
		writeUsers << "mail: " + mail + " " + "password: " + password + " " + "role: " + role + " " +
			"birthday: " + birthday + " tel: " + tel + " name: " + name + " address: " + address
			+ " coupon: " + coupon + "\n";
		writeUsers.close();

		mail = "";
		password = "";
		role = "";

		system("CLS");
		goto MenuInit;
	}
	else {
		readUsers.close();
		readUsers.open("users.txt");
		goto Menu;
	}

	return 0;
}
