#include "date.h"

using namespace project;
using namespace std;

unsigned int Date::sumOfDay(const Date& x)
{
	unsigned int sum{};
	for (int i = Date::yearBase; i < x.year; ++i) {
		sum += (isleap(i) ? 366 : 365);
	}
	for (int i = 1; i < x.month; ++i) {
		sum += Date::dayOfMonths[i];
	}
	return ((x.month > 2 && isleap (x.year)) ? sum + x.dayOfMonth + 1 : sum + x.dayOfMonth);
}

Date::Date(int d, int m, int y)
		{
			if (!((y < yearBase || y > 2023) || (m < 1 || m > 12) || (d < 1 || d > 31))) {
				if (!(dayOfMonths[m] < d)) {
					int sumOfDay{};
					for (int i = yearBase; i < y; ++i) {
						if (isleap(i))
							sumOfDay += 366;
						else sumOfDay += 365;
					}
					for (int i = 1; i < m; ++i)
						sumOfDay += dayOfMonths[i];
					if (m > 2 && isleap(y))
						sumOfDay += 1;
					sumOfDay += d - 1;
					year = y;
					month = m;
					dayOfMonth = d;
					day = (dayArray[sumOfDay % 7]);
				}
			}
}

int Date::getMonthDay()const { return dayOfMonth; } //++
void Date::printMonthDay()const { cout << dayOfMonth << "\n"; };

int Date::getMonth()const { return month; } //++
void Date::printMonth()const { cout << month << "\n"; }

int Date::getYear()const { return year; } //++
void Date::printYear()const { cout << year << "\n"; }

int Date::getYearDay()const
{
	int result{};
	for (int i = 1; i < month; ++i)
		result += dayOfMonths[i];
	return ((month > 2 && isleap(year)) ? result + dayOfMonth + 1 : result + dayOfMonth);
}

void Date::printYearDay()const
{
	int sum{};
	for (int i = 1; i < month; ++i)
		sum += dayOfMonths[i];
	sum += dayOfMonth;
	if (month > 2)
		sum += isleap(year) ? 1 : 0;
	cout << sum;
}

Weekday Date::getWeekDay()const
{
	return day;
}

void Date::printWeekDay()const
{
	cout << dayStrings[(int)this->day];
}

Date& Date::setMonthDay(int day)
{
	dayOfMonth = day;
	return *this;
}

Date& Date::setMonth(int month)
{
	this->month = month;
	return *this;
}

Date& Date::setYear(int year)
{
	this->year = year;
	return *this;
}

Date& Date::set(int d, int m, int y)
{
	if (!((y < yearBase || y > 2023) || (m < 1 || m > 12) || (d < 1 || d > 31))) {
		if (!(dayOfMonths[m] < d)) {
			int sumOfDay{};
			for (int i = yearBase; i < y; ++i) {
				if (isleap(i))
					sumOfDay += 366;
				else sumOfDay += 365;
			}
			for (int i = 1; i < m; ++i)
				sumOfDay += dayOfMonths[i];
			if (m > 2 && isleap(y))
				sumOfDay += 1;
			sumOfDay += d - 1;
			year = y;
			month = m;
			dayOfMonth = d;
			day = (dayArray[sumOfDay % 7]);
		}
	}
	return *this;
}

