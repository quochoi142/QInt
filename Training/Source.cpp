#include<iostream>
#include<stdio.h>
#include<string>
#include<list>
using namespace std;
struct QInt {
	int data[4];

	QInt()
	{
		for (int i = 0; i < 4; i++)
		{
			data[i] = 0;
		}
	}
	QInt operator|(const QInt& a)
	{
		QInt result;
		for (int i = 0; i < 4; i++)
			result.data[i] = this->data[i] | a.data[i];
		return result;
	}

	QInt operator&(const QInt& a)
	{
		QInt result;
		for (int i = 0; i < 4; i++)
			result.data[i] = this->data[i] & a.data[i];
		return result;
	}

	QInt operator^(const QInt& a)
	{
		QInt result;
		for (int i = 0; i < 4; i++)
			result.data[i] = this->data[i] ^ a.data[i];
		return result;
	}

	QInt operator~()
	{
		QInt result;
		for (int i = 0; i < 4; i++)
			result.data[i] = ~(this->data[i]);
		return result;
	}


	QInt operator<<(const unsigned int & amount)
	{
		QInt result;
		if (amount >= 128) return result;
		unsigned int pos = amount / 32;
		unsigned int left = amount % 32;
		unsigned int right = 32 - left;
		unsigned int count = 0;
		unsigned int temp;

		result.data[count] = result.data[count] | (data[pos] << left);
		pos++;
		for (int i = pos; i < 4; i++)
		{
			temp = data[i];
			result.data[count] = result.data[count] | (temp >> right);
			count++;
			result.data[count] = result.data[count] | (data[i] << left);
		}

		return result;
	}


	/*QInt operator>>(const unsigned int & amount)
	{
		QInt result;
		unsigned int pos = 3 - (amount / 32);
		unsigned int right = amount % 32;
		unsigned int left = 32 - right;
		unsigned int count = 3;
		if (data[0] >> 31 & 1 == 1)
		{
			int temp;
			result = ~result;
			if (amount >= 128) return result;
			result.data[count] = result.data[count] & (data[pos] >> right);
			pos--;
			temp = result.data[count];
			int i ;
			for ( i = pos; i >= 0; i--)
			{
				result.data[count] = result.data[count] & (data[i] << left);
				result.data[count] = result.data[count] | temp;
				count--;
				result.data[count] = result.data[count] & (data[i] >> right);
				temp = result.data[count];
			}
		}



		else
		{
			if (amount >= 128) return result;
			result.data[count] = result.data[count] | (data[pos] >> right);
			pos--;
			for (int i = pos; i >= 0; i--)
			{
				result.data[count] = result.data[count] | (data[i] << left);
				count--;
				result.data[count] = result.data[count] | (data[i] >> right);
			}
		}
		return result;
	}*/


	QInt operator>>(const unsigned int & amount)
	{
		QInt result;

		if (amount >= 128) {
			if (data[0] >> 32 & 1 == 1)return ~result;
			return result;

		}
		unsigned int pos = 3 - (amount / 32);
		unsigned int right = amount % 32;
		unsigned int left = 32 - right;
		unsigned int count = 3;
		unsigned int temp;
		temp = data[pos];
		result.data[count] = result.data[count] | (temp >> right);
		pos--;
		for (int i = pos; i >= 0; i--)
		{
			result.data[count] = result.data[count] | (data[i] << left);
			count--;
			temp = data[i];
			result.data[count] = result.data[count] | (temp >> right);
		}
		if (data[0] >> 31 & 1 == 1) {
			result.data[count] = (result.data[count]) | ((-1) << left);
			count--;
			for (int i = count; i >= 0; i--)
				result.data[i] = ~result.data[i];
		}
		return result;
	}

};

