#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <iosfwd>
#include <ctime>
#include <cmath>

/*
Projeden Ç?kard???m Dersler:
1) Bir static s?n?f nesnesi e?er integral bir type ve const bir ifade ise bildirimde ilk de?er verebiliriz.
Biraz kar???k bir ifade gelebilir bildirimde ilk de?er vermek. Bunu ?öyle yorumlamal?y?z. Bu static data member 
class içinde hala bildirim olarak bulunuyor ama derleyicinin oyunu ile buna ilk de?er verebiliyoruz. 

2) Static s?n?f nesnesi yukar?daki sart? sa?lam?yorsa ve s?n?f içerisinde ilk de?er vermek istiyorsak inline anahtar
kelimesini kullan. ?nline variableler hayat?m?za C++17 ile girmi?tir.

3) If a static data member of LiteralType is declared constexpr, it must be initialized with an initializer in which every expression
is a constant expression, right inside the class definition.If a static data member of integral or enumeration type is declared 
const (and not volatile), it can be initialized with an initializer in which every expression is a constant expression, right inside 
the class definition:  https://en.cppreference.com/w/cpp/language/static



*/

#define isleap(year)	(((year % 4) ? 0 : ((year % 100) ? 1 : ((year % 400) ? 0 : 1))))

enum class Weekday : unsigned int{
	Sunday,
	Monday,
	Tuesday,
	Wednesday,
	Thursday,
	Friday,
	Saturday
};


namespace project {
	class Date {
	private:
		inline static const char* dayStrings[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
		inline static const char* monthStrings[] = {nullptr, "Ocak", "Subat", "Mart", "Nisan", "Mayis", "Haziran",
														"Temmuz", "Agustos", "Eylul", "Ekim", "Kasim", "Aralik"};
		inline static Weekday dayArray[7] = { Weekday::Sunday, Weekday::Monday, Weekday:: Tuesday, Weekday:: Wednesday, 
													Weekday:: Thursday, Weekday:: Friday, Weekday::Saturday };
		static constexpr int dayOfMonths[13] = { 0, 31,28,31,30,31,30,31,31,30,31,30,31 };
		static constexpr int yearBase = 1922;  //1
		int year = yearBase;
		int month = 1;
		int dayOfMonth = 1;
		Weekday day = Weekday::Sunday;
	public:
		Date() = default;
		Date(int d, int m, int y); //++
		Date(const char* p); //7
		Date(std::time_t timer); //8
		int getMonthDay()const; //++
		void printMonthDay()const; //++
		int getMonth()const; //++
		void printMonth()const; //++
		int getYear()const; //++
		void printYear() const; //++
		int getYearDay()const; //++
		void printYearDay()const; //++
		Weekday getWeekDay()const; //++
		void printWeekDay()const; //++
		Date& setMonthDay(int day); //++
		Date& setMonth(int month); //++
		Date& setYear(int year); //++
		Date& set(int day, int mon, int year); //++

		Date operator-(int day)const; //++
		Date& operator+=(int day); //++
		Date& operator-=(int day); //++
		Date& operator++(); //++
		Date operator++(int); //++
		Date& operator--(); //++
		Date operator--(int); //++
		static unsigned int sumOfDay(const Date&);
		inline friend bool operator<(const Date& x, const Date& y) //++
		{
			if (x.year < y.year) {
				return true;
			}
			else if (y.year < x.year) {
				return false;
			}
			else if (x.month < y.month) {
				return true;
			}
			else if (y.month < x.month) {
				return false;
			}
			else if (x.dayOfMonth < y.dayOfMonth) {
				return true;
			}
			return false;
		}
		friend bool operator==(const Date& x, const Date& y) //++
		{
			return ((x.year == y.year) && (x.month == y.month) && (x.dayOfMonth == y.dayOfMonth) ? true : false);
		}

		static constexpr bool isleap_(int y); //++

		friend std::ostream& operator<<(std::ostream& scout, const Date& date) //++
		{
			return scout << date.dayOfMonth << " " << date.monthStrings[date.month] << " " << date.year << "\n";
		}
	};

	bool operator<=(const Date&, const Date&); //++
	bool operator>(const Date&, const Date&); //++
	bool operator>=(const Date&, const Date&); //++
	bool operator!=(const Date&, const Date&); //++

	int operator-(const Date& d1, const Date& d2); //++
	Date operator+(const Date& date, int n); //++
	Date operator+(int n, const Date&); //++
	Weekday& operator++(Weekday&); 
	Weekday operator++(Weekday&, int); 
	Weekday& operator--(Weekday&); 
	Weekday operator--(Weekday&, int); 
}

#endif DATE_H