Date Date::operator-(int day)const
{
	if (day < 1)
		return *this;
	Date temp{ *this };
	int newDay = temp.getYearDay() - day;
	if (newDay > 0)
	{
		int x = 0;
		for(int i = 1; i <= temp.month; ++i)
		{
			x += temp.dayOfMonths[i];
			if (i == 2 && isleap(temp.year))
				++x;
			if (x >= newDay) {
				temp.month = i;
				temp.dayOfMonth = newDay - (x - temp.dayOfMonths[i]);
				if (temp.month == 2 && isleap(temp.year))
					++temp.dayOfMonth;
				break;
			}
		}
	}
	else {
		newDay = -newDay;
		--temp.year;
		while (newDay > 365) {
			--temp.year;
			if (temp.year < 1922) {
				return Date{};
			}
			newDay -= isleap(temp.year) ? 366 : 365;
		}
		int hand = newDay % (isleap(temp.year) ? 366 : 365);
		int x = 0;
		for (int i = 12; i > 0; --i) {
			x += temp.dayOfMonths[i];
			if (i == 2 && isleap(temp.year))
				++x;
			if (x >= hand) {
				temp.month = i;
				temp.dayOfMonth = temp.dayOfMonths[i] - (hand - (x - temp.dayOfMonths[i]));
				break;
				}
			}	
	}
	int dayTemp = (int)temp.day - (day % 7);
	if (dayTemp < 0)
		temp.day = Date::dayArray[7 + dayTemp]; 
	else
		temp.day = Date::dayArray[dayTemp];
	return temp;
}

Date& Date::operator+=(int day)
{
	if (day < 1)
		return *this;
	int newDay = getYearDay() + day;
	if (newDay <= (isleap(year) ? 366 : 365)) {
		int sum{ (getYearDay() - dayOfMonth)};
		if (newDay > sum) {
			for (int i = month; i < 13; ++i) {
				sum += dayOfMonths[i];
				month = i;
				if (i == 2 && isleap(year))
					++sum;
				if (newDay <= sum) {
					dayOfMonth = newDay - (sum - dayOfMonths[i]);
					if (month == 2 && isleap(year))
						++dayOfMonth;
					break;
				}

			}
		}
	}
	else {
		newDay -= (isleap(year) ? 366 : 365);
		++year;
		while(newDay > (isleap(year) ? 366 : 365)){
			++year;
			newDay -= (isleap(year) ? 366 : 365);
			if (year > 2023) {
				year = 2023;
				month = 12;
				dayOfMonth = 31;
				this->day = Weekday::Saturday;
				return *this;
			}
		}
		int sum{};
		for (int i = 1; i < 13; ++i) {
			if (newDay == sum) {
				dayOfMonth = dayOfMonths[i - 1];
				break;
			}
			sum += dayOfMonths[i];
			month = i;
			if (i == 2 && isleap(year))
				++sum;
			if (newDay < sum) {
				dayOfMonth = newDay - (sum - dayOfMonths[i]);
				break;
			}
		}
	}
	int dayTemp = (int)Date::day + (day % 7);
	if (dayTemp > 6)
		Date::day = Date::dayArray[dayTemp - 7];
	else
		Date::day = Date::dayArray[dayTemp];
	return *this;
}

Date& Date::operator-=(int day)
{
	return *this = (*this) - day;
}

Date& Date::operator++()
{
	return (*this) += 1;
}

Date Date::operator++(int)
{
	Date temp = *this;
	++(*this);
	return temp;
}

Date& Date::operator--()
{
	return (*this) -= 1;
}

Date Date::operator--(int)
{
	Date  temp = *this;
	--(*this);
	return temp;
}

bool project::operator<=(const Date& x, const Date& y)
{
	return ((x < y) || (x == y));
}

bool project::operator>=(const Date& x, const Date& y)
{
	return !(x <= y);
}

bool project::operator>(const Date& x, const Date& y)
{
	return !(x < y);
}

bool project::operator!=(const Date& x, const Date& y)
{
	return !(x == y);
}

constexpr bool Date::isleap_(int y)
{
	return isleap(y);
}

int project::operator-(const Date& d1, const Date& d2)
{
	return Date::sumOfDay(d1) - Date::sumOfDay(d2);
}

Date project::operator+(const Date& date, int n)
{
	Date temp{ date };
	return temp += n;
}

Date project::operator+(int n, const Date& date)
{
	Date temp{ date };
	return temp += n;
}

Weekday& project::operator++(Weekday& x)
{
	return x = (Weekday)((int)(++x) % 7);
} 

Weekday project::operator++(Weekday& x, int y)
{
	Weekday temp = x;
	return (++temp);
}