string devide_By_2(const string &src) {
	string result;
	int i = 0;//vi tri chia mac dinh
	if (src[0] == '-') {// Neu la so bi chia la so am
		result.push_back('-');//them ki tu dau tru vao
		i = 1;//vi tri chia se bat dau =1
	}
	if (src.length() == i + 1 && src[src.length() - 1] - '0' < 2)//kiem tra so bi chia co nho hon so chia khong
	{
		result.push_back('0');// co thi bang 0 sau do thoat
		return result;
	}
	int minus = 0;// so nho tam de tru
	while (!(i == src.length() && src[i] - '0' < 2))// trog khi van chia duoc
	{
		//chia tu nhien giong chia tay 
		minus = minus * 10 + (src[i] - '0');
		if (!((result.length() == 1 && result[result.length() - 1] == '-' || result.length() == 0) && minus / 2 == 0))
			result.push_back((minus / 2) + '0');
		minus -= minus / 2 * 2;
		i++;
	}

	return result;
}


string devide_By(const string &src, int x) {
	string result;
	int i = 0;
	if (src[0] == '-') {
		result.push_back('-');
		i = 1;
	}
	if (src.length() == i + 1 && src[src.length() - 1] - '0' < x)
	{
		result.push_back('0');
		return result;
	}
	int minus = 0;
	while (!(i == src.length() && src[i] - '0' < x))
	{

		minus = minus * 10 + (src[i] - '0');
		if (!((result.length() == 1 && result[result.length() - 1] == '-' || result.length() == 0) && minus / x == 0))
			result.push_back((minus / x) + '0');
		minus -= minus / x * x;
		i++;
	}

	return result;
}

void ScanQInt(QInt& result)
{
	int pivot = 0;
	string dest;
	cin >> dest;
	bool negative = 0;
	if (dest[0] == '-') {//kiểm tra số âm
		pivot = 1;// đánh dấu mốc
		negative = 1;// đánh dấu là số âm
	}
	int temp;
	int i = 0;
	int pos = 3;
	while (dest.length() > pivot + 1 || dest[pivot] - '0' > 0)
	{
		if (i == 32) {// vị trí điền bit
			i = 0;
			pos--;
			if (pos < 0) return;
		}
		temp = (dest.length() == pivot + 1 && dest[pivot] - '0' < 2) ? dest[pivot] - '0' : (dest[dest.length() - 1] - '0') % 2;//lấy bit

		if (temp == 1)
			result.data[pos] = result.data[pos] | (temp << i);//điền bit

		i++;
		dest = devide_By_2(dest);//chia 2 tiếp tục
	}
	if (negative) {//nếu là số âm thì đổi qua dạng bù 2
		for (int i = 0; i < 4; i++)
			result.data[i] = ~(result.data[i]);// đổi bit
		temp = 1;
		i = 3;
		while (i >= 0)// cộng 1
		{
			if (temp == 0) break;
			result.data[i] += temp;
			temp = (result.data[i] == 0) ? 1 : 0;
			i--;
		}
	}
}


bool* DecToBin(const QInt &src)
{
	int i = 0;
	int pos = 3;;
	bool* result = new bool[128];
	while (pos >= 0)
	{
		if (i == 32)
		{// neu doc het bit trong 1 data thi chuyen qua data khac
			i = 0;
			pos--;
			if (pos < 0)  return result;// neu het data thi tra ve gia tri
		}

		result[(pos * 32) + 32 - i - 1] = (src.data[pos] >> i & 1 == 1) ? 1 : 0;// kiem trai bit 0 hay 1 de dien vao mang bool
		i++;

	}

}





string addition(const string& a, const string &b)
{
	list<char> result;
	int lengA = a.length() - 1;
	int lengB = b.length() - 1;
	int temp = 0;
	int resultTemp;
	while (lengA >= 0 && lengB >= 0)
	{
		resultTemp = a[lengA--] + b[lengB--] + temp - 2 * '0';
		temp = resultTemp / 10;
		result.push_front(resultTemp % 10 + '0');
	}
	if (lengA < 0) {
		for (int i = lengB; i >= 0; i--)
		{
			result.push_front((b[i] - '0' + temp) % 10 + '0');
			temp = (b[i] - '0' + temp) / 10;
		}
	}
	else {
		for (int i = lengA; i >= 0; i--)
		{
			result.push_front((a[i] - '0' + temp) % 10 + '0');
			temp = (a[i] - '0' + temp) / 10;
		}
	}
	if (temp != 0) result.push_front(temp + '0');
	string str(result.begin(), result.end());
	return str;
}


string subtraction(const string& a, const string& b)
{

	int lengA = a.length() - 1;
	int lengB = b.length() - 1;
	if (lengA < lengB || (lengA == lengB && a < b)) {
		string result = "-" + subtraction(b, a);
		return result;
	}
	else {
		list<char> result;
		int temp = 0;
		int resultTemp;
		while (lengB >= 0)
		{
			resultTemp = (a[lengA] >= b[lengB] + temp) ? a[lengA] - b[lengB] - temp : (a[lengA] + 10) - (b[lengB] + temp);
			temp = (a[lengA] >= b[lengB] + temp) ? 0 : 1;
			lengA--;
			lengB--;

			result.push_front(resultTemp + '0');
		}
		for (int i = lengA; i >= 0; i--)
		{
			if (a[i] >= temp) {
				result.push_front((a[i] - temp));
				temp = 0;
			}
			else{
				result.push_front((10+a[i] - temp));
				temp = 1;
			}
			
		}
		while (result.front() == '0') {
			result.pop_front();
		}

		string str(result.begin(), result.end());
		return str;
	}
}


string multiplied_by_2(const string& a)
{
	//if (a[0] == '0'&&a.length() == 1) return "0";
	list<char> result;
	int lengA = a.length() - 1;
	int temp = 0;
	int resultTemp;
	for (int i = lengA; i >= 0; i--)
	{
		resultTemp = 2 * (a[i] - '0') + temp;
		temp = resultTemp / 10;
		result.push_front(resultTemp % 10 + '0');
	}
	if (temp != 0)
		result.push_front(temp + '0');
	string str(result.begin(), result.end());
	return str;
}


string _2exp(int exp)
{
	if (exp == 0) return "1";
	return multiplied_by_2(_2exp(exp - 1));
}

string QIntToString(const QInt& a)
{
	string result;
	int i = 0;
	int pos = 3;
	//int temp;
	int count = 0;
	unsigned int temp;
	while (pos >= 0) {
		temp = a.data[pos];
		if (pos == 0 && i == 31)
		{
			temp = temp >> (i) & 1;
			if (temp == 1)
				return subtraction(result, _2exp(127));
			return result;
		}
		if (i == 32)
		{
			i = 0;
			pos--;
		}
		temp = a.data[pos];
		temp = temp >> (i) & (1);
		if (temp == 1) {
			result = addition(result, _2exp(count));
		}
		count++;
		i++;
	}
}


int main()
{
	//int x = 500;
	//char a[4] = { 0 };
	//char temp;
	//int i = 0;
	//int pos = 3;
	//while (x > 0)
	//{

	//	if (i == 8) {
	//		i = 0;
	//		pos--;
	//	}
	//	temp = (x < 2) ? x : x % 2;
	//	if (temp == 1)
	//		a[pos] = a[pos] | (temp << i);
	//	i++;
	//	x = x / 2;
	//}


	QInt q;
	ScanQInt(q);
	bool* arr = DecToBin(q);
	for (int i = 0; i < 128; i++)
	{
		if (i % 8 == 0 && i != 0) cout << " ";
		if (i % 32 == 0 && i != 0) cout << endl;
		cout << arr[i];
	}
	cout << endl;
	cout << QIntToString(q);

	delete[]arr;
	cout << endl;



	/*string a, b;
	cin >> a >> b;
	cout <<	subtraction(a, b);*/




	system("pause");
	return 0;
}

// vd test github
